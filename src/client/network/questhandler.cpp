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

#include "client/reporter/reporter.h"

void QuestHandler::handleNpcDialog(GenericMessage* msg)
{
  NpcDialogMessage dialog_msg;
  dialog_msg.deserialise(msg->getByteStream());
  Report(PT::Debug, "QuestHandler: Added Dialog %d with %d answers.", dialog_msg.getDialogId(), dialog_msg.getAnswersCount());
  PT::GUI::GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
  Report(PT::Debug, "---------------------------");
  if(dialog_msg.getDialogText()==0)
    dialog_msg.setDialogText("ERROR: handleNpcDialog: DialogText is zero\n");
  PT::GUI::Windows::NpcDialogWindow* npcWindow = (PT::GUI::Windows::NpcDialogWindow*)guimanager->GetWindow(NPCDIALOGWINDOW);
  npcWindow->AddDialog(dialog_msg.getDialogId(), dialog_msg.getDialogText());

  for (int i=0; i<dialog_msg.getAnswersCount(); i++)
  {
    if(dialog_msg.getAnswerText(i)==0)
      dialog_msg.setAnswerText(i, "ERROR: handleNpcDialog: getAnswerText is zero\n");
    Report(PT::Debug, "Added answer %d: %s", dialog_msg.getAnswerId(i), dialog_msg.getAnswerText(i));
    npcWindow->AddAnswer(dialog_msg.getAnswerId(i), dialog_msg.getAnswerText(i));
  }
  Report(PT::Debug, "---------------------------");
}

void QuestHandler::handleNpcEndDialog(GenericMessage* msg)
{
  PT::GUI::GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
  PT::GUI::Windows::NpcDialogWindow* npcWindow = (PT::GUI::Windows::NpcDialogWindow*)guimanager->GetWindow(NPCDIALOGWINDOW);
  npcWindow->HideWindow();
}
