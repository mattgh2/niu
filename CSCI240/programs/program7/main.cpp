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
using namespace std;

int main(){
  
  // array initilization
  string seasonNames[24];
  string cropNames[24];
  int seedCosts[24];
  int saleValues[24];
  int numberOfDays[24];
 
  ifstream infile; // input file stream variable
  
  infile.open("crops.txt"); // open the file for reading
  
  if (infile.fail()){
    cout << "crops.txt failed to open" << endl;
    exit(-1);
  }

  // variables that temperarily store the data before adding it to our arrays
  string season_name, crop_name; 
  int seed_cost, sale_value, days;

  int index = 0; // indices for the the parallel arrays
  
  infile >> season_name; // primary read
  while (infile){ // reads data from file and stores in into the corresponding arrays
    
    infile >> crop_name;
    infile >> seed_cost;
    infile >> sale_value;
    infile >> days;

    // adding data to arrays 
    seasonNames[index] = season_name; 
    cropNames[index] = crop_name;
    seedCosts[index] = seed_cost;
    saleValues[index] = sale_value;
    numberOfDays[index] = days;

    index++; // next subscript
    
    infile >> season_name; // secondary read
  }
  infile.close(); // closing file
  
  return 0;
}
void sort(string season[], string name[], int seed_cost[], int sell_value[], int harvest_time[], int num_of_crops){

}
