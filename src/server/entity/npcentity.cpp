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

#include "server/entity/user.h"
#include "server/entity/character.h"
#include "server/entity/npcentity.h"

#include <time.h>

void NpcEntity::setCharacter(Character* character)
{
  this->character = character->getRef();
  ptScopedMonitorable<Entity> e (entity.get());
  ptScopedMonitorable<Character> c (character);
  character->setEntity(e);
}

void NpcEntity::walkTo(const PtVector3& dst_pos, float speed)
{
  final_dst = dst_pos;

  PtVector3 pos = entity.get()->getPos();

  const float dist = Distance(final_dst, pos);

  //v = s / t => t = s / v
  t_stop = (size_t) (dist / speed + time(0));

  isWalking = true;
}

PtVector3 NpcEntity::getPos()
{
  if (!isWalking)
  {
    return entity.get()->getPos();
  }
  else
  {
    if ((size_t)time(0) >= t_stop)
    {
      ptScopedMonitorable<Entity> ent (entity.get());
      ent->setPos(final_dst);

      isWalking = false;
      return final_dst;
    }
    else
    {
      const PtVector3 pos = entity.get()->getPos();
      //Not sure that's correct...
      size_t delta = t_stop - (size_t) time(0);
      tmp_pos = (final_dst - pos) * (float)delta;
      return tmp_pos;
    }
  }
}
