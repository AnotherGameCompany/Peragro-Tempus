/*
    Copyright (C) 2007 Development Team of Peragro Tempus

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
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <csutil/event.h>
#include <csutil/cfgmgr.h>
#include <csutil/cfgfile.h>
#include <csutil/cfgacc.h>

namespace PT {
  enum keyMap {
    PTKEY_UP = 0,
    PTKEY_DOWN,
    PTKEY_LEFT,
    PTKEY_RIGHT,
    PTKEY_SPACE,
    PTKEY_PAGEUP,
    PTKEY_PAGEDOWN,
    PTKEY_C,
    PTKEY_D,
    PTKEY_H,
    PTKEY_J,
    PTKEY_K,
    PTKEY_ESC,
    PTKEY_SIZE // MUST BE LAST
  };

  class Client;

  class InputManager
  {
    public:
      InputManager();
      typedef bool (Client::*tFunction)(bool down, iEvent &ev);
      bool ProcessEvent(iEvent &) const;
      void SetCallback(Client *, const char *, tFunction const);
      bool Initialize(iObjectRegistry *);
      int GetActionID(const char *);

    private:
      static const char* actionStr[];
      Client  *client;
      int actionCount;
      tFunction *functionList;
      int actionList[PTKEY_SIZE];
      int GetActionType(iEvent &) const;
  };
}
#endif
