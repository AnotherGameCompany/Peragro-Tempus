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

#include "client/gui/gui.h"

#include "CEGUI.h"
#include "CEGUIWindowManager.h" 
#include "CEGUILogger.h"

#include "client/network/network.h"
#include "client/gui/guimanager.h"
#include "common/version.h"

#include "common/data/server.h"
#include "common/data/serverdatamanager.h"

ServerWindow::ServerWindow(GUIManager* guimanager)
: GUIWindow (guimanager)
{
}

ServerWindow::~ServerWindow()
{
}

bool ServerWindow::OnSelection(const CEGUI::EventArgs& e) 
{
  btn = winMgr->getWindow("ServerList/Servers");
  if (((CEGUI::MultiColumnList*)btn)->getSelectedCount() == 0)
    return true;

  CEGUI::ListboxItem* item = ((CEGUI::MultiColumnList*)btn)->getFirstSelectedItem();

  PT::Data::ServerDataManager* servermgr = PointerLibrary::getInstance()->getServerDataManager();
  PT::Data::Server* server = servermgr->GetServerById(((CEGUI::MultiColumnList*)btn)->getItemRowIndex(item));
  if (server)
  {
    btn = winMgr->getWindow("Server");
    btn->setText(CEGUI::String(server->GetHost()));
  }

  if (!item->isSelected()) return true;
  return true;
}

void ServerWindow::ShowWindow() 
{
  GUIWindow::ShowWindow();
}

void ServerWindow::AddServer(const char* name, const char* host)
{
  btn = winMgr->getWindow("ServerList/Servers");
  CEGUI::ListboxItem* serverItem = new CEGUI::ListboxTextItem(name);
  serverItem->setSelectionBrushImage((CEGUI::utf8*)"Peragro", (CEGUI::utf8*)"TextSelectionBrush");
  unsigned row = ((CEGUI::MultiColumnList*)btn)->addRow();
  ((CEGUI::MultiColumnList*)btn)->setItem(serverItem, 1, row);
  ((CEGUI::MultiColumnList*)btn)->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
  if(winMgr->getWindow("Server")->getText()==host)
  {
    ((CEGUI::MultiColumnList*)btn)->setItemSelectState(serverItem, true);
  }
}

void ServerWindow::CreateGUIWindow()
{
  GUIWindow::CreateGUIWindow ("servers.xml");

  winMgr = cegui->GetWindowManagerPtr ();

  // Get the root window
  rootwindow = winMgr->getWindow("ServerList/Frame");

  btn = winMgr->getWindow("ServerList/Servers");

  btn->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&ServerWindow::OnSelection, this));

  CEGUI::String str_name("Servers");
  ((CEGUI::MultiColumnList*)btn)->addColumn(str_name,1,CEGUI::UDim(1,0));
  ((CEGUI::MultiColumnList*)btn)->setSelectionMode(CEGUI::MultiColumnList::RowSingle);

  int i=0;
  PT::Data::ServerDataManager* servermgr = PointerLibrary::getInstance()->getServerDataManager();
  PT::Data::Server* server = servermgr->GetServerById(i);
  while (server)
  {
    AddServer(server->GetName().c_str(), server->GetHost().c_str());
    i++;
    server = servermgr->GetServerById(i);
  }
}