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

#ifndef PT_CONNECTIONDATAMANAGER_H
#define PT_CONNECTIONDATAMANAGER_H

#include <vector>
#include <string>

#include <csutil/ref.h>
#include <iutil/vfs.h>

#include "../datamanager.h"

namespace PT
{
  namespace Data
  {
    //Forward declarations
    class Server;

    /**
     * @ingroup data_handlers
     * Handles the loading of servers data from XML definition file. The data
     * resides in $DATA/xml/servers.xml file, where $DATA is the parent
     * directory where the Peragro Tempus data resides.
     */
    class ConnectionDataManager : public DataManager
    {
    private:
      ///Servers descriptions. Instances are owned by ConnectionDataManager.
      ///@internal We're using a std::vector here since it's being populated
      ///only during application startup. It also offers speed when accessing
      ///elements.
      std::vector<Server*> servers;

      csRef<iVFS> vfs;

    public:
      /**
       * Base constructor
       */
      ConnectionDataManager(PointerLibrary* ptrlib);
      ~ConnectionDataManager();

      /**
       * @param id Unique ID of the wanted server.
       * @return Pointer to server with given ID, or 0 if none was found.
       */
      Server* GetServerById(unsigned int id) const;
      /**
       * @param name Name of the wanted server.
       * @return Pointer to server with given Name, or 0 if none was found.
       */
      Server* GetServerByName(const std::string& name) const;

      void GetAllServers(std::vector<Server*>& list) { list = servers; }

      /// Implements the DataManager superclass
      bool parseElement(iDocumentNode* node);

      /// Root Node of the xml: &lt;servers&gt;
      const char* getRootName() { return "servers"; }

      /// Element Node of the xml: &lt;server&gt;
      const char* getElementName() { return "server"; }
    };
  } // Data namespace
} // PT namespace

#endif // PT_CONNECTIONDATAMANAGER_H
