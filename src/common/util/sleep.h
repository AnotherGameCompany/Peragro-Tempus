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

#ifndef SLEEP_H
#define SLEEP_H

#ifdef WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#else
  #include <unistd.h>
  #include <time.h>
#endif

inline void pt_sleep(size_t ms)
{
  #ifdef WIN32
    Sleep(DWORD(ms));
  #else
    timespec sleeptime;
    sleeptime.tv_sec = ms/1000;
    sleeptime.tv_nsec = (ms%1000)*1000000;
    nanosleep(&sleeptime, 0);
  #endif
}

#endif // SLEEP_H
