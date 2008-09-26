/*
    Copyright (C) 2007-2008 Development Team of Peragro Tempus

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

#ifndef PT_COMMON_POSITIONREF_H
#define PT_COMMON_POSITIONREF_H


namespace PT
{
  namespace Common
  {
    namespace Inventory
    {
      struct PositionRef
      {
        unsigned int row;
        unsigned int column;

        PositionRef(int row, int column);
        virtual ~PositionRef();

        bool operator==(const PositionRef& reference) const;
        bool operator!=(const PositionRef& reference) const;
        PositionRef& operator=(const PositionRef& reference);
        PositionRef& operator+=(const PositionRef& reference);
        PositionRef& operator-=(const PositionRef& reference);
      };

    } // Inventory namespace
  } // Common namespace
} // PT namespace

#endif // PT_COMMON_POSITIONREF_H
