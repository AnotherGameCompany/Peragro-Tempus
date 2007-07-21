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

#ifndef _MONITORABLE_H_
#define _MONITORABLE_H_

#include "monitor.h"
#include "mutex.h"

template<class T>
class ptMonitorable
{
private:
  ptMonitor<T> ref;

protected:
  ptMonitorable() { ref.set((T*)this); }
  virtual ~ptMonitorable() {};

public:
  const ptMonitor<T>& getRef() const { return ref; }

  T* getLock() const
  {
    T* const me = (T*) this;
    return me;
  }

  void freeLock()
  {
  }

};

#endif // _MONITORABLE_H_
