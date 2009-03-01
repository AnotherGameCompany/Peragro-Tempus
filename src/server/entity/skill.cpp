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

#include "entity.h"
#include "pcentity.h"
#include "skill.h"
#include "character.h"
#include "characterskills.h"
#include "entitymanager.h"
#include "server/server.h"
#include "statmanager.h"
#include "common/network/skillmessages.h"
#include "server/network/connection.h"
#include "server/entity/user.h"

#include "server/network/networkhelper.h"

//Skill::Skill() : id(-1), range(0)
//{
//  mp = Server::getServer()->getStatManager()->findByName(ptString("Mana", strlen("Mana")));
//  hp = Server::getServer()->getStatManager()->findByName(ptString("Health", strlen("Health")));
//}

//void Skill::triggerSkill(CharSkill* skilldata, CharacterEntity* caster)
//{
//  Entity* target = Server::getServer()->getEntityManager()->findById(skilldata->target_id);
//  const char* targetname = target?*target->getName():"";
//  printf("Dummy Skill from %s targetting %s!\n",*caster->getName(),targetname);
//}

void Skill::castPrepare(Character* caster, unsigned int target_id)
{
  CharSkill* skilldata = caster->getSkills()->findSkill(id);
  const Entity* target = Server::getServer()->getEntityManager()->findById(target_id);

  SkillUsageStartResponseMessage response_msg;
  response_msg.setSkill(id);
  response_msg.setTarget(0);
  response_msg.setCaster(caster->getEntity()->GetId());

  skilldata->caster_id = caster->getEntity()->GetId();

  printf("Casting: %s starts to cast %s on %s\n", *caster->getName(), *this->getName(), target->GetName().c_str());
  printf("Casting: Skill State: %d \n", skilldata->state);

  Stat* mp = Server::getServer()->getStatManager()->findByName(ptString("Mana", strlen("Mana")));
  if (caster->getStats()->getAmount(mp) < mpCost)
  {
    //Abort 'Not enough MP'
    response_msg.setError(ptString("Not enough MP", strlen("Not enough MP")));
    return ;
  }
  else if (!caster->getEntity())
  {
    response_msg.setError(ptString("Entity disappeared",strlen("Entity disappeared")));
  }
  else if (caster->getEntity()->getDistanceTo(target) > range)
  {
    //Abort 'too far away'
    response_msg.setError(ptString("Too far away", strlen("Too far away")));
  }
  else if (skilldata->state != SkillState::READY)
  {
    //Abort 'Skill not ready'
    response_msg.setError(ptString("Skill not ready", strlen("Skill not ready")));
  }
  else
  {
    skilldata->skill = this;
    skilldata->target_id = target->GetId();

    response_msg.setError(ptString());
    response_msg.setTarget(target->GetId());
    response_msg.setMpCost(mpCost);

    caster->getStats()->takeStat(mp, mpCost);

    skilldata->state = SkillState::CASTING;
    skilldata->setInterval(skillTime);
    skilldata->start();

    // Broadcast the skill start.
    ByteStream bs;
    response_msg.serialise(&bs);
    Server::getServer()->broadCast(bs);
  }

  // An error occurred, send error to caster.
  ByteStream bs;
  response_msg.serialise(&bs);
  NetworkHelper::sendMessage(caster, bs);
}

void Skill::castInterrupt(CharSkill* skilldata)
{
  if (skilldata->state == SkillState::CASTING)
  {
    skilldata->stop();
    skilldata->state = SkillState::RECOVER;
    skilldata->setInterval(reuseDelay);
    skilldata->start();
  }

  SkillUsageInterruptMessage response_msg;
  response_msg.setSkill(skilldata->skill->GetId());
  response_msg.setCaster(skilldata->caster_id);
  response_msg.setTarget(skilldata->target_id);

  ByteStream bs;
  response_msg.serialise(&bs);
  Server::getServer()->broadCast(bs);
}

void Skill::castExecute(CharSkill* skilldata)
{
  if (skilldata->state == SkillState::CASTING)
  {
    skilldata->stop();
    skilldata->state = SkillState::RECOVER;
    skilldata->setInterval(reuseDelay);
    skilldata->start();
  }

  SkillUsageCompletionMessage response_msg;
  response_msg.setSkill(skilldata->skill->GetId());
  response_msg.setCaster(skilldata->caster_id);
  response_msg.setTarget(skilldata->target_id);

  const Entity* target = Server::getServer()->getEntityManager()->findById(skilldata->target_id);
  const PcEntity* player = target->getPlayerEntity();

  if (player == 0) return;

  const Character* c_char = player->getCharacter();
  ptScopedMonitorable<Character> l_char (c_char);
  CharacterStats* stats = l_char->getStats();
  Stat* hp = Server::getServer()->getStatManager()->findByName(ptString("Health", strlen("Health")));
  if (type == TYPE_HURT)
  {
    unsigned int health = stats->getAmount(hp);
    if ( (int) health > power )
    {
      // target took damage
      stats->takeStat(hp, power);
      printf("Hitting %s with %d damage => %d HP remaining\n", target->GetName().c_str(), power, stats->getAmount(hp));
    }
    else
    {
      // target died
      stats->takeStat(hp, health);
      printf("Hitting %s with %d damage => Target Died => %d HP remaining\n", target->GetName().c_str(), power, stats->getAmount(hp));
    }
  }
  else if (type == TYPE_HEAL)
  {
    stats->addStat(hp, power);
    printf("Healing %s with %d Health => %d HP remaining\n", target->GetName().c_str(), power, stats->getAmount(hp));
    //no upper stats limit for now...
  }

  ByteStream bs;
  response_msg.serialise(&bs);
  Server::getServer()->broadCast(bs);
}

void Skill::castRecover(CharSkill* skilldata)
{
  skilldata->stop();
  skilldata->state = SkillState::READY;
}
