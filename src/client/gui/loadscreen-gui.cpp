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

#include "client/gui/loadscreen-gui.h"

#include <CEGUI.h>
#include <CEGUIWindowManager.h>
#include <CEGUILogger.h>

namespace PT
{
  namespace GUI
  {
    namespace Windows
    {
      LoadScreenWindow::LoadScreenWindow(GUIManager* guimanager)
        : GUIWindow (guimanager)
      {
        windowName = LOADSCREENWINDOW;
      } // end LoadScreenWindow()

      LoadScreenWindow::~LoadScreenWindow()
      {
      } // end ~LoadScreenWindow()

      void LoadScreenWindow::SetProgress(float progress)
      {
        CEGUI::ProgressBar* bar = static_cast<CEGUI::ProgressBar*>
          (winMgr->getWindow("LoadScreen/Bar"));
        bar->setProgress(progress);
      } // end SetProgress()

      bool LoadScreenWindow::Create()
      {
        ReloadWindow();
        return true;
      } // end Create()

      bool LoadScreenWindow::ReloadWindow()
      {
        window = GUIWindow::LoadLayout ("client/loadscreen.layout");
        GUIWindow::AddToRoot(window);

        if (!cegui->GetImagesetManagerPtr()->isDefined("LoadScreen"))
        { // TODO: Different loading screens for different tiles(?)
          vfs->ChDir ("/peragro/art/skins/default/images/");
          cegui->GetImagesetManagerPtr()->createFromImageFile("LoadScreen", "loadscreen.jpg");
          window->setProperty("Image", "set:LoadScreen image:full_image");
          window->setProperty("BackgroundEnabled", "True");
        }

        return true;
      } // end ReloadWindow()

      void LoadScreenWindow::ShowWindow()
      {
          GUIWindow::ShowWindow();
      } // end ShowWindow()

      void LoadScreenWindow::HideWindow()
      {
          GUIWindow::HideWindow();
      } // end HideWindow()

      bool LoadScreenWindow::IsVisible()
      {
          return GUIWindow::IsVisible();
      } // end IsVisible()

    } // Windows namespace
  } // GUI namespace
} // PT namespace

