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

#include "slot.h"
#include "object.h"

namespace Common
{
  namespace Inventory
  {
    Slot::Slot(Inventory* parent, PositionRef position) : parent(parent), position(position)
    {
    }

    Inventory* Slot::GetParent() const
    {
      return parent;
    }

    const PositionRef& Slot::GetPosition() const
    {
      return position;
    }

    void Slot::SetContents(boost::shared_ptr<Object> object)
    {
      slotContents = object;
    }

    void Slot::Clear()
    {
      slotContents.reset();
    }

    boost::shared_ptr<Object> Slot::GetContents() const
    {
      return slotContents;
    }

    bool Slot::HasContents() const
    {
      return slotContents!=0;
    }
  }
}
