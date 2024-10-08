/*
Name: Erson Ramirez Mendoza 

Course: Computing IV 

Assignment: PS1 (Part B) 

Instructor: Dr. Daly 
Due Date: 2/7/2022

Program Description:
    This program is meant to replicate a Linear Feedback Shift Register 
    and how this can generate a new sequence of 0s and 1s by left shifting.
    The next bit appended to the end is a result of XORing 4 tap bits. 

    This next part of the assignment requires me to implement a way to encode
    decode png images using the LBSR that I made in part 1 of this assignment.
*/

#include <iostream>
#include <string>

using namespace std;

//Implementation of LFSR (Not actually using bits just simulating using integers of 0 or 1)
class FibLFSR {
public:
    //Document Functions:
    FibLFSR(string seed);
    int step();
    int generate(int k);
    friend ostream& operator <<(ostream& out, const FibLFSR& FibLFSR);
    
    //Personal Functions:
    int zeroOrOne(char a);
    char intToChar(int b);
    
    //Accessors:
    string getSeed() const; //Return the current seed
    int getLength() const; // Return the length of current seed

private:
    string currentSeed;
    int seedLength;
};
