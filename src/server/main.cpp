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

#include "stdio.h"

#include "server/entity/entitymanager.h"
#include "server/entity/character.h"
#include "server/entity/entity.h"
#include "server/entity/itementity.h"
#include "server/entity/pcentity.h"
#include "server/entity/npcentity.h"
#include "server/entity/doorentity.h"
#include "server/entity/doormanager.h"
#include "server/entity/racemanager.h"
#include "server/entity/itemmanager.h"
#include "server/entity/statmanager.h"
#include "server/entity/skillmanager.h"
#include "server/entity/sectormanager.h"
#include "server/zone/zonemanager.h"
#include "server/reputation/reputationmanager.h"
#include "server/quest/npcdialog.h"
#include "server/quest/npcdialoganswer.h"
#include "server/quest/npcdialogmanager.h"
#include "common/util/sleep.h"
#include "common/util/timer.h"
#include "common/items/itemsid.h"

#include "server/server.h"
#include "server/entity/charactermanager.h"
#include "server/database/sqlite/sqlite.h"
#include "server/database/table-entities.h"
#include "server/database/table-spawnpoints.h"
#include "server/database/table-config.h"

#include "server/entity/usermanager.h"
#include "server/useraccountmanager.h"
#include "server/environment/environmentmanager.h"
#include "server/spawner.h"
#include "server/network/network.h"
#include "server/colldet/bullet.h"

#include "common/util/wincrashdump.h"
#include "server/combat/combatmanager.h"

#include <signal.h>

int running = 2;
EntityManager* ent_mgr;
CombatManager* combatMgr;

void shutdown()
{
  if (running < 2) return;
  running = 1;

  printf("Server Shutdown initialised!\n");

  delete ent_mgr;
  delete combatMgr;

  printf("- Shutdown Network:     \t");
  Server::getServer()->getNetwork()->shutdown();
  printf("done\n");

  printf("- Shutdown Database:     \t");
  Server::getServer()->getDatabase()->shutdown();
  printf("done\n");

  printf("- Shutdown Timer Engine:\t");
  Server::getServer()->getTimerEngine()->kill();
  printf("done\n");

  running = 0;
}

void sigfunc(int sig)
{
   if (sig == SIGINT)
   {
     shutdown();
   }
}

int main(int argc, char ** argv)
{
  signal(SIGINT, sigfunc);

  setWinCrashDump(argv[0]);

  Server server;

  Tables tables;
  dbSQLite db(&tables);
  tables.init(&db);

  server.setDatabase(&db);
  server.setTables(&tables);

  unsigned int port = 12345;
  if (tables.getConfigTable()->GetConfigValue(ptString("port",4)) != ptString())
  {
    port = atoi(*tables.getConfigTable()->GetConfigValue(ptString("port",4)));
  }

  for(int i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "-port"))
    {
      i++;
      if (i < argc)
      {
        port = atoi(argv[i]);
        ConfigTableVO* config = new ConfigTableVO();
        config->name = ptString("port", 4);
        config->value = ptString(argv[i], strlen(argv[i]));
        tables.getConfigTable()->Insert(config);
      }
    }
    else
    {
      printf("Invalid argument: %s\n", argv[i]);
      printf("Valid arguments are:\n");
      printf("-port [port number] - Set which network port number the server will use.\n");
      return true;
    }
  }

  CharacterManager char_mgr(&server);
  server.setCharacterManager(&char_mgr);

  combatMgr = new CombatManager();
  server.setCombatManager(combatMgr);

  UserManager usr_mgr;
  server.setUserManager(&usr_mgr);

  UserAccountManager usr_acc_mgr(&server);
  server.setUserAccountManager(&usr_acc_mgr);

  ent_mgr = new EntityManager();
  server.setEntityManager(ent_mgr);

  RaceManager race_mgr;
  server.setRaceManager(&race_mgr);

  ItemManager item_mgr;
  server.setItemManager(&item_mgr);

  StatManager stat_mgr;
  server.setStatManager(&stat_mgr);

  DoorManager door_mgr;
  server.setDoorManager(&door_mgr);

  SkillManager skill_mgr;
  server.setSkillManager(&skill_mgr);

  SectorManager sector_mgr;
  server.setSectorManager(&sector_mgr);

  ZoneManager zone_mgr;
  server.setZoneManager(&zone_mgr);

  ReputationManager reputation_mgr;
  server.setReputationManager(&reputation_mgr);

  TimerEngine timeEngine;
  timeEngine.begin();
  server.setTimerEngine(&timeEngine);

  EnvironmentManager environment_mgr;
  server.setEnvironmentManager(&environment_mgr);
  environment_mgr.Initialize();

  sector_mgr.loadFromDB(tables.getSectorsTable());

  item_mgr.loadFromDB(tables.getItemTable());

  ent_mgr->loadFromDB(tables.getEntityTable());

  door_mgr.loadFromDB(tables.getDoorsTable());
  stat_mgr.loadFromDB(tables.getStatTable());
  skill_mgr.loadFromDB(tables.getSkillTable());
  race_mgr.loadFromDB(tables.getRaceTable());
  zone_mgr.loadFromDB(tables.getZonesTable(), tables.getZonenodesTable());
  reputation_mgr.loadFromDB(tables.getReputationsTable());

  printf("Initialising collision detection... ");
  BulletCD cd;
  server.setCollisionDetection(&cd);
  cd.setup();
  printf("done\n");
  //cd.begin();

  Spawner spawner;
  server.setSpawner(&spawner);
  spawner.loadFromDB(tables.getSpawnPointsTable());
  spawner.start();

  NPCDialogManager dialog_mgr;
  dialog_mgr.load();

  // Finally initialising the network!
  Network network(&server);
  network.init(port);

  printf("Server up and running!\n");

  size_t sentbyte = 0, recvbyte = 0, timestamp = 0;
  size_t delay_time = 10000; //10 sec = 10000 ms

  while (running > 0)
  {
    pt_sleep(delay_time);
    network.getStats(sentbyte, recvbyte, timestamp);
    float uptraffic = sentbyte/(float)delay_time;
    float downtraffic = recvbyte/(float)delay_time;
    if (uptraffic > 0.001 || downtraffic > 0.001)
    {
      printf("Network Usage: Up: %.2f kB/s\t Down: %.2f kB/s\n", uptraffic, downtraffic);
    }
  }

  //cd.kill();

  StringStore::destroy();

  printf("Time to quit now!\n");

  return 0;
}
