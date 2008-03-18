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

#ifndef PTENTITY_EVENT_H
#define PTENTITY_EVENT_H

#include <cssysdef.h>
#include <csgeom/vector3.h>
#include <csutil/array.h>

#include <vector>

#include "client/event/event.h"

#include <physicallayer/datatype.h>
#include "client/entity/entity.h"

namespace PT
{
  namespace Events
  {
    /**
    * Entity event base class.
    */
    class EntityEvent : public Event
    {
    public:
      unsigned int entityId;

    public:
      EntityEvent(EventID name, bool broadCast) : Event(name, broadCast) {}
      virtual ~EntityEvent() {}
    };

    /**
    * EntityEvent helper function.
    */
    template <class T>
    T GetEntityEvent(Eventp ev)
    {
      EntityEvent* entityEv = static_cast<EntityEvent*> (ev.get());
      if (!entityEv)
      {
        printf("E: Not an Entity event!\n");
        return 0;
      }
      T tEv = static_cast<T> (entityEv);
      if (!tEv)
      {
        printf("E: Wasn't listening for this %s event!\n", ev->name.c_str());
        return 0;
      }

      return tEv;
    }

    /**
    * Entity Add event.
    */
    class EntityAddEvent : public EntityEvent
    {
    public:
      PT::Entity::EntityType entityType;
      std::string entityName;
      std::string meshName;
      std::string fileName;
      unsigned int typeId;
      std::string animationName;
      csVector3 position;
      float rotation;
      unsigned int sectorId;

      struct SlotAndItem
      {
        unsigned int slotId;
        unsigned int itemId;
      };

      //std::vector<SlotAndItem> equipment;
      csArray<SlotAndItem> equipment;

      bool locked;
      bool open;

    public:
      EntityAddEvent() : EntityEvent("entity.add", true) {}
      virtual ~EntityAddEvent() {}
    };

    /**
    * Entity Remove event.
    */
    class EntityRemoveEvent : public EntityEvent
    {
    public:
      EntityRemoveEvent() : EntityEvent("entity.remove", true) {}
      virtual ~EntityRemoveEvent() {}
    };

    /**
    * Entity Equip event.
    */
    class EntityEquipEvent : public EntityEvent
    {
    public:
      unsigned char slotId;
      unsigned int itemId;

    public:
      EntityEquipEvent() : EntityEvent("entity.equip", true) {}
      virtual ~EntityEquipEvent() {}
    };

    /**
    * Entity Mount event.
    */
    class EntityMountEvent : public EntityEvent
    {
    public:
      unsigned int mountId;
      bool control;
      bool mount;

    public:
      EntityMountEvent() : EntityEvent("entity.mount", true) {}
      virtual ~EntityMountEvent() {}
    };

    /*---------------*
    *     Movement
    *----------------*/

    /**
    * Entity Move event.
    */
    class EntityMoveEvent : public EntityEvent
    {
    public:
      float walkDirection;
      float turnDirection;
      bool run;
      bool jump;
      bool local;

    public:
      EntityMoveEvent() : EntityEvent("entity.move", true) {}
      virtual ~EntityMoveEvent() {}
    };

    /**
    * Entity MoveTo event.
    */
    class EntityMoveToEvent : public EntityEvent
    {
    public:
      float speed;
      csVector3 origin;
      csVector3 destination;

    public:
      EntityMoveToEvent() : EntityEvent("entity.moveto", true) {}
      virtual ~EntityMoveToEvent() {}
    };

    /**
    * Entity Teleport event.
    */
    class EntityTeleportEvent : public EntityEvent
    {
    public:
      csVector3 position;
      unsigned int sectorId;

    public:
      EntityTeleportEvent() : EntityEvent("entity.teleport", true) {}
      virtual ~EntityTeleportEvent() {}
    };

    /**
    * Entity DrUpdate event.
    */
    class EntityDrUpdateEvent : public EntityEvent
    {
    public:
      float rotation;
      csVector3 position;
      unsigned int sectorId;

    public:
      EntityDrUpdateEvent() : EntityEvent("entity.drupdate", true) {}
      virtual ~EntityDrUpdateEvent() {}
    };

    /**
    * Entity PcPropUpdate event.
    */
    class EntityPcPropUpdateEvent : public EntityEvent
    {
    public:
      std::string pcprop;
      celData celdata;

    public:
      EntityPcPropUpdateEvent() : EntityEvent("entity.pcpropupdate", true) {}
      virtual ~EntityPcPropUpdateEvent() {}
    };

    /**
    * Entity Pose event.
    */
    class EntityPoseEvent : public EntityEvent
    {
    public:
      unsigned int poseId;

    public:
      EntityPoseEvent() : EntityEvent("entity.pose", true) {}
      virtual ~EntityPoseEvent() {}
    };

    /**
    * Entity Stat event.
    */
    class EntityStatEvent : public EntityEvent
    {
    public:
      const char* name;
      unsigned int id;
      unsigned int level;

    public:
      EntityStatEvent() : EntityEvent("entity.stat", true) {}
      virtual ~EntityStatEvent() {}
    };

  } // Events namespace
} // PT namespace

#endif // PTENTITY_EVENT_H
