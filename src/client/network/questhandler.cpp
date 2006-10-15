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

#include "client/network/network.h"
#include "client/gui/gui.h"
#include "client/gui/guimanager.h"

void QuestHandler::handleNpcDialog(GenericMessage* msg)
{
  NpcDialogMessage dialog_msg;
  dialog_msg.deserialise(msg->getByteStream());
  printf("QuestHandler: Added Dialog %d with %d answers.\n", dialog_msg.getDialogId(), dialog_msg.getAnswersCount());
  guimanager = PointerLibrary::getInstance()->getGUIManager();
  printf("---------------------------\n");
  guimanager->GetNpcDialogWindow()->AddDialog(dialog_msg.getDialogId(), dialog_msg.getDialogText());

  for (int i=0; i<dialog_msg.getAnswersCount(); i++)
  {
    printf("QuestHandler: Added answer %d: %s\n", dialog_msg.getAnswerId(i), dialog_msg.getAnswerText(i));
    guimanager->GetNpcDialogWindow()->AddAnswer(dialog_msg.getAnswerId(i), dialog_msg.getAnswerText(i));
  }
  printf("---------------------------\n");
}
