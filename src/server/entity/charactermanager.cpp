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

#include "charactermanager.h"
#include "server/server.h"
#include "server/database/database.h"
#include "server/database/table-characters.h"
#include "server/entity/racemanager.h"

CharacterManager::CharacterManager(Server* server)
: server(server)
{
  charId = server->getDatabase()->getCharacterTable()->getMaxId();
}

ptString CharacterManager::createCharacter(ptString name, int user_id, int& char_id, unsigned char* haircolour, unsigned char* skincolour, unsigned char* decalcolour)
{
  CharacterTable* ct = server->getDatabase()->getCharacterTable();

  if (ct->existsCharacter(name))
  {
    return ptString("Character exists already", strlen("Character exists already")); // <-- TODO: Error Message Container
  }

  Race* race = server->getRaceManager()->findByName(ptString("test", 4));
  if (!race) return ptString("Race not found!", strlen("Race not found!"));  // <-- TODO: Error Message Container

  this->charId++;
  ct->insert(this->charId, name, user_id, ptString("test", 4), race->getId(), haircolour, skincolour, decalcolour, race->getPos(), ptString("room", 4)); // <-- TODO: Keep those ptString as class members

  char_id = this->charId;

  race->getStats()->copyToCharacter(char_id);
  race->getSkills()->copyToCharacter(char_id);

  return ptString(0,0);
}

void CharacterManager::checkForSave(const PcEntity* e)
{
  const Entity* ent = e->getEntity();
  const float dist_square = ent->getDistanceTo2(ent->getLastSaved());
  if (dist_square > 100)
  {
    Entity* l_ent = ent->getLock();
    l_ent->resetSavePos();
    server->getDatabase()->getCharacterTable()->update(ent->getPos(), ent->getRotation(), ent->getSectorName(), e->getCharacter()->getId());
    l_ent->freeLock();
  }
}

void CharacterManager::delCharacter(const Character* character)
{
  CharacterTable* ct = server->getDatabase()->getCharacterTable();
  ct->remove(character->getId());
}
