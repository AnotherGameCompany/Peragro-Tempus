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

#ifndef _CHATMESSAGES_H_
#define _CHATMESSAGES_H_

#include "netmessage.h"

namespace CHAT
{
  enum MESSAGES
  {
    SAY=0,
    SHOUT=1,
    WHISPERTO=2,
    WHISPERFROM=3,
    PARTY=4,
    GUILD=5,
    FAMILY=6
  };
}

class SayMessage : public NetMessage
{
  ptString speakername;
  const char* message;

public:
  SayMessage() : NetMessage(MESSAGES::CHAT,CHAT::SAY)
  {
  }

  ~SayMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getSpeakerName() { return speakername; }
  void setSpeakerName(ptString x) { speakername = x; }

  const char* getMessage() { return message; }
  void setMessage(const char* x) { message = x; }

};

class ShoutMessage : public NetMessage
{
  ptString speakername;
  const char* message;

public:
  ShoutMessage() : NetMessage(MESSAGES::CHAT,CHAT::SHOUT)
  {
  }

  ~ShoutMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getSpeakerName() { return speakername; }
  void setSpeakerName(ptString x) { speakername = x; }

  const char* getMessage() { return message; }
  void setMessage(const char* x) { message = x; }

};

class WhisperToMessage : public NetMessage
{
  ptString listenername;
  const char* message;

public:
  WhisperToMessage() : NetMessage(MESSAGES::CHAT,CHAT::WHISPERTO)
  {
  }

  ~WhisperToMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getListenerName() { return listenername; }
  void setListenerName(ptString x) { listenername = x; }

  const char* getMessage() { return message; }
  void setMessage(const char* x) { message = x; }

};

class WhisperFromMessage : public NetMessage
{
  ptString speakername;
  const char* message;

public:
  WhisperFromMessage() : NetMessage(MESSAGES::CHAT,CHAT::WHISPERFROM)
  {
  }

  ~WhisperFromMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getSpeakerName() { return speakername; }
  void setSpeakerName(ptString x) { speakername = x; }

  const char* getMessage() { return message; }
  void setMessage(const char* x) { message = x; }

};

class PartyMessage : public NetMessage
{
  ptString speakername;
  const char* message;

public:
  PartyMessage() : NetMessage(MESSAGES::CHAT,CHAT::PARTY)
  {
  }

  ~PartyMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getSpeakerName() { return speakername; }
  void setSpeakerName(ptString x) { speakername = x; }

  const char* getMessage() { return message; }
  void setMessage(const char* x) { message = x; }

};

class GuildMessage : public NetMessage
{
  ptString speakername;
  const char* message;

public:
  GuildMessage() : NetMessage(MESSAGES::CHAT,CHAT::GUILD)
  {
  }

  ~GuildMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getSpeakerName() { return speakername; }
  void setSpeakerName(ptString x) { speakername = x; }

  const char* getMessage() { return message; }
  void setMessage(const char* x) { message = x; }

};

class FamilyMessage : public NetMessage
{
  ptString speakername;
  const char* message;

public:
  FamilyMessage() : NetMessage(MESSAGES::CHAT,CHAT::FAMILY)
  {
  }

  ~FamilyMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getSpeakerName() { return speakername; }
  void setSpeakerName(ptString x) { speakername = x; }

  const char* getMessage() { return message; }
  void setMessage(const char* x) { message = x; }

};

#endif // _CHATMESSAGES_H_
