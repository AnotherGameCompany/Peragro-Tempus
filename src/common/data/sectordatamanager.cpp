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

#include "sectordatamanager.h"
#include "sector.h"

#include "ext/tinyxml/tinyxml.h"

namespace PT
{
  namespace Data
  {

    SectorDataManager::~SectorDataManager()
    {
      for (size_t i = 0; i < sectors.size(); i++) delete sectors[i];
    }

    ///@internal Currently the sectors vector is not preallocated, since there's
    ///no efficient way to get the count of items described in XML file. If need
    ///be, we could traverse the XML file once before adding the actual data in
    ///order to determine the number of sectors in file, and preallocate memory
    ///space.
    bool SectorDataManager::LoadSectorData()
    {
      TiXmlDocument doc;
      std::string file;

      file = dataPath + "/xml/world/sectors.xml";
      if (!doc.LoadFile(file.c_str())) return false;

      TiXmlElement* sectorsXML = doc.FirstChildElement("sectors");

      if (!sectorsXML) return false;

      TiXmlElement* sectorNode = sectorsXML->FirstChildElement("sector");
      for (; sectorNode; sectorNode = sectorNode->NextSiblingElement("sector"))
      {
        Sector* sector = new Sector();

        sector->SetId(atoi(sectorNode->Attribute("id")));

        sector->SetRegion(sectorNode->Attribute("region"));

        sector->SetName(sectorNode->GetText());

        sectors.push_back(sector);
      }

      return true;
    }

    Sector* SectorDataManager::GetSectorById(unsigned int id) const
    {
      for (size_t i = 0; i < sectors.size(); i++)
        if (sectors[i]->GetId() == id) return sectors[i];

      return 0;
    }

    Sector* SectorDataManager::GetSectorByName(const std::string& name) const
    {
      for (size_t i = 0; i < sectors.size(); i++)
        if (sectors[i]->GetName() == name) return sectors[i];

      return 0;
    }
  } // Data namespace
} // PT namespace
