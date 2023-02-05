// Joshua Baron

// Purpose: The purpose of this program is to read a binary file containing lap times and
// evaluate the data computing different statistics.
// Description: This program takes in any amount of binary files containing lap times
// and then reads eachs file computing the average of times among laps, the longest lap,
// the shortest lap, and the sum of the lap times. Once the files are read, the program
// prints out a menu where you can see the average of times across all files,
// the file names and the sum of all times in the files.


#include <iostream>
#include "fileUtils.h"
#include <fstream>
#include <string>

using namespace std;


// Structure to hold data
struct Stats{
  string name;
  int max;
  int min;
  int size;
  int average;
  int sum;
};


// Reads the files and computes statistics
Stats readFile(char *filename);

int main(int argc, char *argv[]) {
  bool exit = false;   // Exits the program
  int sumOfSums; // Sum of sums of lap times.
  int averageOfAverages; // Average of averages of lap times.
  string userFileName; // the file name the user inputs
  int option; // Chooses an option from the menu
  string* fileNames = new string[argc - 1]; // Array for file names
  Stats* dataArr = new Stats[argc - 1]; // Array of structures for the data

  // Reads the files and puts the data into array of structures
  for (int i = 0; i < argc - 1; i++) {
    char *filename = argv[i + 1];
    fileNames[i] = argv[i + 1];
    dataArr[i] = readFile(filename);
  }

  // Prints the menu
  while (exit == false) {
    cout << "(1) List the names of the files that have been loaded." << endl;
    cout << "(2) Show summary stats for a certain file." << endl;
    cout << "(3) Show the average of the average times across all files." << endl;
    cout << "(4) Show the total time combined across all files." << endl;
    cout << "(5) Exit the program." << endl;
  
    cout << "What option would you like? ";
    cin >> option;
    cout << endl;
    // Switch statement to go through each menu option
    switch (option) {
      case 1:
        for (int i = 0; i < argc - 1; i++) {
          cout << fileNames[i];
        }
        cout << endl;
        break;
      case 2:
        cout << "What file do you want the statistics for? ";
        cin >> userFileName;
        for (int i = 0; i < argc - 1; i++) {          
          if (userFileName == dataArr[i].name) {
            cout << "Min: " << dataArr[i].min << endl;
            cout << "Max: " << dataArr[i].max << endl;
            cout << "Average: " << dataArr[i].average << endl;
            cout << "Sum: " << dataArr[i].sum << endl;
          }
        }
        break;
      case 3:
        cout << dataArr[0].average;
        for (int i = 0; i < argc - 1; i++) {
          averageOfAverages += (dataArr[i].average / (i + 1));
        }
        cout << averageOfAverages;
        break;
      case 4:
        for (int i = 0; i < argc - 1; i++) {
          sumOfSums += dataArr[i].sum;
        }
        break;
      case 5:
        exit = true;
        break;
      default:  
        cout << "Invalid input. Type a number (1-5). " << endl;
      }
  }
  delete []dataArr;
  delete []fileNames;
  }
}

Stats readFile(char *filename) {
  ifstream input; // input file
  Stats data; // Structure to store data               
  int max; // longest lap time
  int min; // shortest lap time
  int sum; // sum of lap times
  int average; // average of lap times
  int lapTime;
  data.name = filename;
  input.open(filename);
  int numEntries = readByte(input);
  lapTime = readInt(input);
  max = lapTime;
  min = lapTime;
  average = lapTime;
  sum = lapTime;
  cout << "Lap 1: " << lapTime << " ";
  for (int i = 1; i < numEntries; i++) {
    lapTime = readInt(input);
    cout << "Lap " << (i + 1) << ": " << lapTime << " ";
    
    if (lapTime > max) {
      max = lapTime;
    }
    if (lapTime < min){
      min = lapTime;
    }
    sum += lapTime;
  }
  average = sum / numEntries;
  cout << endl;
  data.min = min;
  data.average = average;
  data.max = max;
  data.sum = sum;

  input.close();

  return data;
 }
