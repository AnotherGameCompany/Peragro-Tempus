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

#include "client/gui/gui.h"

#include "CEGUI.h"
#include "CEGUIWindowManager.h" 
#include "CEGUILogger.h"

#include "client/network/network.h"
#include "client/gui/guimanager.h"

#include "client/reporter/reporter.h"

LoginWindow::LoginWindow(GUIManager* guimanager)
: GUIWindow (guimanager)
{
}

LoginWindow::~LoginWindow()
{
}

bool LoginWindow::LoginButtonPressed(const CEGUI::EventArgs& e) 
{
  // Get the login window and disable it
  GUIWindow::DisableWindow();

  LoginRequestMessage answer_msg;
  CEGUI::String login = GetLogin();
  CEGUI::String password = GetPassword();
  if (login.empty() || password.empty()) 
  {
    GUIWindow::EnableWindow();
    return true;
  }
  PointerLibrary::getInstance()->getClient()->login(login.c_str(), password.c_str());

  return true;
}

bool LoginWindow::RegisterButtonPressed(const CEGUI::EventArgs& e)
{
  RegisterRequestMessage answer_msg;
  CEGUI::String login = GetLogin();
  CEGUI::String password = GetPassword();
  if (login.empty() || password.empty()) return true;
  answer_msg.setUsername(ptString(login.c_str(), login.length()));
  answer_msg.setPassword(password.c_str());
  network->send(&answer_msg);

  return true; 
}

void LoginWindow::ShowWindow() 
{
  GUIWindow::ShowWindow();
  CEGUI::Window * wnd = winMgr->getWindow("LoginUI/LoginEditBox");
  wnd->activate();
}

CEGUI::String LoginWindow::GetLogin() 
{
  return winMgr->getWindow("LoginUI/LoginEditBox")->getText();
}

CEGUI::String LoginWindow::GetPassword() 
{
  return winMgr->getWindow("LoginUI/PasswordEditBox")->getText();
}

void LoginWindow::SaveConfig()
{
  app_cfg->Save();
}

bool LoginWindow::LoginTextAccepted(const CEGUI::EventArgs &e)
{
  if (!winMgr->getWindow("LoginUI/Frame")->isDisabled())
  {
    CEGUI::Window * wnd = winMgr->getWindow("LoginUI/PasswordEditBox");
    wnd->activate();
  }
  return true;
}

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
}

bool LoginWindow::OnCheckBox(const CEGUI::EventArgs& e) 
{
  btn = winMgr->getWindow("LoginUI/RemeberLogin");
  bool fs = ((CEGUI::Checkbox*)btn)->isSelected();
  CEGUI::String login = GetLogin();
  const char* string;

  if (fs) 
    string = login.c_str();
  else
    string = "";

  app_cfg->SetStr("Client.Login", string);
  SaveConfig();
  return true;
}

void LoginWindow::CreateCheckBox()
{
  btn = winMgr->getWindow("LoginUI/RemeberLogin");

  const char* login = app_cfg->GetStr("Client.Login");

  bool selected;
  if (!strcmp(login, ""))
    selected = false;
  else
    selected = true;

  ((CEGUI::Checkbox*)btn)->setSelected(selected);

  // Set the login
  btn = winMgr->getWindow("LoginUI/LoginEditBox");
  btn->setText(login);
}

void LoginWindow::CreateGUIWindow()
{
  GUIWindow::CreateGUIWindow ("login.xml");

  winMgr = cegui->GetWindowManagerPtr ();

  // Get the root window
  rootwindow = winMgr->getWindow("LoginUI/Frame");

  app_cfg =  csQueryRegistry<iConfigManager> (PointerLibrary::getInstance()->getClient()->GetObjectRegistry());
  if (!app_cfg) 
  {
    Report(PT::Error, "Can't find the config manager!"); 
    return;
  }

  // Setup masking on the Password editbox.
  btn = winMgr->getWindow("LoginUI/PasswordEditBox");
  ((CEGUI::Editbox*)btn)->setMaskCodePoint('*'); //0x359
  ((CEGUI::Editbox*)btn)->setTextMasked(true);

  // Register the button events.
  btn = winMgr->getWindow("LoginUI/PasswordEditBox");
  btn->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&LoginWindow::PasswordTextAccepted, this));

  btn = winMgr->getWindow("LoginUI/LoginEditBox");
  btn->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&LoginWindow::LoginTextAccepted, this));

  btn = winMgr->getWindow("LoginUI/Login_Button");
  btn->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LoginWindow::LoginButtonPressed, this));

  btn = winMgr->getWindow("LoginUI/Register_Button");
  btn->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&LoginWindow::RegisterButtonPressed, this));

  // Set up the Fullscreen checkbox.
  CreateCheckBox();
  btn = winMgr->getWindow("LoginUI/RemeberLogin");
  btn->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged, CEGUI::Event::Subscriber(&LoginWindow::OnCheckBox, this));

}
