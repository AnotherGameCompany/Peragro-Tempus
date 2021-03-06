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

#ifndef TRADE_GUI_H
#define TRADE_GUI_H

#include "base-gui.h"

#include "client/gui/common/inventory.h"

#define TRADEWINDOW "TradeWindow/Frame"

namespace PT
{
  namespace GUI
  {
    namespace Windows
    {

      class TradeWindow : public GUIWindow
      {
      private:
        PT::GUI::Windows::DragDrop* dragdrop;
        PT::Data::ItemDataManager* itemDataManager;
        unsigned int numberOfSlots;
        bool accept1;
        bool accept2;
        Inventory* trade1;
        Inventory* trade2;
        csArray<Slot*> inventory;

      private:
        bool OnCloseButton(const CEGUI::EventArgs& args);
        bool OnAcceptPlayer1(const CEGUI::EventArgs& args);
        bool OnAcceptPlayer2(const CEGUI::EventArgs& args);

      public:
        TradeWindow(GUIManager* guimanager);
        virtual ~TradeWindow();
        bool Create();
        bool ReloadWindow();
        Slot* GetOldSlot(Slot* slot);
        void UpdateOffer();

      public:
        bool OnYesConfirm(const CEGUI::EventArgs& args);
        bool OnNoConfirm(const CEGUI::EventArgs& args);

      public:
        void SetName(unsigned int player, csString name);
        bool AddItem(unsigned int player, unsigned int itemid,
                  unsigned int slotid, const char* name, const char* iconname);
        bool AddItem(Slot* oldslot, Slot* newslot);
        void SetMoney(unsigned int player, unsigned int amount);
        void SetAccept(unsigned int player, bool value);
        void SetNotificationMsg(csString errormsg);
        void CancelTrade();
        void AcceptTrade();
        void ClearItems();

      };

    } // Windows namespace
  } // GUI namespace
} // PT namespace

#endif // TRADE_GUI_H
