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

#include "playerinventory.h"

#include "client/event/eventmanager.h"
#include "client/event/tradeevent.h"

#include "client/reporter/reporter.h"
#include "client/pointer/pointer.h"

#include "client/gui/guimanager.h"
#include "client/gui/gui.h"


namespace PT
{
  namespace Trade
  {
    PlayerInventory::PlayerInventory ()
    {
    }

    PlayerInventory::~PlayerInventory ()
    {
    }

    bool PlayerInventory::Initialize ()
    {
      using namespace PT::Events;

      // Register listener for InventoryAddEvent.
      EventHandler<PlayerInventory>* cbAdd = new EventHandler<PlayerInventory>(&PlayerInventory::Add, this);
      PointerLibrary::getInstance()->getEventManager()->AddListener("trade.inventory.add", cbAdd);

      return true;
    }

    bool PlayerInventory::Add(PT::Events::Eventp ev)
    {
      using namespace PT::Events;

      InventoryAddEvent* tradeEv = GetTradeEvent<InventoryAddEvent*>(ev);
      if (!tradeEv) return false;

      GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
      if (!guimanager) return true;
      guimanager->GetInventoryWindow()->AddItem(tradeEv->itemId, tradeEv->variationId, tradeEv->slotId);

      return true;
    }

  } // Trade namespace 
} // PT namespace 
