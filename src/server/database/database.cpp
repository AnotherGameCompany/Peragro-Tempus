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
#include "table-users.h"
#include "table-characters.h"
#include "table-entities.h"
#include "table-items.h"
#include "table-inventory.h"
#include "table-stats.h"
#include "table-characterstats.h"
#include "table-races.h"
#include "table-racestats.h"
#include "table-raceskills.h"
#include "table-skills.h"
#include "table-characterskills.h"
#include "table-npcaisetting.h"
#include "table-npcdialogs.h"
#include "table-npcdialoganswers.h"
#include "table-npcentities.h"
#include "table-spawnpoints.h"
#include "table-books.h"
#include "table-doors.h"
#include "table-sectors.h"
#include "table-permissions.h"
#include "table-meshes.h"
#include "table-vertices.h"
#include "table-triangles.h"
#include "table-config.h"

Database::Database()
{
  userstable = 0;
  charactertable = 0;
  entitytable = 0;
  inventorytable = 0;
  stattable = 0;
  characterstattable = 0;
  racetable = 0;
  racestattable = 0;
  skilltable = 0;
  raceskilltable = 0;
  characterskillstable = 0;
  npcaisettingtable = 0;
  npcdialogstable = 0;
  npcdialoganswerstable = 0;
  npcentitiestable = 0;
  bookstable = 0;
  doorstable = 0;
  sectorstable = 0;
  configtable = 0;
}

void Database::init()
{
  update("begin transaction");
  userstable = new UsersTable(this);
  charactertable = new CharacterTable(this);
  entitytable = new EntityTable(this);
  itemtable = new ItemTable(this);
  inventorytable = new InventoryTable(this);
  stattable = new StatTable(this);
  characterstattable = new CharacterStatsTable(this);
  racetable = new RaceTable(this);
  racestattable = new RaceStatsTable(this);
  skilltable = new SkillTable(this);
  raceskilltable = new RaceSkillsTable(this);
  characterskillstable = new CharacterSkillsTable(this);
  npcaisettingtable = new NpcAiSettingTable(this);
  npcdialogstable = new NpcDialogsTable(this);
  npcdialoganswerstable = new NpcDialogAnswersTable(this);
  npcentitiestable = new NpcEntitiesTable(this);
  spawnpointstable = new SpawnPointsTable(this);
  bookstable = new BooksTable(this);
  doorstable = new DoorsTable(this);
  sectorstable = new SectorsTable(this);
  permissionstable = new PermissionsTable(this);
  meshestable = new MeshesTable(this);
  verticestable = new VerticesTable(this);
  trianglestable = new TrianglesTable(this);
  configtable = new ConfigTable(this);
  update("commit");
}

Database::~Database()
{
  delete userstable;
  delete charactertable;
  delete entitytable;
  delete itemtable;
  delete inventorytable;
  delete stattable;
  delete characterstattable;
  delete racetable;
  delete racestattable;
  delete raceskilltable;
  delete skilltable;
  delete characterskillstable;
  delete npcaisettingtable;
  delete npcdialogstable;
  delete npcdialoganswerstable;
  delete npcentitiestable;
  delete spawnpointstable;
  delete bookstable;
  delete doorstable;
  delete sectorstable;
  delete permissionstable;
  delete meshestable;
  delete verticestable;
  delete trianglestable;
  delete configtable;
}

