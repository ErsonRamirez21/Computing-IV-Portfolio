// Copyright [2022] <Erson Ramirez Mendoza>
#ifndef _ROOT_PS3_TRIANGLE_H_
#define _ROOT_PS3_TRIANGLE_H_

// General
#include <iostream>
#include <cmath>

// Graphics
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Class Triangle will hold information for a triangle object
class Triangle : public sf::Drawable {
public:
    // Constructors
    explicit Triangle(double length);
    Triangle(double length, sf::Vector2f point);

    // Accessors
    double getLength() const;
    double getHeight() const;
    sf::Vector2f getP1() const;
    sf::Vector2f getP2() const;
    sf::Vector2f getP3() const;

private:
    // Overload draw function from Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Triangle dimensions and points
    double baseLength, height;
    sf::ConvexShape triangle;  // SFML shape to represent the triangle
    sf::Vector2f p1, p2, p3;    // Triangle points going from left -> right -> bottom
};

#endif  // _ROOT_PS3_TRIANGLE_H_
