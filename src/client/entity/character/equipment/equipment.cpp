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

#include "equipment.h"

Equipment::Equipment(PtEntity* entity) : entity(entity)
{
}

void Equipment::AddItem(EquipedItem* equipeditem)
{
  unsigned int slotid =  equipeditem->GetSlotId();
  UnEquip(slotid);
  equipment.Push(equipeditem);
}

void Equipment::RemoveItem(unsigned int slotid)
{
  for (size_t i=0; i < equipment.Length(); i++)
   {
     EquipedItem* item = equipment.Get(i);
     if(item->GetSlotId() == slotid)
       {
         item->DestructMesh();
         equipment.DeleteIndex(i);
         return;
       }
   }
  printf("Equipment: ERROR Couldn't remove equiped item for slot %d!\n", slotid);
}

void Equipment::Equip(unsigned int itemid, unsigned int slotid)
{  
  // Create an EquipedItem with the slotname and item information.
  EquipedItem* equipeditem = new EquipedItem(entity, itemid, slotid);

  // Add it to the equipment.
  AddItem(equipeditem);

  // Create the mesh for the item so it shows.
  equipeditem->ConstructMesh();
  
}

void Equipment::UnEquip(unsigned int slotid)
{
  RemoveItem(slotid);
}

void Equipment::ConstructMeshes()
{
  for (size_t i=0; i < equipment.Length(); i++)
   {
     EquipedItem* equipeditem = equipment.Get(i);
     equipeditem->ConstructMesh();
   }
}

void Equipment::DestructMeshes()
{
  for (size_t i=0; i < equipment.Length(); i++)
   {
     EquipedItem* equipeditem = equipment.Get(i);
     equipeditem->DestructMesh();
   }
}

void Equipment::ClearAll()
{
  DestructMeshes();
  equipment.DeleteAll();
}