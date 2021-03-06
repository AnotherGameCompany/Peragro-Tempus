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
/**
 * @file environmentmanager.h
 *
 * @brief Controls the game environment.
 */

#ifndef ENVIRONMENTMANAGER_H
#define ENVIRONMENTMANAGER_H

#include <boost/scoped_ptr.hpp>

namespace PT
{
  namespace Server
  {
    namespace Environment
    {
      class Clock;
    }
  }
}

/**
 * Controls the current game environment, like weather and time.
 */
class EnvironmentManager
{
public:
  /// Constructor.
  EnvironmentManager();

  /// Destructor.
  ~EnvironmentManager();

  /// Returns the game clock.
  PT::Server::Environment::Clock* GetClock();

private:
  /// The game clock.
  boost::scoped_ptr<PT::Server::Environment::Clock> clock;
};

inline PT::Server::Environment::Clock* EnvironmentManager::GetClock()
{ return clock.get(); }

#endif // ENVIRONMENT_H
