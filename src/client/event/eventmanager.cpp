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

#include "eventmanager.h"

#include "entityevent.h"

#include "common/util/mutex.h"

#include "client/reporter/reporter.h"

namespace PT
{
  namespace Events
  {
    EventManager::EventManager()
    {
    }

    EventManager::~EventManager()
    {
    }

    bool EventManager::Initialize()
    {

      return true;
    }

    void EventManager::AddEvent(Event* ev)
    {
      mutex.lock();

      //Report(PT::Debug, "Adding event.");

      Eventp evp(ev);
      events.push(evp);

      mutex.unlock();
    }

    void EventManager::AddListener(EventID eventId, EventHandlerCallback* handler)
    {
      Report(PT::Debug, "Adding event listener: %s", eventId.c_str());
      Listener listen;
      listen.handler = boost::shared_ptr<EventHandlerCallback>(handler);
      listen.eventId = eventId;
      listeners.push_back(listen);
    }

    void EventManager::Handle()
    {
      if (events.empty()) return;

      Eventp ev = events.front();
      if (!ev) return;
      EventID id = ev->GetEventID();

      std::vector<Listener>::iterator it;
      for(it = listeners.begin(); it != listeners.end(); ++it)
      {
        if ((id.length() == it->eventId.length()) && id == it->eventId)
        {
          if (!it->handler) continue;
          //Report(PT::Debug, "Handling event: %s", it->GetEventId());
          bool handled = it->handler->HandleEvent(ev);
          if (handled && !ev->GetBroadCast())
          {
            Report(PT::Debug, "Event handled: deleting %s", it->GetEventId());
            events.pop();
            return;
          }
        } // if
      } // for

      // The event isn't broadcasting and it's still present at the end.
      if (!ev->GetBroadCast())
        Report(PT::Warning, "No listeners for event: deleting %s", id.c_str());

      events.pop();
    }

  } // Events namespace 
} // PT namespace 

