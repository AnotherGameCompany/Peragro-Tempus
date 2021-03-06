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

#ifndef MUTEX_H
#define MUTEX_H

#include <boost/thread/mutex.hpp>

typedef boost::mutex Mutex;

typedef boost::mutex::scoped_lock ptScopedMutex;

class ptScopedMutexCopyAble : public boost::unique_lock<Mutex>
{
public:
  ptScopedMutexCopyAble(Mutex& m_):
    boost::unique_lock<Mutex>(m_)
  {
  }

  ptScopedMutexCopyAble(const ptScopedMutexCopyAble& s):
    boost::unique_lock<Mutex>()
  {
    swap(*const_cast<ptScopedMutexCopyAble*>(&s));
  }
};

#endif // MUTEX_H
