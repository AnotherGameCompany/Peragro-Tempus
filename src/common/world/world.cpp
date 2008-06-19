/*
    Copyright (C) 2005 Development Team of Peragro Tempus

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "world.h"

#include <iengine/rview.h>
#include <iengine/camera.h>
#include <csgeom/transfrm.h>

#include "maptile.h"
#include "modelmanager.h"
#include "interiormanager.h"

#include "common/reporter/reporter.h"
#include "common/pointer/ipointer.h"
#include "common/event/eventmanager.h"
#include "common/event/regionevent.h"

namespace PT
{
  namespace World
  {
    World::World(const char* name, iPointerLibrary* pl)
      : pointerLibrary(pl), basename(name)
    {
      loading = false;
      camera.Set(0.0f);
      maptilecachesize = 0;
      maptilecache = 0;
      current_size = 0;
      current = 0;
      // Set to a very big number, so if they are changed to "0,0"
      // it can be detected.
      cx = cz = INT_MAX;

      Report(PT::Notify, "Loading world %s", basename.c_str());

      object_reg = pointerLibrary->getObjectRegistry();
      if (!object_reg) Report(PT::Error, "Failed to locate Object Registry!");

      csRef<iLoader> loader = csQueryRegistry<iLoader> (object_reg);
      if (!loader) Report(PT::Error, "Failed to locate Loader!");
      csRef<iVFS> vfs = csQueryRegistry<iVFS> (object_reg);
      if (!vfs) Report(PT::Error, "Failed to locate VFS!");

      vfs->ChDir("/peragro/art/world/");
      loader->LoadMapFile("world", false);

      modelManager = new ModelManager(object_reg);
      interiorManager = new InteriorManager(this);

      // Init map tilechache.
      SetCacheSize(16); // default 16

      // Init current.
      SetGridSize(3); // default 3x3
    } // end World() :P

    World::~World()
    {
      Report(PT::Notify, "Unloading world %s", basename.c_str());

      // Remove callback.
      if (cb.IsValid())
      {
        csRef<iEngine> engine = csQueryRegistry<iEngine> (object_reg);
        engine->RemoveEngineFrameCallback(cb);
      }

      // Delete the cache array AND it's elements.
      if (maptilecache != 0)
      {
        for (int i=0; i< GetCacheSize(); i++)
        {
          if (maptilecache[i] != 0) delete maptilecache[i];
        }
        delete [] maptilecache;
      }

      // Delete the grid array.
      if (current != 0)
      {
        for (int i = 0; i < GetGridSize(); i++)
        {
          delete [] current[i];
        }
        delete [] current;
      }

      // Delete the model manager.
      delete modelManager;

      // Delete the interior manager.
      delete interiorManager;
    } // end ~World()

    void World::SetGridSize(int size)
    {
      // Sanity check.
      // We don't support smaller than 3!
      if (size < 3) size = 3;

      // Sanity check.
      // The cache should always be bigger then size^2
      int gridSizeSqr = size * size;
      if (GetCacheSize() < gridSizeSqr) SetCacheSize(gridSizeSqr + size);

      // Init a new grid array.
      MapTile*** newGrid = new MapTile**[size];
      for (int j = 0; j < size; j++)
      {
        newGrid[j] = new MapTile*[size];
        for (int i = 0; i < size; i++)
        {
          newGrid[j][i] = 0;
        }
      }

      if (current != 0)
      {
        // Copy.
        int min = std::min(size, GetGridSize());
        int oldCenter = (GetGridSize() - 1) / 2;
        int newCenter = (size - 1) / 2;
        int offset = (min - 1) / 2;
        int oldIdx = oldCenter-offset;
        int newIdx = newCenter-offset;
        for (int j = 0; j < min; j++)
        {
          for (int i = 0; i < min; i++)
          {
            newGrid[newIdx+i][newIdx+j] = current[oldIdx+i][oldIdx+j];
          }
        }

        // Remains are taken care of by the cache.

        // Delete the old array.
        for (int i = 0; i < GetGridSize(); i++)
        {
          delete [] current[i];
        }
        delete [] current;
      }

      bool load = (current != 0); // If it's an init, don't load any tiles.
      current_size = size;
      current = newGrid;
      if (load) EnterTile(cx, cz); // Load new surrounding tiles.
    } // end SetGridSize()

    int World::GetGridSize() const
    {
      return current_size;
    } // end GetGridSize()

    void World::SetCacheSize(int size)
    {
      // Sanity check.
      int gridSizeSqr = GetGridSize() * GetGridSize();
      if (size < gridSizeSqr) size = gridSizeSqr + GetGridSize();

      // Init a new cache array.
      MapTile** newCache = new MapTile*[size];
      for (int i = 0; i < size; i++){ newCache[i] = 0;}

      if (maptilecache != 0)
      {
        // Sort from closest to furthest.
        MapTile* temp;
        for(int j = 0; j < GetCacheSize()-1; j++)
        {
          for(int i = 1; i < GetCacheSize()-j; i++)
          {
            unsigned int score_i_1 = ~0; // Very big number.
            unsigned int score_i = ~0;
            if (maptilecache[i-1] != 0)
            {
              score_i_1 = abs(maptilecache[i-1]->x - cx) +
                abs(maptilecache[i-1]->z - cz);
            }
            if (maptilecache[i] != 0)
            {
              score_i = abs(maptilecache[i]->x - cx) +
                abs(maptilecache[i]->z - cz);
            }
            // If score is bigger: swap.
            if (score_i_1 > score_i)
            {
              temp = maptilecache[i];
              maptilecache[i]   = maptilecache[i-1];
              maptilecache[i-1] = temp;
            }
          }
        }

        // Copy.
        for (int i = 0; i < std::min(size, GetCacheSize()); i++)
        {
          newCache[i] = maptilecache[i];
        }

        // Delete any remains: the ones that are the furthest.
        for (int i = size; i < GetCacheSize(); i++)
        {
          if (maptilecache[i] != 0) delete maptilecache[i];
        }

        // Delete the old array.
        delete [] maptilecache;
      }

      maptilecachesize = size;
      maptilecache = newCache;
    } // end SetCacheSize()

    int World::GetCacheSize() const
    {
      return maptilecachesize;
    } // end GetCacheSize()

    void World::EnterTile(int x, int z)
    {
      // Hide everything.
      if (maptilecache != 0)
      {
        for (int i = 0 ; i < maptilecachesize; i++)
        {
          if (maptilecache[i] != 0) maptilecache[i]->SetVisible(false);
        }
      }

      // Update our position.
      cx = x;
      cz = z;

      // Load the surrounding tiles.
      int offset = (GetGridSize() - 1) / 2;
      for (int j = 0; j < GetGridSize(); j++)
      {
        for (int i = 0; i < GetGridSize(); i++)
        {
          current[j][i] = LoadTile(x-offset+i, z-offset+j);
          current[j][i]->SetVisible(true);
        }
      }
    } // end EnterTile()

    MapTile* World::LoadTile(int x, int z)
    {
      int firstnull = maptilecachesize;
      for (int i = 0; i < maptilecachesize; i++)
      {
        if ((maptilecache[i] != 0) && (maptilecache[i]->x == x) &&
          (maptilecache[i]->z == z))
        {
          return maptilecache[i];
        }
        if (maptilecache[i] == 0 && i < firstnull) firstnull = i;
      }

      // We need to find a place in the cache.
      if (firstnull == maptilecachesize)
      {
        int score, maxscore = 0, maxidx = 0;
        // Oh shit! we need to throw away a tile!
        for (int i = 0; i < maptilecachesize; i++)
        {
          score = abs(maptilecache[i]->x - cx) + abs(maptilecache[i]->z - cz);
          if (score > maxscore)
          {
            maxscore = score;
            maxidx = i;
          }
        }

        // maxidx is the winner. (loser)
        delete maptilecache[maxidx];
        firstnull = maxidx;
      }

      char name[256];
      snprintf(name, 256, "tile-%d-%d", x, z);

      maptilecache[firstnull] = new MapTile(x,z,name, this);
      return maptilecache[firstnull];
    } // end LoadTile()

    void World::Tick(float dt)
    {
      if (loading)
      {
        bool allLoaded = true;
        float tilesLoaded = 0.0f;
        for (int j = 0; j < GetGridSize(); j++)
        {
          for (int i = 0; i < GetGridSize(); i++)
          {
            if ( (current[j][i] == 0) || !current[j][i]->IsReady() )
              allLoaded = false;
            else
              tilesLoaded += 1;
          }
        }
        if (!interiorManager->IsReady())
          allLoaded = false;

        PT::Events::EventManager* evmgr = pointerLibrary->getEventManager();
        csRef<iEvent> worldEvent = evmgr->CreateEvent("world.loading");
        worldEvent->Add("progress",
          tilesLoaded/static_cast<float>(GetGridSize()*GetGridSize()));
        evmgr->AddEvent(worldEvent);

        if (allLoaded)
        {
          Report(PT::Notify, "World loaded!");
          csRef<iEvent> worldEvent = evmgr->CreateEvent("world.loaded");
          evmgr->AddEvent(worldEvent);
          loading = false;
        }

        return;
      }

      int p = (GetGridSize() - 1) / 2;
      if (current[p][p] != 0)
      {
        // If we're out of bounds of our center tile, we're entering a new tile.
        if ((camera.x < current[p][p]->xbase) ||
            (camera.x > (current[p][p]->xbase+TILESIZE)) ||
            (camera.z < current[p][p]->zbase) ||
            (camera.z > (current[p][p]->zbase+TILESIZE)))
        {
          if (camera.x < 0)
          {
            camera.x -= TILESIZE;
          }
          if (camera.z < 0)
          {
            camera.z -= TILESIZE;
          }

          int ex,ez;
          ex = (int)(camera.x / TILESIZE);
          ez = (int)(camera.z / TILESIZE);

          EnterTile(ex,ez);
          Report(PT::Debug, "EnterTile (%d,%d) (%f, %f)",
            ex, ez, camera.x, camera.z);
        }
      }
    } // end Tick()

    void World::FrameCallBack::StartFrame(iEngine* engine, iRenderView* rview)
    {
      if (!world)
      {
        engine->RemoveEngineFrameCallback(this);
        return;
      }

      iCamera* cam = rview->GetCamera();
      if (cam)
        world->camera = cam->GetTransform().GetOrigin();

      world->Tick(0);

    } // end StartFrame()

    void World::EnterWorld(float x, float z)
    {
      camera.x = x;
      camera.z = z;

      // This is so the int cast below rounds to the correct value.
      if (x < 0)
      {
        x -= TILESIZE;
      }
      if (z < 0)
      {
        z -= TILESIZE;
      }

      int ex, ez;
      ex = static_cast<int>(x / TILESIZE);
      ez = static_cast<int>(z / TILESIZE);

      if (ex != cx || ez != cz)
      {
        Report(PT::Notify, "World loading...");

        PT::Events::EventManager* evmgr = pointerLibrary->getEventManager();
        csRef<iEvent> worldEvent = evmgr->CreateEvent("world.loading");
        worldEvent->Add("progress", 0.0f);
        evmgr->AddEvent(worldEvent);

        loading = true;
      }

      EnterTile(ex, ez);

      // Register a callback for the camera coordinates.
      csRef<iEngine> engine = csQueryRegistry<iEngine> (object_reg);
      if (!cb.IsValid())
      {
        cb.AttachNew(new FrameCallBack(this));
        engine->AddEngineFrameCallback(cb);
      }

    } // end StartFrame()

  } // World namespace
} // PT namespace
