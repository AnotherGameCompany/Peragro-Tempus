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

InventoryWindow::InventoryWindow(GUIManager* guimanager)
: GUIWindow (guimanager)
{
}

InventoryWindow::~InventoryWindow()
{
}

bool InventoryWindow::handleCloseButton(const CEGUI::EventArgs& args)
{
  winMgr->getWindow("Inventory/Frame")->setVisible(false);
  return true;
}

bool InventoryWindow::AddItem(uint itemid, uint slotid)
{
  if(slotid > numberOfSlots) return false;
  if(slotid == -1) return false;

  Slot* slot = inventory[slotid];

  if (!slot)
  {
    printf("InventoryWindow: ERROR Couldn't add item %d in slot %d!\n", itemid, slotid);
    return false;
  }

  if (!slot->IsEmpty() && !slot->GetObject()->IsStackable())
  {
    printf("InventoryWindow: ERROR Slot %d already occupied!\n", slotid);
    return false;
  }

  ClientItem* clientitem = itemmanager->GetItemById(itemid);

  // If the slot already has an item and it's stackable
  // increase the amount.
  if (!slot->IsEmpty() && slot->GetObject()->IsStackable())
  {
    slot->GetObject()->SetAmount(slot->GetObject()->GetAmount()+1);
    dragdrop->UpdateItemCounter(slot->GetWindow(), slot->GetObject()->GetAmount());
  }
  // Create a new item.
  else
  {
    Object* object = new Object();
    object->SetId(itemid);
    object->SetAmount(1);
    object->SetWindow(dragdrop->createIcon(DragDrop::Item, itemid));
    // If stackable is bigger then 1 the item is stackable by that amount.
    // If stackable equals 0 its infinitly stackable.
    if (clientitem->GetStackable() > 1 || clientitem->GetStackable() == 0)
      object->SetStackable(true);
    slot->SetObject(object);
    slot->GetWindow()->addChildWindow(object->GetWindow());
  }

  return true;
}

bool InventoryWindow::MoveItem(uint olslotid, uint newslotid)
{
  Slot* oldslot = inventory[olslotid];
  Slot* newslot = inventory[newslotid];
  Object* object = oldslot->GetObject();

  if (!oldslot || !newslot || !object)
  {
    printf("InventoryWindow: ERROR Couldn't move item from slot %d to slot %d!\n", olslotid, newslotid);
    return false;
  }

  oldslot->MoveObjectTo(newslot);
  dragdrop->UpdateItemCounter(oldslot->GetWindow(), 0);
  newslot->GetWindow()->addChildWindow(object->GetWindow());
  dragdrop->UpdateItemCounter(newslot->GetWindow(), newslot->GetObject()->GetAmount());

  return true;
}

void InventoryWindow::CreateGUIWindow()
{
  // First 10 slots(0-9) are equipment,
  // other 20 are inventory.
  numberOfSlots = 30;

  GUIWindow::CreateGUIWindow ("inventory.xml");
  winMgr = cegui->GetWindowManagerPtr ();

  dragdrop = guimanager->GetDragDrop();
  itemmanager = guimanager->GetClient ()->getItemmgr();

  //Load the inventory icon imageset
  vfs = guimanager->GetClient()->getVFS ();
  vfs->ChDir ("/peragro/skin/");
  cegui->GetImagesetManagerPtr()->createImageset("/peragro/skin/inventory.imageset", "Inventory");

  // Get the frame window
  CEGUI::FrameWindow* frame = static_cast<CEGUI::FrameWindow*>(winMgr->getWindow("Inventory/Frame"));
  frame->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&InventoryWindow::handleCloseButton, this));

  CEGUI::Window* root = winMgr->getWindow("Root");
  root->subscribeEvent(CEGUI::Window::EventDragDropItemDropped, CEGUI::Event::Subscriber(&DragDrop::handleDragDroppedRoot, dragdrop));

  // Populate the bag with slots.
  CEGUI::Window* bag = winMgr->getWindow("Inventory/Bag");
  for (int j=0; j<4; j++)
  {
    for (int i=0; i<5; i++)
    {
      Slot* slot = new Slot();
      slot->SetId((i+(j*5))+10);
      slot->SetType(DragDrop::Item);
      slot->SetWindow(dragdrop->createDragDropSlot(bag, CEGUI::UVector2(CEGUI::UDim(0,4.0f+(28*i)), CEGUI::UDim(0,4.0f+(28*j)))));
      slot->GetWindow()->setUserData(slot);
      inventory.Put(slot->GetId(), slot);
    }
  }

 // Get the root window
  rootwindow = winMgr->getWindow("Inventory/Frame");

}
