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

#ifndef USERHANDLER_H
#define USERHANDLER_H

#include "common/network/nwtypes.h"
#include "common/network/messagehandler.h"

#include "common/network/usermessages.h"

class UserHandler : public MessageHandler
{
public:
  UserHandler()
  {
  }

  char getType() { return MESSAGES::USER; }

  void handle(GenericMessage* msg)
  {
    char type = msg->getMsgType();
    if (type != MESSAGES::USER) assert("wrong message type");
    char id = msg->getMsgId();

    if (id == USER::LOGINRESPONSE) handleLoginResponse(msg);
    else if (id == USER::REGISTERRESPONSE) handleRegisterResponse(msg);
    else if (id == USER::CHARLIST) handleCharList(msg);
    else if (id == USER::CHARCREATERESPONSE) handleCharCreateResponse(msg);
    else if (id == USER::CHARSELECTRESPONSE) handleCharSelectResponse(msg);
    else if (id == USER::MESHLISTRESPONSE) handleMeshListResponse(msg);
    else if (id == USER::AVATARLISTRESPONSE) handleAvatarListResponse(msg);
    else if (id == USER::AVATARINFORESPONSE) handleAvatarInfoResponse(msg);
  }

  void handleLoginResponse(GenericMessage* msg);
  void handleRegisterResponse(GenericMessage* msg);
  void handleCharList(GenericMessage* msg);
  void handleCharCreateResponse(GenericMessage* msg);
  void handleCharSelectResponse(GenericMessage* msg);
  void handleMeshListResponse(GenericMessage* msg);
  void handleAvatarListResponse(GenericMessage* msg);
  void handleAvatarInfoResponse(GenericMessage* msg);
};

#endif // USERHANDLER_H
