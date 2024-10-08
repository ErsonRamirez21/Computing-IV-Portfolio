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
//Personal 
#include <iostream>
#include <string>
#include "FibLFSR.h"

//This function will be used to transform PNGs using an LFSR object
void transform(sf::Image& a, FibLFSR* b);

// Display an encrypted copy of the picture, using the LFSR 
// to do the encryption
int main(int argc, char* argv[]) {
    //First we should load the image that we want to transform
    sf::Image image;
    if (!image.loadFromFile(argv[1])) {
        return -1;
    }
    
    //Prepare the sprite for the decrypted image 
    sf::Vector2u size = image.getSize();
    sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Decrypted");
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite1;
    sprite1.setTexture(texture);
    
    //Next we should create a FibLFSR Object using the password provided in the main
    FibLFSR passwordObj(argv[3]);
    
    //Transform the object and save the new image into the output
    transform(image, &passwordObj);
    if (!image.saveToFile(argv[2])) {
        return -1;
    }
    
    //Load up the encrypted image
    sf::Image image2;
    if (!image2.loadFromFile(argv[2])) {
        return -1;
    }

    //Prepare the sprite for the encrypted image
    sf::Vector2u size2 = image2.getSize();
    sf::RenderWindow window2(sf::VideoMode(size2.x, size2.y), "Encrypted");
    sf::Texture texture2;
    texture2.loadFromImage(image2);
    sf::Sprite sprite2;
    sprite2.setTexture(texture2);

    //Display both the encrypted and decrypted image
    while (window1.isOpen() && window2.isOpen()) { 
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window1.close();
        }
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window2.close();
        }
        window1.clear();
        window1.draw(sprite1);
        window1.display();
        window2.clear();
        window2.draw(sprite2);
        window2.display();
    }
    return 0;
}

//Function definition 
void transform(sf::Image& a, FibLFSR* b) {
    //A pixel object that I can reuse within a loop
    sf::Color p;

    //Need to get the size and width of the PNG image being used 
    int width = a.getSize().x;
    int height = a.getSize().y;

    // create photographic negative image of upper-left 200 px square
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            p = a.getPixel(x, y);
            //XOR with a random number generated from the LFSR Object
            p.r = p.r ^ b->generate(8);
            p.g = p.g ^ b->generate(8);
            p.b = p.b ^ b->generate(8);
            a.setPixel(x, y, p);
        }
    }
}
