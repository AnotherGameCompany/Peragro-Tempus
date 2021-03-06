/*
    Copyright (C) 2009 Development Team of Peragro Tempus

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

#ifndef CHARNEW_GUI_H
#define CHARNEW_GUI_H

#include "base-gui.h"

#define CREATECHARWINDOW "CharNew/Frame"

namespace PT
{
  namespace GUI
  {
    namespace Windows
    {
      class CreateCharWindow : public GUIWindow
      {
      private:
        /// Returns the character name.
        CEGUI::String GetNewCharName();

        /// Clears the character name textbox.
        void ClearNewCharName();

        /// Returns to the character menu.
        bool CancelButton(const CEGUI::EventArgs& e);

        /// Submits new character to the server.
        bool CreateButton(const CEGUI::EventArgs& e);

        /// Updates new Avatar's model on selection
        bool OnAvatarTemplateSelect(const CEGUI::EventArgs& e);

        void ToggleNewWindow(bool visible);

      public:
        CreateCharWindow(GUIManager* guimanager);
        virtual ~CreateCharWindow();
        bool Create();
        bool ReloadWindow();
        bool CreateCharacter(const CEGUI::EventArgs& e);
        void EmptyAvatarList();
        void EmptyAvatarInfo();
        void SetInfoTextBox(const std::string infotext );
        void AddModel(unsigned int avatarId, const char* avatarName);

        void ShowWindow();

      };

    } // Windows namespace
  } // GUI namespace
} // PT namespace

#endif // CHARNEW_GUI_H
