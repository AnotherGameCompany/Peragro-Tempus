/*
    Copyright (C) 2009 Development Team of Peragro Tempus

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

#ifndef TABLE_ITEMS_H
#define TABLE_ITEMS_H

#include "common/database/table.h"
#include "common/database/tablehelper.h"

class Database;
class ResultSet;

//-----------------------------------------------------------------------------------
//| Name               | C++ type name    | Primary Key  | Foreign Key
//-----------------------------------------------------------------------------------
#define DB_TABLE_ITEMS Items
#define DB_TABLE_ITEMS_FIELDS \
  ((entity_id,         size_t,             1,            (Entities, id) )) \
  ((itemTemplates_id,  size_t,             0,            (ItemTemplates, id) ))

PT_DECLARE_VO(ItemsTable, DB_TABLE_ITEMS, DB_TABLE_ITEMS_FIELDS)

/**
 * Provides an interface to the database to handle storage of Items.
 */
class ItemsTable : public Table
{
private:
  PT_DECLARE_ParseSingleResultSet(ItemsTable, DB_TABLE_ITEMS, DB_TABLE_ITEMS_FIELDS)
  PT_DECLARE_ParseMultiResultSet(ItemsTable, DB_TABLE_ITEMS, DB_TABLE_ITEMS_FIELDS)

  PT_DECLARE_CreateTable(ItemsTable, DB_TABLE_ITEMS, DB_TABLE_ITEMS_FIELDS)

public:
  ItemsTable(Database* db);

  PT_DECLARE_DropTable(ItemsTable, DB_TABLE_ITEMS, DB_TABLE_ITEMS_FIELDS)

  PT_DECLARE_Insert(ItemsTable, DB_TABLE_ITEMS, DB_TABLE_ITEMS_FIELDS)
  PT_DECLARE_GetAll(ItemsTable, DB_TABLE_ITEMS, DB_TABLE_ITEMS_FIELDS)

  PT_DECLARE_GetSingle(ItemsTable, DB_TABLE_ITEMS, DB_TABLE_ITEMS_FIELDS)
};

#endif //TABLE_ITEMS_H
