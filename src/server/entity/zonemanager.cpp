/*
    Copyright (C) 2008 Development Team of Peragro Tempus

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

#include "common/util/math.h"

#include "server/database/database.h"
#include "server/database/table-zones.h"
#include "server/database/table-zonenodes.h"
#include "server/server.h"

#include "zonemanager.h"

void ZoneManager::delAll()
{
  Server::getServer()->getDatabase()->getZonesTable()->removeAll();
  Server::getServer()->getDatabase()->getZonenodesTable()->removeAll();
  zones.clear();
}

void ZoneManager::loadFromDB(ZonesTable* zonestable, ZonenodesTable* zonenodestable)
{
  Array<ZonesTableVO*>rows=zonestable->getAll();
  for(size_t i=0; i<rows.getCount(); i++)
  {
    Zone zone;
    zone.type=ptString::create(rows[i]->type);
    Array<ZonenodesTableVO*> nodes=zonenodestable->getById(rows[i]->id);
    for(size_t i2=0; i2<nodes.getCount(); i2++)
    {
      zone.coords.push_back(PtVector2(nodes[i2]->x,nodes[i2]->z));
    }
    zones.push_back(zone);
  }
}

ptString ZoneManager::GetZone(float x, float z)
{
  PtVector2 position(x,z);
  for(size_t i=0; i<zones.size(); i++)
  {
    if(Math::IsInArea(&zones[i].coords.front(), zones[i].coords.size(), position))
    {
      return zones[i].type;
    }
  }
  return ptString("",0);
}
