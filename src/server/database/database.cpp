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
#include "table-skills.h"
#include "table-characterskills.h"

Database::Database()
{
}

void Database::init()
{
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
  characterskillstable = new CharacterSkillsTable(this);
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
  delete skilltable;
  delete characterskillstable;
}

