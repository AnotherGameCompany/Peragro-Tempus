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

#ifndef COMMANDS_H
#define COMMANDS_H

#include <cssysdef.h>
#include <imesh/objmodel.h>
#include <igeom/trimesh.h>
#include <csgeom/tri.h>

#include "command.h"

#include "client/pointer/pointer.h"
#include "client/reporter/reporter.h"

#include "client/network/network.h"
#include "common/network/netmessage.h"

#include "client/gui/guimanager.h"
#include "client/gui/chat-gui.h"
#include "client/gui/whisper-gui.h"

#include "client/entity/entitymanager.h"

#include "client/data/sector.h"
#include "client/data/sectordatamanager.h"

namespace PT
{
  namespace Chat
  {
    //--------------------------------------------------------------------------
    class cmdHelp : public Command
    {
    public:
      cmdHelp () { }
      virtual ~cmdHelp () { }
      virtual const char* GetCommand () { return "help"; }
      virtual const char* GetDescription () { return "Prints this help."; }
      virtual void Help ()
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        guimanager->GetChatWindow ()->AddMessage ("Usage: '/help'");
      }
      virtual void Execute (const StringArray& args)
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        PT::Chat::ChatManager* chatmgr = PointerLibrary::getInstance()->getChatManager();
        if(!chatmgr) return;

        // Element 0 is '/', 1 is 'help'
        if (args.size() < 2 || args.size() > 2)
        {
          Help();
          return;
        }
        else
        {
          std::vector<Commandp> commands = chatmgr->GetAllCommands();

          std::vector<Commandp>::const_iterator it;
          for(it = commands.begin(); it != commands.end(); ++it)
          {
            std::string text = it->get()->GetCommand();
            text += ": ";
            text += it->get()->GetDescription();
            guimanager->GetChatWindow ()->AddMessage (text.c_str());
          } // for

          return;
        }
      }
    };
    //--------------------------------------------------------------------------
    class cmdSay : public Command
    {
    public:
      cmdSay () { }
      virtual ~cmdSay () { }
      virtual const char* GetCommand () { return "say"; }
      virtual const char* GetDescription () { return "Say something to the world."; }
      virtual void Help ()
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        guimanager->GetChatWindow ()->AddMessage ("Usage: '/say <message>'");
      }
      virtual void Execute (const StringArray& args)
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        Network* network = PointerLibrary::getInstance()->getNetwork();
        if(!network) return;

        // Element 0 is '/', 1 is 'say'
        if (args.size() > 0 && args[0].compare("/") != 0)
        {
          // Special case for when text was inputted without '/'.
          std::string text;
          for(size_t i = 0; i < args.size(); i++)
          {
            text += args[i];
            text += " ";
          }
          Report(PT::Debug, "Say1: %s", text.c_str());
          SayMessage msg;
          msg.setMessage(text.c_str());
          network->send(&msg);
        }
        else if (args.size() < 3)
        {
          Help();
          return;
        }
        else
        {
          std::string text;
          for(size_t i = 2; i < args.size(); i++)
          {
            text += args[i];
            text += " ";
          }

          Report(PT::Debug, "Say2: %s", text.c_str());
          SayMessage msg;
          msg.setMessage(text.c_str());
          network->send(&msg);

          return;
        }
      }
    };
    //--------------------------------------------------------------------------
    class cmdSayMe : public Command
    {
    public:
      cmdSayMe () { }
      virtual ~cmdSayMe () { }
      virtual const char* GetCommand () { return "me"; }
      virtual const char* GetDescription () { return "Say something in third person to the world."; }
      virtual void Help ()
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        guimanager->GetChatWindow ()->AddMessage ("Usage: '/me <message>'");
      }
      virtual void Execute (const StringArray& args)
      {
        Network* network = PointerLibrary::getInstance()->getNetwork();
        if(!network) return;

        // Element 0 is '/', 1 is 'me'
        if (args.size() < 3)
        {
          Help();
          return;
        }
        else
        {
          std::string text = "/";
          for(size_t i = 1; i < args.size(); i++)
          {
            text += args[i];
            text += " ";
          }

          Report(PT::Debug, "Say3: %s", text.c_str());
          SayMessage msg;
          msg.setMessage(text.c_str());
          network->send(&msg);

          return;
        }
      }
    };
    //--------------------------------------------------------------------------
    class cmdGreet : public Command
    {
    public:
      cmdGreet () { }
      virtual ~cmdGreet () { }
      virtual const char* GetCommand () { return "greet"; }
      virtual const char* GetDescription () { return "Wave at someone."; }
      virtual void Help ()
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        guimanager->GetChatWindow ()->AddMessage ("Usage: '/greet <target>'");
      }
      virtual void Execute (const StringArray& args)
      {
        Network* network = PointerLibrary::getInstance()->getNetwork();
        if(!network) return;
        PT::Entity::EntityManager* entmgr = PointerLibrary::getInstance()->getEntityManager();
        if(!entmgr) return;

        // Element 0 is '/', 1 is 'greet'
        if (args.size() < 3 || args.size() > 3)
        {
          Help();
          return;
        }
        else
        {
          std::string target = args[2];
          std::string text = "/greet " + target;

          // TODO: Turn and wave to target.
          /*
          PtEntity* targetent = entmgr->findPtEntByName(target);
          PtEntity* ownent = entmgr->getOwnPtEntity();
          ownent->Target(targetent);
          ownent->PlayAction("wave");
          */

          Report(PT::Debug, "waving at %s", target.c_str());
          SayMessage msg;
          msg.setMessage(text.c_str());
          network->send(&msg);

          //We want to send a pose request to server as well.
          //TODO: If we decide to introduce more poses, replacing this by some
          //"PoseManager" might be nice (ie we wouldn't need to hard-code those
          //commands like now).
          PoseRequestMessage poseMsg;
          poseMsg.setPoseId(1); //Magic number - bad developer!
          network->send(&poseMsg);

          return;
        }
      }
    };
    //--------------------------------------------------------------------------
    class cmdSit : public Command
    {
    public:
      cmdSit () { }
      virtual ~cmdSit () { }
      virtual const char* GetCommand () { return "sit"; }
      virtual const char* GetDescription () { return "Sit down."; }
      virtual void Help ()
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        guimanager->GetChatWindow ()->AddMessage ("Usage: '/sit'");
      }
      virtual void Execute (const StringArray& args)
      {
        Network* network = PointerLibrary::getInstance()->getNetwork();
        if(!network) return;
        PT::Entity::EntityManager* entmgr = PointerLibrary::getInstance()->getEntityManager();
        if(!entmgr) return;

        // Element 0 is '/', 1 is 'sit'
        if (args.size() < 2 || args.size() > 3)
        {
          Help();
          return;
        }
        else
        {
          //We want to send a pose request to server as well.
          //TODO: If we decide to introduce more poses, replacing this by some
          //"PoseManager" might be nice (ie we wouldn't need to hard-code those
          //commands like now).
          PoseRequestMessage poseMsg;
          poseMsg.setPoseId(2); //Magic number - bad developer!
          network->send(&poseMsg);

          return;
        }
      }
    };
    //--------------------------------------------------------------------------
    class cmdRelocate : public Command
    {
    public:
      cmdRelocate () { }
      virtual ~cmdRelocate () { }
      virtual const char* GetCommand () { return "relocate"; }
      virtual const char* GetDescription () { return "Teleport yourself to the start location."; }
      virtual void Help ()
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        guimanager->GetChatWindow ()->AddMessage ("Usage: '/relocate'");
      }
      virtual void Execute (const StringArray& args)
      {
        Network* network = PointerLibrary::getInstance()->getNetwork();
        if(!network) return;

        // Element 0 is '/', 1 is 'relocate'
        if (args.size() < 2)
        {
          Help();
          return;
        }
        else
        {
          RelocateMessage msg;
          network->send(&msg);

          return;
        }
      }
    };
    //--------------------------------------------------------------------------
    class cmdWhisper : public Command
    {
    public:
      cmdWhisper () { }
      virtual ~cmdWhisper () { }
      virtual const char* GetCommand () { return "whisper"; }
      virtual const char* GetDescription () { return "Start a private conversation with the target."; }
      virtual void Help ()
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        guimanager->GetChatWindow ()->AddMessage ("Usage: '/whisper <target> <message>'");
      }
      virtual void Execute (const StringArray& args)
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        Network* network = PointerLibrary::getInstance()->getNetwork();
        if(!network) return;

        // Element 0 is '/', 1 is 'whisper'
        if (args.size() < 4)
        {
          Help();
          return;
        }
        else
        {
          std::string nick = args[2];

          std::string text;
          for(size_t i = 3; i < args.size(); i++)
          {
            text += args[i];
            text += " ";
          }

          // Get your own nickname.
          std::string ownnick = Entity::PlayerEntity::Instance()->GetName();
          // Add your own text to the whisper.
          guimanager->GetWhisperWindow()->AddWhisper(nick.c_str(), text.c_str(), ownnick.c_str());
          // Send the whisper to the network.
          WhisperToMessage nmsg;
          nmsg.setListenerName(ptString(nick.c_str(), nick.size())); //<-- name of who you want to talk to...
          nmsg.setMessage(text.c_str());
          network->send(&nmsg);

          return;
        }
      }
    };
    //--------------------------------------------------------------------------
    class cmdDbg : public Command
    {
    public:
      cmdDbg () { }
      virtual ~cmdDbg () { }
      virtual const char* GetCommand () { return "dbg"; }
      virtual const char* GetDescription () { return "Command used for developers to debug stuff. Read the code!"; }
      virtual void Help ()
      {
        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;
        guimanager->GetChatWindow ()->AddMessage ("Usage: '/dbg #number [args]'");
        guimanager->GetChatWindow ()->AddMessage ("  - Write book: '/dbg write #itemid #bookid #name #text'");
        guimanager->GetChatWindow ()->AddMessage ("  - Player Pos: '/dbg pos'");
        guimanager->GetChatWindow ()->AddMessage ("  - Flash Step: '/dbg flashstep'");
        guimanager->GetChatWindow ()->AddMessage ("  - Spawn Item: '/dbg spawn item #itemid #variation'");
        guimanager->GetChatWindow ()->AddMessage ("  - Spawn Mount: '/dbg spawn mount meshname entityname'");
        guimanager->GetChatWindow ()->AddMessage ("  - Sector: '/dbg sector sectorname'");
        guimanager->GetChatWindow ()->AddMessage ("  - Sector: '/dbg rm entity #id'");
      }
      virtual void Execute (const StringArray& args)
      {
        Network* network = PointerLibrary::getInstance()->getNetwork();
        if(!network) return;

        GUIManager* guimanager = PointerLibrary::getInstance()->getGUIManager();
        if(!guimanager) return;

        PointerLibrary* ptr_lib = PointerLibrary::getInstance();
        Entity::EntityManager* ent_mgr = ptr_lib->getEntityManager();

        PT::Data::SectorDataManager* sectorDataMgr = ptr_lib->getSectorDataManager();

        // Element 0 is '/', 1 is 'relocate'
        if (args.size() < 3)
        {
          Help();
          return;
        }
        else
        {
          if (args[2].compare("write") == 0)
          {
            BookWriteRequestMessage msg;
            msg.setItemId(atoi(args[3].c_str()));
            msg.setBookId(atoi(args[4].c_str()));
            msg.setBookName(ptString(args[5].c_str(), args[5].size()));

            std::string text;
            for(size_t i = 6; i < args.size(); i++){ text += args[i]; text += " ";}

            msg.setText(text.c_str());
            network->send(&msg);
          }
          else if (args[2].compare("pos") == 0)
          {
            iCelEntity* entity = ent_mgr->findCelEntById(ent_mgr->GetPlayerId());

            csRef<iPcLinearMovement> pclinmove =
              CEL_QUERY_PROPCLASS_ENT(entity, iPcLinearMovement);

            csVector3 pos = pclinmove->GetFullPosition();
            iSector* sector = pclinmove->GetSector();

            char buffer[1024];

            sprintf(buffer, "Position: %s <%f.2, %f.2, %f.2>", 
              sector->QueryObject()->GetName(), pos.x, pos.y, pos.z);

            guimanager->GetChatWindow ()->AddMessage (buffer);
          }
          else if (args[2].compare("flashstep") == 0)
          {
            ToggleFlashStepMessage msg;
            network->send(&msg);
          }
          else if (args[2].compare("spawn") == 0)
          {
            iCelEntity* entity = ent_mgr->findCelEntById(ent_mgr->GetPlayerId());

            csRef<iPcLinearMovement> pclinmove =
              CEL_QUERY_PROPCLASS_ENT(entity, iPcLinearMovement);

            csVector3 pos = pclinmove->GetFullPosition();
            float rotation = pclinmove->GetYRotation();
            iSector* sector = pclinmove->GetSector();

            int sectorId = sectorDataMgr->GetSectorByName(sector->QueryObject()->GetName())->GetId();

            if (args[3].compare("item") == 0)
            {
              SpawnItemMessage itemmsg;
              itemmsg.setItemId(atoi(args[4].c_str()));
              itemmsg.setVariation(atoi(args[5].c_str()));
              itemmsg.setPos(pos.x, pos.y, pos.z);
              itemmsg.setSectorId(sectorId);
              network->send(&itemmsg);
            }
            else if(args[3].compare("mount") == 0)
            {
              SpawnMountMessage mountmsg;
              mountmsg.setMesh(ptString(args[4].c_str(), args[4].length()));
              mountmsg.setName(ptString(args[5].c_str(), args[5].length()));
              mountmsg.setPos(pos.x, pos.y, pos.z);
              mountmsg.setRotation(rotation);
              mountmsg.setSectorId(sectorId);
              network->send(&mountmsg);
            }
          }
          else if (args[2].compare("sector") == 0)
          {
            iCelEntity* entity = ent_mgr->findCelEntById(ent_mgr->GetPlayerId());

            csRef<iPcLinearMovement> pclinmove =
              CEL_QUERY_PROPCLASS_ENT(entity, iPcLinearMovement);

            csVector3 pos = pclinmove->GetFullPosition();

            using namespace PT::Events;
            EntityTeleportEvent* ev = new EntityTeleportEvent();
            ev->entityId = ent_mgr->GetPlayerId();
            ev->position = pos;
            ev->sectorId = sectorDataMgr->GetSectorByName(args[3])->GetId();
            PointerLibrary::getInstance()->getEventManager()->AddEvent(ev);
          }
          else if (args[2].compare("rm") == 0)
          {
            if (args[3].compare("entity") == 0)
            {
              RemoveSpawnedEntityMessage rmmsg;
              rmmsg.setEntityId(atoi(args[4].c_str()));
              network->send(&rmmsg);
            }
          }
          else if (args[2].compare("dump") == 0)
          {
            iObjectRegistry* objreg = ptr_lib->getObjectRegistry();
            csRef<iEngine> engine (csQueryRegistry<iEngine> (objreg));
            csRef<iVFS> vfs (csQueryRegistry<iVFS> (objreg));

            csRef<iStringSet> strings = 
              csQueryRegistryTagInterface<iStringSet> (objreg, 
              "crystalspace.shared.stringset");

            csStringID colldetid = strings->Request ("base");

            vfs->ChDir("/this");

            csRef<iFile> file (vfs->Open("dbcreate.sql", VFS_FILE_WRITE));

            std::string create;
            create += "drop table vertices;\n";
            create += "drop table triangles;\n";
            create += "drop table meshes;\n";
            create += "create table meshes (id INTEGER, sector INTEGER, name TEXT, PRIMARY KEY (id) );\n";
            create += "create table triangles (mesh INTEGER, num INTEGER, a INTEGER, b INTEGER, c INTEGER, PRIMARY KEY (mesh, num) );\n";
            create += "create table vertices (mesh INTEGER, num INTEGER, x FLOAT, y FLOAT, z FLOAT, PRIMARY KEY (mesh, num) );\n";

            file->Write(create.c_str(), create.length());
            file->Flush();

            iSectorList* sectors = engine->GetSectors();

            for (int i = 0; sectors && i < sectors->GetCount(); i++)
            {
              iSector* sector = sectors->Get(i);

              csString str ("db_");
              str += sector->QueryObject()->GetName();
              str += ".sql";

              csRef<iFile> file (vfs->Open(str.GetData(), VFS_FILE_WRITE));

              std::stringstream data;

              data << "\nBEGIN TRANSACTION;\n";

              iMeshList* meshes = sector->GetMeshes();
              for (int j = 0; meshes && j < meshes->GetCount(); j++)
              {
                iMeshWrapper* mesh = meshes->Get(j);

                unsigned int sector_id = ptr_lib->getSectorDataManager()
                  ->GetSectorByName(sector->QueryObject()->GetName())->GetId();

                data << "insert into meshes (id, sector, name) values ( "
                     << mesh->QueryObject()->GetID() << ", " 
                     << sector_id << ", " 
                     << "'" << mesh->QueryObject()->GetName() << "');\n";

                iObjectModel* model = mesh->GetMeshObject()->GetObjectModel();
                if (model == 0) continue;

                iTriangleMesh* trimesh = model->GetTriangleData(colldetid);
                if (trimesh == 0) continue;

                csTriangle* triangles = trimesh->GetTriangles();
                for (size_t k = 0; triangles && k < trimesh->GetTriangleCount(); k++)
                {
                  data << "insert into triangles (mesh, num, a, b, c) values ( "
                       << mesh->QueryObject()->GetID() << ", " << k << ", "
                       << triangles[k].a << ", " << triangles[k].b << ", " 
                       << triangles[k].c << ");\n";
                }

                csReversibleTransform t = mesh->GetMovable()->GetFullTransform();

                csVector3* vertices = trimesh->GetVertices();
                for (size_t k = 0; vertices && k < trimesh->GetVertexCount(); k++)
                {
                  csVector3 v = t.This2Other(vertices[k]);
                  data << "insert into vertices (mesh, num, x, y, z) values ( "
                       << mesh->QueryObject()->GetID() << ", " << k << ", "
                       << v.x << ", " << v.y << ", " << v.z << ");\n";
                }

              }

              data << "\nCOMMIT;\n";

              file->Write(data.str().c_str(), data.str().length());
              file->Flush();
            }
          }
          return;
        }
      }
    };
    //--------------------------------------------------------------------------
  } // Chat namespace
} // PT namespace

#endif // COMMANDS_H
