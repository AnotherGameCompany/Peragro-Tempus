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

#include "client/network/network.h"
#include "client/gui/gui.h"
#include "client/gui/guimanager.h"
#include <propclass/prop.h>
#include <physicallayer/propclas.h>

#include "client/entity/entitymanager.h"

#include "client/event/eventmanager.h"
#include "client/event/entityevent.h"
#include "client/event/tradeevent.h"

#include "client/reporter/reporter.h"

void EntityHandler::handleAddNpcEntity(GenericMessage* msg)
{
  Report(PT::Debug, "EntityHandler: Received AddNpcEntity.");
  AddNpcEntityMessage entmsg;
  entmsg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityAddEvent* entityEvent = new EntityAddEvent();

  entityEvent->entityName   = *entmsg.getName();
  entityEvent->meshName     = *entmsg.getMesh();
  csVector3 pos(entmsg.getPos()[0], entmsg.getPos()[1], entmsg.getPos()[2]);
  entityEvent->position     = pos;
  entityEvent->sectorId	    = entmsg.getSectorId();
  entityEvent->entityId     = entmsg.getEntityId();
  entityEvent->entityType   = PT::Entity::NPCEntityType;

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handleAddDoorEntity(GenericMessage* msg)
{
  Report(PT::Debug, "EntityHandler: Received AddDoor.");
  AddDoorEntityMessage entmsg;
  entmsg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityAddEvent* entityEvent = new EntityAddEvent();

  entityEvent->typeId      = entmsg.getDoorId();
  entityEvent->locked      = (entmsg.getIsLocked() != 0);
  entityEvent->open        = (entmsg.getIsOpen() != 0);
  entityEvent->entityId    = entmsg.getEntityId();
  entityEvent->entityType  = PT::Entity::DoorEntityType;

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}
void EntityHandler::handleRemove(GenericMessage* msg)
{
  Report(PT::Debug, "EntityHandler: Received RemoveEntity.");
  RemoveMessage entmsg;
  entmsg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityRemoveEvent* entityEvent = new EntityRemoveEvent();

  entityEvent->entityId = entmsg.getEntityId();

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handleMove(GenericMessage* msg)
{
  Report(PT::Debug, "EntityHandler: Received MoveEntity.");
  MoveMessage entmsg;
  entmsg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityMoveEvent* entityEvent = new EntityMoveEvent();

  entityEvent->entityId      = entmsg.getEntityId();
  entityEvent->walkDirection = entmsg.getWalk();
  entityEvent->turnDirection = entmsg.getTurn();
  entityEvent->run           = entmsg.getRun();

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handlePickResponse(GenericMessage* msg)
{
  PickResponseMessage response_msg;
  response_msg.deserialise(msg->getByteStream());

  if (response_msg.getError().isNull())
  {
    using namespace PT::Events;
    TradePickUpEvent* pickUpEv = new TradePickUpEvent();

    pickUpEv->itemId = response_msg.getItemId();
    pickUpEv->slotId = response_msg.getSlotId();

    PointerLibrary::getInstance()->getEventManager()->AddEvent(pickUpEv);
  }
  else
    Report(PT::Notify, "You can't pick Item %d! Reason: '%s'.", response_msg.getItemId(), *response_msg.getError());
}

void EntityHandler::handleDropResponse(GenericMessage* msg)
{
  DropResponseMessage response_msg;
  response_msg.deserialise(msg->getByteStream());

  if (response_msg.getError().isNull())
  {
    using namespace PT::Events;
    TradeDropEvent* dropEv = new TradeDropEvent();

    //dropEv->itemId = response_msg.getItemId();
    dropEv->slotId = response_msg.getSlotId();

    PointerLibrary::getInstance()->getEventManager()->AddEvent(dropEv);
  }
  else
    Report(PT::Notify, "You can't drop slot %d! Reason: '%s'.", response_msg.getSlotId(), *response_msg.getError());
}

void EntityHandler::handleDrUpdate(GenericMessage* msg)
{
  DrUpdateMessage dr_msg;
  dr_msg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityDrUpdateEvent* entityEvent = new EntityDrUpdateEvent();

  entityEvent->entityId	= dr_msg.getEntityId();
  entityEvent->position	= csVector3(dr_msg.getPos()[0],dr_msg.getPos()[1],dr_msg.getPos()[2]);
  entityEvent->rotation	= dr_msg.getRotation();
  entityEvent->sectorId	= dr_msg.getSectorId();

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handleInventoryList(GenericMessage* msg)
{
  InventoryListMessage item_msg;
  item_msg.deserialise(msg->getByteStream());

  Report(PT::Debug, "---------------------------");
  Report(PT::Debug, "EntityHandler: Got %d items in the Inventory:", item_msg.getInventoryCount());
  GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
  for (int i=0; i<item_msg.getInventoryCount(); i++)
  {
    Report(PT::Debug, "Item %d with amount 1 in slot %d.", item_msg.getItemId(i), item_msg.getSlotId(i));
    guimanager->GetInventoryWindow()->AddItem(item_msg.getItemId(i), item_msg.getSlotId(i));
  }
  Report(PT::Debug, "---------------------------\n");
}

void EntityHandler::handleStatsList(GenericMessage* msg)
{
  StatsListMessage stat_msg;
  stat_msg.deserialise(msg->getByteStream());
  Report(PT::Debug, "---------------------------");
  Report(PT::Debug, "EntityHandler: Got %d stats for the Character:", stat_msg.getStatsCount());
  GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
  for (int i=0; i<stat_msg.getStatsCount(); i++)
  {
    guimanager->GetStatusWindow()->AddSkil(*stat_msg.getName(i), stat_msg.getLevel(i));
    Report(PT::Debug, "Stat %s (%d): \t %d", *stat_msg.getName(i), stat_msg.getStatId(i), stat_msg.getLevel(i));
  }
  Report(PT::Debug, "---------------------------\n");
}

void EntityHandler::handleStatsChange(GenericMessage* msg)
{
  //TODO: Implement
  StatsChangeMessage stat_msg;
  Report(PT::Debug, "Changing stat %d to %d.", stat_msg.getStatId(), stat_msg.getLevel());
}

void EntityHandler::handleMoveTo(GenericMessage* msg)
{
  MoveToMessage move_msg;
  move_msg.deserialise(msg->getByteStream());

  float* fv1 = move_msg.getFrom();
  float* fv2 = move_msg.getTo();

  using namespace PT::Events;
  EntityMoveToEvent* entityEvent = new EntityMoveToEvent();

  entityEvent->entityId	    = move_msg.getEntityId();
  entityEvent->origin	    = csVector3(fv1[0],fv1[1],fv1[2]);
  entityEvent->destination  = csVector3(fv2[0],fv2[1],fv2[2]);
  entityEvent->speed	    = move_msg.getSpeed();

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}


void EntityHandler::handleSkillsList(GenericMessage* msg)
{
  SkillsListMessage skill_msg;
  skill_msg.deserialise(msg->getByteStream());
  Report(PT::Debug, "---------------------------");
  Report(PT::Debug, "EntityHandler: Got %d skill(s) for the Character:", skill_msg.getSkillsCount());
  for (int i=0; i<skill_msg.getSkillsCount(); i++)
  {
    //guimanager->GetInventoryWindow()->AddSkil(*stat_msg.getName(i), stat_msg.getStatLevel(i));
    Report(PT::Debug, "Skill %s (%d)", *skill_msg.getName(i), skill_msg.getSkillId(i));
  }
  Report(PT::Debug, "---------------------------\n");
}

void EntityHandler::handleEquip(GenericMessage* msg)
{
  EquipMessage equip_msg;
  equip_msg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityEquipEvent* entityEvent = new EntityEquipEvent();

  entityEvent->entityId	= equip_msg.getEntityId();
  entityEvent->slotId	= equip_msg.getSlotId();
  entityEvent->itemId	= equip_msg.getItemId();

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handleInventoryMoveItem(GenericMessage* msg)
{
  InventoryMoveItemMessage invmove_msg;
  invmove_msg.deserialise(msg->getByteStream());
  GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();

  unsigned char old_slot = invmove_msg.getOldSlot();
  unsigned char new_slot = invmove_msg.getNewSlot();

  Report(PT::Debug, "EquipMessage: You moved an item from slot %d to slot %d", old_slot, new_slot);

  guimanager->GetInventoryWindow()->MoveItem(old_slot, new_slot);
}

void EntityHandler::handleTeleport(GenericMessage* msg)
{
  TeleportMessage telemsg;
  telemsg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityTeleportEvent* entityEvent = new EntityTeleportEvent();

  entityEvent->entityId	= telemsg.getEntityId();
  entityEvent->position	= csVector3(telemsg.getPos()[0],telemsg.getPos()[1],telemsg.getPos()[2]);
  entityEvent->sectorId = telemsg.getSectorId();

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handleAddPlayerEntity(GenericMessage* msg)
{
  Report(PT::Debug, "EntityHandler: Received AddEntity.");
  AddPlayerEntityMessage entmsg;
  entmsg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityAddEvent* entityEvent = new EntityAddEvent();

  entityEvent->entityName   = *entmsg.getName();
  entityEvent->meshName     = *entmsg.getMesh();
  csVector3 pos(entmsg.getPos()[0], entmsg.getPos()[1], entmsg.getPos()[2]);
  entityEvent->position     = pos;
  entityEvent->sectorId	    = entmsg.getSectorId();
  entityEvent->entityId     = entmsg.getEntityId();
  entityEvent->entityType   = PT::Entity::PCEntityType;

  unsigned char itemCount = entmsg.getEquipmentCount();
  for (unsigned char i = 0; i < itemCount; i++)
  {
    unsigned int itemId = entmsg.getItemId(i);
    unsigned int slotId = i;
    if (itemId == 0)  continue;

    EntityAddEvent::SlotAndItem pair;
    pair.slotId = slotId;
    pair.itemId = itemId;

    entityEvent->equipment.Push(pair);
  }

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handleAddItemEntity(GenericMessage* msg)
{
  Report(PT::Debug, "EntityHandler: Received AddItemEntity.");

  AddItemEntityMessage entmsg;
  entmsg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityAddEvent* entityEvent = new EntityAddEvent();

  entityEvent->typeId       = entmsg.getItemId();
  csVector3 pos(entmsg.getPos()[0], entmsg.getPos()[1], entmsg.getPos()[2]);
  entityEvent->position     = pos;
  entityEvent->sectorId	    = entmsg.getSectorId();
  entityEvent->entityId     = entmsg.getEntityId();
  entityEvent->entityType   = PT::Entity::ItemEntityType;

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handleAddMountEntity(GenericMessage* msg)
{
  Report(PT::Debug, "EntityHandler: Received AddMountEntity.");
  AddMountEntityMessage entmsg;
  entmsg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityAddEvent* entityEvent = new EntityAddEvent();

  entityEvent->entityName   = *entmsg.getName();
  entityEvent->meshName     = *entmsg.getMesh();
  csVector3 pos(entmsg.getPos()[0], entmsg.getPos()[1], entmsg.getPos()[2]);
  entityEvent->position     = pos;
  entityEvent->sectorId	    = entmsg.getSectorId();
  entityEvent->entityId     = entmsg.getEntityId();
  entityEvent->entityType   = PT::Entity::MountEntityType;

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handleMount(GenericMessage* msg)
{
  MountMessage mount_msg;
  mount_msg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityMountEvent* entityEvent = new EntityMountEvent();

  entityEvent->entityId	= mount_msg.getPlayerEntityId();
  entityEvent->mountId	= mount_msg.getMountEntityId();
  entityEvent->control	= mount_msg.getCanControl();
  entityEvent->mount	= true;

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handleUnmount(GenericMessage* msg)
{
  UnmountMessage mount_msg;
  mount_msg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  EntityMountEvent* entityEvent = new EntityMountEvent();

  entityEvent->entityId	= mount_msg.getPlayerEntityId();
  entityEvent->mountId	= mount_msg.getMountEntityId();
  entityEvent->control	= false;
  entityEvent->mount	= false;

  PointerLibrary::getInstance()->getEventManager()->AddEvent(entityEvent);
}

void EntityHandler::handlePose(GenericMessage* msg)
{
}
