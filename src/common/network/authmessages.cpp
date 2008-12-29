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

#include "common/network/authmessages.h"
#include "deserialiser.h"
#include "serialiser.h"

bool ClientLoginRequestMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(serverid);
  return serial.isValid();
}

void ClientLoginRequestMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  serverid = (unsigned int) serial.getInt32();
}

bool ClientLoginChallengeMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(challenge);
  return serial.isValid();
}

void ClientLoginChallengeMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  challenge = (unsigned int) serial.getInt32();
}

bool ClientLoginResponseMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setString(hash);
  return serial.isValid();
}

void ClientLoginResponseMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  serial.getString(hash);
}

bool ServerLoginRequestMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(serverid);
  return serial.isValid();
}

void ServerLoginRequestMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  serverid = (unsigned int) serial.getInt32();
}

bool ServerLoginChallengeMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(challenge);
  return serial.isValid();
}

void ServerLoginChallengeMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  challenge = (unsigned int) serial.getInt32();
}

bool ServerLoginResponseMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setString(hash);
  return serial.isValid();
}

void ServerLoginResponseMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  serial.getString(hash);
}

bool JoinServerRequestMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(serverid);
  return serial.isValid();
}

void JoinServerRequestMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  serverid = (unsigned int) serial.getInt32();
}

bool SessionIdMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(sessionid);
  return serial.isValid();
}

void SessionIdMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  sessionid = (unsigned int) serial.getInt32();
}

bool ClientJoinedMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(userid);
  return serial.isValid();
}

void ClientJoinedMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  userid = (unsigned int) serial.getInt32();
}

bool ClientLeftMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(userid);
  return serial.isValid();
}

void ClientLeftMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  userid = (unsigned int) serial.getInt32();
}

bool RegisterGameRequestMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setString(name);
  serial.setInt32(ipaddress);
  return serial.isValid();
}

void RegisterGameRequestMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  name = serial.getString();
  ipaddress = (unsigned int) serial.getInt32();
}

bool RegisterServerRequestMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(userid);
  serial.setString(username);
  return serial.isValid();
}

void RegisterServerRequestMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  userid = (unsigned int) serial.getInt32();
  username = serial.getString();
}

bool RegisterServerResponseMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setString(passwordhash);
  serial.setString(error);
  return serial.isValid();
}

void RegisterServerResponseMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  serial.getString(passwordhash);
  error = serial.getString();
}

bool RegisterGameResponseMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setString(error);
  return serial.isValid();
}

void RegisterGameResponseMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  error = serial.getString();
}

bool ServerListMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt24(unnamed1count);
  for ( size_t i = 0; i < unnamed1count ; i++ )
  {
    serial.setInt32(unnamed1[i].serverid);
    serial.setString(unnamed1[i].name);
    serial.setInt32(unnamed1[i].ipaddress);
    serial.setInt8(unnamed1[i].isjoinable?1:0);
  };

  return serial.isValid();
}

void ServerListMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  unnamed1count = (unsigned int) serial.getInt24();
  setunnamed1Count(unnamed1count);
  for ( size_t i = 0; i < unnamed1count ; i++ )
  {
    unnamed1[i].serverid = (unsigned int) serial.getInt32();
    unnamed1[i].name = serial.getString();
    unnamed1[i].ipaddress = (unsigned int) serial.getInt32();
    unnamed1[i].isjoinable = serial.getInt8() != 0;
  };

}

bool ServerListAddMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(serverid);
  serial.setString(name);
  serial.setInt32(ipaddress);
  serial.setInt8(isjoinable?1:0);
  return serial.isValid();
}

void ServerListAddMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  serverid = (unsigned int) serial.getInt32();
  name = serial.getString();
  ipaddress = (unsigned int) serial.getInt32();
  isjoinable = serial.getInt8() != 0;
}

bool ServerListRemoveMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(serverid);
  return serial.isValid();
}

void ServerListRemoveMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  serverid = (unsigned int) serial.getInt32();
}

bool ServerListUpdateMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(serverid);
  serial.setInt8(isjoinable?1:0);
  return serial.isValid();
}

void ServerListUpdateMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  serverid = (unsigned int) serial.getInt32();
  isjoinable = serial.getInt8() != 0;
}

