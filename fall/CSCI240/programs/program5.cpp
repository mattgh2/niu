
CSCI 240         Program 5     Fall 2023

Programmer: Matt Warner

Section: 240-001

Date Due: October 13, 2023

Purpose: this program simulates a battle between a Dungeon & Dragon character and a random type of monster
***************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// srand seed value
const int SEED_VALUE = 14; 

// holds the two critical hit values
const int CRITICAL_SUCCESS = 20; 
const int CRITICAL_FAILURE = 1;

// monster types
const int GOBLIN = 0;
const int OGRE = 1;
const int DRAGON = 2;

// monster encounter messages
const string GOBLIN_ENCOUNTER = "You encounter a meager goblin. This should be easy enough!";
const string OGRE_ENCOUNTER = "You encounter a towering ogre. Hope you brought health potions!"; 
const string DRAGON_ENCOUNTER = "You encounter a dragon the size of a modest castle. Ruination has come!";

// adding situation messages as variables since they are going to be used a lot
  // death messages
const string PLAYER_DEATH_MESSAGE = "Gasping for breath and realizing their mother wasn't wrong when they suggested they just stay on the farm and live a quiet life, the player passes away!";
const string MONSTER_DEATH_MESSAGE = "The monster has been slain! The adrenaline rush from the victory restores their HP to full!";

  // critical failure messages
const string CRITICAL_FAILURE_MONSTER_MESSAGE = "The attack hits! Critical failure! The monster recklessly attacks, slips and bumps their head on the floor. -1 HP. Player's current HP: ";
const string CRITICAL_FAILURE_PLAYER_MESSAGE = "The attack hits! Critical failure! The player swings wildly, loses balances, and bumps their head on a wall. -1 HP. Player's Current HP: ";

  //critical success messages
const string CRITICAL_SUCCESS_MONSTER_MESSAGE = "The attack hits! Natural 20! The monster's combat prowess becomes the stuff of nightmares, savagely rending the player, dealing -25 HP them! Player's current HP: ";
const string CRITICAL_SUCCESS_PLAYER_MESSAGE = "The attack hits! Natural 20! The player experts attacks the monster's exposed weaknesses, dealing -25 HP to it! Monster's current HP: ";

  // messages for a unsuccessful attack
const string NO_HIT_MESSAGE_PLAYER = "The player's attack fails to deal damage to the monster. Monster's current HP: ";
const string NO_HIT_MESSAGE_MONSTER = "The monster's attack fails to deal damage to the player. players's current HP: ";

  // horizontal line used to seperate battle outputs
const string H_LINE = "---------------------------------------------------------------------------------------------------------------------";



int main(){

  srand(SEED_VALUE); // setting rand seed

  // assigns player stats
  int playerMaxHealth = 50 + rand() % (150 - 50 + 1);
  int playerArmor =  rand() % 4 + 1;
  int highestKillStreak = 0;

  // outputs the players stats
  cout << "The player's maximum HP is " << playerMaxHealth << endl;
  cout << "The player's armor class is " << playerArmor << endl << endl;

  // initilizes monster related things
  int monsterHealth;
  int monsterArmor;
  int monsterType; // will be used to determine which monster is selected
  

  int playerHealth; // need this for resetting health 
  int damageValue; 
  bool alive = true; // exit condition

  while( alive == true ){ // main loop that ends when player dies

    playerHealth = playerMaxHealth; // resetting health here instead of after each case of monster defeat

    monsterType = rand() % 3; 
     
    switch (monsterType){ // assigns the monster that will be fought
    
      case GOBLIN: // sets attributes for the Goblin
        monsterHealth = 30 + rand() % (45 - 30 + 1);
        monsterArmor = rand() % 2 + 1; 
        cout << GOBLIN_ENCOUNTER << endl;
        cout << "The monster's maximum HP is " << monsterHealth << endl;
        cout << "The monster's armor class is " << monsterArmor << endl << endl;
        break;

      case OGRE: // sets attributes for the Ogre
        monsterHealth = 75 + rand() % (100 - 75 + 1);
        monsterArmor = 2 + rand() % (4 - 2 + 1);
        cout << OGRE_ENCOUNTER << endl;
        cout << "The monster's maximum HP is " << monsterHealth << endl;
        cout << "The monster's armor class is " << monsterArmor << endl << endl;
        break;

      case DRAGON: // sets attributes for the dragon.
        monsterHealth = 345 + rand() % (500 - 345 + 1);
        monsterArmor = 5 + rand() % (6 - 5 + 1);
        cout << DRAGON_ENCOUNTER << endl;
        cout << "The monster's maximum HP is " << monsterHealth << endl;
        cout << "The monster's armor class is " << monsterArmor << endl << endl; 
        break;

    } // end of switch
    
    while (true) { // loop responsible for fighting monsters, manually breaks out of loop in the event of a death, will break out of top loop aswell if player dies
      
      // players turn to attack 
      int playerAttack = rand() % 8 + 1; // simulates the roll of an 8 sided die
    
      if (playerAttack > monsterArmor) // executes code for attacking if player rolls a number higher the value of the monsters armor
      {
        damageValue = rand() % 20 + 1; // simulates rolling a 20 sided die, used for determining damage output
      
        if (damageValue == CRITICAL_FAILURE) // case for rolling a 1 from the 20 sided die
        {
          if ((playerHealth - 1) > 0) // checks if healthy
          {
            playerHealth -= 1;

            cout << CRITICAL_FAILURE_PLAYER_MESSAGE << playerHealth << endl;
          }
          else
          {
            playerHealth = 0;

            cout << CRITICAL_FAILURE_PLAYER_MESSAGE << playerHealth << endl;
            cout << PLAYER_DEATH_MESSAGE << endl << endl
                 << H_LINE << endl;
            alive = false; // exit condition for outer loop
            break;  
          }
        }
        else if (damageValue == CRITICAL_SUCCESS) // case for rolling a 20
        {

          if ((monsterHealth - (damageValue + 5)) > 0) // checks if healthy
          {
            monsterHealth -= (damageValue + 5); 

            cout << CRITICAL_SUCCESS_PLAYER_MESSAGE << monsterHealth << endl;
          }

          else // executes this block if not healthy
          {
            monsterHealth = 0; 

            cout << CRITICAL_SUCCESS_PLAYER_MESSAGE << monsterHealth << endl;
            cout << MONSTER_DEATH_MESSAGE << endl << endl
                 << H_LINE << endl; 

            highestKillStreak++; // adds one to the killstreak count
            break; 
          }

        }
        else // case for rolling a non critical value
        {
          if ((monsterHealth - damageValue) > 0) // checks if healthy
          {
            monsterHealth -= damageValue; 
            cout << "The attack hits! The player damages for " << -damageValue << "HP to the monster.  Monster's current HP: " << monsterHealth << endl;
          }
          else // not healthy
          {
            monsterHealth = 0;

            cout << "The attack hits! The player damages for " << -damageValue << "HP to the player.  Player's current HP: " << playerHealth << endl;
            cout << MONSTER_DEATH_MESSAGE << endl << endl 
                 << H_LINE << endl; 

            highestKillStreak++; // adds 1 to kill count
            break;
          }
        }
      } 
      else // attack value was not high enough to land
      {
        cout << NO_HIT_MESSAGE_PLAYER << monsterHealth << endl;
      }

    // Monsters turn to attack
    
      int monsterAttack = rand() % 8 + 1; // rolls the 8-sided die

      if(monsterAttack > playerArmor) // executues if value in monsterAttack value is high enough
     {
        damageValue = rand() % 20 + 1;  // rols the 20-sided die

        if (damageValue == CRITICAL_FAILURE) // case for rolling a 1 
        {
          if ((monsterHealth - 1) > 0){ // checks if monster survives critical failure 
          
          monsterHealth -= 1; 
          cout << CRITICAL_FAILURE_MONSTER_MESSAGE << playerHealth << endl << endl;
          }

          else // monster did not survive critical failure
          {
            monsterHealth = 0;

            cout << CRITICAL_FAILURE_MONSTER_MESSAGE << monsterHealth << endl << endl;
            cout << MONSTER_DEATH_MESSAGE << endl << endl 
                 << H_LINE << endl; 
            
            highestKillStreak++;
            break;
          }
        }
      
        else if (damageValue == CRITICAL_SUCCESS) // case for rolling a 20
        {
          if ((playerHealth - (damageValue + 5)) > 0) // checks if player has enough health to survive the hit
        {
          playerHealth -= (damageValue + 5);
          cout << CRITICAL_SUCCESS_MONSTER_MESSAGE << playerHealth << endl;
        }
          else // not healthy enough 
          {
            playerHealth = 0;
            cout << CRITICAL_SUCCESS_MONSTER_MESSAGE << playerHealth << endl << endl;
            cout << PLAYER_DEATH_MESSAGE << endl << endl
                 << H_LINE << endl;
            alive = false;
            break;
          }
        }
        else{ // didnt roll a critical hit
          
          if (playerHealth - damageValue > 0){ // health check
            playerHealth -= damageValue;
            cout << "The attack hits! The monster damages for " << -damageValue << "HP to the player.  Player's current HP: " << playerHealth << endl << endl;
          }
          else{ // not healthy enough
            playerHealth = 0;
            cout << "The attack hits! The monster damages for " << -damageValue << "HP to the player.  Player's current HP: " << playerHealth << endl << endl;
            cout << PLAYER_DEATH_MESSAGE << endl << endl
                 << H_LINE << endl;
            alive = false;
            break;
          }
        }
      }
      else // attack didnt hit
      {
        cout << NO_HIT_MESSAGE_MONSTER << playerHealth << endl << endl;
      }
    }
  }
  // printing players total kill count
  cout << "Monster kill streak: " << highestKillStreak << endl;

  return 0;
}
