/***************************************************************
CSCI 240         Program 7       Fall 2023

Programmer: Matt Warner

Section: 240-001 

Date Due: November 3, 2023

Purpose: 
****************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

const int SIZE_ARRAY = 30;
const int COLUMN_WIDTH = 16;

// function prototypes
int build(string[], string[], int[], int[], int[]);
void print(string[], string[], int[], int[], int[], int);

int main(){
  
  // array initilization
  string seasonNames[SIZE_ARRAY];
  string cropNames[SIZE_ARRAY];
  int seedCosts[SIZE_ARRAY];
  int saleValues[SIZE_ARRAY];
  int numberOfDays[SIZE_ARRAY];
  
  int cropAmount = build(seasonNames, cropNames, seedCosts, saleValues, numberOfDays);
  print(seasonNames, cropNames, seedCosts, saleValues, numberOfDays, cropAmount);
  
  
  return 0;
}
int build(string season[], string name[], int seed_cost[], int sell_value[], int harvest_time[]){

  ifstream infile; // input file stream variable
  
  infile.open("crops.txt"); // open the file for reading
  
  if (infile.fail()){
    cout << "crops.txt failed to open" << endl;
    exit(-1);
  }

  // variables that temperarily store the data before adding it to our arrays
  string season_name, crop_name; 
  int seedCost, saleValue, Days;

  int index = 0; // indices for the the parallel arrays
  
  infile >> season_name; // primary read
  while (infile){ // reads data from file and stores in into the corresponding arrays
    
    infile >> crop_name;
    infile >> seedCost;
    infile >> saleValue;
    infile >> Days;

    // adding data to arrays 
    season[index] = season_name; 
    name[index] = crop_name;
    seed_cost[index] = seedCost;
    sell_value[index] = saleValue;
    harvest_time[index] = Days;

    index++; // next subscript
    
    infile >> season_name; // secondary read
  }
  infile.close(); // closing file

  int amountOfCrops = index; 

 return amountOfCrops; 
}

void print(string season[], string name[], int seed_cost[], int sell_value[], int harvest_time[], int num_of_crops){

  cout << setw(30) << right << "" << "Gold Profit Per Day Report for All Crops" << endl <<endl;
  cout << setw(COLUMN_WIDTH) << right << "Season" << setw(COLUMN_WIDTH) << right << "Crop Name" << setw(COLUMN_WIDTH) << right << "Seed Cost" << setw(COLUMN_WIDTH) << right << "Sell Value" << setw(COLUMN_WIDTH) << right << "Harvest Time" << setw(COLUMN_WIDTH) << right << "Gold Profit/Day" << endl;
  for (int i = 0; i < 96; i++){
    cout << "-";
  }
  cout << endl;
  for (int i = 0; i < num_of_crops; i++){
    double profit = (double)(sell_value[i] - seed_cost[i]) / harvest_time[i]; // performing profit calculation


    cout << setw(COLUMN_WIDTH) << right << season[i];
    cout << setw(COLUMN_WIDTH) << right << name[i];
    cout << setw(COLUMN_WIDTH) << right << seed_cost[i];
    cout << setw(COLUMN_WIDTH) << right << sell_value[i];
    cout << setw(COLUMN_WIDTH) << right << harvest_time[i];
    cout << setw(COLUMN_WIDTH) << right << setprecision(2) << fixed << profit;
    cout << endl;
  }
}
void sort(string season[], string name[], int seed_cost[], int sell_value[], int harvest_time[], int num_of_crops){
  for (int i = num_of_crops - 1; i > 0; i--){
    int min = i;
    for (int j = i - 1; j >= 0; j--){
      if ()
    }
  }
}
