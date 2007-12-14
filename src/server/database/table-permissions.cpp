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

#include "database.h"
#include "table-permissions.h"

PermissionsTable::PermissionsTable(Database* db) : db(db)
{
  ResultSet* rs = db->query("select count(*) from permissions;");
  if (rs == 0)
  {
    createTable();
  }
  delete rs;
}

PermissionsTableVO* PermissionsTable::parseSingleResultSet(ResultSet* rs, size_t row)
{
  PermissionsTableVO* vo = new PermissionsTableVO();
  vo->userid = atoi(rs->GetData(row,0).c_str());
  vo->permissionid = atoi(rs->GetData(row,1).c_str());
  vo->permissionlevel = atoi(rs->GetData(row,2).c_str());
  return vo;
}

Array<PermissionsTableVO*> PermissionsTable::parseMultiResultSet(ResultSet* rs)
{
  Array<PermissionsTableVO*> arr;
  for (size_t i = 0; i < rs->GetRowCount(); i++)
  {
    PermissionsTableVO* obj = parseSingleResultSet(rs, i);    arr.add(obj);
  }
  return arr;
}

void PermissionsTable::createTable()
{
  printf("Creating Table permissions...\n");
  db->update("create table permissions ("
             "userid INTEGER,"
             "permissionid INTEGER,"
             "permissionlevel INTEGER,"
             "PRIMARY KEY (UserId, PermissionId) );");
}

void PermissionsTable::insert(int userid, int permissionid, unsigned char level)
{
  const char* query = { "insert or replace into permissions(userid, permissionid, permissionlevel) values (%d, %d, %d);" };
  db->update(query, userid, permissionid, level);
}

void PermissionsTable::remove(int userid, int permissionid)
{
  db->update("delete from permissions where userid = %d and permissionid = %d");
}

Array<PermissionsTableVO*> PermissionsTable::getUserAll(int userid)
{
  ResultSet* rs = db->query("select * from permissions where userid = %d;", userid);
  Array<PermissionsTableVO*> vo = parseMultiResultSet(rs);
  delete rs;
  return vo;
}

PermissionsTableVO* PermissionsTable::get(int userid, int permissionid)
{
  ResultSet* rs = db->query("select * from permissions where userid = %d and permissionid = %d;", userid, permissionid);
  PermissionsTableVO* vo = parseSingleResultSet(rs);
  delete rs;
  return vo;
}
