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

#ifndef NPC_DIALOG_ANSWER_H
#define NPC_DIALOG_ANSWER_H

#include <string>

class NPCDialog;

class NPCDialogAnswer
{
private:
  NPCDialog* next_dialog;
  std::string text;

public:
  NPCDialogAnswer(NPCDialog* next_dialog, const std::string& text)
  : next_dialog(next_dialog), text(text) {}

  ~NPCDialogAnswer() {}

  NPCDialog* GetNextDialog() const { return next_dialog; }
  const std::string& GetText() const { return text; }
};

#endif // NPC_DIALOG_ANSWER_H
