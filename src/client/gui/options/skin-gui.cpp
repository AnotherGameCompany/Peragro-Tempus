/*
  Copyright (C) 2005 - 2007 Development Team of Peragro Tempus

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

#include "client/gui/options/skin-gui.h"

#include <CEGUI.h>
#include <CEGUIWindowManager.h>
#include <CEGUILogger.h>
#include <ivaria/icegui.h>

#include "common/reporter/reporter.h"
#include "common/eventcs/eventmanager.h"
#include "common/eventcs/interfaceevent.h"

#include "client/pointer/pointer.h"

#include "client/gui/guimanager.h"
#include "client/gui/skinmanager.h"

namespace PT
{
  namespace GUI
  {
    namespace Windows
    {

      SkinOptionsWindow::SkinOptionsWindow(GUIManager* guiManager)
        : GUIWindow (guiManager)
      {
        windowName = SKINOPTIONSWINDOW;
      } // end SkinOptionsWindow()

      SkinOptionsWindow::~SkinOptionsWindow()
      {
      } // end ~SkinOptionsWindow()

      bool SkinOptionsWindow::Create()
      {
        ReloadWindow();

        return true;
      } // end Create()

      bool SkinOptionsWindow::LoadPressed(const CEGUI::EventArgs& e)
      {
        using namespace CEGUI;
        using namespace PT::Events;

        PT::Events::EventManager* evmgr =
          PointerLibrary::getInstance()->getEventManager();
        csRef<iEvent> interfaceEvent =
          evmgr->CreateEvent("interface.skinwindow.buttons.load", false);
        evmgr->AddEvent(interfaceEvent);

        return true;
      } // end LoadPressed()

      bool SkinOptionsWindow::ReloadWindow()
      {
        // Load the layout.
        window = GUIWindow::LoadLayout ("client/options/skin.layout");

        // Readd the skins.
        for (size_t i = 0; i < skinList.GetSize();i++)
        {
          CreateSkinItem(skinList.Get(i));
        }// for

        // Readd the Load button event.
        CEGUI::Window* btn = guimanager->GetCeguiWindow("Options/Skins/LoadButton");
        btn->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::SubscriberSlot(&SkinOptionsWindow::LoadPressed, this));

        return true;
      } // end ReloadWindow()

      bool SkinOptionsWindow::CreateSkinItem(Skin& skin)
      {
        // Get the window.
        CEGUI::Window* btn = guimanager->GetCeguiWindow("Options/Skins/List");
        if (!btn) return false;

        // Create and add the item to the list window.
        CEGUI::ListboxItem* skinItem =
          new CEGUI::ListboxTextItem(skin.GetName()); // CEGUI deletes this.
        skinItem->setSelectionBrushImage("Peragro", "TextSelectionBrush");
        skinItem->setUserData(&skin);
        ((CEGUI::Listbox*)btn)->addItem(skinItem);

        return true;
      } // end CreateSkinItem()

      bool SkinOptionsWindow::AddSkin(Skin skin)
      {
        // Add the skin to the array.
        size_t idx = skinList.Push(skin);

        CreateSkinItem(skinList.Get(idx));

        return true;
      } // end AddSkin()

      Skin* SkinOptionsWindow::GetSelectedSkin()
      {
        // Get the window.
        CEGUI::Window* window = guimanager->GetCeguiWindow("Options/Skins/List");
        if (!window)
        {
          Report(PT::Error,
            "SkinOptionsWindow: the 'Options/Skins/List' window couldn't be found!");
          return 0;
        }

        // Get the listbox.
        CEGUI::Listbox* listbox = static_cast<CEGUI::Listbox*>(window);
        if (!listbox)
        {
          Report(PT::Error,
            "SkinOptionsWindow: the 'Options/Skins/List' window isn't a Listbox!");
          return 0;
        }
        // Get the item.
        CEGUI::ListboxItem* item = listbox->getFirstSelectedItem();
        if (!item)
        {
          Report(PT::Error, "SkinOptionsWindow: Invalid item!");
          return 0;
        }

        //Get the skin.
        Skin* skin = static_cast<Skin*>(item->getUserData());
        if (!skin)
        {
          Report(PT::Error, "SkinOptionsWindow: Invalid Skin!");
          return 0;
        }

        return skin;
      } // end GetSelectedSkin()

    } // Windows namespace
  } // GUI namespace
} // PT namespace

