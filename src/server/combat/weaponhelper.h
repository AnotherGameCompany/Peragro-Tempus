/*
    Copyright (C) 2009 Development Team of Peragro Tempus

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
/**
 * @file weaponhelper.h
 *
 * @basic Helper to get weapon attributes.
 */

#ifndef WEAPONHELPER_H
#define WEAPONHELPER_H

#include <boost/shared_ptr.hpp>

class ItemEntity;

/**
 * Weapon helper
 */
class WeaponHelper
{
public:
  /**
   * Queries the Reach value from a weapon item.
   * @param item The item to return the value for.
   * @return The weapon's reach.
   */
  static unsigned int GetReach(boost::shared_ptr<ItemEntity> item);

  /**
   * Queries the heft value from a weapon item.
   * @param item The item to return the value for.
   * @return The weapon's heft.
   */
  static unsigned int GetHeft(boost::shared_ptr<ItemEntity> item);

  /**
   * Queries the Reach value from a weapon item.
   * @param item The item to return the value for.
   * @return The weapon's base damage.
   */
  static unsigned int GetBaseDamage(boost::shared_ptr<ItemEntity> item);

  /**
   * Queries the Reach value from a weapon item.
   * @param item The item to return the value for.
   * @return The weapon's damage.
   */
  static unsigned int GetDamage(boost::shared_ptr<ItemEntity> item);
};

#endif // WEAPONHELPER_H