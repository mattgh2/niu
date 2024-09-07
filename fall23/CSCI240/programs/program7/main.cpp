/***************************************************************
CSCI 240         Program 7       Fall 2023

Programmer: Matt Warner

Section: 240-001 

Date Due: November 3, 2023

Purpose: Reads data from a file, stores in arrays, then outputs the data
***************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;

const int SIZE_ARRAY = 30;
const int COLUMN_WIDTH = 16;
// function prototypes
int build(string[], string[], int[], int[], int[]);
void print(string[], string[], int[], int[], int[], int);
void sort(string[], string[], int[], int[], int[], int);

int main(){
  
  // array initilization
  string seasonNames[SIZE_ARRAY];
  string cropNames[SIZE_ARRAY];
  int seedCosts[SIZE_ARRAY];
  int saleValues[SIZE_ARRAY];
  int numberOfDays[SIZE_ARRAY];
  
  int cropAmount = build(seasonNames, cropNames, seedCosts, saleValues, numberOfDays);
  // function calls
  print(seasonNames, cropNames, seedCosts, saleValues, numberOfDays, cropAmount);
  sort(seasonNames, cropNames, seedCosts, saleValues, numberOfDays, cropAmount);
  print(seasonNames, cropNames, seedCosts, saleValues, numberOfDays, cropAmount);
  
  return 0;
}


/***************************************************************
Function: build 

Use: build 

Arguments: 4 arrays that are the seasons, names, seed costs, sell,values, harvest times. An int variable that is the length of the arrays

Returns: the amount of crops, i.e. the length of the arrays

Notes: grabs the data from the text file, then builds the arrays with the data
***************************************************************/
int build(string season[], string name[], int seed_cost[], int sell_value[], int harvest_time[]){

  ifstream infile("crops.txt"); // input file stream variable
  
  
  if (infile.fail()){ // checks if the file failed to open
    cout << "crops.txt failed to open" << endl; // outputs error message
    exit(-1);
  }

  // variables that temperarily store the data before adding it to our arrays
  string season_name, crop_name; 
  int seedCost, saleValue, Days;

  int index = 0; // indices for the the parallel arrays
  
  infile >> season_name; // primary read
  while (infile){ // reads data from file and stores in into the corresponding arrays
  
    // storing data from text file into variables 
    infile >> crop_name >> seedCost >> saleValue >> Days;

    // adding data to their corresponding arrays
    season[index] = season_name; 
    name[index] = crop_name;
    seed_cost[index] = seedCost;
    sell_value[index] = saleValue;
    harvest_time[index] = Days;

    index++; // moves to next index
    
    infile >> season_name; // secondary read
  }
  infile.close(); // closing file

  int amountOfCrops = index; // grabs the length of the arrays, that is the index value

 return amountOfCrops; // returns the length of the arrays
}


/***************************************************************
Function: print

Use: outputs all the arrays

Arguments: 4 arrays that are the seasons, names, seed costs, sell,values, harvest times. An int variable that is the length of the arrays

Returns:  Nothing

Notes: formats and prints the arrays in nicely arranged columns
***************************************************************/
void print(string season[], string name[], int seed_cost[], int sell_value[], int harvest_time[], int num_of_crops){

  cout << setw(30) << right << "" << "Gold Profit Per Day Report for All Crops" << endl <<endl;
  cout << setw(COLUMN_WIDTH) << right << "Season" << setw(COLUMN_WIDTH) << right << "Crop Name" << setw(COLUMN_WIDTH) << right << "Seed Cost" << setw(COLUMN_WIDTH) << right << "Sell Value" << setw(COLUMN_WIDTH) << right << "Harvest Time" << setw(COLUMN_WIDTH) << right << "Gold Profit/Day" << endl;
  for (int i = 0; i < 96; i++){
    cout << "-";
  }
  cout << endl;
  for (int i = 0; i < num_of_crops; i++){
    double profit = (double)(sell_value[i] - seed_cost[i]) / harvest_time[i]; // performing profit calculation 

    // outputting arrays
    cout << setw(COLUMN_WIDTH) << right << season[i];
    cout << setw(COLUMN_WIDTH) << right << name[i];
    cout << setw(COLUMN_WIDTH) << right << seed_cost[i];
    cout << setw(COLUMN_WIDTH) << right << sell_value[i];
    cout << setw(COLUMN_WIDTH) << right << harvest_time[i];
    cout << setw(COLUMN_WIDTH) << right << setprecision(2) << fixed << profit;
    cout << endl;
  }
}


/***************************************************************
Function: sort

Use: Sorts the arrays in decending order based on Profit per day

Arguments: array of seasons, names, seed costs, sell values, harvest times, and an int varible that is the length of the arrays.


Returns: Nothing

Notes: 
***************************************************************/
void sort(string season[], string name[], int seed_cost[], int sell_value[], int harvest_time[], int num_of_crops){
  double profit[num_of_crops]; // initilization array to store profits
  for (int i = 0; i < num_of_crops; i++){
    profit[i] = (double)(sell_value[i] - seed_cost[i]) / harvest_time[i]; // calculates and stores profit
  }
  // selection sort
  for (int i = 0; i < num_of_crops - 1; i++){
    int largest = i; // initilizes index with largest value to the current position in the loop
    for (int j = i + 1; j < num_of_crops; j++){ // inner loops that captures the index holding the largest number in the array
      if (profit[j] > profit[largest]){
        largest = j; // captures the index with the largest value
      }
    }
    if (i != largest){ // if current index doesn't hold largest value, perform swap
      
      // declaring variables to temperarily store values that are stored in current index
      int temp_profit = profit[i], temp_seedCost = seed_cost[i], temp_sellValue = sell_value[i], temp_harvestTime = harvest_time[i];
      string temp_season = season[i], temp_name = name[i];

      // swapping value in current position for captured value
      profit[i] = profit[largest];
      season[i] = season[largest];
      name[i] = name[largest];
      seed_cost[i] = seed_cost[largest];
      sell_value[i] = sell_value[largest];
      harvest_time[i] = harvest_time[largest];
      
      // swapping largest value for value in current positon
      profit[largest] = temp_profit;
      season[largest] = temp_season;
      name[largest] = temp_name;
      seed_cost[largest] = temp_seedCost;
      sell_value[largest] = temp_sellValue;
      harvest_time[largest] = temp_harvestTime;
    }
  }
}
