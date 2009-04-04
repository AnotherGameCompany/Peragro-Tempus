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

#include "table-speciesreputations.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "common/database/database.h"

SpeciesReputationsTable::SpeciesReputationsTable(Database* db) : Table(db)
{
  ResultSet* rs = db->query("select count(*) from " PT_GetTableName(DB_TABLE_SPECIESREPUTATIONS) ";");
  if (rs == 0)
  {
    CreateTable();
  }
  delete rs;
}

PT_DEFINE_CreateTable(SpeciesReputationsTable, DB_TABLE_SPECIESREPUTATIONS, DB_TABLE_SPECIESREPUTATIONS_FIELDS)
PT_DEFINE_DropTable(SpeciesReputationsTable, DB_TABLE_SPECIESREPUTATIONS, DB_TABLE_SPECIESREPUTATIONS_FIELDS)
PT_DEFINE_ParseSingleResultSet(SpeciesReputationsTable, DB_TABLE_SPECIESREPUTATIONS, DB_TABLE_SPECIESREPUTATIONS_FIELDS)
PT_DEFINE_ParseMultiResultSet(SpeciesReputationsTable, DB_TABLE_SPECIESREPUTATIONS, DB_TABLE_SPECIESREPUTATIONS_FIELDS)
PT_DEFINE_Insert(SpeciesReputationsTable, DB_TABLE_SPECIESREPUTATIONS, DB_TABLE_SPECIESREPUTATIONS_FIELDS)
//PT_DEFINE_Delete(SpeciesReputationsTable, DB_TABLE_SPECIESREPUTATIONS, DB_TABLE_SPECIESREPUTATIONS_FIELDS)
//PT_DEFINE_GetAll(SpeciesReputationsTable, DB_TABLE_SPECIESREPUTATIONS, DB_TABLE_SPECIESREPUTATIONS_FIELDS)
//PT_DEFINE_DeleteAll(SpeciesReputationsTable, DB_TABLE_SPECIESREPUTATIONS, DB_TABLE_SPECIESREPUTATIONS_FIELDS)
//PT_DEFINE_Get(SpeciesReputationsTable, DB_TABLE_SPECIESREPUTATIONS, DB_TABLE_SPECIESREPUTATIONS_FIELDS)
//PT_DEFINE_GetSingle(SpeciesReputationsTable, DB_TABLE_SPECIESREPUTATIONS, DB_TABLE_SPECIESREPUTATIONS_FIELDS)