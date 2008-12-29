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
    serial.setInt32(inventory[i].itemid);
    serial.setInt32(inventory[i].variation);
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
    inventory[i].itemid = (unsigned int) serial.getInt32();
    inventory[i].variation = (unsigned int) serial.getInt32();
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

bool StatsListMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt24(statscount);
  for ( size_t i = 0; i < statscount ; i++ )
  {
    serial.setInt16(stats[i].statid);
    serial.setString(stats[i].name);
    serial.setInt16(stats[i].level);
  };

  return serial.isValid();
}

void StatsListMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  statscount = (unsigned int) serial.getInt24();
  setStatsCount(statscount);
  for ( size_t i = 0; i < statscount ; i++ )
  {
    stats[i].statid = (unsigned short) serial.getInt16();
    stats[i].name = serial.getString();
    stats[i].level = (unsigned short) serial.getInt16();
  };

}

bool StatsChangeMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt16(statid);
  serial.setInt16(entityid);
  serial.setString(name);
  serial.setInt16(level);
  return serial.isValid();
}

void StatsChangeMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  statid = (unsigned short) serial.getInt16();
  entityid = (unsigned short) serial.getInt16();
  name = serial.getString();
  level = (unsigned short) serial.getInt16();
}

bool SkillsListMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt24(skillscount);
  for ( size_t i = 0; i < skillscount ; i++ )
  {
    serial.setInt16(skills[i].skillid);
    serial.setString(skills[i].name);
  };

  return serial.isValid();
}

void SkillsListMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  skillscount = (unsigned int) serial.getInt24();
  setSkillsCount(skillscount);
  for ( size_t i = 0; i < skillscount ; i++ )
  {
    skills[i].skillid = (unsigned short) serial.getInt16();
    skills[i].name = serial.getString();
  };

}

bool MasteriesListMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt24(masteriescount);
  for ( size_t i = 0; i < masteriescount ; i++ )
  {
    serial.setInt8(masteries[i].level);
    serial.setInt16(masteries[i].id);
    serial.setInt16(masteries[i].type);
  };

  return serial.isValid();
}

void MasteriesListMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  masteriescount = (unsigned int) serial.getInt24();
  setMasteriesCount(masteriescount);
  for ( size_t i = 0; i < masteriescount ; i++ )
  {
    masteries[i].level = (unsigned char) serial.getInt8();
    masteries[i].id = (unsigned short) serial.getInt16();
    masteries[i].type = (unsigned short) serial.getInt16();
  };

}

