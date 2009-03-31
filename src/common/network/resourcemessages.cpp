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

#include "common/network/resourcemessages.h"
#include "deserialiser.h"
#include "serialiser.h"

bool ResourceListMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(entityid);
  serial.setInt24(resourcescount);
  for ( size_t i = 0; i < resourcescount ; i++ )
  {
    serial.setInt16(resources[i].resourceid);
    serial.setString(resources[i].name);
    serial.setInt32(resources[i].value);
    serial.setInt32(resources[i].maxvalue);
  };

  return serial.isValid();
}

void ResourceListMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  entityid = (unsigned int) serial.getInt32();
  resourcescount = (unsigned int) serial.getInt24();
  setResourcesCount(resourcescount);
  for ( size_t i = 0; i < resourcescount ; i++ )
  {
    resources[i].resourceid = (unsigned short) serial.getInt16();
    resources[i].name = serial.getString();
    resources[i].value = (unsigned int) serial.getInt32();
    resources[i].maxvalue = (unsigned int) serial.getInt32();
  };

}

bool ResourceUpdateMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(entityid);
  serial.setInt16(resourceid);
  serial.setInt32(value);
  serial.setInt32(maxvalue);
  return serial.isValid();
}

void ResourceUpdateMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  entityid = (unsigned int) serial.getInt32();
  resourceid = (unsigned short) serial.getInt16();
  value = (unsigned int) serial.getInt32();
  maxvalue = (unsigned int) serial.getInt32();
}

