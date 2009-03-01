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

#ifndef REPUTATION_H_
#define REPUTATION_H_

#include <string.h>
#include "common/util/ptstring.h"

class Reputation
{
private:
  int id;

  ptString name_id;

public:
  Reputation() : id(-1) {}
  ~Reputation() {}

  void setId(int id) { this->id = id; }
  int GetId() { return id; }

  ptString& getName() { return name_id; }
  void setName(ptString id) { name_id = id; }
};

#endif // REPUTATION_H_
