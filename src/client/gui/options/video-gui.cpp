/*
  Copyright (C) 2005 - 2007 Development Team of Peragro Tempus

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
#include "client/gui/guimanager.h"
#include "client/gui/skinmanager.h"

#include <CEGUI.h>
#include <CEGUIWindowManager.h>
#include <CEGUILogger.h>
#include <ivaria/icegui.h>

#include "common/reporter/reporter.h"
#include "common/event/eventmanager.h"
#include "common/event/interfaceevent.h"

// MSVC doesn't define log2 :/
#include <cmath>
double log2( double n )
{
  return log( n ) / log( 2.0f );
}

namespace PT
{
  namespace GUI
  {
    namespace Windows
    {
      VideoOptionsWindow::VideoOptionsWindow(GUIManager* guiManager)
        : GUIWindow (guiManager)
      {
        windowName = VIDEOOPTIONSWINDOW;
      } // end VideoOptionsWindow()

      VideoOptionsWindow::~VideoOptionsWindow()
      {
      } // end ~VideoOptionsWindow()

      void VideoOptionsWindow::SendUpdateEvent()
      {
        PT::Events::EventManager* evmgr =
          PointerLibrary::getInstance()->getEventManager();
        evmgr->AddEvent(evmgr->CreateEvent("interface.options.video"));
      } // end SendUpdateEvent()

      void VideoOptionsWindow::SaveConfig()
      {
        SendUpdateEvent();
        app_cfg->Save();
      } // end SaveConfig()

      bool VideoOptionsWindow::Create()
      {
        // Load the layout.
        window = GUIWindow::LoadLayout("client/options/video.xml");

        app_cfg = csQueryRegistry<iConfigManager>
          (PointerLibrary::getInstance()->getObjectRegistry());
        if (!app_cfg)
        {
          Report(PT::Error, "Can't find the config manager!");
          return false;
        }

        // Set up the resolution drop list.
        CreateDropListResolution();
        btn = winMgr->getWindow("Options/Video/Resolution/DropList");
        btn->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted,
          CEGUI::Event::Subscriber(&VideoOptionsWindow::OnDropListResolution, this));

        // Set up the full screen checkbox.
        CreateFullScreenCheckBox();
        btn = winMgr->getWindow("Options/Video/Fullscreen");
        btn->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged,
          CEGUI::Event::Subscriber(&VideoOptionsWindow::OnFullScreenCheckBox, this));

        // Set up the texture quality drop list.
        CreateDropListTextureQuality();
        btn = winMgr->getWindow("Options/Video/TextureQuality/DropList");
        btn->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted,
          CEGUI::Event::Subscriber(&VideoOptionsWindow::OnDropListTextureQuality, this));

        // Set up the texture filtering drop list.
        CreateDropListTextureFiltering();
        btn = winMgr->getWindow("Options/Video/TextureFilter/DropList");
        btn->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted,
          CEGUI::Event::Subscriber(&VideoOptionsWindow::OnDropListTextureFiltering, this));

        // Set up the multisampling slider.
        CreateMultisampleSlider();
        btn = winMgr->getWindow("Options/Video/Multisample/Slider");
        btn->subscribeEvent(CEGUI::Slider::EventValueChanged,
          CEGUI::Event::Subscriber(&VideoOptionsWindow::OnMultisampleSliderChanged, this));

        // Set up the anisotrophic filtering slider.
        CreateAnisotropySlider();
        btn = winMgr->getWindow("Options/Video/Anisotropy/Slider");
        btn->subscribeEvent(CEGUI::Slider::EventValueChanged,
          CEGUI::Event::Subscriber(&VideoOptionsWindow::OnAnisotropySliderChanged, this));

        // Set up the reflection toggle drop list.
        CreateDropListReflectionsQuality();
        btn = winMgr->getWindow("Options/Video/ReflectionsQuality/DropList");
        btn->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted,
          CEGUI::Event::Subscriber(&VideoOptionsWindow::OnDropListReflectionsQuality, this));

        // Set up the reflection frame skip slider.
        CreateReflectionUpdateIntervalSlider();
        btn = winMgr->getWindow("Options/Video/ReflectionUpdateInterval/Slider");
        btn->subscribeEvent(CEGUI::Slider::EventValueChanged,
          CEGUI::Event::Subscriber(&VideoOptionsWindow::OnReflectionUpdateIntervalSliderChanged, this));

        // Set up the reflection toggle drop list.
        CreateDropListTerrainViewDistance();
        btn = winMgr->getWindow("Options/Video/TerrainViewDistance/DropList");
        btn->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted,
          CEGUI::Event::Subscriber(&VideoOptionsWindow::OnDropListTerrainViewDistance, this));

        return true;
      } // end Create()

      bool VideoOptionsWindow::OnDropListResolution(const CEGUI::EventArgs& e)
      {
        using CEGUI::String;
        btn = winMgr->getWindow("Options/Video/Resolution/DropList");
        String resStr(((CEGUI::Combobox*)btn)->getSelectedItem()->getText());

        int width = 0;
        int height = 0;
        std::stringstream ss(resStr.c_str());
        ss >> width;
        ss.ignore(512, 'x');
        ss >> height;

        if (width <= 0 || height <= 0)
        {
          Report(PT::Error, "OnDropListResolution: failed '%dx%d'", width,
            height);
          return true;
        }

        app_cfg->SetInt("Video.ScreenWidth", width);
        app_cfg->SetInt("Video.ScreenHeight", height);

        SaveConfig();
        return true;
      } // end OnDropListResolution()

      void VideoOptionsWindow::CreateDropListResolution()
      {
        using CEGUI::String;
        btn = winMgr->getWindow("Options/Video/Resolution/DropList");

        int width = app_cfg->GetInt("Video.ScreenWidth", 1024);
        int height = app_cfg->GetInt("Video.ScreenHeight", 768);

        std::stringstream ss;
        ss << width;
        ss << "x";
        ss << height;

        ((CEGUI::Combobox*)btn)->setText(ss.str());

        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"800x600"));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"1024x768"));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"1152x864"));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"1440x960"));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"1280x1024"));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"1600x1200"));

        ((CEGUI::Combobox*)btn)->setReadOnly(true);
      } // end CreateDropListResolution()

      bool VideoOptionsWindow::OnFullScreenCheckBox(const CEGUI::EventArgs& e)
      {
        btn = winMgr->getWindow("Options/Video/Fullscreen");
        bool fs = ((CEGUI::Checkbox*)btn)->isSelected();

        app_cfg->SetBool("Video.FullScreen", fs);
        SaveConfig();
        return true;
      } // end OnFullScreenCheckBox()

      void VideoOptionsWindow::CreateFullScreenCheckBox()
      {
        btn = winMgr->getWindow("Options/Video/Fullscreen");

        bool fs = app_cfg->GetBool("Video.FullScreen", false);

        ((CEGUI::Checkbox*)btn)->setSelected(fs);
      } // end CreateFullScreenCheckBox()

      bool VideoOptionsWindow::OnDropListTextureQuality(const CEGUI::EventArgs& e)
      {
        btn = winMgr->getWindow("Options/Video/TextureQuality/DropList");
        uint id = ((CEGUI::Combobox*)btn)->getSelectedItem()->getID();

        int quality = 0;
        switch(id)
        {
        case 0: // Normal
          quality = 0;
          break;
        case 1: // Low
          quality = 1;
          break;
        case 2: // Very Low
          quality = 2;
          break;
        case 3: // Lowest
          quality = 3;
          break;

        default:
          Report(PT::Error, "OnDropListTexture: failed %d", id);
        }

        app_cfg->SetInt("Video.OpenGL.TextureDownsample", quality);
        SaveConfig();
        return true;
      } // end OnDropListTextureQuality()

      void VideoOptionsWindow::CreateDropListTextureQuality()
      {

        btn = winMgr->getWindow("Options/Video/TextureQuality/DropList");

        int quality = app_cfg->GetInt("Video.OpenGL.TextureDownsample", 0);

        switch(quality)
        {
        case 0:
          ((CEGUI::Combobox*)btn)->setText("Normal");
          break;
        case 1:
          ((CEGUI::Combobox*)btn)->setText("Low");
          break;
        case 2:
          ((CEGUI::Combobox*)btn)->setText("Very Low");
          break;
        case 3:
          ((CEGUI::Combobox*)btn)->setText("Lowest");
          break;
        default:
          ((CEGUI::Combobox*)btn)->setText("Custom");
        }

        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"Normal", 0));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"Low", 1));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"Very Low", 2));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"Lowest", 3));

        ((CEGUI::Combobox*)btn)->setReadOnly(true);

      } // end CreateDropListTextureQuality()

      bool VideoOptionsWindow::OnDropListTextureFiltering(const CEGUI::EventArgs& e)
      {
        using CEGUI::String;
        btn = winMgr->getWindow("Options/Video/TextureFilter/DropList");

        String filter(((CEGUI::Combobox*)btn)->getSelectedItem()->getText());
        if (filter.empty()) return true;

        app_cfg->SetStr("Video.OpenGL.TextureFilter", filter.c_str());
        SaveConfig();
        return true;
      } // end OnDropListTextureFilter()

      void VideoOptionsWindow::CreateDropListTextureFiltering()
      {
        using CEGUI::String;
        btn = winMgr->getWindow("Options/Video/TextureFilter/DropList");

        const char* filter = app_cfg->GetStr("Video.OpenGL.TextureFilter", "trilinear");
        ((CEGUI::Combobox*)btn)->setText(filter);

        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"none"));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"nearest"));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"bilinear"));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"trilinear"));

        ((CEGUI::Combobox*)btn)->setReadOnly(true);

      } // end CreateDropListTextureFilter()

      bool VideoOptionsWindow::OnMultisampleSliderChanged(const CEGUI::EventArgs &e)
      {
        btn = winMgr->getWindow("Options/Video/Multisample/Slider");
        float AA = pow(2.0f, ceil(((CEGUI::Slider*)btn)->getCurrentValue()));

        std::stringstream ss;
        ss << AA;
        ss << "x";

        btn = winMgr->getWindow("Options/Video/Multisample/Value");
        btn->setText(ss.str());

        app_cfg->SetFloat("Video.OpenGL.MultiSamples", AA);
        SaveConfig();
        return true;
      } // end OnMultisampleSliderChanged()

      void VideoOptionsWindow::CreateMultisampleSlider()
      {
        btn = winMgr->getWindow("Options/Video/Multisample/Slider");
        float AA = log2(app_cfg->GetFloat("Video.OpenGL.MultiSamples", 0.0f));

        ((CEGUI::Slider*)btn)->setCurrentValue(AA);
        CEGUI::EventArgs e;
        OnMultisampleSliderChanged(e);
      } // end CreateMultisampleSlider()

      bool VideoOptionsWindow::OnAnisotropySliderChanged(const CEGUI::EventArgs &e)
      {
        btn = winMgr->getWindow("Options/Video/Anisotropy/Slider");
        float AF = pow(2.0f, ceil(((CEGUI::Slider*)btn)->getCurrentValue()));

        std::stringstream ss;
        ss << AF;
        ss << "x";

        btn = winMgr->getWindow("Options/Video/Anisotropy/Value");
        btn->setText(ss.str());

        app_cfg->SetFloat("Video.OpenGL.TextureFilterAnisotropy", AF);
        SaveConfig();
        return true;
      } // end OnAnisotropySliderChanged()

      void VideoOptionsWindow::CreateAnisotropySlider()
      {
        btn = winMgr->getWindow("Options/Video/Anisotropy/Slider");
        float AA = log2(app_cfg->GetFloat("Video.OpenGL.TextureFilterAnisotropy", 1.0f));

        ((CEGUI::Slider*)btn)->setCurrentValue(AA);
        CEGUI::EventArgs e;
        OnAnisotropySliderChanged(e);
      } // end CreateAnisotropySlider()

      bool VideoOptionsWindow::OnDropListReflectionsQuality(const CEGUI::EventArgs& e)
      {
        btn = winMgr->getWindow("Options/Video/ReflectionsQuality/DropList");
        uint id = ((CEGUI::Combobox*)btn)->getSelectedItem()->getID();

        int quality = 0;
        switch(id)
        {
        case 0: // Normal
          quality = 0;
          break;
        case 1: // Low
          quality = 1;
          break;
        case 2: // Very Low
          quality = 2;
          break;
        case 3: // Lowest
          quality = 3;
          break;

        default:
          Report(PT::Error, "OnDropListReflectionsQuality: failed %d", id);
        }

        app_cfg->SetInt("RenderManager.Reflections.Downsample", quality);
        app_cfg->SetInt("RenderManager.Refractions.Downsample", quality);
        SaveConfig();
        return true;
      } // end OnDropListReflections()

      void VideoOptionsWindow::CreateDropListReflectionsQuality()
      {
        btn = winMgr->getWindow("Options/Video/ReflectionsQuality/DropList");

        int quality = app_cfg->GetInt("RenderManager.Reflections.Downsample", 0);

        switch(quality)
        {
        case 0:
          ((CEGUI::Combobox*)btn)->setText("Normal");
          break;
        case 1:
          ((CEGUI::Combobox*)btn)->setText("Low");
          break;
        case 2:
          ((CEGUI::Combobox*)btn)->setText("Very Low");
          break;
        case 3:
          ((CEGUI::Combobox*)btn)->setText("Lowest");
          break;
        default:
          ((CEGUI::Combobox*)btn)->setText("Custom");
        }

        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"Normal", 0));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"Low", 1));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"Very Low", 2));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"Lowest", 3));

        ((CEGUI::Combobox*)btn)->setReadOnly(true);

      } // end CreateDropListReflections()

      bool VideoOptionsWindow::OnReflectionUpdateIntervalSliderChanged(const CEGUI::EventArgs &e)
      {
        btn = winMgr->getWindow("Options/Video/ReflectionUpdateInterval/Slider");
        int interval = static_cast<int>(((CEGUI::Slider*)btn)->getCurrentValue());

        std::stringstream ss;
        ss << interval;

        btn = winMgr->getWindow("Options/Video/ReflectionUpdateInterval/Value");
        btn->setText(ss.str());

        app_cfg->SetInt("RenderManager.Reflections.UpdateInterval", interval);
        SaveConfig();
        return true;
      } // end OnReflectionSkipSliderChanged()

      void VideoOptionsWindow::CreateReflectionUpdateIntervalSlider()
      {
        btn = winMgr->getWindow("Options/Video/ReflectionUpdateInterval/Slider");
        int interval = app_cfg->GetInt("RenderManager.Reflections.UpdateInterval", 30);

        ((CEGUI::Slider*)btn)->setCurrentValue(static_cast<float>(interval));
        CEGUI::EventArgs e;
        OnReflectionUpdateIntervalSliderChanged(e);
      } // end CreateReflectionSkipSlider()

      bool VideoOptionsWindow::OnDropListTerrainViewDistance(const CEGUI::EventArgs& e)
      {
        btn = winMgr->getWindow("Options/Video/TerrainViewDistance/DropList");
        uint id = ((CEGUI::Combobox*)btn)->getSelectedItem()->getID();

        int size = 3;
        switch(id)
        {
        case 3: // 3x3
          size = 3;
          break;
        case 5: // 5x5
          size = 5;
          break;
        case 7: // 7x7
          size = 7;
          break;

        default:
          Report(PT::Error, "OnDropListTerrainViewDistance: failed %d", id);
        }

        app_cfg->SetInt("Peragro.Terrain.GridSize", size);
        SaveConfig();
        return true;
      } // end OnDropListReflections()

      void VideoOptionsWindow::CreateDropListTerrainViewDistance()
      {
        btn = winMgr->getWindow("Options/Video/TerrainViewDistance/DropList");

        int size = app_cfg->GetInt("Peragro.Terrain.GridSize", 3);

        switch(size)
        {
        case 3:
          ((CEGUI::Combobox*)btn)->setText("3x3");
          break;
        case 5:
          ((CEGUI::Combobox*)btn)->setText("5x5");
          break;
        case 7:
          ((CEGUI::Combobox*)btn)->setText("7x7");
          break;
        default:
          size= 3;
          ((CEGUI::Combobox*)btn)->setText("3x3");
        }

        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"3x3", 3));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"5x5", 5));
        ((CEGUI::Combobox*)btn)->addItem(
          new CEGUI::ListboxTextItem((CEGUI::utf8*)"7x7", 7));

        ((CEGUI::Combobox*)btn)->setReadOnly(true);

      } // end CreateDropListReflections()

    } // Windows namespace
  } // GUI namespace
} // PT namespace

