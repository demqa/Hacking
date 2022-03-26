#ifndef HACK_H_
#define HACK_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <string.h>
#include <math.h>

namespace Hack
{
    void sleep(unsigned int milliseconds);

    void Bouncing(sf::RenderWindow &window, sf::Vector2i &step);
    void ProceedKeyboard(sf::RenderWindow &window, sf::Event &event);
    int  ProceedWindowFocus(sf::RenderWindow &window, sf::Music &music, sf::Text &text, std::vector<sf::Texture> &textures);
    int  LoadTextures(std::vector<sf::Texture> &textures);

    int  BouncingWindow();
    int  PolishCowWindow();
    int  OutAnswer(sf::String &outString);

    int  PatchProgram();
}


#endif // HACK_H_
