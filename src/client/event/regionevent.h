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

#ifndef PT_REGION_EVENT_H
#define PT_REGION_EVENT_H

#include <cssysdef.h>

#include "client/event/event.h"

namespace PT
{
  namespace Events
  {
		/**
		* RegionEvent helper function.
		*/
		template <class T>
		T GetRegionEvent(Eventp ev)
		{
			RegionEvent* regionEv = static_cast<RegionEvent*> (ev.px);
			if (!regionEv)
			{
				printf("E: Not a Region event!\n");
				return 0;
			}
			T tEv = static_cast<T> (regionEv);
			if (!tEv)
			{
				printf("E: Wasn't listening for this %s event!\n", ev->name.c_str());
				return 0;
			}

			return tEv;
		}

		/**
		 * Region event base class.
		 */
    class RegionEvent : public Event
    {
		public:
			RegionEvent(EventID name, bool broadCast) : Event(name, broadCast) {}
			virtual ~RegionEvent() {}
    };

		/**
		 * Chat say event.
		 */
    class RegionLoadEvent : public RegionEvent
    {
		public:
			std::string regionName;

    public:
      RegionLoadEvent() : RegionEvent("RegionLoadEvent", true) {}
      virtual ~RegionLoadEvent() {}
    };

  } // Events namespace 
} // PT namespace 

#endif // PT_REGION_EVENT_H
