#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// constants
const int SEED_VALUE = 14;
const int CRITICAL_SUCCESS = 20;
const int CRITICAL_FAILURE = 1;

int main(){
  srand(SEED_VALUE);

  // assigns player stats set to random values within a certain range
  int playerMaxHealth = 50 + rand() % (150 - 50 + 1);
  int playerArmor =  rand() % 4 + 1;
  int highestKillStreak = 0;

  // initilizes monster stats
  int monsterType = rand() % 3; // used to determine which monster appears
  string monster;
  int monsterHealth;
  int monsterArmor;
  
  // death messages
  string playerDeathMessage = "Gasping for breath and realizing their mother wasn't wrong when they suggested they just stay on the farm and live a quiet life, the player passes away!";

  string monsterDeathMessage = "The monster has been slain! The adrenaline rush from the victory restores their HP to full";

  // critical failure messages
  string criticalFailureMonsterMessage = "The attack hits! Critical failure! The monster recklessly attacks, slips and bumps their head on the floor. -1 HP. Player's current HP: ";
  string criticalFailurePlayerMessage = "The attack hits! Critical failure! The player swings wildly, loses balances, and bumps their head on a wall. -1 HP. Player's Current HP: ";
//critical success messages string criticalSuccessMonsterMessage = "The attack hits! Natural 20! The monster's combat prowess becomes the stuff of nightmares, savagely rending the player, dealing -25 HP them! Player's current HP: "; string criticalSuccessPlayerMessage = "The attack hits! Natural 20! The player experts attacks the monster's exposed weaknesses, dealing -25 HP to it! Monster's current HP: ";

  // messages for a unsuccessful attack
  string noHitMessagePlayer = "The player's attack fails to deal damage to the monster. Monster's current HP: ";
  string noHitMessageMonster = "The monster's attack fails to deal damage to the player. players's current HP: ";

  // horizontal line used to seperate battle outputs
  string hline = "---------------------------------------------------------------------------------------------------------------------";
    
  // outputs the players stats
  cout << "The player's maximum HP is " << playerMaxHealth << endl;
  cout << "The player's armor class is " << playerArmor << endl << endl;


  // assigns monster based off randomly generated monster type
  switch (monsterType){ 
    case 0: // sets attributes for the Goblin
      monster = "Goblin";
      monsterHealth = 30 + rand() % (45 - 30 + 1);
      monsterArmor = rand() % 2 + 1; 
      cout << "You encounter a meager goblin. This should be easy enough!" << endl;
      cout << "The monster's maximum HP is " << monsterHealth << endl;
      cout << "The monster's armor class is " << monsterArmor << endl << endl;
      break;
    case 1: // sets attributes for the Ogre
      monster = "Ogre";
      monsterHealth = 75 + rand() % (100 - 75 + 1);
      monsterArmor = 2 + rand() % (4 - 2 + 1);
      cout << "You encounter a towering ogre. Hope you brought health potions!" << endl;
      cout << "The monster's maximum HP is " << monsterHealth << endl;
      cout << "The monster's armor class is " << monsterArmor << endl << endl;
      break;
    case 2: // sets attributes for the dragon.
      monster = "Dragon";
      monsterHealth = 345 + rand() % (500 - 345 + 1);
      monsterArmor = 5 + rand() % (6 - 5 + 1);
      cout << "You encounter a dragon the size of a modest castle. Ruination has come!" << endl;
      cout << "The monster's maximum HP is " << monsterHealth << endl;
      cout << "The monster's armor class is " << monsterArmor << endl << endl; 
      break;
  } // end of switch
  
  int playerHealth = playerMaxHealth; // players health points used during the battle
  int damageValue;
  int killStreak = 0; // used to keep track of the players kill count

  while (true) { // loops untill player or monster is defeated, exit statement occurs when monster or player dies

    // players turn to attack 
    int playerAttack = rand() % 8 + 1; // simulates the roll of an 8 sided die
    
    if (playerAttack > monsterArmor) // executes code for attacking if player rolls a number higher the value of the monsters armor
    {
      damageValue = rand() % 20 + 1; // simulates rolling a 20 sided die, used for determining damage output
      
      if (damageValue == CRITICAL_FAILURE) // case for rolling a 1 from the 20 sided die
      {
        if ((playerHealth - 1) > 0) // executes if player does not die from a critical failure roll 
        {
          playerHealth -= 1;
          cout << criticalFailurePlayerMessage << playerHealth << endl;
        }
        else // 
        {
          playerHealth = 0;

          cout << criticalFailurePlayerMessage << playerHealth << endl;
          cout << playerDeathMessage << endl << endl;
          break; // player died, exiting loop
        }
      }
      else if (damageValue == CRITICAL_SUCCESS) // case for rolling a 20
      {

        if ((monsterHealth - (damageValue + 5)) > 0) // checks if enough hp to continue fighting
        {
          monsterHealth -= (damageValue + 5);

          cout << criticalSuccessPlayerMessage << monsterHealth << endl;
        }

        else // case for monster dying on hit
        {
          monsterHealth = 0;

          cout << criticalSuccessPlayerMessage << monsterHealth << endl;
          cout << monsterDeathMessage << endl << endl
               << hline << endl; 

          killStreak++; // adds 1 to current kill streak
          highestKillStreak++; // adds 1 players highest kill count, will be output at the end
          break; // monster was defeated, exiting loop
        }

      }
      else // case for rolling a basic damage value
      {
        if ((monsterHealth - damageValue) > 0) // checks if healthy
        {
          monsterHealth -= damageValue; 
          cout << "The attack hits! The player damages for " << -damageValue << "HP to the monster.  Monster's current HP: " << monsterHealth << endl;
        }
        else
        {
          monsterHealth = 0;

          cout << "The attack hits! The player damages for " << -damageValue << "HP to the player.  Player's current HP: " << playerHealth << endl;
          cout << monsterDeathMessage << endl << endl 
               << hline << endl; 

          killStreak++;
          highestKillStreak++;
          break;
        }
      }
    } 
    else
    {
      cout << noHitMessagePlayer << monsterHealth << endl;
    }

    // Monsters turn to attack
    int monsterAttack = rand() % 8 + 1;

    if(monsterAttack > playerArmor) // attack is successfull
    {
      damageValue = rand() % 20 + 1; // sets amount of damage dealt

      if (damageValue == CRITICAL_FAILURE) // case for rolling a 1 
      {
        if ((monsterHealth - 1) > 0){ // checks if monster survives its slip and fall
        // survived ---> continues game
         monsterHealth -= 1; 
         cout << criticalFailureMonsterMessage << playerHealth << endl << endl;
        }

        else // monster did not survive critical failure
        {
          monsterHealth = 0;

          cout << criticalFailureMonsterMessage << monsterHealth << endl << endl;
          cout << monsterDeathMessage << endl << endl 
               << hline << endl; 

          killStreak++;
          highestKillStreak++;

          break;
        }
      }
      
      else if (damageValue == CRITICAL_SUCCESS) // case for rolling a 20
      {
        if ((playerHealth - (damageValue + 5)) > 0) // checks if player has enough health to survive the hit
      {
        playerHealth -= (damageValue + 5);
        cout << criticalSuccessMonsterMessage << playerHealth << endl;
      }
        else
        {
          playerHealth = 0;
          cout << criticalSuccessMonsterMessage << playerHealth << endl << endl;
          cout << playerDeathMessage << endl << endl;
          break;
        }
      }
      else{
        if (playerHealth - damageValue > 0){
          playerHealth -= damageValue;
          cout << "The attack hits! The monster damages for " << -damageValue << "HP to the player.  Player's current HP: " << playerHealth << endl << endl;
        }
        else{
          playerHealth = 0;
          cout << "The attack hits! The monster damages for " << -damageValue << "HP to the player.  Player's current HP: " << playerHealth << endl << endl;
          cout << playerDeathMessage<< endl << endl;
          break;
        }
      }
    }
    else
    {
      cout << noHitMessageMonster << playerHealth << endl << endl;
    }
  }


  // Executes if player has an active killstreak. Most of it is cut and paste from above
  while (killStreak > 0) // player keeps facing monsters until he dies, player dying resets their killstreak to 0, which exits the loop
  {
    playerHealth = playerMaxHealth; // resetting health here instead of after each case of defeating monster
    
    monsterType = rand() % 3; // value stored here decides which monster is to be fought.
  
    switch (monsterType){
      case 0: // assigns attributes for the Goblin
        monster = "Goblin";
        monsterHealth = 30 + rand() % (45 - 30 + 1);
        monsterArmor = rand() % 2 + 1;
        cout << "You encounter a meager goblin. This should be easy enough!" << endl;
        cout << "The monster's maximum HP is " << monsterHealth << endl;
        cout << "The monster's armor class is " << monsterArmor << endl << endl;
        break;
      case 1: // assigns attributes for the Ogre
        monster = "Ogre";
        monsterHealth = 75 + rand() % (100 - 75 + 1);
        monsterArmor = 2 + rand() % (4 - 2 + 1);
        cout << "You encounter a towering ogre. Hope you brought health potions!" << endl;
        cout << "The monster's maximum HP is " << monsterHealth << endl;
        cout << "The monster's armor class is " << monsterArmor << endl << endl;

        break;
      case 2: // assigns attributes for the dragon.
        monster = "Dragon";
        monsterHealth = 345 + rand() % (500 - 345 + 1);
        monsterArmor = 5 + rand() % (6 - 5 + 1);
        cout << "You encounter a dragon the size of a modest castle. Ruination has come!" << endl;
        cout << "The monster's maximum HP is " << monsterHealth << endl;
        cout << "The monster's armor class is " << monsterArmor << endl << endl; 
        break;
    } // end of switch
      
     // exact same loop used for fighting first monster. 
      while (true) { // loops untill either party is defeated, this is the same loop used for the first monster

        // players turn to attack 
        int playerAttack = rand() % 8 + 1;
        if (playerAttack > monsterArmor)
        {
          damageValue = rand() % 20 + 1;
      
          if (damageValue == CRITICAL_FAILURE)
          {
            if ((playerHealth - 1) > 0)
            {
              playerHealth -= 1;
              cout << criticalFailurePlayerMessage << monsterHealth << endl;
            }
            else
            {
              playerHealth = 0;
              cout << criticalFailurePlayerMessage << monsterHealth << endl;
              cout << playerDeathMessage << endl << endl;
              killStreak = 0;
              break;
            }
          }
          else if (damageValue == CRITICAL_SUCCESS)
          {
            if ((monsterHealth - (damageValue + 5)) > 0)
            {
              monsterHealth -= (damageValue + 5);

              cout << criticalSuccessPlayerMessage << monsterHealth << endl;
            }
            else
            {
              monsterHealth = 0;

              cout << criticalSuccessPlayerMessage << monsterHealth << endl;
              cout << monsterDeathMessage << endl << endl 
                   << hline << endl; // displays death message
              
              killStreak++;
              highestKillStreak++;
              break;
            }
          }
          else
          {
            if ((monsterHealth - damageValue) > 0)
            {
              monsterHealth -= damageValue;
              cout << "The attack hits! The player damages for " << -damageValue << "HP to the monster.  Monster's current HP: " << monsterHealth << endl;
            }
            else
            {
              monsterHealth = 0;
              cout << "The attack hits! The player damages for " << -damageValue << "HP to the player.  Player's current HP: " << playerHealth << endl;
              cout << monsterDeathMessage << endl << endl 
                   << hline << endl; // displays death message
              killStreak++;
              highestKillStreak++;
              break;
            }
          }
        } 
        else
        {
          cout << noHitMessagePlayer << monsterHealth << endl;
        }

        // Monsters turn to attack
        int monsterAttack = rand() % 8 + 1;

        if(monsterAttack > playerArmor) 
        {
          damageValue = rand() % 20 + 1; 

          if (damageValue == CRITICAL_FAILURE) 
          {
            if ((monsterHealth - 1) > 0){ 
            monsterHealth -= 1; 
            cout << criticalFailureMonsterMessage << playerHealth << endl << endl;
            }
            else 
            {
              monsterHealth = 0; 
              cout << criticalFailureMonsterMessage << playerHealth << endl << endl;
              cout << monsterDeathMessage << endl << endl 
                   << hline << endl; // displays death message
              killStreak++;
              highestKillStreak++;
              break;
            }
          }
      
          else if (damageValue == CRITICAL_SUCCESS) 
          {
            if ((playerHealth - (damageValue + 5)) > 0) 
          {
            playerHealth -= (damageValue + 5);
            cout << criticalSuccessMonsterMessage << playerHealth << endl;
          }
            else
            {
              playerHealth = 0;
              cout << criticalSuccessMonsterMessage << playerHealth << endl << endl;
              cout << monsterDeathMessage << endl << endl;
              killStreak = 0;
              break;
            }
          }
          else{
            if (playerHealth - damageValue > 0){
              playerHealth -= damageValue;
              cout << "The attack hits! The monster damages for " << -damageValue << "HP to the player.  Player's current HP: " << playerHealth << endl << endl;
            }
            else{
              playerHealth = 0;
              cout << "The attack hits! The monster damages for " << -damageValue << "HP to the player.  Player's current HP: " << playerHealth << endl << endl;
              cout << playerDeathMessage << endl << endl
                   << hline << endl; 
              killStreak = 0;
              break;
            }
          }
        }
        else
        {
          cout << noHitMessageMonster << playerHealth << endl << endl;
       }
      }
      }

// prints amount of monsters player defeated before dying
  cout << "Monster kill streak: " << highestKillStreak << endl;




  return 0;
}
