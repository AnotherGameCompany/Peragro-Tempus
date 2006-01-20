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

#ifndef _TABLE_CHARACTERS_H_
#define _TABLE_CHARACTERS_H_

#include <vector>

#include "table.h"

class Database;
class Character;
class User;

class CharacterTable : public Table
{
public:
  CharacterTable(Database* db);
  void createTable();
  void insert(int id, const std::string& name, int user_id, const std::string& mesh, const float pos[3], const std::string& sector);
  int getMaxId() const;
  void dropTable();
  void remove(int id);
  bool existsCharacter(const std::string& name);
  Character* findCharacterById(int id);
  void getAllCharacters(std::vector<Character*>& characters, User* user_id);
};

#endif // _TABLE_CHARACTERS_H_
