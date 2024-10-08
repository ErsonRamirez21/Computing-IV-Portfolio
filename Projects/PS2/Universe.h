/*
Name: Erson Ramirez Mendoza 

Course: Computing IV 

Assignment: PS2 (Part B) 

Instructor: Dr. Daly 
Due Date: 2/22/2022

Program Description:
//PS2B
This program will build on the planetary simulation I began to work on last week. 
This part of the project requires me to make the planets move with their own orbits
using velocity and acceleration logic.
*/

#ifndef UNIVERSE_H
#define UNIVERSE_H

// Graphics 
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// General
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

class Universe : public sf::Drawable {
public:
    // Default Constructor
    Universe();

    // PS2B Functions
    // This function should move the celestial body object using its own velocity for a set amount of seconds 
    // set by the parameter
    void step(double seconds);

    // Overloaded Insertion Operator
    friend ostream &operator<<(ostream &ls, const Universe &c);

private:
    // Vector that contains pointers to CelestialBody objects
    vector<unique_ptr<CelestialBody>> _planets;

    // Another override for the draw function
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // General Settings
    int numPlanets;
    double radius;
    double width = 512;
    double height = 512;
};

// Overloaded Insertion Operator
ostream &operator<<(ostream &ls, const Universe &c);

#endif
