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

//  !! This file was automatically generated by a network code generator   !!
//  !! Do not change this file since all changes will be overwritten later !!
//  !! Instead please change the source files here: peragro/data/generate  !!

#ifndef QUESTHANDLER_H
#define QUESTHANDLER_H

#include "common/network/nwtypes.h"

#include "common/network/questmessages.h"

#include <vector>
#include <string>

class NPCDialog;
class Character;

class QuestHandler : public MessageHandler
{
public:
  QuestHandler()
  {
  }

  char getType() { return MESSAGES::QUEST; }

  void handle(GenericMessage* msg)
  {
    char type = msg->getMsgType();
    if (type != MESSAGES::QUEST) assert("wrong message type");
    char id = msg->getMsgId();

    if (id == QUEST::NPCDIALOGANSWER) handleNpcDialogAnswer(msg);
    else if (id == QUEST::NPCSTARTDIALOG) handleNpcStartDialog(msg);
    else if (id == QUEST::NPCENDDIALOG) handleNpcEndDialog(msg);
    else if (id == QUEST::SETUPDIALOGS) handleSetupDialogs(msg);
  }

  void handleNpcDialogAnswer(GenericMessage* msg);
  void handleNpcStartDialog(GenericMessage* msg);
  void handleNpcEndDialog(GenericMessage* msg);
  void handleSetupDialogs(GenericMessage* msg);

  void SendDialog(Character* character, const NPCDialog* dialog);

  int Parse(Character* character, const std::string& function);
  int Apply(Character* character, const std::string& op, const std::vector<std::string>& args);
  std::string GetOperation(const std::string& function);
  std::vector<std::string> GetArguments(const std::string& function);
  bool IsAtom(const std::string& function);
  void RemoveSpaces(std::string& function);
};

#endif // QUESTHANDLER_H
