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

#ifndef USER_H
#define USER_H

#include <map>

#include "common/entity/entitymanager.h"

//#include "common/util/monitorable.h"
#include "common/util/ptstring.h"

#include "server/network/connection.h"

#include "permission.h"

class Network;
class Connection;
class Entity;
class PcEntity;

class User
{
private:
  std::string login;
  std::string pwhash;

  ptMonitor<Connection> connection;
  PcEntity* own_entity;

  std::map<size_t, Common::Entity::WeakEntityp> knownEntitites;

  PermissionList permissions;

  void SendAddEntity(Common::Entity::Entityp entity);
  void SendRemoveEntity(Common::Entity::Entityp entity);

public:
  User(const std::string& login) : login(login), own_entity(0), permissions(login) { }
  ~User() { }

  const std::string& GetName() const { return login; }
  //void setName(const std::string& login) { this->login = login; }

  const std::string& getPwHash() { return pwhash; }
  void setPwHash(const std::string& pwhash) { this->pwhash = pwhash; }

  PcEntity* GetEntity() const { return own_entity; }
  void SetEntity(PcEntity* entity);

  const Connection* GetConnection() const { return connection.get(); }
  void SetConnection(Connection* connection)
  {
    if (connection)
      this->connection = connection->getRef();
    else
      this->connection.clear();
  }

  void SendEntityDiff(const std::list<Common::Entity::Entityp>& entities);

  void ClearKnownEntitites() { knownEntitites.clear(); }
  void remove();

  PermissionList& getPermissionList() { return permissions; }
  const PermissionList& getPermissionList() const { return permissions; }
};

#endif // USER_H
