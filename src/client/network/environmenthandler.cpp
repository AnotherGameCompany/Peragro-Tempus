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

#include "client/network/network.h"

void EnvironmentHandler::handleDayTime(GenericMessage* msg)
{
  DayTimeMessage time_msg;
  time_msg.deserialise(msg->getByteStream());
  printf("The time after next beep is %d o'clock..... *beep*\n", time_msg.getHour());

  // TODO: Do something
}

void EnvironmentHandler::handleWeather(GenericMessage* msg)
{
  // TODO: Do something
}
