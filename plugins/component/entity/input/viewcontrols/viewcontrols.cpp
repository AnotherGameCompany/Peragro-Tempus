/*
    Copyright (C) 2008 Development Team of Peragro Tempus

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

#include <cssysdef.h>
#include "plugins/component/entity/input/viewcontrols/viewcontrols.h"

#include <iutil/objreg.h>
#include <iutil/cfgmgr.h>

#include <physicallayer/pl.h>
#include <physicallayer/propfact.h>
#include <physicallayer/propclas.h>
#include <propclass/actormove.h>
#include <propclass/linmove.h>

#include <propclass/defcam.h>
#include <iengine/camera.h>

#include "client/event/eventmanager.h"
#include "client/event/entityevent.h"
#include "client/event/inputevent.h"

#include "client/entity/entity.h"

#include "client/reporter/reporter.h"
#include "client/pointer/pointer.h"

CS_IMPLEMENT_PLUGIN
IMPLEMENT_COMPONENTFACTORY (ViewControls, "peragro.entity.input.viewcontrols")

ComponentViewControls::ComponentViewControls(iObjectRegistry* object_reg) :
	scfImplementationType (this, object_reg)
{
  cameraDistance = 3.0f;
  invertYAxis = false;
  minDistance = 50.0f;
  minFPS = 20.0f;
  maxFPS = 60.0f;
}

ComponentViewControls::~ComponentViewControls()
{
}

bool ComponentViewControls::Initialize (PointerLibrary* pl, PT::Entity::Entity* ent)
{
  pointerlib = pl;
  entity = ent;

  camera = CEL_QUERY_PROPCLASS_ENT(entity->GetCelEntity(), iPcDefaultCamera);

  using namespace PT::Events;
  EventManager* evmgr = pointerlib->getEventManager();

  REGISTER_LISTENER(ComponentViewControls, ActionPanLeft, "input.ACTION_PANLEFT", false)
  REGISTER_LISTENER(ComponentViewControls, ActionPanRight, "input.ACTION_PANRIGHT", false)
  REGISTER_LISTENER(ComponentViewControls, ActionPanUp, "input.ACTION_PANUP", false)
  REGISTER_LISTENER(ComponentViewControls, ActionPanDown, "input.ACTION_PANDOWN", false)
  REGISTER_LISTENER(ComponentViewControls, ActionZoomIn, "input.ACTION_ZOOMIN", false)
  REGISTER_LISTENER(ComponentViewControls, ActionZoomOut, "input.ACTION_ZOOMOUT", false)
  REGISTER_LISTENER(ComponentViewControls, ActionToggleCamera, "input.ACTION_TOGGLECAMERA", false)
  REGISTER_LISTENER(ComponentViewControls, ActionToggleDistClipping, "input.ACTION_TOGGLEDISTCLIP", false)

  UpdateOptions();

  return true;
} // end Initialize()

bool ComponentViewControls::UpdateOptions(iEvent& ev)
{
  UpdateOptions();
  return false;
} // end UpdateOptions()

bool ComponentViewControls::UpdateOptions()
{
  csRef<iConfigManager> app_cfg = csQueryRegistry<iConfigManager> (pointerlib->getObjectRegistry());

  invertYAxis = app_cfg->GetBool("Client.invertYAxis", invertYAxis);
  minFPS = app_cfg->GetFloat("Client.minFPS", minFPS);
  maxFPS = app_cfg->GetFloat("Client.maxFPS", maxFPS);
  minDistance = app_cfg->GetFloat("Client.minDistance", minDistance);

  return true;
} // end UpdateOptions()

bool ComponentViewControls::ActionPanLeft(iEvent& ev)
{
  using namespace PT::Events;

  if (!entity->GetCelEntity()) return false;

  if (InputHelper::GetButtonDown(&ev))
  {
    camera->SetYawVelocity(-1.0f);
  }
  else
  {
    if (camera->GetYawVelocity() < 0.0f)
      camera->SetYawVelocity(0.0f);
  }

  return true;
} // end ActionLeft()

bool ComponentViewControls::ActionPanRight(iEvent& ev)
{
  using namespace PT::Events;

  if (!entity->GetCelEntity()) return false;

  if (InputHelper::GetButtonDown(&ev))
  {
    camera->SetYawVelocity(1.0f);
  }
  else
  {
    if (camera->GetYawVelocity() > 0.0f)
      camera->SetYawVelocity(0.0f);
  }

  return true;
} // end ActionRight()

bool ComponentViewControls::ActionPanUp(iEvent& ev)
{
  using namespace PT::Events;

  if (!entity->GetCelEntity()) return false;

  if (InputHelper::GetButtonDown(&ev))
  {
    if (invertYAxis) camera->SetPitchVelocity(-1.0f);
    else camera->SetPitchVelocity(1.0f);
  }
  else
  {
    if ((invertYAxis && (camera->GetPitchVelocity() < 0.0f)) ||
        (!invertYAxis && (camera->GetPitchVelocity() > 0.0f)))
      camera->SetPitchVelocity(0.0f);
  }

  return true;
} // end ActionPanUp()

bool ComponentViewControls::ActionPanDown(iEvent& ev)
{
  using namespace PT::Events;

  if (!entity->GetCelEntity()) return false;

  if (InputHelper::GetButtonDown(&ev))
  {
    if (invertYAxis) camera->SetPitchVelocity(1.0f);
    else camera->SetPitchVelocity(-1.0f);
  }
  else
  {
    if ((invertYAxis && (camera->GetPitchVelocity() > 0.0f)) ||
        (!invertYAxis && (camera->GetPitchVelocity() < 0.0f)))
      camera->SetPitchVelocity(0.0f);
  }

  return true;
} // end ActionPanDown()

bool ComponentViewControls::ActionZoomIn(iEvent& ev)
{
  using namespace PT::Events;

  if (InputHelper::GetButtonDown(&ev))
  {
    if (!entity->GetCelEntity()) return false;
    cameraDistance -= 0.5;
    if (camera.IsValid()) camera->SetDistance(cameraDistance);
  }
  return true;
} // end ActionZoomIn()

bool ComponentViewControls::ActionZoomOut(iEvent& ev)
{
  using namespace PT::Events;

  if (InputHelper::GetButtonDown(&ev))
  {
    if (!entity->GetCelEntity()) return false;
    cameraDistance += 0.5;
    if (camera.IsValid()) camera->SetDistance(cameraDistance);
  }
  return true;
} // end ActionZoomOut()

bool ComponentViewControls::ActionToggleCamera(iEvent& ev)
{
  using namespace PT::Events;

  if (InputHelper::GetButtonDown(&ev))
  {
    csRef<iPcActorMove> pcactormove =
      CEL_QUERY_PROPCLASS_ENT(entity->GetCelEntity(), iPcActorMove);
    if (!pcactormove) return false;
    pcactormove->ToggleCameraMode();
  }

  return true;
} // end ActionToggleCamera()

bool ComponentViewControls::ActionToggleDistClipping(iEvent& ev)
{
  using namespace PT::Events;

  if (InputHelper::GetButtonDown(&ev))
  {
    if (!entity->GetCelEntity()) return false;

    ///@TODO
    //pointerlib->getGUIManager()->GetChatWindow()->AddMessage("Toggled Distance Clipping.");

    if (camera->UseDistanceClipping()) camera->DisableDistanceClipping();
    else camera->EnableAdaptiveDistanceClipping(minFPS, maxFPS, minDistance);
  }

  return true;
} // end ActionToggleDistClipping()
