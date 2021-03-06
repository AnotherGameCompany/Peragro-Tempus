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

#ifndef PERMISSION_H
#define PERMISSION_H

#include <string>

#define PT_PERMISSION_COUNT 1


namespace Permission
{
  enum Type
  {
    Admin=0
  };
}

class PermissionList
{
  std::string login;
  unsigned char levels[PT_PERMISSION_COUNT];

public:
  PermissionList(const std::string& login);
  virtual ~PermissionList() {}

  unsigned char getLevel(Permission::Type type) const { return levels[type]; }
  void setLevel(Permission::Type type, unsigned char level);
};

#endif // PERMISSION_H
