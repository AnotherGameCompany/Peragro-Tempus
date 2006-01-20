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

void EntityHandler::handleAddEntity(GenericMessage* msg)
{
  printf("Received AddEntity\n");
  AddEntityMessage entmsg;
  entmsg.deserialise(msg->getByteStream());
  Entity* entity = new Entity();
  entity->setName(entmsg.getName());
  entity->setMesh(entmsg.getMesh());
  entity->setPos(entmsg.getPos());
  entity->setSector(entmsg.getSector());
  entity->setType(entmsg.getType());
  entity->setId(entmsg.getId());
  client->addEntity(entity);
}

void EntityHandler::handleRemoveEntity(GenericMessage* msg)
{
  printf("Received RemoveEntity\n");
  RemoveEntityMessage entmsg;
  entmsg.deserialise(msg->getByteStream());
  Entity* entity = new Entity();
  entity->setName(entmsg.getName());
  entity->setType(entmsg.getType());
  entity->setId(entmsg.getId());
  client->delEntity(entity);
}

void EntityHandler::handleMoveEntity(GenericMessage* msg)
{
  printf("Received MoveEntity\n");
  MoveEntityMessage response_msg;
  response_msg.deserialise(msg->getByteStream());
  client->moveEntity(response_msg.getName().c_str(), response_msg.getWalk(), response_msg.getRot());
}

void EntityHandler::handlePickEntity(GenericMessage* msg)
{
  PickEntityResponseMessage response_msg;
  response_msg.deserialise(msg->getByteStream());

  if (response_msg.getError() == "")
    printf("%s picks Item %s\n", response_msg.getName().c_str(), response_msg.getTarget().c_str());
  else
    printf("%s can't pick Item %s! Reason: '%s'\n", response_msg.getName().c_str(), response_msg.getTarget().c_str(), response_msg.getError().c_str());
}

void EntityHandler::handleDropEntity(GenericMessage* msg)
{
  DropEntityResponseMessage response_msg;
  response_msg.deserialise(msg->getByteStream());

  if (response_msg.getError() == "")
    printf("%s picks %s\n", response_msg.getName().c_str(), response_msg.getTarget().c_str());
  else
    printf("%s can't pick %s! Reason: '%s'\n", response_msg.getName().c_str(), response_msg.getTarget().c_str(), response_msg.getError().c_str());
}

void EntityHandler::handleDrUpdate(GenericMessage* msg)
{
  UpdateDREntityMessage dr_msg;
  dr_msg.deserialise(msg->getByteStream());

  Client::DrUpdate* drupdate = new Client::DrUpdate();
  drupdate->speed = dr_msg.getSpeed();
  drupdate->rot = dr_msg.getRot();
  drupdate->avel = dr_msg.getAVel();
  drupdate->vel = csVector3(dr_msg.getVel()[0],dr_msg.getVel()[1],dr_msg.getVel()[2]);
  drupdate->wvel = csVector3(dr_msg.getWVel()[0],dr_msg.getWVel()[1],dr_msg.getWVel()[2]);
  drupdate->pos = csVector3(dr_msg.getPos()[0],dr_msg.getPos()[1],dr_msg.getPos()[2]);
  drupdate->on_ground = dr_msg.getOnGround();
  drupdate->sector = dr_msg.getSector().c_str();
  drupdate->name = dr_msg.getName().c_str();

  client->DrUpdateEntity(drupdate);
}

