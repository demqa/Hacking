#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hacking Rustamchik");

    sf::Font font;
    if (!font.loadFromFile("Src/fonts/UbuntuMono-Regular.ttf"))
    {
        std::cout << "Cant load font" << std::endl;
        return 0;
    }

    std::srand(std::time(nullptr));

    sf::Text   text("Hacking...", font, 24);
    text.setFillColor(sf::Color::Green);

    sf::Vector2i step(1, 1);

    while (window.isOpen())
    {
        sf::Event event = {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // There I Can Add Some Code To Change
        // Image If User Do Something
        if (window.getPosition().x <= 0 || window.getPosition().x >= 1920 - 800)
        {
            step.x = -step.x;
        }

        if (window.getPosition().y <= 0 || window.getPosition().y >= 1000 - 600)
        {
            step.y = -step.y;
        }


        window.setPosition(window.getPosition() + step);

        if (std::abs(window.getPosition().x - window.getPosition().y) <= 2)
        {
            window.setPosition({std::rand()%(1920-800), std::rand()%(1000 - 600)});
        }

        window.clear();

        // There I Can Draw Something Else
        window.draw(text);

        window.display();
    }

    return 0;
}
