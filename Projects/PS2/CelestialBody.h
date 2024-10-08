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

#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

// Graphics 
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// General
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// This class will hold the information for one planet
class CelestialBody : public sf::Drawable {
public:
    // Default Constructor
    CelestialBody();
    
    // Overloaded Insertion Operator
    friend istream &operator>>(istream &ls, CelestialBody &c);
    // Overloaded Insertion Operator
    friend ostream &operator<<(ostream &ls, const CelestialBody &c);

    // PS2B Mutator and Accessor Functions
    // Accessor
    sf::Sprite getSprite() const;
    double getXVel() const;
    double getYVel() const;
    double getMass() const;
    double getX() const;
    double getY() const;

    // Setters
    void setInformation(double r, double w, double h);
    void updateVelocity(double xy, double yv);
    void updateSpritePosition(double x, double y);
    sf::Vector2f net_force(vector<unique_ptr<CelestialBody>> &planets);

private:
    // Planet Data
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    double x, y, xvel, yvel, mass;
    string filename;

    // Graphical Data 
    sf::Texture texture;
    sf::Sprite obj_sprite;

    // General Data needed for scaling
    double universeRadius;
    double windowWidth;
    double windowHeight;
};

// Overloaded Insertion Operator
istream &operator>>(istream &ls, CelestialBody &c);
// Overloaded Insertion Operator
ostream &operator<<(ostream &ls, const CelestialBody &c);

#endif
