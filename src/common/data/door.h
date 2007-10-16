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

#ifndef PT_DATADOOR_H
#define PT_DATADOOR_H

#include <string>
#include "common/util/ptvector3.h"

namespace PT
{
  namespace Data
  {
    /**
      @ingroup data_handlers
      Helper class that contains basic information about door. Usually not
      created directly, but accessed via DoorDataManager instance. Use the
      Set/Get methods to access the door properties.
      @see DoorDataManager
      @author Branko Majic <branko.majic@gmail.com>
    */
    class Door
    {
    private:
      ///Unique ID of the door (ie '1').
      unsigned int id;
      ///Name of the door (ie 'North Gate').
      std::string name;
      ///meshName - name of the mesh in the mesh file used for this door (ie
      ///'gate_north_gate').
      std::string meshName;
      ///Position of the door in a sector (ie x='20', y='30', z='40').
      PtVector3 position;
      ///Name of the sector where the door resides (ie 'room').
      std::string sectorName;
      ///ID of the key that locks/unlocks the door (ie '7').
      unsigned int keyId;
      ///Quest to be used for door events (ie 'GateUpward').
      std::string questName;

    public:
      Door() : id(0) {}

      void SetId(unsigned int value) { id = value; }
      unsigned int GetId() const { return id; }

      void SetName(const std::string& value) { name = value; }
      const std::string& GetName() const { return name; }

      void SetMeshName(const std::string& value) { meshName = value; }
      const std::string& GetMeshName() const { return meshName; }

      void SetPosition(double x,double y,double z)
        { position = PtVector3(x,y,z); }
      void SetPosition(const PtVector3& value) { position = value;}
      const PtVector3& GetPosition() const { return position; }

      void SetSectorName(const std::string& value) { sectorName = value; }
      const std::string& GetSectorName() const { return sectorName; }

      void SetKeyId(unsigned int value) { keyId = value; }
      unsigned int GetKeyId() const { return keyId; }

      void SetQuestName(const std::string& value) { questName = value; }
      const std::string& GetQuestName() const { return questName; }
    };
  }
}

#endif
