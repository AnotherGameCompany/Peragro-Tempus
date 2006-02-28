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

#ifndef _ITEMENTITY_H_
#define _ITEMENTITY_H_

#include <string.h>
#include <time.h>
#include <math.h>

#include "common/util/stringstore.h"

#include "inventory.h"
#include "characterstats.h"

class Item;

class ItemEntity : public Entity
{
private:
  int item;

public:
  ItemEntity() : Entity(Entity::ItemEntity)
  {
  }

  ~ItemEntity()
  {
  }

  void setItem(int i)
  {
    item = i;
  }

  int getItem()
  {
    return item;
  }

  void createFromItem(Item* item)
  {
    this->setName(item->getName());
    this->setMesh(item->getMesh());
    this->setItem(item->getId());
  }
};

#endif // _ITEMENTITY_H_
