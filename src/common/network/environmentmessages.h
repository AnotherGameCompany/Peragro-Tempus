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

#ifndef _ENVIRONMENTMESSAGES_H_
#define _ENVIRONMENTMESSAGES_H_

#include "netmessage.h"

namespace ENVIRONMENT
{
  enum MESSAGES
  {
    DAYTIME=0,
    WEATHER=1
  };
}

class DayTimeMessage : public NetMessage
{
  unsigned char hour;

public:
  DayTimeMessage() : NetMessage(MESSAGES::ENVIRONMENT,ENVIRONMENT::DAYTIME)
  {
  }

  ~DayTimeMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned char getHour() { return hour; }
  void setHour(unsigned char x) { hour = x; }

};

class WeatherMessage : public NetMessage
{
  unsigned char weatherid;

public:
  WeatherMessage() : NetMessage(MESSAGES::ENVIRONMENT,ENVIRONMENT::WEATHER)
  {
  }

  ~WeatherMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned char getWeatherId() { return weatherid; }
  void setWeatherId(unsigned char x) { weatherid = x; }

};

#endif // _ENVIRONMENTMESSAGES_H_
