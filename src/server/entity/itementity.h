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

#ifndef ITEMENTITY_H
#define ITEMENTITY_H

#include "entity.h"

class ItemTemplate;

#include "common/inventory/item.h"

class ItemEntity : public Entity, public Common::Inventory::Item
{
private:
  bool inWorld;
  boost::shared_ptr<ItemTemplate> itemTemplate;

public:
#pragma warning( push)
#pragma warning( disable : 4355 )
  ItemEntity() : Entity(Common::Entity::ItemEntityType)
  {
    inWorld = false;
  }
#pragma warning( pop )

  ~ItemEntity() {}

  bool GetInWorld() { return inWorld; }
  void SetInWorld(bool value) { inWorld = value; }

  virtual void LoadFromDB();
  virtual void SaveToDB();
};

#endif // ITEMENTITY_H
