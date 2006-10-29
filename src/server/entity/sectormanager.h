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

#ifndef _SECTORMANAGER_H_
#define _SECTORMANAGER_H_

#include "common/util/array.h"
#include "common/util/ptString.h"

namespace Sector
{
  static unsigned short NoSector = 0;
}

class SectorManager
{
private:
  Array<ptString> sectors;

public:
  SectorManager() {}
  ~SectorManager()
  {
  }

  unsigned short getSectorCount()
  {
    return sectors.getCount()+1;
  }

  unsigned short getSectorId(ptString name)
  {
    for (size_t i = 0; i < sectors.getCount(); i++)
    {
      if (sectors.get(i) == name) return i+1;
    }
    return Sector::NoSector;
  }

  const ptString& getSectorName(unsigned short id)
  {
    if (id > sectors.getCount()) return ptString::Null;
    return sectors.get(id+1);
  }

  void addSector(unsigned short id, ptString name)
  {
    if (sectors.getCount()+1 == id)
      sectors.add(name);
    else
      printf("Sectors out of order! Expected sector id %d but got %d!\n", sectors.getCount(), id);
  }
};

#endif // _ITEMMANAGER_H_
