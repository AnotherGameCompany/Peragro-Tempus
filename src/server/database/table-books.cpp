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
#include "table-books.h"

BooksTable::BooksTable(Database* db) : Table(db)
{
  ResultSet* rs = db->query("select count(*) from books;");
  if (rs == 0)
  {
    createTable();
  }
  delete rs;
  ResultSet* rs2 = db->query("select count(*) from books;");
  delete rs2;
}

BooksTableVO* BooksTable::parseSingleResultSet(ResultSet* rs, size_t row)
{
  if (rs->GetRowCount() != 1) return 0;

  BooksTableVO* vo = new BooksTableVO();
  vo->id = atoi(rs->GetData(row,0).c_str());
  vo->itemId = atoi(rs->GetData(row,1).c_str());
  vo->name = ptString(rs->GetData(row,2).c_str(), rs->GetData(row,1).length());
  vo->text = ptString(rs->GetData(row,3).c_str(), rs->GetData(row,2).length());
  return vo;
}

Array<BooksTableVO*> BooksTable::parseMultiResultSet(ResultSet* rs)
{
  Array<BooksTableVO*> arr;
  for (size_t i = 0; i < rs->GetRowCount(); i++)
  {
    BooksTableVO* obj = parseSingleResultSet(rs, i);    arr.add(obj);
  }
  return arr;
}

void BooksTable::createTable()
{
  db->update("create table books ("
             "id INTEGER, "
             "itemId INTEGER, "
             "name TEXT, "
             "text TEXT, "
             "PRIMARY KEY (id, itemId) );");

  BooksTableVO book(0,ptString("Empty book", 10), ptString());
  insert(&book);
}

void BooksTable::dropTable()
{
  db->update("drop table books;");
}

void BooksTable::insert(BooksTableVO* vo)
{
  const char* query = { "insert into books(id, itemId, name, text) values (%d, %d, '%q', '%q');" };
  db->update(query, vo->id, vo->itemId, *vo->name, *vo->text);
}

void BooksTable::update(BooksTableVO* vo)
{
  const char* query = { "update books set name = '%q', text = '%q' where id = %d and itemId = %d;" };
  db->update(query, *vo->name, *vo->text, vo->id, vo->itemId);
}

void BooksTable::remove(BooksTableVO* vo)
{
  db->update("delete from books where id = %d and itemId = %d", vo->id, vo->itemId);
}

unsigned int BooksTable::getCount(unsigned int itemId)
{
  ResultSet* rs = db->query("select count(*) from books where itemId = %d;", itemId);
  unsigned int count = atoi(rs->GetData(0,0).c_str());
  delete rs;
  return count;
}

bool BooksTable::existsByName(ptString name)
{
  ResultSet* rs = db->query("select * from books where name like '%q';", *name);
  bool existence = (rs->GetRowCount() > 0);
  delete rs;
  return existence;
}

bool BooksTable::existsById(int id)
{
  ResultSet* rs = db->query("select * from books where id = %d;", id);
  bool existence = (rs->GetRowCount() > 0);
  delete rs;
  return existence;
}

BooksTableVO* BooksTable::getByName(ptString name)
{
  ResultSet* rs = db->query("select * from books where name like '%q';", *name);
  return parseSingleResultSet(rs);
}

BooksTableVO* BooksTable::getById(int id)
{
  ResultSet* rs = db->query("select * from books where id = %d;", id);
  return parseSingleResultSet(rs);
}

Array<BooksTableVO*> BooksTable::getAll()
{
  ResultSet* rs = db->query("select * from books;");
  return parseMultiResultSet(rs);
}
