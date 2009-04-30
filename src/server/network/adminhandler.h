/*
    Copyright (C) 2008 Development Team of Peragro Tempus

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

//  !! This file was automatically generated by a network code generator   !!
//  !! Do not change this file since all changes will be overwritten later !!
//  !! Instead please change the source files here: peragro/data/generate  !!

#ifndef ADMINHANDLER_H
#define ADMINHANDLER_H

#include "common/network/nwtypes.h"

#include "common/network/adminmessages.h"

class AdminHandler : public MessageHandler
{
public:
  AdminHandler()
  {
  }

  char getType() { return MESSAGES::ADMIN; }

  void handle(GenericMessage* msg)
  {
    char type = msg->getMsgType();
    if (type != MESSAGES::ADMIN) assert("wrong message type");
    char id = msg->getMsgId();

    if (id == ADMIN::REMOVEALL) handleRemoveAll(msg);
    else if (id == ADMIN::SETCONFIG) handleSetConfig(msg);
    else if (id == ADMIN::CREATEMESH) handleCreateMesh(msg);
    else if (id == ADMIN::CREATESPAWNPOINT) handleCreateSpawnPoint(msg);
    else if (id == ADMIN::SPAWNITEM) handleSpawnItem(msg);
    else if (id == ADMIN::SPAWNMOUNT) handleSpawnMount(msg);
    else if (id == ADMIN::SPAWNDOOR) handleSpawnDoor(msg);
    else if (id == ADMIN::REMOVESPAWNEDENTITY) handleRemoveSpawnedEntity(msg);
    else if (id == ADMIN::TOGGLEFLASHSTEP) handleToggleFlashStep(msg);
    else if (id == ADMIN::CREATEZONE) handleCreateZone(msg);
    else if (id == ADMIN::SETDATE) handleSetDate(msg);
    else if (id == ADMIN::CREATECHANDEFAULT) handleCreateChanDefault(msg);
    else if (id == ADMIN::CREATECHANSPACE) handleCreateChanSpace(msg);
  }

  void handleRemoveAll(GenericMessage* msg);
  void handleSetConfig(GenericMessage* msg);
  void handleCreateMesh(GenericMessage* msg);
  void handleCreateSpawnPoint(GenericMessage* msg);
  void handleSpawnItem(GenericMessage* msg);
  void handleSpawnMount(GenericMessage* msg);
  void handleSpawnDoor(GenericMessage* msg);
  void handleRemoveSpawnedEntity(GenericMessage* msg);
  void handleToggleFlashStep(GenericMessage* msg);
  void handleCreateZone(GenericMessage* msg);
  void handleSetDate(GenericMessage* msg);
  void handleCreateChanDefault(GenericMessage* msg);
  void handleCreateChanSpace(GenericMessage* msg);
};

#endif // ADMINHANDLER_H
