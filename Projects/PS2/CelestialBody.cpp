/*
Name: Erson Ramirez Mendoza 

Course: Computing IV 

Assignment: PS2 (Part B) 

Instructor: Dr. Daly 
Due Date: 2/22/2022

Program Description:
// PS2B
This program will build on the planetary simulation I began to work on last week. 
This part of the project requires me to make the planets move with their own orbits
using velocity and acceleration logic.
*/

// Graphics 
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
// General
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
// Personal
#include "CelestialBody.h"
#include "Universe.h"

using namespace std;

const double gravity = 6.67e-11;

// CELESTIAL BODY FUNCTIONS
// Default Constructor (This constructor doesn’t do much)
CelestialBody::CelestialBody() {
    x = 0;
    y = 0;
    xvel = 0;
    yvel = 0;
    mass = 0;
    filename = "NOT SET";
}

// Overloaded Insertion Operator (This is where I get the information I need to create the sprites)
istream &operator>>(istream &ls, CelestialBody &c) {
    ls >> c.x >> c.y >> c.xvel >> c.yvel >> c.mass >> c.filename;
    
    // Load the image from within this overload so that it can be used!
    if (!c.texture.loadFromFile(c.filename)) {
        cout << "Could not load texture" << endl;
    }
    
    c.obj_sprite.setTexture(c.texture);
    c.updateSpritePosition(c.x, c.y);
    return ls;
}

// Draw the sprite within this current object 
void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(obj_sprite, states);
}

// Return the sprite that is within the current CelestialBody Object
sf::Sprite CelestialBody::getSprite() const {
    return obj_sprite;
}

// Set information for the object
void CelestialBody::setInformation(double r, double w, double h) {
    universeRadius = r;
    windowWidth = w;
    windowHeight = h;
}

// UNIVERSE FUNCTIONS
Universe::Universe() {
    // Get the number of planets and the radius of the universe from STDIN
    cin >> numPlanets;
    cin >> radius;
    
    // Loop until 5 pointers to celestial objects are created
    for(int i = 0; i < numPlanets; i++) {
        _planets.push_back(make_unique<CelestialBody>());
    }
    
    // Update the information for each planet in the vector
    for(auto& planet : _planets) {
        // Set the general information first before getting planet details
        // Avoids bugs later 
        planet->setInformation(radius, width, height);
        cin >> *planet;
    }
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw all CelestialBody Objects included in the planet vector
    for(auto& planet : _planets) {
        target.draw(planet->getSprite(), states);
    }
}

// NEW PS2B FUNCTIONS
// This function will update the x and y velocities of a celestial body object
void CelestialBody::updateVelocity(double xv, double yv) {
    xvel = xv;
    yvel = yv;
}

// Updates the position of the sprite with scaling in mind
void CelestialBody::updateSpritePosition(double x, double y) {
    this->x = x;
    this->y = y;

    // Calculate where in the window it should be
    double true_x = (universeRadius + x) * (windowWidth / (universeRadius * 2));
    double true_y = (universeRadius - y) * (windowHeight / (universeRadius * 2)); 

    // Set the position 
    obj_sprite.setPosition(true_x, true_y);
}

// Accessor Functions
double CelestialBody::getXVel() const {
    return xvel;
}

double CelestialBody::getYVel() const {
    return yvel;
}

double CelestialBody::getMass() const {
    return mass;
}

double CelestialBody::getX() const {
    return x;
}

double CelestialBody::getY() const {
    return y;
}

// New Universe functions 
// Step will update all the positions of the celestial body objects
// using the leapfrog calculation technique described in the PDF
// Each object will have a new updated position along with new x/y velocities!

// This net force function will take a mass, x_pos and a y_pos
// Using this information, I create a loop that gets the same information 
// for every other planet and use it to calculate the net Fx and net Fy. 
// I then return a vector2f since the function needs to return both total Fx and total Fy
sf::Vector2f CelestialBody::net_force(vector<unique_ptr<CelestialBody>>& planets) {
    sf::Vector2f totalForce;
    for (auto& planet : planets) {
        // Check if planet is itself 
        if (this == planet.get()) {
            continue;
        }

        // Get second planet info
        double mass2 = planet->getMass();
        double x2 = planet->getX();
        double y2 = planet->getY();

        // Calculate Delta X and Y 
        double deltaX = x2 - x;
        double deltaY = y2 - y;

        // Calculation of Net Force 
        double r = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
        double force = ((gravity * mass * mass2) / pow(r, 2));
        double fX = force * (deltaX / r);
        double fY = force * (deltaY / r);

        totalForce.x += fX;
        totalForce.y += fY;   
    }
    return totalForce;
}

void Universe::step(double seconds) {
    // Forces
    sf::Vector2f _force;
    for (auto& planet : _planets) {
        // Get the values 
        double x_vel = planet->getXVel();
        double y_vel = planet->getYVel();
        double mass = planet->getMass();
        double x_pos = planet->getX();
        double y_pos = planet->getY();

        _force = planet->net_force(_planets);
        // Split the force (fY seems to always be 0)
        double fX = _force.x;
        double fY = _force.y;
        // Calculation of Acceleration 
        double x_acc = fX / mass;
        double y_acc = fY / mass;
        // Calculation of New Velocity
        x_vel += seconds * x_acc;
        y_vel += seconds * y_acc;
        // Calculation of New Position
        x_pos += seconds * x_vel;
        y_pos += seconds * y_vel;
        // Update the new position and the velocity
        planet->updateVelocity(x_vel, y_vel);
        planet->updateSpritePosition(x_pos, y_pos);
    }
}

// Overloaded Ostream Operator for CelestialBody
ostream &operator<<(ostream &ls, const CelestialBody &c) {
    ls << c.x << " " << c.y << " " << c.xvel << " " << c.yvel << " " << c.mass << " " << c.filename;
    return ls;
}

// Overloaded OStream Operator for Universe
ostream &operator<<(ostream &ls, const Universe &c) {
    ls << c.numPlanets << endl;
    ls << c.radius << endl;
    for (auto& planet : c._planets) {
        ls << *planet << endl;
    }
    return ls;
}
