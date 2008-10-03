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

#include "common/network/adminmessages.h"
#include "deserialiser.h"
#include "serialiser.h"

bool RemoveAllMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setString(datatype);
  return serial.isValid();
}

void RemoveAllMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  datatype = serial.getString();
}

bool CreateSectorMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt16(sectorid);
  serial.setString(name);
  serial.setString(region);
  return serial.isValid();
}

void CreateSectorMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  sectorid = (unsigned short) serial.getInt16();
  name = serial.getString();
  region = serial.getString();
}

bool CreateItemMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(itemid);
  serial.setString(name);
  serial.setString(icon);
  serial.setString(description);
  serial.setString(file);
  serial.setString(mesh);
  serial.setFloat(weight);
  serial.setString(equiptype);
  return serial.isValid();
}

void CreateItemMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  itemid = (unsigned int) serial.getInt32();
  name = serial.getString();
  icon = serial.getString();
  description = serial.getString();
  file = serial.getString();
  mesh = serial.getString();
  weight = serial.getFloat();
  equiptype = serial.getString();
}

bool CreateNpcMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setString(name);
  serial.setString(filename);
  serial.setString(mesh);
  serial.setFloat(pos.x);
  serial.setFloat(pos.y);
  serial.setFloat(pos.z);
  serial.setFloat(rotation);
  serial.setInt16(sectorid);
  serial.setString(race);
  serial.setInt8(haircolour[0]);
  serial.setInt8(haircolour[1]);
  serial.setInt8(haircolour[2]);
  serial.setInt8(skincolour[0]);
  serial.setInt8(skincolour[1]);
  serial.setInt8(skincolour[2]);
  serial.setInt8(decalcolour[0]);
  serial.setInt8(decalcolour[1]);
  serial.setInt8(decalcolour[2]);
  serial.setString(ai);
  serial.setInt8(aisettingcount);
  for ( size_t i = 0; i < aisettingcount ; i++ )
  {
    serial.setString(aisetting[i].key);
    serial.setString(aisetting[i].value);
  };

  serial.setInt8(inventorycount);
  for ( size_t i = 0; i < inventorycount ; i++ )
  {
    serial.setInt8(inventory[i].slotid);
    serial.setInt32(inventory[i].itemid);
    serial.setInt32(inventory[i].variation);
  };

  return serial.isValid();
}

void CreateNpcMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  name = serial.getString();
  filename = serial.getString();
  mesh = serial.getString();
  pos.x = serial.getFloat();
  pos.y = serial.getFloat();
  pos.z = serial.getFloat();
  rotation = serial.getFloat();
  sectorid = (unsigned short) serial.getInt16();
  race = serial.getString();
  haircolour[0] = (unsigned char) serial.getInt8();
  haircolour[1] = (unsigned char) serial.getInt8();
  haircolour[2] = (unsigned char) serial.getInt8();
  skincolour[0] = (unsigned char) serial.getInt8();
  skincolour[1] = (unsigned char) serial.getInt8();
  skincolour[2] = (unsigned char) serial.getInt8();
  decalcolour[0] = (unsigned char) serial.getInt8();
  decalcolour[1] = (unsigned char) serial.getInt8();
  decalcolour[2] = (unsigned char) serial.getInt8();
  ai = serial.getString();
  aisettingcount = (unsigned char) serial.getInt8();
  setAiSettingCount(aisettingcount);
  for ( size_t i = 0; i < aisettingcount ; i++ )
  {
    aisetting[i].key = serial.getString();
    aisetting[i].value = serial.getString();
  };

  inventorycount = (unsigned char) serial.getInt8();
  setInventoryCount(inventorycount);
  for ( size_t i = 0; i < inventorycount ; i++ )
  {
    inventory[i].slotid = (unsigned char) serial.getInt8();
    inventory[i].itemid = (unsigned int) serial.getInt32();
    inventory[i].variation = (unsigned int) serial.getInt32();
  };

}

bool CreateSpawnPointMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(itemid);
  serial.setInt32(variation);
  serial.setFloat(pos.x);
  serial.setFloat(pos.y);
  serial.setFloat(pos.z);
  serial.setInt16(sectorid);
  serial.setInt32(interval);
  return serial.isValid();
}

void CreateSpawnPointMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  itemid = (unsigned int) serial.getInt32();
  variation = (unsigned int) serial.getInt32();
  pos.x = serial.getFloat();
  pos.y = serial.getFloat();
  pos.z = serial.getFloat();
  sectorid = (unsigned short) serial.getInt16();
  interval = (unsigned int) serial.getInt32();
}

bool SpawnItemMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(itemid);
  serial.setInt32(variation);
  serial.setFloat(pos.x);
  serial.setFloat(pos.y);
  serial.setFloat(pos.z);
  serial.setInt16(sectorid);
  return serial.isValid();
}

void SpawnItemMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  itemid = (unsigned int) serial.getInt32();
  variation = (unsigned int) serial.getInt32();
  pos.x = serial.getFloat();
  pos.y = serial.getFloat();
  pos.z = serial.getFloat();
  sectorid = (unsigned short) serial.getInt16();
}

bool SpawnMountMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setString(name);
  serial.setString(mesh);
  serial.setFloat(pos.x);
  serial.setFloat(pos.y);
  serial.setFloat(pos.z);
  serial.setFloat(rotation);
  serial.setInt16(sectorid);
  return serial.isValid();
}

void SpawnMountMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  name = serial.getString();
  mesh = serial.getString();
  pos.x = serial.getFloat();
  pos.y = serial.getFloat();
  pos.z = serial.getFloat();
  rotation = serial.getFloat();
  sectorid = (unsigned short) serial.getInt16();
}

bool SpawnDoorMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt16(doorid);
  serial.setString(name);
  serial.setString(mesh);
  serial.setInt16(sectorid);
  serial.setFloat(pos.x);
  serial.setFloat(pos.y);
  serial.setFloat(pos.z);
  serial.setInt8(isopen?1:0);
  serial.setInt8(islocked?1:0);
  serial.setString(animation);
  return serial.isValid();
}

void SpawnDoorMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  doorid = (unsigned short) serial.getInt16();
  name = serial.getString();
  mesh = serial.getString();
  sectorid = (unsigned short) serial.getInt16();
  pos.x = serial.getFloat();
  pos.y = serial.getFloat();
  pos.z = serial.getFloat();
  isopen = serial.getInt8() != 0;
  islocked = serial.getInt8() != 0;
  animation = serial.getString();
}

bool RemoveSpawnedEntityMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(entityid);
  return serial.isValid();
}

void RemoveSpawnedEntityMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  entityid = (unsigned int) serial.getInt32();
}

bool ToggleFlashStepMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  return serial.isValid();
}

void ToggleFlashStepMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
}

bool CreateZoneMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt16(zoneid);
  serial.setString(zonetype);
  serial.setInt8(nodescount);
  for ( size_t i = 0; i < nodescount ; i++ )
  {
    serial.setFloat(nodes[i].x);
    serial.setFloat(nodes[i].z);
  };

  return serial.isValid();
}

void CreateZoneMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  zoneid = (unsigned short) serial.getInt16();
  zonetype = serial.getString();
  nodescount = (unsigned char) serial.getInt8();
  setNodesCount(nodescount);
  for ( size_t i = 0; i < nodescount ; i++ )
  {
    nodes[i].x = serial.getFloat();
    nodes[i].z = serial.getFloat();
  };

}

