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
#include "ext/bullet/btBulletDynamicsCommon.h"

class btDiscreteDynamicsWorld;
class btRigidBody;

class BulletCD : public CollisionDetection
{
private:
  btDiscreteDynamicsWorld* world;

  std::map<Common::Entity::Entityp, btRigidBody*> cobjs;

  btDefaultCollisionConfiguration* collisionConfiguration;
  btCollisionDispatcher* dispatcher;
  btAxisSweep3* overlappingPairCache;
  btSequentialImpulseConstraintSolver* constraintSolver;

protected:
  virtual void Run();

public:
  BulletCD();
  virtual ~BulletCD();

  virtual void setup();

  virtual void addEntity(Common::Entity::Entityp entity);
  virtual void removeEntity(Common::Entity::Entityp entity);

  virtual void loadPosition(Common::Entity::Entityp entity);
  virtual void savePosition(Common::Entity::Entityp entity);

  virtual void moveEntity(Common::Entity::Entityp entity, const WFMath::Point<3>& pos,
                          float speed);
  virtual void moveEntity(Common::Entity::Entityp entity, float speed, float rot);
};

#endif // PT_BULLET_H
