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

#ifndef DOORMESSAGES_H
#define DOORMESSAGES_H

#include "netmessage.h"

namespace DOOR
{
  enum MESSAGES
  {
    OPENDOORREQUEST=0,
    OPENDOORRESPONSE=1,
    CLOSEDOORREQUEST=2,
    CLOSEDOORRESPONSE=3,
    LOCKDOORREQUEST=4,
    LOCKDOORRESPONSE=5,
    UNLOCKDOORREQUEST=6,
    UNLOCKDOORRESPONSE=7
  };
}

class OpenDoorRequestMessage : public NetMessage
{
  unsigned int doorid;

public:
  OpenDoorRequestMessage() : NetMessage(MESSAGES::DOOR,DOOR::OPENDOORREQUEST)
  {
  }

  ~OpenDoorRequestMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getDoorId() const { return doorid; }
  void setDoorId(unsigned int x) { doorid = x; }

};

class OpenDoorResponseMessage : public NetMessage
{
  unsigned int doorid;
  ptString error;

public:
  OpenDoorResponseMessage() : NetMessage(MESSAGES::DOOR,DOOR::OPENDOORRESPONSE)
  {
  }

  ~OpenDoorResponseMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getDoorId() const { return doorid; }
  void setDoorId(unsigned int x) { doorid = x; }

  ptString getError() const { return error; }
  void setError(ptString x) { error = x; }

};

class CloseDoorRequestMessage : public NetMessage
{
  unsigned int doorid;

public:
  CloseDoorRequestMessage() : NetMessage(MESSAGES::DOOR,DOOR::CLOSEDOORREQUEST)
  {
  }

  ~CloseDoorRequestMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getDoorId() const { return doorid; }
  void setDoorId(unsigned int x) { doorid = x; }

};

class CloseDoorResponseMessage : public NetMessage
{
  unsigned int doorid;
  ptString error;

public:
  CloseDoorResponseMessage() : NetMessage(MESSAGES::DOOR,DOOR::CLOSEDOORRESPONSE)
  {
  }

  ~CloseDoorResponseMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getDoorId() const { return doorid; }
  void setDoorId(unsigned int x) { doorid = x; }

  ptString getError() const { return error; }
  void setError(ptString x) { error = x; }

};

class LockDoorRequestMessage : public NetMessage
{
  unsigned int doorid;

public:
  LockDoorRequestMessage() : NetMessage(MESSAGES::DOOR,DOOR::LOCKDOORREQUEST)
  {
  }

  ~LockDoorRequestMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getDoorId() const { return doorid; }
  void setDoorId(unsigned int x) { doorid = x; }

};

class LockDoorResponseMessage : public NetMessage
{
  unsigned int doorid;
  ptString error;

public:
  LockDoorResponseMessage() : NetMessage(MESSAGES::DOOR,DOOR::LOCKDOORRESPONSE)
  {
  }

  ~LockDoorResponseMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getDoorId() const { return doorid; }
  void setDoorId(unsigned int x) { doorid = x; }

  ptString getError() const { return error; }
  void setError(ptString x) { error = x; }

};

class UnlockDoorRequestMessage : public NetMessage
{
  unsigned int doorid;

public:
  UnlockDoorRequestMessage() : NetMessage(MESSAGES::DOOR,DOOR::UNLOCKDOORREQUEST)
  {
  }

  ~UnlockDoorRequestMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getDoorId() const { return doorid; }
  void setDoorId(unsigned int x) { doorid = x; }

};

class UnlockDoorResponseMessage : public NetMessage
{
  unsigned int doorid;
  ptString error;

public:
  UnlockDoorResponseMessage() : NetMessage(MESSAGES::DOOR,DOOR::UNLOCKDOORRESPONSE)
  {
  }

  ~UnlockDoorResponseMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getDoorId() const { return doorid; }
  void setDoorId(unsigned int x) { doorid = x; }

  ptString getError() const { return error; }
  void setError(ptString x) { error = x; }

};

#endif // DOORMESSAGES_H
