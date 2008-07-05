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

#include "chatmanager.h"

#include "server/entity/entity.h"
#include "server/entity/pcentity.h"
#include "server/entity/entitymanager.h"
#include "server/server.h"

ChatManager::ChatManager() : ChatGroups()
{
}

ChatManager* ChatManager::getChatManager()
{
  static ChatManager* chatmanager = new ChatManager();
  static bool initialized = false; 

  // register a callback with the EntityManager for entity add/remove
  if (!initialized && Server::getServer() && Server::getServer()->getEntityManager())
  {
    Server::getServer()->getEntityManager()->AddEntityCallback(chatmanager);
    initialized = true;
  }

  return chatmanager;
}

void ChatManager::OnEntityAdd(const Entity* entity)
{
  if (!entity) return;
  const PcEntity* user;
  if ( !(user = entity->getPlayerEntity()) ) return;
  const CharChats* c_cchats = user->getCharChats();
  if (!c_cchats)
  {
    PcEntity* u = user->getLock();
    u->setCharChats(new CharChatsDef(user));
    c_cchats = u->getCharChats();
    u->freeLock();
  }
  if (!c_cchats) return;

  CharChats* cchats = c_cchats->getLock();
  for (size_t i=0;  i< cchats->GetDefChannelCount();  i++)
  {
    const char* channel = cchats->GetDefChannelName(i);
    addUser(user, channel);
    cchats->JoinChannel(channel, &getUserList(channel));
  }
  cchats->freeLock(); 
}

void ChatManager::OnEntityRemove(const Entity* entity)
{
  if (!entity) return; 
  const PcEntity* user;
  if ( !(user = entity->getPlayerEntity()) ) return;
  const CharChats* c_cchats = user->getCharChats();
  if (!c_cchats) return;

  
  CharChats* cchats = c_cchats->getLock(); 
  for (size_t i=0;  i < cchats->GetChannelCount();  i++)
    delUser(user, cchats->GetChannelName(i));
  cchats->freeLock();
}
