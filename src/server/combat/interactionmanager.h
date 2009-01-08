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

/**
 * @file interactionmanager.h
 *
 * @basic Server interaction manager.
 */

#ifndef INTERACTIONMANAGER
#define INTERACTIONMANAGER

#include "common/util/thread.h"
#include "interaction.h"

#include "src/server/entity/pcentity.h"
#include "interactionqueue.h"


/**
 * Server interaction manager.
 */
class InteractionManager : public Thread
{
public:
  /// Constructor.
  InteractionManager();
  /// Destructor.
  ~InteractionManager();
  /**
   * Selects new target for a given character.
   * @param sourceEntity entity for the character that request target selection.
   * @param targetID the Entity ID of the target.
   * @return True upon sucess, otherwise false.
   */
  bool SelectTarget(const PcEntity *sourceEntity, unsigned int tagetID);
  /**
   * Selects new target for a given character.
   * @param sourceEntity entity for the character that request target selection.
   * @param interactionID the action ID for the interaction.
   * @return True upon sucess, otherwise false.
   */
  bool QueueInteraction(const PcEntity *sourceEntity,
                        unsigned int interactionID);
  void Start();
  void Stop();

protected:
  /**
   * Function popping interactions of the head of the interaction queue.
   * @return None.
   */
  void Run();

private:
  bool pendingStop;
  bool stopped;
  InteractionQueue* interactionQueue;
  bool NormalAttack(Interaction* interaction);
  /**
   * Deducts the players stamina after an attack.
   * @param lockedCharacter The character to deduct stamina for.
   * @param interaction The interaction that causes stamina deduction.
   */
  bool DeductStamina(Character* lockedCharacter, Interaction* interaction);
  /**
   * Calculates the attacking character's chance of hitting.
   * @param lockedCharacter The locked version of the attacking character.
   * @param lockedCharacter The locked version of the target character.
   * @return attack chance.
   */
  float GetAttackChance(Character* lockedAttacker, Character* lockedTarget);
  float CalculateDamage(Character* lockedAttacker, Character* lockedTarget);
  bool PerformInteraction(Interaction* interaction);
  bool TargetAttackable(Character* lockedAttacker, Character* lockedTarget);
  const Character* GetTargetCharacter(Character* lockedCharacter);
  /**
   * Returns the combined block for a character, including bonuses.
   * @param lockedCharacter The locked version of the character.
   * @return The characters block.
   */
  float GetBlock(Character* lockedCharacter);
  /**
   * Returns the combined dodge for a character, including bonuses.
   * @param lockedCharacter The locked version of the character.
   * @return The characters dodge.
   */
  float GetDodge(Character* lockedCharacter);
  /**
   * Returns the combined parry for a character, including bonuses.
   * @param lockedCharacter The locked version of the character.
   * @return The characters parry.
   */
  float GetParry(Character* lockedCharacter);
  /**
   * Returns the combined strength for a character, including bonuses.
   * @param lockedCharacter The locked version of the character.
   * @return The characters strength.
   */
  float GetStrength(Character* lockedCharacter);
  /**
   * Returns the combined reach for a character, including bonuses.
   * @param lockedCharacter The locked version of the character.
   * @return The characters reach.
   */
  float GetReach(Character* lockedCharacter);
  /**
   * Returns the combined agility for a character, including bonuses.
   * @param lockedCharacter The locked version of the character.
   * @return The characters agility.
   */
  float GetAgility(Character* lockedCharacter);
  /**
   * Returns the combined skill bonuses.
   * @todo
   * @param lockedCharacter The locked version of the character.
   * @return The characters skill bonuses.
   */
  float GetSkillBonus(Character* lockedCharacter);
  /**
   * Returns the combined sapience for a character, including bonuses.
   * @param lockedCharacter The locked version of the character.
   * @return The characters sapience.
   */
  float GetSapience(Character* lockedCharacter);
  /**
   * Function to get the weapon(s) heft value.
   * @param lockedCharacter The owner of the weapon
   * @return The weapon(s) heft value.
   */
  float GetWeaponHeft(Character* lockedCharacter);
  /**
   * Calculates the damage given by the character's weapon(s).
   * @param lockedCharacter The locked version of the character.
   * @return The weapon damage.
   */
  float GetWeaponDamage(Character* lockedCharacter);
  /**
   * Combines the characters weapon stat values, based on stat name
   * @param lockedCharacter The locked version of the character.
   * @param statName The stat's name.
   * @return The weapons bonuses given a special stat.
   */
  float GetStatValueForEquipedWeapons(Character* lockedCharacter,
                                      const char* statName);
  /**
   * Queries the stat value from an item based on stat name.
   * @param item The item to return the stat value for.
   * @param statName The stat's name.
   * @return The items stat based on the statName.
   */
  float GetStatValueForItem(const Item* item, const char* statName);
  /**
   * Queries the stat for a character based on the stat's name.
   * It would be tempting to use this function directly,however a character can
   * get bonuses, therefore this function should be called from the different
   * getters for stats.
   * @param lockedCharacter The locked version of the character.
   * @param statName The stat's name.
   * @return The stats current value.
   */
  float GetStatValue(Character* lockedCharacter,
                                         const char* statName);
  /**
   * Combines the character's items stat values, based on stat name
   * @param lockedCharacter The locked version of the character.
   * @param statName The stat's name.
   * @return The items bonuses given a special stat.
   */
  float GetStatValueForAllEquipedItems(Character* lockedCharacter,
                                       const char* statName);
  /**
   * Used to get an equiped item based on the slot number.
   * @param lockedCharacter The locked version of the character.
   * @param slot Which item, is decided by the slot its equiped on.
   * @return The item in that slot, or NULL if none found.
   */
  Item* GetItem(Character* lockedCharacter, unsigned char slot);
  /**
   * Get a random number between 0 and 100.
   * @return A random number between 0 and 100.
   */
  int RollDice(void);
  /**
   * Wrapper function to send stat update.
   * @param stat The type of stat to update.
   * @param stats The characters stat container.
   * @param lockedCharacter The locked version of the character.
   * @param name The name of the stat.
   * @param target Whom to send to.
   */
  void SendStatUpdate(const Stat* stat, const CharacterStats* stats,
                      Character* lockedCharacter, const char* name, int target);
  float GetHightDeviation(const Character* lockedAttacker,
                          const Character* lockedTarget);

};

namespace InteractionManagerSendTo
{
  enum SendTo
  {
    CHARACTER,
    LOCALCAST,
    BROADCAST,
  };
}

#endif //INTERACTIONMANAGER
