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
#include "client/entity/entitymanager.h"

#include "client/event/eventmanager.h"
#include "client/event/stateevent.h"
#include "client/event/regionevent.h"

#include "client/reporter/reporter.h"

void UserHandler::handleLoginResponse(GenericMessage* msg)
{
  Report(PT::Notify, "Received LoginResponse.");
  LoginResponseMessage response;
  response.deserialise(msg->getByteStream());

  using namespace PT::Events;
  StateLoggedInEvent* stateEvent = new StateLoggedInEvent();

  if (!response.getError().isNull()) // An error occured.
  {
    stateEvent->errorMessage	= *response.getError();
    stateEvent->error					= true;
  }
  else
  {
    stateEvent->errorMessage	= "blah";
    stateEvent->error					= false;
  }

  PointerLibrary::getInstance()->getEventManager()->AddEvent(stateEvent);
}

void UserHandler::handleRegisterResponse(GenericMessage* msg)
{
  Report(PT::Notify, "Received RegisterResponse.");
  RegisterResponseMessage answer_msg;
  answer_msg.deserialise(msg->getByteStream());
  ptString error = answer_msg.getError();
  if (!error.isNull())
  {
    Report(PT::Warning, "Registration Failed due to: %s", *error);
    GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
    guimanager->CreateOkWindow()->SetText(*error);
    return;
  }

  Report(PT::Notify, "Registration succeeded!");
}

void UserHandler::handleCharList(GenericMessage* msg)
{
  CharListMessage char_msg;
  char_msg.deserialise(msg->getByteStream());
  //printf("Got %d character:\n---------------------------\n", char_msg.getCharacterCount());
  GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
  for (int i=0; i<char_msg.getCharacterCount(); i++)
  {
    guimanager->GetSelectCharWindow ()->AddCharacter(
      char_msg.getCharId(i), *char_msg.getName(i),
      char_msg.getSkinColour(i), char_msg.getHairColour(i), char_msg.getDecalColour(i));
    //printf("Char %d: %s\n", char_msg.getCharacterId(i), char_msg.getCharacterName(i));
  }
}

void UserHandler::handleCharCreateResponse(GenericMessage* msg)
{
  CharCreateResponseMessage answer_msg;
  answer_msg.deserialise(msg->getByteStream());
  GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();

  if (answer_msg.getError().isNull())
  {
    guimanager->GetSelectCharWindow ()->AddCharacter(answer_msg.getCharId(), *answer_msg.getName(),
      answer_msg.getSkinColour(), answer_msg.getHairColour(), answer_msg.getDecalColour());
  }
  else
  {
    Report(PT::Warning, "Character creation failed due to: %s", *answer_msg.getError());
    guimanager->CreateOkWindow()->SetText(*answer_msg.getError());
  }
}

void UserHandler::handleCharSelectResponse(GenericMessage* msg)
{
  CharSelectResponseMessage answer_msg;
  answer_msg.deserialise(msg->getByteStream());

  using namespace PT::Events;
  StatePlayEvent* stateEvent = new StatePlayEvent();
  stateEvent->ownEntityId = answer_msg.getEntityId();
  PointerLibrary::getInstance()->getEventManager()->AddEvent(stateEvent);
}
