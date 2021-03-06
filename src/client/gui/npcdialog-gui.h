/*
    Copyright (C) 2005 Development Team of Peragro Tempus

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General public License for more details.

    You should have received a copy of the GNU General public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef NPCDIALOG_GUI_H
#define NPCDIALOG_GUI_H

#include "base-gui.h"

#define NPCDIALOGWINDOW "NpcDialog/Frame"

namespace PT
{
  namespace GUI
  {
    namespace Windows
    {
      class NpcDialogWindow : public GUIWindow
      {
      private:
        bool newDialog;
        void ClearAnswers();

        unsigned int dialogId;
        bool OnCloseButton(const CEGUI::EventArgs& args);
        bool OnAnswer(const CEGUI::EventArgs& args);

      public:
        NpcDialogWindow(GUIManager* guimanager);
        virtual ~NpcDialogWindow();
        bool Create();
        bool ReloadWindow();

        void SetName(const std::string& name);
        void AddDialog(unsigned int dialogId, const std::string& dialog);
        void AddAnswer(unsigned int number, const std::string& answer);
        void SelectFirstAnswer();
        void ShowWindow();
      };

    } // Windows namespace
  } // GUI namespace
} // PT namespace

#endif // NPCDIALOG_GUI_H
