/*
    Copyright (C) 2005 Development Team of Peragro Tempus

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General public License for more details.

    You should have received a copy of the GNU General public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef SERVERS_GUI_H
#define SERVERS_GUI_H

#include "base-gui.h"

#include "iutil/cfgmgr.h"
#include "iutil/cfgfile.h"

#define SERVERWINDOW "ServerList/Frame"

namespace PT
{
  namespace GUI
  {
    namespace Windows
    {
      class ServerWindow : public GUIWindow
      {
      private:
        csRef<iConfigManager> app_cfg;
        void AddServer(const char* name, const char* host);
        bool OnSelection(const CEGUI::EventArgs& e);

      public:
        csString GetServerHost();
        unsigned int GetServerPort();
        csString GetServerName();
        bool IsCustom();
        ServerWindow(GUIManager* guimanager);
        virtual ~ServerWindow();
        bool Create();
        bool ReloadWindow();

        void ShowWindow();
      };

    } // Windows namespace
  } // GUI namespace
} // PT namespace

#endif // SERVERS_GUI_H
