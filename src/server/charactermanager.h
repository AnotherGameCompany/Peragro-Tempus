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

#ifndef _CHARACTERMANAGER_H_
#define _CHARACTERMANAGER_H_

#include "common/util/array.h"
#include "common/entity/character.h"
#include "common/entity/pcentity.h"

class Server;

class CharacterManager
{
private:
  Server* server;

  int charId;

public:
  CharacterManager(Server* server);

  ptString createCharacter(ptString name, int user_id, int& char_id, unsigned int haircolour, unsigned int skincolour, unsigned int decalcolour);
  void checkForSave(PcEntity* e);

  Character* getCharacter(int id);


};

#endif // _CHARACTERMANAGER_H_
