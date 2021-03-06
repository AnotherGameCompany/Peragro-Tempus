/*
    Copyright (C) 2006 Development Team of Peragro Tempus

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

#ifndef EVENTS_WORKERHOME
#define EVENTS_WORKERHOME

#include <vector>
#include "worker.h"

class EventEngine;

/**
 * This class knows all worker instances.
 */
class EventWorkerHome
{
private:
  EventEngine* engine;
  std::vector<EventWorker*> workers;

public:
  EventWorkerHome(EventEngine* engine) : engine(engine) {}

  EventWorker* addWorker();

  void start()
  {
    for (size_t i = 0; i<workers.size(); i++)
    {
      workers[i]->Begin();
    }
  }

  void stop()
  {
    for (size_t i = 0; i<workers.size(); i++)
    {
      workers[i]->Kill();
    }
  }
};

#endif // EVENTS_WORKERHOME
