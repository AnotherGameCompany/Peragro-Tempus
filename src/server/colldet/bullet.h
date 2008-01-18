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

#ifndef PT_BULLET_H
#define PT_BULLET_H

#include <map>

#include "colldet.h"

class btCollisionWorld;
class btCollisionObject;

class BulletCD : public CollisionDetection
{
private:
  btCollisionWorld* collisionWorld;

  std::map<const Entity*, btCollisionObject*> cobjs;

protected:
  virtual void Run();

public:
  BulletCD() {}
  virtual ~BulletCD() {}

  virtual void setup();

  virtual void addEntity(const Entity* entity);
  virtual void removeEntity(const Entity* entity);

  virtual void loadPosition(const Entity* entity);
  virtual void savePosition(const Entity* entity);

  virtual void moveEntity(const Entity* entity, float* pos, float speed);
  virtual void moveEntity(const Entity* entity, float speed, float rot);
};

#endif // PT_BULLET_H
