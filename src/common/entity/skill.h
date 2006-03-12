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

#ifndef SKILL_H_
#define SKILL_H_

#include <string.h>
#include "common/util/ptstring.h"

class Entity;

class Skill
{
private:
  int id;

  ptString name_id;

  enum SkillType
  {
    TYPE_HEAL = 0,
    TYPE_HURT = 1
  };

  SkillType type;

  enum SkillWorking
  {
    WORKS_ALWAYS = 0,
    WORKS_ONCE = 1,
    WORKS_DURATION = 2,
    WORKS_TOGGLE = 3
  };

  SkillWorking op;

  enum SkillAffect
  {
    AFFECT_YOU = 0,  // Skills appicalbe only on yourself.
    AFFECT_ONE = 1,  // Skills appicalbe on one target.
    AFFECT_NEAR = 2, // Skills appicalbe on nearby characters.
    AFFECT_PARTY = 3 // Skills appicalbe on all party members.
  };

  SkillAffect affect;

  float range; // Radius in which the skill will be applied.

  int skillTime;
  int hitTime;
  int reuseDelay;
  int buffDuration;

  int targetType;
  int power;

public:
  Skill() : id(-1), range(0) {}
  ~Skill() {}

  void setId(int id) { this->id = id; }
  int getId() { return id; }

  ptString& getName() { return name_id; }
  void setName(ptString id) { name_id = id; }

  SkillType getType() { return type; }
  void setType(SkillType t) { type = t; }

  SkillAffect getAffect() { return affect; }
  void setAffect(SkillAffect a) { affect = a; }
};

#endif // SKILL_H_
