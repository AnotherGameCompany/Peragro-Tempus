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

#ifndef AUTHHANDLER_H
#define AUTHHANDLER_H

#include "common/network/nwtypes.h"

#include "common/network/authmessages.h"

class AuthHandler : public MessageHandler
{
public:
  AuthHandler()
  {
  }

  char getType() { return MESSAGES::AUTH; }

  void handle(GenericMessage* msg)
  {
    char type = msg->getMsgType();
    if (type != MESSAGES::AUTH) assert("wrong message type");
    char id = msg->getMsgId();

    if (id == AUTH::CLIENTLOGINREQUEST) handleClientLoginRequest(msg);
    else if (id == AUTH::CLIENTLOGINRESPONSE) handleClientLoginResponse(msg);
    else if (id == AUTH::SERVERLOGINREQUEST) handleServerLoginRequest(msg);
    else if (id == AUTH::SERVERLOGINRESPONSE) handleServerLoginResponse(msg);
    else if (id == AUTH::JOINSERVERREQUEST) handleJoinServerRequest(msg);
    else if (id == AUTH::CLIENTJOINED) handleClientJoined(msg);
    else if (id == AUTH::CLIENTLEFT) handleClientLeft(msg);
    else if (id == AUTH::REGISTERGAMEREQUEST) handleRegisterGameRequest(msg);
    else if (id == AUTH::REGISTERSERVERRESPONSE) handleRegisterServerResponse(msg);
  }

  void handleClientLoginRequest(GenericMessage* msg);
  void handleClientLoginResponse(GenericMessage* msg);
  void handleServerLoginRequest(GenericMessage* msg);
  void handleServerLoginResponse(GenericMessage* msg);
  void handleJoinServerRequest(GenericMessage* msg);
  void handleClientJoined(GenericMessage* msg);
  void handleClientLeft(GenericMessage* msg);
  void handleRegisterGameRequest(GenericMessage* msg);
  void handleRegisterServerResponse(GenericMessage* msg);
};

#endif // AUTHHANDLER_H