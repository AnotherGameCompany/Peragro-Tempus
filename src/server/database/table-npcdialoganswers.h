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

#ifndef TABLE_NPCDIALOGANSWERS_H
#define TABLE_NPCDIALOGANSWERS_H

#include "common/database/table.h"
#include "common/database/tablehelper.h"

class Database;
class ResultSet;

//-----------------------------------------------------------------------------------
//| Name               | C++ type name    | Key Type        | Foreign Key
//-----------------------------------------------------------------------------------
#define DB_TABLE_NPCDIALOGANSWERS NpcDialogAnswers
#define DB_TABLE_NPCDIALOGANSWERS_FIELDS \
  ((entity_id,        size_t,             PT_PrimaryKeyS,   (Entities, id) )) \
  ((dialog_id,        size_t,             PT_PrimaryKeyS,   (NpcDialogs, id) )) \
  ((id,               size_t,             PT_PrimaryKey,    0)) \
  ((text,             std::string,        0,                0)) \
  ((isEnd,            bool,               0,                0)) \
  ((nextDialog_id,    size_t,             0,                (NpcDialogs, id) )) \

PT_DECLARE_VO(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)

/**
 * Provides an interface to the database to handle storage of reputations.
 */
class NpcDialogAnswersTable : public Table
{
private:
  PT_DECLARE_ParseSingleResultSet(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)
  PT_DECLARE_ParseMultiResultSet(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)

  PT_DECLARE_CreateTable(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)

public:
  NpcDialogAnswersTable(Database* db);

  PT_DECLARE_DropTable(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)

  PT_DECLARE_Insert(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)
  //PT_DECLARE_Delete(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)
  PT_DECLARE_GetAll(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)
  PT_DECLARE_DeleteAll(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)

  //PT_DECLARE_Get(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)
  //PT_DECLARE_GetSingle(NpcDialogAnswersTable, DB_TABLE_NPCDIALOGANSWERS, DB_TABLE_NPCDIALOGANSWERS_FIELDS)
};

#endif //TABLE_NPCDIALOGANSWERS_H
