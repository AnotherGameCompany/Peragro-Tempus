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

#include "server/network/network.h"
#include "server/usermanager.h"

void ChatHandler::handleChat(GenericMessage* msg)
{
  char buff[1024];
  const Connection* conn = msg->getConnection();
  if (!conn) return;
  ptString name = conn->getUser()->getEntity()->getName();
  ChatMessage in_msg;
  in_msg.deserialise(msg->getByteStream());
  sprintf(buff, "%s' says: '%s'", *name, in_msg.getMessage());
  printf("Chat: %s\n", buff);
  ChatMessage out_msg;
  in_msg.setType(0);
  in_msg.setMessage(buff);
  ByteStream bs;
  in_msg.serialise(&bs);
  for (size_t i=0; i<server->getUserManager()->getUserCount(); i++)
  {
    User* user = server->getUserManager()->getUser(i);
    if (user->getConnection())
      user->getConnection()->send(bs);
  }
}
