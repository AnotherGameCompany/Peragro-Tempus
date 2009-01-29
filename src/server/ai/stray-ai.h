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

#ifndef STRAY_AI_H
#define STRAY_AI_H

#include "ai.h"
#include <wfmath/point.h>

class StrayAI : public AI
{
private:
  NpcEntity* npc;

  WFMath::Point<3> base;
  WFMath::Point<3> radius;

  unsigned int interval_base;
  unsigned int interval_rand;

protected:
  virtual void timeOut();

public:
  StrayAI() : npc(0) { paused = false; }
  ~StrayAI() {}

  virtual void setNPC(NpcEntity* npc);
  virtual void think();
};

#endif // STRAY_AI_H
