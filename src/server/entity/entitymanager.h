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

#include <list>

#include "common/entity/entitymanager.h"

#include "entity.h"
#include "entitycallback.h"

class EntityTable;

typedef boost::shared_ptr<Entity> Entityp;

class EntityManager : public Common::Entity::EntityManager, WFMath::iShape::Listener
{
private:
  std::list<Common::Entity::EntityCallback*> callback_list;

  Mutex mutex;
  void lock() { mutex.lock(); }
  void unlock() { mutex.unlock(); }

  virtual void Moved(WFMath::iShape*);
  virtual void Destroyed(WFMath::iShape*) {}

  void NetworkAddEntity(const Common::Entity::Entityp entity);

public:
  EntityManager();
  ~EntityManager();

  void LoadFromDB(EntityTable* table);

  Entityp CreateNew(Common::Entity::EntityType type, size_t id=Common::Entity::Entity::NoEntity);

  virtual bool Add(Common::Entity::Entityp entity);
  virtual void Remove(const Common::Entity::Entityp entity);

  void AddEntityCallback(Common::Entity::EntityCallback* cb);
  void RemoveEntityCallback(Common::Entity::EntityCallback* cb);
};

#endif // ENTITYMANAGER_H
