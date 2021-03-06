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

#include "client/gui/skillshud-gui.h"

#include <CEGUI.h>
#include <CEGUIWindowManager.h>
#include <CEGUILogger.h>

#include "client/network/network.h"

#include "client/pointer/pointer.h"
#include "common/reporter/reporter.h"

#include "client/combat/combatmanager.h"

namespace PT
{
  namespace GUI
  {
    namespace Windows
    {
      SkillsHUDWindow::SkillsHUDWindow (GUIManager* guimanager)
        : GUIWindow (guimanager)
      {
        windowName = SKILLSHUDWINDOW;
        selectedskill = 0;
      }

      SkillsHUDWindow::~SkillsHUDWindow ()
      {
        delete selectedskill;
      }

      void SkillsHUDWindow::HideWindow()
      {
        winMgr->getWindow("SkillHUD/Frame")->setVisible(false);
      }

      void SkillsHUDWindow::ShowWindow()
      {
        winMgr->getWindow("SkillHUD/Frame")->setVisible(true);
      }


      void SkillsHUDWindow::SetName (const char* name)
      {
        try
        {
          CEGUI::DefaultWindow* namewin   = (CEGUI::DefaultWindow*) winMgr->getWindow("HUD/Name");
          namewin->setText((CEGUI::String)name);
        }
        catch(CEGUI::Exception /*&e*/)
        {
        }
      } // end SetName()

      void SkillsHUDWindow::SetText (const char* name, const char* text)
      {
        CEGUI::String cname(name);
        CEGUI::String ctext(text);
        try
        {
          CEGUI::DefaultWindow* namewin   = (CEGUI::DefaultWindow*) winMgr->getWindow(cname);
          namewin->setText(ctext);
        }
        catch(CEGUI::Exception /*&e*/)
        {
        }
      } // end SetText()

      CEGUI::Window* SkillsHUDWindow::CreateSkillSlot(CEGUI::Window* parent, const CEGUI::UVector2& position, int id)
      {
        // Create a name.
        char uniquename[64];
        snprintf(uniquename, 64, "SkillHUD/quickslot_%d", id+1);
        // Create the slot
        CEGUI::Window* slot = winMgr->createWindow("Peragro/StaticImage", uniquename);
        parent->addChildWindow(slot);
        slot->setPosition(position);
        slot->setSize(CEGUI::UVector2(CEGUI::UDim(0,24.0f), CEGUI::UDim(0,24.0f)));
        slot->subscribeEvent(CEGUI::Window::EventDragDropItemDropped, CEGUI::Event::Subscriber(&SkillsHUDWindow::HandleDragDropped, this));

        return slot;
      }

      bool SkillsHUDWindow::HandleSkillSelected(const CEGUI::EventArgs& args)
      {
        using namespace CEGUI;

        const DragDropEventArgs& ddea = static_cast<const DragDropEventArgs&>(args);

        SetActiveSkill(ddea.window);

        return true;
      }

      bool SkillsHUDWindow::HandleDragDropped(const CEGUI::EventArgs& args)
      {
        using namespace CEGUI;

        const DragDropEventArgs& ddea = static_cast<const DragDropEventArgs&>(args);

        ddea.window->setProperty("FrameColours", "tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFFFFFF");
        ddea.window->addChildWindow(ddea.dragDropItem);
        return true;
      }

      bool SkillsHUDWindow::HandleDragDroppedOnSkill(const CEGUI::EventArgs& args)
      {
        using namespace CEGUI;

        const DragDropEventArgs& ddea = static_cast<const DragDropEventArgs&>(args);

        ddea.window->getParent()->addChildWindow(ddea.dragDropItem);

        // Remove the previos skill.
        winMgr->destroyWindow(ddea.window);
        return true;
      }

      int SkillsHUDWindow::GetActiveSkillId()
      {
        return selectedskill->SkillId;
      }

      void SkillsHUDWindow::SetActiveSkill(CEGUI::Window* window)
      {
        // See if its actually a skill in the slot.
        if (window->isUserStringDefined("skillid"))
        {
          // Reset the alpha on the previous window.
          CEGUI::Window* oldwindow = selectedskill->SkillWindow;
          if (oldwindow) oldwindow->setAlpha(0.5f);

          // Set the new skill active.
          window->setAlpha(1.0f);

          // Set the new window as the selected one
          selectedskill->SkillId = atoi((window->getUserString("skillid")).
                                        c_str());

          PointerLibrary::getInstance()->getCombatManager()->AttackRequest(
                                         selectedskill->SkillId);
        }
      }

      bool SkillsHUDWindow::AddSkill(int skillid)
      {
        CEGUI::Window* skillframe = winMgr->getWindow("SkillHUD/Frame");

        CEGUI::Window* freeslot = 0;
        unsigned int i = 0;

        while ((freeslot == 0) && (i < skillframe->getChildCount()))
        {
          CEGUI::Window* slot = skillframe->getChildAtIdx(i);
          i += 1;
          if (slot)
          {
            if (strcmp( "SkillHUD/Drag",slot->getName().c_str() ) )
            {
              if ((slot->getChildCount() < 1 ))
              {
                Report(PT::Debug, "AddSkill: slot %s is empty: Item added to slot.", slot->getName().c_str());
                freeslot = slot;
                //freeslot->addChildWindow(CreateSkillIcon(skillid));
                return true;
              }
            }
          }
        }

        Report(PT::Error, "AddSkill: quickbar is full!");

        return false;
      }

      bool SkillsHUDWindow::OnRootKeyDown(const CEGUI::EventArgs& e)
      {
        using namespace CEGUI;

        const KeyEventArgs& keyArgs = static_cast<const KeyEventArgs&>(e);

        CEGUI::Window* slot = 0;
        CEGUI::Window* skill = 0;

        switch (keyArgs.scancode)
        {
        case Key::F1:
          slot = winMgr->getWindow("SkillHUD/quickslot_1");
          if (slot && slot->getChildCount() > 0) skill = slot->getChildAtIdx(0);
          if (skill) SetActiveSkill(skill);
          return true;
          break;

        case Key::F2:
          slot = winMgr->getWindow("SkillHUD/quickslot_2");
          if (slot && slot->getChildCount() > 0) skill = slot->getChildAtIdx(0);
          if (skill) SetActiveSkill(skill);
          return true;
          break;

        case Key::F3:
          slot = winMgr->getWindow("SkillHUD/quickslot_3");
          if (slot && slot->getChildCount() > 0) skill = slot->getChildAtIdx(0);
          if (skill) SetActiveSkill(skill);
          return true;
          break;

        case Key::F4:
          slot = winMgr->getWindow("SkillHUD/quickslot_4");
          if (slot && slot->getChildCount() > 0) skill = slot->getChildAtIdx(0);
          if (skill) SetActiveSkill(skill);
          return true;
          break;

        case Key::F5:
          slot = winMgr->getWindow("SkillHUD/quickslot_5");
          if (slot && slot->getChildCount() > 0) skill = slot->getChildAtIdx(0);
          if (skill) SetActiveSkill(skill);
          return true;
          break;

        case Key::F6:
          slot = winMgr->getWindow("SkillHUD/quickslot_6");
          if (slot && slot->getChildCount() > 0) skill = slot->getChildAtIdx(0);
          if (skill) SetActiveSkill(skill);
          return true;
          break;

        case Key::F7:
          slot = winMgr->getWindow("SkillHUD/quickslot_7");
          if (slot && slot->getChildCount() > 0) skill = slot->getChildAtIdx(0);
          if (skill) SetActiveSkill(skill);
          return true;
          break;

        case Key::F8:
          slot = winMgr->getWindow("SkillHUD/quickslot_8");
          if (slot && slot->getChildCount() > 0) skill = slot->getChildAtIdx(0);
          if (skill) SetActiveSkill(skill);
          return true;
          break;

        case Key::F9:
          slot = winMgr->getWindow("SkillHUD/quickslot_9");
          if (slot && slot->getChildCount() > 0) skill = slot->getChildAtIdx(0);
          if (skill) SetActiveSkill(skill);
          return true;
          break;

        case Key::F10:
          slot = winMgr->getWindow("SkillHUD/quickslot_10");
          if (slot && slot->getChildCount() > 0) skill = slot->getChildAtIdx(0);
          if (skill) SetActiveSkill(skill);
          return true;
          break;

        default: return false;
        }

        return false;
      }

      bool SkillsHUDWindow::Create()
      {
        ReloadWindow();
        return true;
      }

      bool SkillsHUDWindow::ReloadWindow()
      {
        window = GUIWindow::LoadLayout ("client/entityhud.layout");
        GUIWindow::AddToRoot(window);
        window = GUIWindow::LoadLayout ("client/skillhud.layout");
        GUIWindow::AddToRoot(window);

        winMgr = cegui->GetWindowManagerPtr ();

        selectedskill = new SelectedSkill();
        selectedskill->SkillId = 0;

        counter = 0;

            //TODO
        //Load the skill icon imageset
        vfs->ChDir ("/peragro/art/skins/default/");
        cegui->GetImagesetManagerPtr()->create("/peragro/art/skins/default/images/skill.imageset", "Skill");

        // Create the skill holders.
        CEGUI::Window* skillframe = winMgr->getWindow("SkillHUD/Frame");
        for (int i=0; i<10; i++)
        {
          CreateSkillSlot(skillframe, CEGUI::UVector2(CEGUI::UDim(0,2.0f+(28*i)), CEGUI::UDim(0,2.0f)), i);
        }

        // F1-F6 keys for quickbar.
        btn = winMgr->getWindow("Root");
        btn->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&SkillsHUDWindow::OnRootKeyDown, this));

        // test.
        AddSkill(1);
        AddSkill(2);
        return true;
      }
    }
  }
}
