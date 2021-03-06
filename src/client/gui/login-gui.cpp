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

#include "client/gui/login-gui.h"

#include <CEGUI.h>
#include <CEGUIWindowManager.h>
#include <CEGUILogger.h>

#include <csutil/csstring.h>

#include "client/network/network.h"
#include "client/state/statemanager.h"
#include "common/version.h"

#include "common/reporter/reporter.h"
#include "client/pointer/pointer.h"

#include "client/gui/confirmdialog-gui.h"
#include "client/gui/servers-gui.h"
#include "client/gui/guimanager.h"

#include "client/user/usermanager.h"

namespace PT
{
  namespace GUI
  {
    namespace Windows
    {

      LoginWindow::LoginWindow(GUIManager* guimanager)
        : GUIWindow (guimanager)
      {
        windowName = LOGINWINDOW;
      } // end LoginWindow()

      LoginWindow::~LoginWindow()
      {
      } // end ~LoginWindow()

      bool LoginWindow::LoginButtonPressed(const CEGUI::EventArgs& e)
      {
        // Get the login window and disable it
        GUIWindow::DisableWindow();
        ServerWindow* serverWindow =
          guimanager->GetWindow<ServerWindow>(SERVERWINDOW);
        serverWindow->DisableWindow();

        SaveConfig();

        LoginRequestMessage answer_msg;
        CEGUI::String login = GetLogin();
        CEGUI::String password = GetPassword();
        if (login.empty() || password.empty())
        {
          OkDialogWindow* dialog = new OkDialogWindow(guimanager);
          dialog->SetText("You must enter username and password");
          GUIWindow::EnableWindow();
          serverWindow->EnableWindow();
          return true;
        }
        else
        {
          if (!network->isRunning())
          {
            // Connect to selected server
            ConnectRequestMessage msg(CLIENTVERSION);
            network->setServerAddress(serverWindow->GetServerHost(),
              serverWindow->GetServerPort());
            if (! network->init())
            {
              //unable to etablish tcp connection
              GUIWindow::EnableWindow();
              serverWindow->EnableWindow();
              OkDialogWindow* dialog = new OkDialogWindow(guimanager);
              dialog->SetText("Unable to connect to server!");
              return true;
            }
            network->send(&msg);
          }
        }
        if (login.length() > 255)
        {
          GUIWindow::EnableWindow();
          serverWindow->EnableWindow();
          OkDialogWindow* dialog = new OkDialogWindow(guimanager);
          dialog->SetText("Username is too long");
          return true;
        }
        if (password.length() > 255)
        {
          GUIWindow::EnableWindow();
          serverWindow->EnableWindow();
          OkDialogWindow* dialog = new OkDialogWindow(guimanager);
          dialog->SetText("Password is too long");
          return true;
        }
        PointerLibrary::getInstance()->getUserManager()->
          Login(login.c_str(), password.c_str());

        return true;
      } // end LoginButtonPressed()

      bool LoginWindow::RegisterButtonPressed(const CEGUI::EventArgs& e)
      {
        // Connect to selected server
        ConnectRequestMessage msg(CLIENTVERSION);
        ServerWindow* serverWindow =
          guimanager->GetWindow<ServerWindow>(SERVERWINDOW);
        network->setServerAddress(serverWindow->GetServerHost(),
          serverWindow->GetServerPort());
        if (! network->init())
        {
          //unable to etablish tcp connection
          GUIWindow::EnableWindow();
          serverWindow->EnableWindow();
          OkDialogWindow* dialog = new OkDialogWindow(guimanager);
          dialog->SetText("Unable to connect to server!");
          return true;
        }
        network->send(&msg);

        RegisterRequestMessage answer_msg;
        CEGUI::String login = GetLogin();
        CEGUI::String password = GetPassword();
        if (login.empty() || password.empty())
        {
          OkDialogWindow* dialog = new OkDialogWindow(guimanager);
          dialog->SetText("You must enter username and password");
          return true;
        }
        if (login.length() > 255)
        {
          OkDialogWindow* dialog = new OkDialogWindow(guimanager);
          dialog->SetText("Username is too long");
          return true;
        }
        if (password.length() > 255)
        {
          OkDialogWindow* dialog = new OkDialogWindow(guimanager);
          dialog->SetText("Password is too long");
          return true;
        }
        answer_msg.setUsername(ptString(login.c_str(), login.length()));
        answer_msg.setPassword(password.c_str());
        network->send(&answer_msg);

        return true;
      } // end RegisterButtonPressed()

      void LoginWindow::ShowWindow()
      {
        GUIWindow::ShowWindow();
        CEGUI::Window * wnd = winMgr->getWindow("LoginUI/LoginEditBox");
        wnd->activate();
        //if (guimanager->IsInitialized())
        //{
        UpdateLogin();
        //}
      } // end ShowWindow()

      CEGUI::String LoginWindow::GetLogin()
      {
        return winMgr->getWindow("LoginUI/LoginEditBox")->getText();
      } // end GetLogin()

      CEGUI::String LoginWindow::GetPassword()
      {
        return winMgr->getWindow("LoginUI/PasswordEditBox")->getText();
      } // end GetPassword()

      void LoginWindow::SaveConfig()
      {
        btn = winMgr->getWindow("LoginUI/RemeberLogin");
        bool fs = ((CEGUI::Checkbox*)btn)->isSelected();
        CEGUI::String login = GetLogin();
        const char* string;
        unsigned int integer;

        if (fs)
          string = login.c_str();
        else
          string = "";

        ServerWindow* serverWindow =
          guimanager->GetWindow<ServerWindow>(SERVERWINDOW);
        app_cfg->
          SetStr("Peragro.Server["+serverWindow->GetServerName()+"].Login",
            string);

        if (serverWindow->IsCustom())
        {
          string=serverWindow->GetServerHost().GetData();
          app_cfg->SetStr("Peragro.Server.Custom", string);
          integer=serverWindow->GetServerPort();
          app_cfg->SetInt("Peragro.Server.Customport", integer);
        }
        app_cfg->
          SetStr("Peragro.Server.LastUsed", serverWindow->GetServerName());
        app_cfg->Save();
      } // end SaveConfig()

      bool LoginWindow::LoginTextAccepted(const CEGUI::EventArgs &e)
      {
        if (!winMgr->getWindow("LoginUI/Frame")->isDisabled())
        {
          CEGUI::Window * wnd = winMgr->getWindow("LoginUI/PasswordEditBox");
          wnd->activate();
        }
        return true;
      } // end LoginTextAccepted()

      bool LoginWindow::PasswordTextAccepted(const CEGUI::EventArgs &e)
      {
        if (!winMgr->getWindow("LoginUI/Frame")->isDisabled())
        {
          CEGUI::Window * log = winMgr->getWindow("LoginUI/LoginEditBox");
          CEGUI::Window * reg = winMgr->getWindow("LoginUI/PasswordEditBox");
          if (log->getText().empty())
          {
            log->activate();
          }
          else
          {
            if (!reg->getText().empty())
            {
              LoginButtonPressed(e);
            }
          }
        }
        return true;
      } // end PasswordTextAccepted()

      bool LoginWindow::OnCheckBox(const CEGUI::EventArgs& e)
      {
        SaveConfig();
        return true;
      } // end OnCheckBox()

      void LoginWindow::UpdateLogin()
      {
        CEGUI::Window *passwordEditBox;
        ServerWindow* serverWindow =
          guimanager->GetWindow<ServerWindow>(SERVERWINDOW);
        const char* login = app_cfg->
          GetStr("Peragro.Server["+serverWindow->GetServerName()+"].Login");
        btn = winMgr->getWindow("LoginUI/LoginEditBox");
        btn->setText(login);
        passwordEditBox = winMgr->getWindow("LoginUI/PasswordEditBox");
        passwordEditBox->setText("");

        btn = winMgr->getWindow("LoginUI/RemeberLogin");
        bool selected;
        if (!strcmp(login, ""))
        {
          selected = false;
          winMgr->getWindow("LoginUI/LoginEditBox")->activate();
        }
        else
        {
          selected = true;
          winMgr->getWindow("LoginUI/PasswordEditBox")->activate();
        }
        ((CEGUI::Checkbox*)btn)->setSelected(selected);
      } // end UpdateLogin()

      bool LoginWindow::Create()
      {
        ReloadWindow();
        return true;
      } // end Create()

      bool LoginWindow::ReloadWindow()
      {
        window = GUIWindow::LoadLayout ("client/login.layout");
        GUIWindow::AddToRoot(window);

        winMgr = cegui->GetWindowManagerPtr ();

        app_cfg =  csQueryRegistry<iConfigManager>
          (PointerLibrary::getInstance()->getObjectRegistry());
        if (!app_cfg)
        {
          Report(PT::Error, "Can't find the config manager!");
          return false;
        }

        // Setup masking on the Password editbox.
        btn = winMgr->getWindow("LoginUI/PasswordEditBox");
        ((CEGUI::Editbox*)btn)->setMaskCodePoint('*'); //0x359
        ((CEGUI::Editbox*)btn)->setTextMasked(true);

        // Register the button events.
        btn = winMgr->getWindow("LoginUI/PasswordEditBox");
        btn->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
          CEGUI::Event::Subscriber(&LoginWindow::PasswordTextAccepted, this));

        btn = winMgr->getWindow("LoginUI/LoginEditBox");
        btn->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
          CEGUI::Event::Subscriber(&LoginWindow::LoginTextAccepted, this));

        btn = winMgr->getWindow("LoginUI/Login_Button");
        btn->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&LoginWindow::LoginButtonPressed, this));

        btn = winMgr->getWindow("LoginUI/Register_Button");
        btn->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&LoginWindow::RegisterButtonPressed, this));

        // Set up the remember-login checkbox.
        btn = winMgr->getWindow("LoginUI/RemeberLogin");
        btn->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged,
          CEGUI::Event::Subscriber(&LoginWindow::OnCheckBox, this));


        return true;
      } // end ReloadWindow()

    } // Windows namespace
  } // GUI namespace
} // PT namespace

