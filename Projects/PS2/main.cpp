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

// Graphics
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
// Audio
#include <SFML/Audio.hpp>
// General
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
// Personal
#include "CelestialBody.h"
#include "Universe.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Get the required information from argv
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <total_time> <delta_time>" << endl;
        return 1;
    }

    double T = stod(argv[1]);
    double deltaT = stod(argv[2]);

    // Store the elapsed time
    double curT = 0.0;

    // Background Image
    sf::Texture b;
    if (!b.loadFromFile("background.jpg")) {
        cerr << "Error loading background image!" << endl;
        return 1;
    }
    sf::Sprite s;
    s.setTexture(b);

    // Window Settings
    sf::RenderWindow window(sf::VideoMode(512, 512), "The Universe");
    // Limit the windows to 60 fps
    window.setFramerateLimit(60);

    // Create a universe object
    Universe uniObj;

    // Text
    sf::Font font;
    if (!font.loadFromFile("BebasNeue-Regular.ttf")) {
        cerr << "Error loading font!" << endl;
        return 1;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Italic);

    // Audio (This doesn’t work on my computer. I believe it’s just an issue with Windows 10)
    sf::Music music;
    if (!music.openFromFile("Too Eazy.wav")) {
        return -1;
    }
    music.play();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        // Draw the background
        window.draw(s);

        if (curT < T) {
            uniObj.step(deltaT);
            curT += deltaT;
        }

        // Calculate the current time in minutes
        double minutes = curT / 60;
        string currentTimeString = to_string(minutes);
        
        if (curT < T) {
            text.setString("Elapsed Time (In Minutes): " + currentTimeString);
        } else {
            // Display the Final Time Results
            text.setString("Final Time (In Minutes): " + currentTimeString);
        }

        window.draw(text);
        // Draw the Universe
        window.draw(uniObj);
        window.display();
    }

    cout << uniObj << endl;
    return 0;
}
