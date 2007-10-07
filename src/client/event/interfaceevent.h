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

#ifndef PT_INTERFACE_EVENT_H
#define PT_INTERFACE_EVENT_H

#include <cssysdef.h>

#include "client/event/event.h"

namespace PT
{
  namespace Events
  {
    /**
    * Interface event base class.
    */
    class InterfaceEvent : public Event
    {
    public:
      InterfaceEvent(EventID name, bool broadCast) : Event(name, broadCast) {}
      virtual ~InterfaceEvent() {}
    };

    /**
    * InterfaceEvent helper function.
    */
    template <class T>
    T GetInterfaceEvent(Eventp ev)
    {
      InterfaceEvent* interfaceEv = static_cast<InterfaceEvent*> (ev.get());
      if (!interfaceEv)
      {
        printf("E: Not an Interface event!\n");
        return 0;
      }
      T tEv = static_cast<T> (interfaceEv);
      if (!tEv)
      {
        printf("E: Wasn't listening for this %s event!\n", ev->name.c_str());
        return 0;
      }

      return tEv;
    }

    /**
    * Interface Event event.
    */
    class InterfaceInteract : public InterfaceEvent
    {
    public:
      unsigned int entityId;
      std::string actions;
      bool Contains(const char* action)
      {
        if (actions.find(action) != std::string::npos)
          return true;
        else
          return false;
      }
    public:
      InterfaceInteract() : InterfaceEvent("interface.interact", true) {}
      virtual ~InterfaceInteract() {}
    };


  } // Events namespace 
} // PT namespace 

#endif // PT_INTERFACE_EVENT_H