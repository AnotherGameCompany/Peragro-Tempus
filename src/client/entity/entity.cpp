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

#include "entity.h"

#include <iengine/mesh.h>

#include <iutil/objreg.h>
#include <iengine/engine.h>
#include <iengine/movable.h>
#include <iengine/sector.h>

#include <physicallayer/pl.h>
#include <physicallayer/propfact.h>
#include <physicallayer/propclas.h>
#include <propclass/mesh.h>
#include <propclass/linmove.h>
#include <propclass/prop.h>

#include "common/reporter/reporter.h"

#include "client/pointer/pointer.h"
#include "common/event/eventmanager.h"
#include "common/event/entityevent.h"
#include "common/event/regionevent.h"
#include "client/data/sector/sectordatamanager.h"
#include "client/data/sector/sector.h"

#include "client/component/componentmanager.h"
#include "include/client/component/entity/stat/stats.h"

namespace PT
{
  namespace Entity
  {
    Entity::Entity(const iEvent& ev)
    {
      id = PT::Events::EntityHelper::GetEntityID(&ev);
      type = (Common::Entity::EntityType)PT::Events::EntityHelper::GetEntityType(&ev);
      name = PT::Events::EntityHelper::GetString(&ev, "entityName");
      meshName = PT::Events::EntityHelper::GetString(&ev, "meshName");
      fileName = PT::Events::EntityHelper::GetString(&ev, "fileName");
      position = PT::Events::EntityHelper::GetPosition(&ev);
      ev.Retrieve("rotation", rot);

      unsigned int sectorId = PT::Events::EntityHelper::GetSectorId(&ev);
      PT::Data::Sector* sector = PointerLibrary::getInstance()->
        getSectorDataManager()->GetSectorById(sectorId);
      if (sector)
      {
        sectorName = sector->GetName();
      }
      else
      {
        sectorName = "Default_Sector";
        Report(PT::Error, "Unknown sectorID: %u!", sectorId);
      }

      PT::Component::ComponentManager* componentManager =
        PointerLibrary::getInstance()->getComponentManager();

      ADD_COMPONENT(componentManager, iStats, "peragro.entity.stats")
    }

    void Entity::CreateCelEntity()
    {
      csRef<iObjectRegistry> obj_reg =
        PointerLibrary::getInstance()->getObjectRegistry();
      csRef<iCelPlLayer> pl = csQueryRegistry<iCelPlLayer> (obj_reg);

      celEntity = pl->CreateEntity();

      pl->CreatePropertyClass(celEntity, "pcobject.mesh");
      pl->CreatePropertyClass(celEntity, "pcmove.solid");
      pl->CreatePropertyClass(celEntity, "pctools.properties");

      csRef<iPcMesh> pcmesh = CEL_QUERY_PROPCLASS_ENT(celEntity, iPcMesh);
      csRef<iPcProperties> pcprop =
        CEL_QUERY_PROPCLASS_ENT(celEntity, iPcProperties);

      // Add some properties.
      pcprop->SetProperty("Entity Type", (long)type);
      pcprop->SetProperty("Entity ID", (long)id);
      pcprop->SetProperty("Entity Name", name.c_str());
    }

    void Entity::SetFullPosition(const csVector3& pos,
                                 float rotation,
                                 const std::string& sector)
    {
      csRef<iObjectRegistry> obj_reg =
        PointerLibrary::getInstance()->getObjectRegistry();
      csRef<iEngine> engine =  csQueryRegistry<iEngine> (obj_reg);

      if (sector != "Default_Sector") Entity::sectorName = sector;
      Entity::position = pos;
      Entity::rot = rotation;

      if (celEntity.IsValid())
      {
        csRef<iPcMesh> pcmesh = CEL_QUERY_PROPCLASS_ENT(celEntity, iPcMesh);
        csRef<iMeshWrapper> mesh = pcmesh->GetMesh();
        csRef<iSector> sec = engine->FindSector(sector.c_str());

        if (!sec.IsValid())
        {
          sec = engine->FindSector("Default_Sector");
          Report(PT::Debug,
            "Entity: Failed to find sector %s switching to default!", sector.c_str());
        }

        if (pcmesh.IsValid() && mesh.IsValid() && sec.IsValid())
        {
          csRef<iMovable> mov = mesh->GetMovable();
          if (mov.IsValid())
          {
            mov->SetSector(sec);
            mov->SetPosition(pos);
            mov->GetTransform ().SetO2T (csYRotMatrix3(rotation));
            mov->UpdateMove();
          }

          csRef<iPcLinearMovement> pclinmove = CEL_QUERY_PROPCLASS_ENT(celEntity, iPcLinearMovement);
          if (pclinmove.IsValid())
          {
            pclinmove->SetOnGround(false);
          }

          return; // success so return.
        }
      }

      Report(PT::Error, "Entity: SetFullPosition failed for %s(%d)!\n",
             name.c_str(), id);
    }

  } // Entity namespace
} // PT namespace
