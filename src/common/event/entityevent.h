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
/**
 * @file entityevent.h
 *
 * @brief Helper classes for entity events.
 */

#ifndef PTENTITY_EVENT_H
#define PTENTITY_EVENT_H

#include <cssysdef.h>
#include <csgeom/vector3.h>
#include <csutil/array.h>
#include <csutil/parray.h>

#include "event.h"

#include <vector>
#include <string>
#include <sstream>

#include "common/geom/ptvector3.h"

#include "common/reporter/reporter.h"

namespace PT
{
  namespace Events
  {
    /**
     * @ingroup events
     * Provides helper functions for entity events.
     */
    struct EntityHelper
    {
      /**
       * Returns a string with the event name and an ID appended.
       * @param eventname The event name.
       * @param id The event ID.
       * @return A string with the name, a period, then the ID.
       */
      static std::string MakeEntitySpecific(const char* eventname, unsigned int id)
      {
        std::string str;
        std::stringstream out;
        out << eventname << "." <<id;
        str = out.str();
        return str;
      }

      /**
       * Create an equipment data stucture from an entity event.
       * @param ev An entity event.
       * @return The equipment data.
       */
      static iEvent* GetEquipment(const iEvent* ev)
      {
        csRef<iEvent> equipment;
        if (ev->Retrieve("equipmentList", equipment) != csEventErrNone)
        {
          Report(PT::Error, "EntityHelper::GetEquipment failed!");
          return 0;
        }
        return equipment;
      }

      /**
       * Add coordinates to an event parameter, as a csVector3.
       * @param ev An entity event.
       * @param name The name of the event parameter to add the coordinates to.
       * @param pos The coordinates.
       */
      static void SetVector3(iEvent* ev, const char* name, const csVector3& pos)
      {
        SetVector3(ev, name, PtVector3(pos.x, pos.y, pos.z));
      }

      /**
       * Add coordinates to an event parameter, as a PtVector3.
       * @param ev An entity event.
       * @param name The name of the event parameter to add the coordinates to.
       * @param pos The coordinates.
       */
      static void SetVector3(iEvent* ev, const char* name, const PtVector3& pos)
      {
        std::string nm = name;
        std::string nmX = nm + "_x";
        std::string nmY = nm + "_y";
        std::string nmZ = nm + "_z";

        ev->Add(nmX.c_str(), pos.x);
        ev->Add(nmY.c_str(), pos.y);
        ev->Add(nmZ.c_str(), pos.z);
      }

      /**
       * Get coordinates from an event parameter.
       * @param ev An entity event.
       * @param name The name of the event parameter to get the coordinates from.
       * @return The coordinates.
       */
      static csVector3 GetVector3(const iEvent* ev, const char* name)
      {
        std::string nm = name;
        std::string nmX = nm + "_x";
        std::string nmY = nm + "_y";
        std::string nmZ = nm + "_z";

        float x, y, z;
        x = y = z = 0.0f;

        if (ev->Retrieve(nmX.c_str(), x) != csEventErrNone)
          Report(PT::Error, "EntityHelper::GetVector3 failed! X attribute not present!");
        if (ev->Retrieve(nmY.c_str(), y) != csEventErrNone)
          Report(PT::Error, "EntityHelper::GetVector3 failed! Y attribute not present!");
        if (ev->Retrieve(nmZ.c_str(), z) != csEventErrNone)
          Report(PT::Error, "EntityHelper::GetVector3 failed! Z attribute not present!");

        csVector3 pos(x, y, z);
        return pos;
      }

      /**
       * Set the position for an entity event.
       * @param ev An entity event.
       * @param pos The coordinates.
       */
      static void SetPosition(iEvent* ev, const PtVector3& pos)
      {
        SetVector3(ev, "position", pos);
      }

      /**
       * Get the position from an entity event.
       * @param ev An entity event.
       * @return The coordinates.
       */
      static csVector3 GetPosition(const iEvent* ev)
      {
        return GetVector3(ev, "position");
      }

      /**
       * Get the entity's ID from an event.
       * @param ev An entity event.
       * @return The entity's ID.
       */
      static unsigned int GetEntityID(const iEvent* event)
      {
        unsigned int id = -1;
        if (event->Retrieve("entityId", id) != csEventErrNone)
          Report(PT::Error, "EntityHelper::GetEntityID failed!");

        return id;
      }

      /**
       * Get the entity's type from an event.
       * @param ev An entity event.
       * @return The entity's type.
       */
      static unsigned int GetEntityType(const iEvent* event, EventManager* evmgr)
      {
        const csStringID id = event->Name;
        if (evmgr->IsKindOf(id, "entity.add.pc"))
            return 0;
        else if (evmgr->IsKindOf(id, "entity.add.npc"))
          return 1;
        else if (evmgr->IsKindOf(id, "entity.add.door"))
          return 2;
        else if (evmgr->IsKindOf(id, "entity.add.item"))
          return 3;
        else if (evmgr->IsKindOf(id, "entity.add.mount"))
          return 4;
        else if (evmgr->IsKindOf(id, "entity.add.teleport"))
          return 5;
        else if (evmgr->IsKindOf(id, "entity.add.player"))
          return 0;
        else
          return -1;
      }

      /**
       * Get the entity's sector ID from an event.
       * @param ev An entity event.
       * @return The entity's sector ID.
       */
      static unsigned int GetSectorId(const iEvent* event)
      {
        unsigned int sector = -1;
        if (event->Retrieve("sectorId", sector) != csEventErrNone)
          Report(PT::Error, "EntityHelper::GetSectorId failed!");

        return sector;
      }

    };
  } // Events namespace
} // PT namespace

#endif // PTENTITY_EVENT_H
