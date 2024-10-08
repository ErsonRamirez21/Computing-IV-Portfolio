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

//Graphics 
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "FibLFSR.h"

//Constructor
FibLFSR::FibLFSR(string seed) {
    currentSeed = seed;
    seedLength = seed.size();
}

//Step functions 
int FibLFSR::step() {
    //Calculate the new bit that will be added to the end of the new array (Using tap positions 15, 13, 12, 10)
    int newBit = ((zeroOrOne(currentSeed[0]) ^ zeroOrOne(currentSeed[2])) 
                  ^ zeroOrOne(currentSeed[3])) ^ zeroOrOne(currentSeed[5]);

    //Shift the characters to the left by one 
    string temp = currentSeed;
    for (int i = 0; i < seedLength - 1; i++) {
        temp[i] = temp[i + 1];
    }
    //Add the new bit to the end of the string and update the currentSeed
    temp[seedLength - 1] = intToChar(newBit);
    currentSeed = temp;
    seedLength = temp.size();
    return newBit;
}

int FibLFSR::generate(int k) {
    int a = 0;
    for (int i = 0; i < k; i++) {
        a = a * 2;
        a += step();
    }
    return a;
}

//Prints out the current seed 
ostream& operator <<(ostream& out, const FibLFSR& FibLFSR) {
    out << FibLFSR.getSeed();
    return out;
}

//Function to check if a character is a zero or a one 
int FibLFSR::zeroOrOne(char a) {
    if (a == 48) {
        return 0;
    }
    else if (a == 49) {
        return 1;
    }
    else {
        return -1;
    }
}

//Function to convert an integer 0 or 1 to a character 0 or 1
char FibLFSR::intToChar(int b) {
    if (b == 0) {
        return '0';
    }
    else if (b == 1) {
        return '1';
    }
    else {
        return '2';
    }
}

//Accessors:
string FibLFSR::getSeed() const { return currentSeed; } 
int FibLFSR::getLength() const { return seedLength; } 
