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

#ifndef PLAYERMESSAGES_H
#define PLAYERMESSAGES_H

#include "netmessage.h"

namespace PLAYER
{
  enum MESSAGES
  {
    INVENTORYLIST = 1,
    INVENTORYMOVEITEMREQUEST = 2,
    INVENTORYMOVEITEM = 3
  };
}

class InventoryListMessage : public NetMessage
{
  unsigned int inventoryid;
  class ListInventory
  {
  public:
    unsigned int itementityid;
    Common::Inventory::PositionRef position;
    ptString name;
    ptString fileName;
    ptString meshFactName;
    Common::Inventory::Size size;
    ptString description;
    float weight;
    ptString equiptype;
  };

  unsigned int inventorycount;
  ListInventory* inventory;


public:
  InventoryListMessage() : NetMessage(MESSAGES::PLAYER,PLAYER::INVENTORYLIST)
  {
    inventory = 0;
  }

  ~InventoryListMessage()
  {
    delete [] inventory;
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getInventoryId() const { return inventoryid; }
  void setInventoryId(unsigned int x) { inventoryid = x; }

  unsigned char getInventoryCount() const { return inventorycount; }
  void setInventoryCount(unsigned char ic)
  {
    inventorycount = ic;
    delete [] inventory;
    inventory = new ListInventory[ic];
  }

  // --- begin ListInventory Getter and Setter ---

  unsigned int getItemEntityId(size_t i) { return inventory[i].itementityid; }
  void setItemEntityId(size_t i, unsigned int x) { inventory[i].itementityid = x; }

  Common::Inventory::PositionRef getPosition(size_t i) const { return inventory[i].position; }
  void setPosition(size_t i, Common::Inventory::PositionRef x) {inventory[i].position = x; }

  ptString getName(size_t i) { return inventory[i].name; }
  void setName(size_t i, ptString x) { inventory[i].name = x; }

  ptString getFileName(size_t i) { return inventory[i].fileName; }
  void setFileName(size_t i, ptString x) { inventory[i].fileName = x; }

  ptString getMeshFactName(size_t i) { return inventory[i].meshFactName; }
  void setMeshFactName(size_t i, ptString x) { inventory[i].meshFactName = x; }

  Common::Inventory::Size getSize(size_t i) { return inventory[i].size; }
  void setSize(size_t i, const Common::Inventory::Size& x)
  {
    inventory[i].size = x;
  }

  ptString getDescription(size_t i) { return inventory[i].description; }
  void setDescription(size_t i, ptString x) { inventory[i].description = x; }

  float getWeight(size_t i) { return inventory[i].weight; }
  void setWeight(size_t i, float x) { inventory[i].weight = x; }

  ptString getEquipType(size_t i) { return inventory[i].equiptype; }
  void setEquipType(size_t i, ptString x) { inventory[i].equiptype = x; }

  // --- end ListInventory Getter and Setter ---

};

class InventoryMoveItemRequestMessage : public NetMessage
{
  Common::Inventory::PositionRef oldslot;
  unsigned int oldinventoryid;
  Common::Inventory::PositionRef newslot;
  unsigned int newinventoryid;

public:
  InventoryMoveItemRequestMessage() : NetMessage(MESSAGES::PLAYER,PLAYER::INVENTORYMOVEITEMREQUEST)
  {
  }

  ~InventoryMoveItemRequestMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  Common::Inventory::PositionRef getOldSlot() const { return oldslot; }
  void setOldSlot(Common::Inventory::PositionRef x) { oldslot = x; }

  unsigned int getOldInventoryId() const { return oldinventoryid; }
  void setOldInventoryId(unsigned int x) { oldinventoryid = x; }

  Common::Inventory::PositionRef getNewSlot() const { return newslot; }
  void setNewSlot(Common::Inventory::PositionRef x) { newslot = x; }

  unsigned int getNewInventoryId() const { return newinventoryid; }
  void setNewInventoryId(unsigned int x) { newinventoryid = x; }

};

class InventoryMoveItemMessage : public NetMessage
{
  Common::Inventory::PositionRef oldslot;
  unsigned int oldinventoryid;
  Common::Inventory::PositionRef newslot;
  unsigned int newinventoryid;
  ptString error;

public:
  InventoryMoveItemMessage() : NetMessage(MESSAGES::PLAYER,PLAYER::INVENTORYMOVEITEM)
  {
  }

  ~InventoryMoveItemMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  Common::Inventory::PositionRef getOldSlot() const { return oldslot; }
  void setOldSlot(Common::Inventory::PositionRef x) { oldslot = x; }

  unsigned int getOldInventoryId() const { return oldinventoryid; }
  void setOldInventoryId(unsigned int x) { oldinventoryid = x; }

  Common::Inventory::PositionRef getNewSlot() const { return newslot; }
  void setNewSlot(Common::Inventory::PositionRef x) { newslot = x; }

  unsigned int getNewInventoryId() const { return newinventoryid; }
  void setNewInventoryId(unsigned int x) { newinventoryid = x; }

  ptString getError() const { return error; }
  void setError(ptString x) { error = x; }

};

#endif // PLAYERMESSAGES_H
