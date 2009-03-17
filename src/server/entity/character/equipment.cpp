/*
    Copyright (C) 2009 Development Team of Peragro Tempus

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


#include "equipment.h"

#include "common/network/serialiser.h"
#include "common/network/playermessages.h"
#include "server/network/connection.h"

#include "../entity.h"

#include "server/server.h"

#include "src/server/database/tablemanager.h"
#include "src/server/database/table-equiptypes.h"
#include "src/server/database/table-equipment.h"

#include "server/entity/entitymanager.h"
#include "server/entity/itementity.h"

boost::shared_ptr<ItemEntity> Convert1(Entityp e)
{
  return boost::shared_dynamic_cast<ItemEntity>(e);
}

Equipment::Equipment(EquipmentFactory* fact, Entity* entity, TableManager* db)
  : fact(fact), entity(entity),  db(db)
{
}

bool Equipment::Equiped(size_t slotId)
{
  fact->GetSlotName(slotId); // Will throw exception when the slotId doesn't exists.
  return equipment.find(slotId) != equipment.end();
}

bool Equipment::Equiped(const std::string& slotName)
{
  return Equiped(fact->GetSlotID(slotName));
}

void Equipment::Equip(size_t slotId, boost::shared_ptr<ItemEntity> item)
{
  if (Equiped(slotId))
  {
    printf("E: Equipment::Equip: slot %d already occupied!", slotId);
    throw EquipmentFactory::Exception();
  }
  // We added the item to the equipment, so remove it from the world.
  item->SetInWorld(false);
  item->SaveToDB();
  Server::getServer()->getEntityManager()->Remove(item);
  equipment[slotId] = item;
  SaveItemToDB(slotId, item);
}

void Equipment::Equip(const std::string& slotName, boost::shared_ptr<ItemEntity> item)
{
  Equip(fact->GetSlotID(slotName), item);
}

boost::shared_ptr<ItemEntity> Equipment::UnEquip(size_t slotId)
{
  if (!Equiped(slotId))
  {
    printf("E: Equipment::UnEquip: slot %d empty!", slotId);
    throw EquipmentFactory::Exception();
  }
  Iterator it = equipment.find(slotId);
  boost::shared_ptr<ItemEntity> item(it->second);
  equipment.erase(it);
  DeleteItemFromDB(slotId, item);
  return item;
}

boost::shared_ptr<ItemEntity> Equipment::UnEquip(const std::string& slotName)
{
  return UnEquip(fact->GetSlotID(slotName));
}

void Equipment::LoadFromDB()
{
  if(entity->GetId() == Common::Entity::Entity::NoEntity)
    throw "Invalid entity!";

  EquipmentTable* table = db->Get<EquipmentTable>();
  EquipmentTableVOArray arr = table->Get(entity->GetId());
  EquipmentTableVOArray::const_iterator it = arr.begin();
  for ( ; it != arr.end(); it++)
  {
    Entityp entity = Server::getServer()->getEntityManager()->CreateNew(Common::Entity::ItemEntityType, (*it)->item_id);
    Equip((*it)->equipType_id, Convert1(entity));
  }
}

void Equipment::SaveItemToDB(size_t slotId, boost::shared_ptr<ItemEntity> item)
{
  EquipmentTable* table = Server::getServer()->GetTableManager()->Get<EquipmentTable>();
  table->Insert(entity->GetId(), slotId, item->GetId());
}

void Equipment::DeleteItemFromDB(size_t slotId, boost::shared_ptr<ItemEntity> item)
{
  EquipmentTable* table = Server::getServer()->GetTableManager()->Get<EquipmentTable>();
  table->Delete(entity->GetId(), slotId, item->GetId());
}

void Equipment::SaveToDB()
{
  //Already taken care of by Equip and UnEquip.
}

EquipmentFactory::EquipmentFactory(TableManager* db) : db(db)
{
  LoadFromDB();
}

void EquipmentFactory::LoadFromDB()
{
  EquipTypesTable* table = db->Get<EquipTypesTable>();
  EquipTypesTableVOArray arr = table->GetAll();
  EquipTypesTableVOArray::const_iterator it = arr.begin();
  for ( ; it != arr.end(); it++)
  {
    Add((*it)->id, (*it)->slotName);
    printf("Added Equipment %s\n", (*it)->name.c_str());
  }
}

boost::shared_ptr<Equipment> EquipmentFactory::Create(Entity* entity)
{
  boost::shared_ptr<Equipment> equipment(new Equipment(this, entity, db));
  return equipment;
}