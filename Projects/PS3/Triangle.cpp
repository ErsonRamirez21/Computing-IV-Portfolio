// Copyright [2022] <Erson Ramirez Mendoza>
// Personal
#include "Triangle.h"

// General
#include <iostream>
#include <cmath>

// Graphics
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const double center = 300;

// This constructor will just position one triangle at the center
Triangle::Triangle(double length) {
    baseLength = length;
    height = (baseLength * sqrt(3)) / 2;

    // Set the triangle info
    triangle.setPointCount(3);

    // Triangle Properties
    triangle.setFillColor(sf::Color::Black);
    triangle.setOutlineThickness(2);
    triangle.setOutlineColor(sf::Color::Magenta);

    // Set points to draw at the center-ish
    triangle.setPoint(0, sf::Vector2f(center, center));
    triangle.setPoint(1, sf::Vector2f(center + baseLength, center));
    triangle.setPoint(2, sf::Vector2f(center + (baseLength / 2), center + height));

    // Save the point information
    p1 = triangle.getPoint(0);
    p2 = triangle.getPoint(1);
    p3 = triangle.getPoint(2);
}

// This constructor will position a triangle at the given vector2f point
Triangle::Triangle(double length, sf::Vector2f point) {
    baseLength = length;
    height = (baseLength * sqrt(3)) / 2;

    // Set the triangle info
    triangle.setPointCount(3);

    // Triangle Properties
    triangle.setFillColor(sf::Color::Black);
    triangle.setOutlineThickness(2);
    triangle.setOutlineColor(sf::Color::Cyan);

    // Set points to draw at the specified point
    triangle.setPoint(0, sf::Vector2f(point.x, point.y));
    triangle.setPoint(1, sf::Vector2f(point.x + baseLength, point.y));
    triangle.setPoint(2, sf::Vector2f(point.x + (baseLength / 2), point.y + height));

    // Save the point information
    p1 = triangle.getPoint(0);
    p2 = triangle.getPoint(1);
    p3 = triangle.getPoint(2);
}

// Overloaded Draw Function
void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(triangle, states);
}

// Accessors
double Triangle::getLength() const { return baseLength; }
double Triangle::getHeight() const { return height; }
sf::Vector2f Triangle::getP1() const { return p1; }
sf::Vector2f Triangle::getP2() const { return p2; }
sf::Vector2f Triangle::getP3() const { return p3; }
