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

#ifndef _NPCENTITY_H_
#define _NPCENTITY_H_

#include "common/util/ptstring.h"
#include "common/util/monitorable.h"

#include "entity.h"
#include "character.h"

#include "server/ai/ai.h"

class Character;

class NpcEntity : public ptMonitorable<NpcEntity>
{
private:
  ptMonitor<Entity> entity;
  ptMonitor<Character> character;

  bool isWalking;

  float final_dst[3];
  size_t t_stop;

  float tmp_pos[3]; //used only for temporary calculations!

  AI* ai;

  unsigned int dialog_id;

public:
  NpcEntity()
  {
    entity = (new Entity(Entity::NPCEntityType))->getRef();

    Entity* e = entity.get()->getLock();
    e->setNpcEntity(this);
    e->freeLock();

    isWalking = false;

    ai = 0;
    dialog_id = 0;
  }

  ~NpcEntity()
  {
    delete ai;
    delete character.get();
  }

  const Entity* getEntity() const { return entity.get(); }

  void setAI(AI* ai) { this->ai = ai; ai->setNPC(this); }
  AI* getAI() { return ai; }

  void setCharacter(Character* character);
  const Character* getCharacter() const { return this->character.get(); }

  void walkTo(float* dst_pos, float speed);
  const float* getPos();

  void setStartDialog(unsigned int id) { dialog_id = id; }
  unsigned int getStartDialog() { return dialog_id; }
  void pause(bool pause) { if (ai) ai->pause(pause); }
};

#endif // _NPCENTITY_H_
