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

#include "common/network/playermessages.h"
#include "deserialiser.h"
#include "serialiser.h"

bool InventoryListMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(inventoryid);
  serial.setInt24(inventorycount);
  for ( size_t i = 0; i < inventorycount ; i++ )
  {
    serial.setInt32(inventory[i].entityid);
    serial.setInt8(inventory[i].slotid);
    serial.setString(inventory[i].name);
    serial.setString(inventory[i].iconname);
    serial.setString(inventory[i].description);
    serial.setFloat(inventory[i].weight);
    serial.setString(inventory[i].equiptype);
  };

  return serial.isValid();
}

void InventoryListMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  inventoryid = (unsigned int) serial.getInt32();
  inventorycount = (unsigned int) serial.getInt24();
  setInventoryCount(inventorycount);
  for ( size_t i = 0; i < inventorycount ; i++ )
  {
    inventory[i].entityid = (unsigned int) serial.getInt32();
    inventory[i].slotid = (unsigned char) serial.getInt8();
    inventory[i].name = serial.getString();
    inventory[i].iconname = serial.getString();
    inventory[i].description = serial.getString();
    inventory[i].weight = serial.getFloat();
    inventory[i].equiptype = serial.getString();
  };

}

bool InventoryMoveItemRequestMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt8(oldslot);
  serial.setInt32(oldinventoryid);
  serial.setInt8(newslot);
  serial.setInt32(newinventoryid);
  return serial.isValid();
}

void InventoryMoveItemRequestMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  oldslot = (unsigned char) serial.getInt8();
  oldinventoryid = (unsigned int) serial.getInt32();
  newslot = (unsigned char) serial.getInt8();
  newinventoryid = (unsigned int) serial.getInt32();
}

bool InventoryMoveItemMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt8(oldslot);
  serial.setInt32(oldinventoryid);
  serial.setInt8(newslot);
  serial.setInt32(newinventoryid);
  serial.setString(error);
  return serial.isValid();
}

void InventoryMoveItemMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  oldslot = (unsigned char) serial.getInt8();
  oldinventoryid = (unsigned int) serial.getInt32();
  newslot = (unsigned char) serial.getInt8();
  newinventoryid = (unsigned int) serial.getInt32();
  error = serial.getString();
}

