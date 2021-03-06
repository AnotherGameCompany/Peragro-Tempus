/*
    Copyright (C) 2007 Development Team of Peragro Tempus

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

#ifndef PT_DATASPAWNPOINT_H
#define PT_DATASPAWNPOINT_H

#include <string>
#include <wfmath/point.h>

namespace PT
{
  namespace Data
  {
    /**
     * @ingroup data_handlers
     * Helper class that contains basic information about spawnpoint. Usually not
     * created directly, but accessed via SpawnPointDataManager instance. Use the
     * Set/Get methods to access the spawnpoint properties.
     * @see SpawnPointDataManager
     * @author Branko Majic <branko.majic@gmail.com>
     */
    class SpawnPoint
    {
    private:

      unsigned int item;

      ///Position of the spawnpoint in a sector (ie x='20', y='30', z='40').
      WFMath::Point<3> position;
      ///Name of the sector where the spawnpoint resides (e.g. 'room').
      std::string sectorName;

      unsigned int interval;

    public:
      SpawnPoint() : position(0.0f) {}

      void SetItem(unsigned int value) { item = value; }
      unsigned int GetItem() const { return item; }

      void SetPosition(float x, float y, float z)
      { position = WFMath::Point<3>(x,y,z); }
      void SetPosition(const WFMath::Point<3>& value) { position = value;}
      const WFMath::Point<3>& GetPosition() const { return position; }

      void SetSectorName(const std::string& value) { sectorName = value; }
      const std::string& GetSectorName() const { return sectorName; }

      void SetInterval(unsigned int value) { interval = value; }
      unsigned int GetInterval() const { return interval; }
    };
  } // Data namespace
} // PT namespace

#endif // PT_DATASPAWNPOINT_H
