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

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "common/util/array.h"
#include "entity.h"
#include "pcentity.h"
#include "npcentity.h"
#include "itementity.h"
#include "doorentity.h"
#include "mountentity.h"
#include "entitylist.h"
#include "entitycallback.h"

class EntityManager
{
private:
  EntityList entity_list;
  unsigned int ent_id;

  std::vector<EntityCallback*> callback_list;

  Mutex mutex;

public:
  EntityManager() : ent_id(0) {}
  ~EntityManager()
  {
    for (size_t i = 0; i < entity_list.getEntityCount(); i++)
    {
      delete entity_list.getEntity(i);
    }
  }

  size_t getEntityCount()
  {
    return entity_list.getEntityCount();
  }

  const Entity* getEntity(size_t index)
  {
    return entity_list.getEntity(index);
  }

  void addLockedEntity(Entity* locked_entity)
  {
    mutex.lock();
    ent_id++;

    locked_entity->setId(ent_id);

    entity_list.addEntity(locked_entity);
    mutex.unlock();

    for (unsigned int i = 0; i < callback_list.size(); i++)
    {
      callback_list[i]->OnEntityAdd(locked_entity);
    }
  }

  void addEntity(const Entity* entity)
  {
    ptScopedMonitorable<Entity> e (entity);

    addLockedEntity(e);
  }

  void removeEntity(const Entity* entity)
  {
    for (unsigned int i = 0; i < callback_list.size(); i++)
    {
      callback_list[i]->OnEntityRemove(entity);
    }

    mutex.lock();
    entity_list.removeEntity(entity);
    mutex.unlock();
  }

  bool exists(const Entity* entity)
  {
    return entity_list.exists(entity);
  }

  const Entity* findByName(ptString name)
  {
    return entity_list.findByName(name);
  }

  const Entity* findById(int id)
  {
    return entity_list.findById(id);
  }

  void lock() { mutex.lock(); }
  void unlock() { mutex.unlock(); }

  void loadFromDB(EntityTable* et);

  void AddEntityCallback(EntityCallback* cb)
  {
    callback_list.push_back(cb);
  }

  void RemoveEntityCallback(EntityCallback* cb)
  {
    std::vector<EntityCallback*>::iterator it;
    for (it = callback_list.begin(); it != callback_list.end(); it++)
    {
      if (*it == cb)
      {
        callback_list.erase(it);
        return;
      }
    }
  }
};

#endif // ENTITYMANAGER_H
