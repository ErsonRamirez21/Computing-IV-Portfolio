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

// Window Settings (Universal so that my function can draw from within)
sf::RenderWindow window(sf::VideoMode(800, 800), "Triangles");

// Recursive Function for Drawing Triangles
void fTree(Triangle &temp, int depth);

// Main Function
int main(int argc, char *argv[]) {
    // Get the command line arguments
    double length = std::stod(argv[1]);
    int recursionDepth = std::stoi(argv[2]);

    Triangle beginTriangle(length);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        // Start the recursion
        fTree(beginTriangle, recursionDepth);
        window.display();
    }
    return 0;
}

// Implementation of Recursive Function for Drawing Triangles
void fTree(Triangle &temp, int depth) {
    if (depth <= 1) {
        // Draw the triangle
        window.draw(temp);
        return;
    }

    // Set triangle data
    double length = temp.getLength();
    double height = temp.getHeight();
    Triangle tAngle1((length / 2), temp.getP1() - sf::Vector2f(length / 4, height / 2));
    Triangle tAngle2((length / 2), temp.getP2());
    Triangle tAngle3((length / 2), temp.getP3() - sf::Vector2f(length / 2, 0));

    // Draw the triangles
    window.draw(temp);
    window.draw(tAngle1);
    window.draw(tAngle2);
    window.draw(tAngle3);

    // Make triangles for these as well
    fTree(tAngle1, depth - 1);
    fTree(tAngle2, depth - 1);
    fTree(tAngle3, depth - 1);
}
