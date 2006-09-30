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

#include "common/network/skillmessages.h"
#include "deserialiser.h"
#include "serialiser.h"

void SkillUsageStartRequestMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(caster);
  serial.setInt32(target);
  serial.setInt16(skill);
}

void SkillUsageStartRequestMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  caster = (unsigned int) serial.getInt32();
  target = (unsigned int) serial.getInt32();
  skill = (unsigned short) serial.getInt16();
}

void SkillUsageStartResponseMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(caster);
  serial.setInt32(target);
  serial.setInt16(skill);
  serial.setInt16(mpcost);
  serial.setString(error);
}

void SkillUsageStartResponseMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  caster = (unsigned int) serial.getInt32();
  target = (unsigned int) serial.getInt32();
  skill = (unsigned short) serial.getInt16();
  mpcost = (unsigned short) serial.getInt16();
  error = serial.getString();
}

void SkillUsageStopRequestMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt16(skill);
}

void SkillUsageStopRequestMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  skill = (unsigned short) serial.getInt16();
}

void SkillUsageCompletionMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(caster);
  serial.setInt32(target);
  serial.setInt16(skill);
}

void SkillUsageCompletionMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  caster = (unsigned int) serial.getInt32();
  target = (unsigned int) serial.getInt32();
  skill = (unsigned short) serial.getInt16();
}

void SkillUsageInterruptMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(caster);
  serial.setInt32(target);
  serial.setInt16(skill);
}

void SkillUsageInterruptMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  caster = (unsigned int) serial.getInt32();
  target = (unsigned int) serial.getInt32();
  skill = (unsigned short) serial.getInt16();
}

