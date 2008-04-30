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

//  !! This file was automatically generated by a network code generator   !!
//  !! Do not change this file since all changes will be overwritten later !!
//  !! Instead please change the source files here: peragro/data/generate  !!

#ifndef SKILLMESSAGES_H
#define SKILLMESSAGES_H

#include "netmessage.h"

namespace SKILL
{
  enum MESSAGES
  {
    SKILLUSAGESTARTREQUEST=0,
    SKILLUSAGESTARTRESPONSE=1,
    SKILLUSAGESTOPREQUEST=2,
    SKILLUSAGECOMPLETION=3,
    SKILLUSAGEINTERRUPT=4
  };
}

class SkillUsageStartRequestMessage : public NetMessage
{
  unsigned int caster;
  unsigned int target;
  unsigned short skill;

public:
  SkillUsageStartRequestMessage() : NetMessage(MESSAGES::SKILL,SKILL::SKILLUSAGESTARTREQUEST)
  {
  }

  ~SkillUsageStartRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getCaster() const { return caster; }
  void setCaster(unsigned int x) { caster = x; }

  unsigned int getTarget() const { return target; }
  void setTarget(unsigned int x) { target = x; }

  unsigned short getSkill() const { return skill; }
  void setSkill(unsigned short x) { skill = x; }

};

class SkillUsageStartResponseMessage : public NetMessage
{
  unsigned int caster;
  unsigned int target;
  unsigned short skill;
  unsigned short mpcost;
  ptString error;

public:
  SkillUsageStartResponseMessage() : NetMessage(MESSAGES::SKILL,SKILL::SKILLUSAGESTARTRESPONSE)
  {
  }

  ~SkillUsageStartResponseMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getCaster() const { return caster; }
  void setCaster(unsigned int x) { caster = x; }

  unsigned int getTarget() const { return target; }
  void setTarget(unsigned int x) { target = x; }

  unsigned short getSkill() const { return skill; }
  void setSkill(unsigned short x) { skill = x; }

  unsigned short getMpCost() const { return mpcost; }
  void setMpCost(unsigned short x) { mpcost = x; }

  ptString getError() const { return error; }
  void setError(ptString x) { error = x; }

};

class SkillUsageStopRequestMessage : public NetMessage
{
  unsigned short skill;

public:
  SkillUsageStopRequestMessage() : NetMessage(MESSAGES::SKILL,SKILL::SKILLUSAGESTOPREQUEST)
  {
  }

  ~SkillUsageStopRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned short getSkill() const { return skill; }
  void setSkill(unsigned short x) { skill = x; }

};

class SkillUsageCompletionMessage : public NetMessage
{
  unsigned int caster;
  unsigned int target;
  unsigned short skill;

public:
  SkillUsageCompletionMessage() : NetMessage(MESSAGES::SKILL,SKILL::SKILLUSAGECOMPLETION)
  {
  }

  ~SkillUsageCompletionMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getCaster() const { return caster; }
  void setCaster(unsigned int x) { caster = x; }

  unsigned int getTarget() const { return target; }
  void setTarget(unsigned int x) { target = x; }

  unsigned short getSkill() const { return skill; }
  void setSkill(unsigned short x) { skill = x; }

};

class SkillUsageInterruptMessage : public NetMessage
{
  unsigned int caster;
  unsigned int target;
  unsigned short skill;

public:
  SkillUsageInterruptMessage() : NetMessage(MESSAGES::SKILL,SKILL::SKILLUSAGEINTERRUPT)
  {
  }

  ~SkillUsageInterruptMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getCaster() const { return caster; }
  void setCaster(unsigned int x) { caster = x; }

  unsigned int getTarget() const { return target; }
  void setTarget(unsigned int x) { target = x; }

  unsigned short getSkill() const { return skill; }
  void setSkill(unsigned short x) { skill = x; }

};

#endif // SKILLMESSAGES_H
