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

#include "client/entity/ptentitymanager.h"

void EntityHandler::handleAddNpcEntity(GenericMessage* msg)
{
  printf("EntityHandler: Received AddNpcEntity\n");
  AddNpcEntityMessage entmsg;
  entmsg.deserialise(msg->getByteStream());
  PtEntity* entity = new PtNpcEntity();
  entity->SetName(*entmsg.getName());
  entity->SetMeshName(*entmsg.getMesh());
  csVector3 pos(entmsg.getPos()[0], entmsg.getPos()[1], entmsg.getPos()[2]);
  entity->SetPosition(pos);
  entity->SetSectorName(*entmsg.getSector());
  entity->SetId(entmsg.getId());
  PointerLibrary::getInstance()->getEntityManager()->addEntity(entity);
}

void EntityHandler::handleAddDoor(GenericMessage* msg)
{
  printf("EntityHandler: Received AddDoor\n");
  AddDoorMessage entmsg;
  entmsg.deserialise(msg->getByteStream());
  PtDoorEntity* entity = 0;
  entity = new PtDoorEntity();
  entity->SetName(*entmsg.getName());
  entity->SetMeshName(*entmsg.getMesh());
  entity->SetOpen(entmsg.getOpen());
  entity->SetLocked(entmsg.getLocked());
  entity->SetId(entmsg.getId());
  PointerLibrary::getInstance()->getEntityManager()->addEntity(entity);
}
void EntityHandler::handleRemoveEntity(GenericMessage* msg)
{
  printf("EntityHandler: Received RemoveEntity\n");
  RemoveEntityMessage entmsg;
  entmsg.deserialise(msg->getByteStream());
  PtEntity* entity = 0;
  switch (entmsg.getType())
  {
    case PtEntity::ItemEntity: entity = new PtItemEntity(); break;
    case PtEntity::PlayerEntity: entity = new PtPcEntity(); break;
    case PtEntity::NPCEntity: entity = new PtNpcEntity(); break;
  };
  entity->SetName(*entmsg.getName());
  entity->SetId(entmsg.getId());
  PointerLibrary::getInstance()->getEntityManager()->delEntity(entity);
  if (entmsg.getType() == PtEntity::PlayerEntity)
    PointerLibrary::getInstance()->getGUIManager()->GetBuddyWindow()->RemovePlayer(*entmsg.getName());
}

void EntityHandler::handleMoveEntity(GenericMessage* msg)
{
  printf("EntityHandler: Received MoveEntity\n");
  MoveEntityMessage response_msg;
  response_msg.deserialise(msg->getByteStream());
  PointerLibrary::getInstance()->getEntityManager()->moveEntity(response_msg.getId(), response_msg.getWalk(), response_msg.getRot());
}

void EntityHandler::handlePickEntity(GenericMessage* msg)
{
  PickEntityResponseMessage response_msg;
  response_msg.deserialise(msg->getByteStream());
  guimanager = PointerLibrary::getInstance()->getGUIManager();
  const char* ownname = PointerLibrary::getInstance()->getEntityManager()->GetOwnName().GetData();

  if (response_msg.getError().isNull())
  {
    printf("%s picks Item %s(%d) %s\n", *response_msg.getName(), *response_msg.getTarget(), response_msg.getItemId(),ownname);
    if (strlen(*response_msg.getName()) == strlen(ownname) && !strcmp(*response_msg.getName(), ownname))
      guimanager->GetInventoryWindow()->AddItem(response_msg.getItemId(), response_msg.getSlot());
  }
  else
    printf("%s can't pick Item %s! Reason: '%s'\n", *response_msg.getName(), *response_msg.getTarget(), *response_msg.getError());
}

void EntityHandler::handleDropEntity(GenericMessage* msg)
{
  DropEntityResponseMessage response_msg;
  response_msg.deserialise(msg->getByteStream());

  if (response_msg.getError().isNull())
    printf("%s picks %s\n", *response_msg.getName(), *response_msg.getTarget());
  else
    printf("%s can't pick %s! Reason: '%s'\n", *response_msg.getName(), *response_msg.getTarget(), *response_msg.getError());
}

void EntityHandler::handleDrUpdate(GenericMessage* msg)
{
  UpdateDREntityMessage dr_msg;
  dr_msg.deserialise(msg->getByteStream());

  DrUpdateData* drupdate = new DrUpdateData();
  drupdate->speed = dr_msg.getSpeed();
  drupdate->rot = dr_msg.getRot();
  drupdate->avel = dr_msg.getAVel();
  drupdate->vel = csVector3(dr_msg.getVel()[0],dr_msg.getVel()[1],dr_msg.getVel()[2]);
  drupdate->wvel = csVector3(dr_msg.getWVel()[0],dr_msg.getWVel()[1],dr_msg.getWVel()[2]);
  drupdate->pos = csVector3(dr_msg.getPos()[0],dr_msg.getPos()[1],dr_msg.getPos()[2]);
  drupdate->on_ground = dr_msg.getOnGround();
  drupdate->sector = *dr_msg.getSector();
  drupdate->entity_id = dr_msg.getId();

  PointerLibrary::getInstance()->getEntityManager()->DrUpdateEntity(drupdate);
}

void EntityHandler::handleInventoryItemList(GenericMessage* msg)
{
  InventoryItemListMessage item_msg;
  item_msg.deserialise(msg->getByteStream());
  printf("EntityHandler: Got %d items in the Inventory: \n---------------------------\n", item_msg.getItemCount());
  guimanager = PointerLibrary::getInstance()->getGUIManager();
  for (int i=0; i<item_msg.getItemCount(); i++)
  {
    for (int j=0; j<item_msg.getItemAmount(i); j++)
    {
      printf("Item %d in slot %d\n", item_msg.getItemId(i), item_msg.getItemSlot(i));
      guimanager->GetInventoryWindow()->AddItem(item_msg.getItemId(i), item_msg.getItemSlot(i));
    }
  }
}

void EntityHandler::handleCharacterStatList(GenericMessage* msg)
{
  CharacterStatListMessage stat_msg;
  stat_msg.deserialise(msg->getByteStream());
  printf("EntityHandler: Got %d stats for the Character: \n---------------------------\n", stat_msg.getStatCount());
  guimanager = PointerLibrary::getInstance()->getGUIManager();
  for (int i=0; i<stat_msg.getStatCount(); i++)
  {
    guimanager->GetStatusWindow()->AddSkil(*stat_msg.getName(i), stat_msg.getStatLevel(i));
    printf("Stat %s (%d): \t %d\n", *stat_msg.getName(i), stat_msg.getStatId(i), stat_msg.getStatLevel(i));
  }
}

void EntityHandler::handleMoveEntityTo(GenericMessage* msg)
{
  MoveEntityToMessage move_msg;
  move_msg.deserialise(msg->getByteStream());
  
  float* fv1 = move_msg.getFromPos();
  float* fv2 = move_msg.getToPos();

  PointerLibrary::getInstance()->getEntityManager()->moveEntity(move_msg.getId(), move_msg.getSpeed(), fv1, fv2);
}


void EntityHandler::handleCharacterSkillList(GenericMessage* msg)
{
  CharacterSkillListMessage skill_msg;
  skill_msg.deserialise(msg->getByteStream());
  printf("EntityHandler: Got %d skill(s) for the Character: \n---------------------------\n", skill_msg.getSkillCount());
  guimanager = PointerLibrary::getInstance()->getGUIManager();
  for (int i=0; i<skill_msg.getSkillCount(); i++)
  {
    //guimanager->GetInventoryWindow()->AddSkil(*stat_msg.getName(i), stat_msg.getStatLevel(i));
    printf("Skill %s (%d)\n", *skill_msg.getName(i), skill_msg.getSkillId(i));
  }
}

void EntityHandler::handleEquip(GenericMessage* msg)
{
  EquipMessage equip_msg;
  equip_msg.deserialise(msg->getByteStream());
  guimanager = PointerLibrary::getInstance()->getGUIManager();
  if (!equip_msg.getError().isNull())
  {
    printf("EquipMessage: ERROR: '%s'\n", *equip_msg.getError());
    return;
  }
  else
  {
    if (equip_msg.getNewSlotID() < 10)
    {
      printf("EquipMessage: Entity %d equiped item %d to slot %d\n", 
        equip_msg.getEntityID(), equip_msg.getItemID(), equip_msg.getNewSlotID());
    }
    else
    {
      printf("EquipMessage: You moved item %d from slot %d to slot %d\n", 
        equip_msg.getItemID(), equip_msg.getOldSlotID(), equip_msg.getNewSlotID());
      guimanager->GetInventoryWindow()->MoveItem(equip_msg.getOldSlotID(), equip_msg.getNewSlotID());
    }
  }
  // do something
}

void EntityHandler::handleTeleport(GenericMessage* msg)
{
  TeleportMessage telemsg;
  telemsg.deserialise(msg->getByteStream());

  int entity_id = telemsg.getId();
  float* pos = telemsg.getPos();
  const char* sector = *telemsg.getSector();

  PointerLibrary::getInstance()->getEntityManager()->teleport(entity_id, pos, sector);
}

void EntityHandler::handleAddCharacterEntity(GenericMessage* msg)
{
  printf("EntityHandler: Received AddEntity\n");
  AddCharacterEntityMessage entmsg;
  entmsg.deserialise(msg->getByteStream());
  PtPcEntity* entity = new PtPcEntity();
  entity->SetName(*entmsg.getName());
  entity->SetMeshName(*entmsg.getMesh());
  csVector3 pos(entmsg.getPos()[0], entmsg.getPos()[1], entmsg.getPos()[2]);
  entity->SetPosition(pos);
  entity->SetSectorName(*entmsg.getSector());
  entity->SetId(entmsg.getEntityId());
  /*
  Character* character = new Character();
  character->setDecalColour(entmsg.getDecalColour());
  character->setHairColour(entmsg.getHairColour());
  character->setSkinColour(entmsg.getSkinColour());
  entity->setCharacter(character);
  */
  PointerLibrary::getInstance()->getEntityManager()->addEntity(entity);
  if (entmsg.getEntityType() == PtEntity::PlayerEntity)
    PointerLibrary::getInstance()->getGUIManager()->GetBuddyWindow()->AddPlayer(*entmsg.getName());
}

void EntityHandler::handleAddItemEntity(GenericMessage* msg)
{
}
