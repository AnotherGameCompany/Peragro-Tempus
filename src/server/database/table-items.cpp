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

#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "database.h"

#include "table-items.h"
#include "common/entity/item.h"

ItemTable::ItemTable(Database* db) : Table(db)
{
  ResultSet* rs = db->query("select count(*) from items;");
  if (rs == 0)
  {
    createTable();
  }
  delete rs;
}

void ItemTable::createTable()
{
  db->update("create table items ("
    "id INTEGER, "
    "name TEXT, "
    "mesh TEXT, "
    "PRIMARY KEY (id) );");

  //Example Data!
  insert("apple", "apple");
}

void ItemTable::insert(const char* name, const char* mesh)
{
  if (strlen(name) > 512) assert("Strings too long");
  char query[1024];
  sprintf(query, "insert into items (name, mesh) values ('%s','%s');", name, mesh);
  db->update(query);
}

void ItemTable::dropTable()
{
  db->update("drop table items;");
}

bool ItemTable::existsItem(const char* name)
{
  if (strlen(name)> 512) assert("String too long");
  char query[1024];
  sprintf(query, "select id from items where name = '%s';", name);
  ResultSet* rs = db->query(query);
  bool existence = (rs->GetRowCount() > 0);
  delete rs;
  return existence;
}

Item* ItemTable::getItem(const char* name)
{
  if (strlen(name)> 512) assert("String too long");
  char query[1024];
  sprintf(query, "select * from users where name = '%s';", name);
  ResultSet* rs = db->query(query);

  Item* item = 0;

  if (rs && rs->GetRowCount() == 1) 
  {
    /*
    Item* item = new Item();
    item->setId(atoi(rs->GetData(0,0).c_str()));
    item->setName(rs->GetData(0,1).c_str(), rs->GetData(0,1).length());
    */
  }
  delete rs;
  return item;
}

void ItemTable::getAllItems(Array<Item*>& items)
{
  ResultSet* rs = db->query("select * from items;");
  if (!rs) return;
  for (size_t i=0; i<rs->GetRowCount(); i++)
  {
    Item* item = new Item();
    item->setId(atoi(rs->GetData(i,0).c_str()));
    item->setName(rs->GetData(i,1).c_str(), rs->GetData(i,1).length());
    item->setMesh(rs->GetData(i,2).c_str(), rs->GetData(i,2).length());
    items.add(item);
  }
}  
