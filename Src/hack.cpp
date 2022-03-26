#include "hack_config.hpp"

namespace Hack
{

void Bouncing(sf::RenderWindow &window, sf::Vector2i &step)
{
    if (window.getPosition().x <= 0 || window.getPosition().x >= Hack::displayWidth  - Hack::windowWidth)
        step.x = -step.x;

    if (window.getPosition().y <= 0 || window.getPosition().y >= Hack::displayHeight - Hack::windowHeight)
        step.y = -step.y;

    window.setPosition(window.getPosition() + step);

    if (std::abs(window.getPosition().x - window.getPosition().y) == 0)
    {
        window.setPosition({
                            std::rand() % (Hack::displayWidth  - Hack::windowWidth),
                            std::rand() % (Hack::displayHeight - Hack::windowHeight)
                           });
    }
}

void ProceedKeyboard(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        sf::Event::KeyEvent key = event.key;

        if (key.code == sf::Keyboard::Key::Q)
        {
            if (key.shift)
            {
                window.close(); // returning like default
                return;         // not to go further & create another window
            }

            if (std::rand() % 5 < 3)
                window.close();
            else
                BouncingWindow();
        }
    }
}

int BouncingWindow()
{
    sf::RenderWindow window(sf::VideoMode(Hack::windowWidth, Hack::windowHeight), "Hacking Rustamchik");

    sf::Font font;
    if (!font.loadFromFile(Hack::fontSrc))
        return Hack::FailedLoadingFont;

    std::srand(std::time(nullptr));

    sf::Text   text("Catch me to hack Rustamchik", font, 36);
    text.setFillColor(sf::Color::White);
    text.setPosition(30, Hack::windowHeight / 2 - 36);

    int xStep = 1 + std::rand() % 3;
    if (std::rand() % 1) xStep = -xStep;

    int yStep = 1 + std::rand() % 3;
    if (std::rand() % 1) yStep = -yStep;

    sf::Vector2i step(xStep, yStep);

    while (window.isOpen())
    {
        sf::Event  event = {};

        while (window.pollEvent(event))
        {
            ProceedKeyboard(window, event);

            if (event.type == sf::Event::Closed)
                BouncingWindow();

            // There I Can Add Some Code To Change
            // Image If User Do Something
        }

        Bouncing(window, step);
        Hack::sleep(1);

        window.clear();

        // There I Can Draw Something Else
        // In My Window )))

        window.draw(text);


        window.display();
    }

    return 0;
}

int ProceedHackingBar(sf::RenderWindow &window, sf::Clock &clock, float &timeToHack)
{
    static sf::RectangleShape frame(sf::Vector2f(Hack::progressWidth, Hack::progressHeight));
    frame.setFillColor(sf::Color::Black);
    frame.setOutlineColor(sf::Color::Green);
    frame.setOutlineThickness(2);
    frame.setPosition(Hack::answerWidth - Hack::progressWidth, Hack::cowHeight / 2 + 20);

    window.draw(frame);

    sf::Time timeFromStart = clock.getElapsedTime();

    float percentage = timeFromStart.asSeconds() / timeToHack;
    if (percentage < 0) return Hack::FloatBecomeNegative;

    if (timeFromStart.asSeconds() > timeToHack)
    {
        window.close();
        if (timeToHack >= 2 * Hack::timeToHack)
        {
            return Hack::TooManyAttemptsToClose;
        }
    }


    unsigned int currentProgress = roundf(percentage * Hack::progressWidth);

    sf::RectangleShape progress(sf::Vector2f(currentProgress, Hack::progressHeight));
    progress.setFillColor(sf::Color::Green);
    progress.setPosition(Hack::answerWidth - Hack::progressWidth, Hack::cowHeight / 2 + 20);

    window.draw(progress);

    return 0;
}

int ProceedWindowFocus(sf::RenderWindow &window, sf::Music &music, sf::Text &text, std::vector<sf::Texture> &textures, float &timeToHack)
{
    static int windowHasFocus    = 1;
    static unsigned int picIndex = textures.size() - 1;
    // picIndex = textures.size() - 1
    // Because it increments in the first time
    // & It will be equal to 0
    static sf::Clock clock;

    if (!window.hasFocus())
    {
        if (!windowHasFocus)
        {
            picIndex = (picIndex + 1) % textures.size();
            sf::Sprite cow(textures[picIndex]);

            window.draw(cow);      // It is already activated

            Hack::sleep(85);
        }
        else
        {
            windowHasFocus = 0;    // It is the first time
            music.play();
        }
    }
    else
    {
        if (!windowHasFocus)
        {
            windowHasFocus = 1;    // User switched focus to this program
            music.pause();
            clock.restart();
        }

        int status = ProceedHackingBar(window, clock, timeToHack);
        if (status) return status;

        window.draw(text);
   }

    return 0;
}

int LoadTextures(std::vector<sf::Texture> &textures)
{
    const char *formatString = Hack::textureSrc;
    char *buffer = (char *) std::calloc(strlen(formatString), 1);

    for (size_t i = 0; i < Hack::texturesAmount; ++i)
    {
        std::sprintf(buffer, formatString, i);

        if (!textures[i].loadFromFile(buffer))
        {
            free(buffer);
            return Hack::FailedLoadingTexture;
        }
    }

    free(buffer);

    return 0;
}

int PolishCowWindow()
{
    sf::RenderWindow window(sf::VideoMode(Hack::cowWidth, Hack::cowHeight), "Hacking...");

    sf::Music music;
    if (!music.openFromFile(Hack::musicSrc))
        return Hack::FailedLoadingMusic;

    sf::Font font;
    if (!font.loadFromFile(Hack::fontSrc))
        return Hack::FailedLoadingFont;

    std::vector<sf::Texture> textures(Hack::texturesAmount);

    int status = LoadTextures(textures);
    if (status) return status;

    sf::Text text("Hacking...", font, 70);
    text.setFillColor(sf::Color::Green);
    text.setPosition(80, Hack::cowHeight / 2 - 80);

    static float timeToHack = Hack::timeToHack;

    while (window.isOpen())
    {
        sf::Event event = {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                timeToHack *= 2;
        }

        window.clear();

        int status = ProceedWindowFocus(window, music, text, textures, timeToHack);
        if (status) return status;

        // There I Can Draw Something Else
        // In My Window )))

        window.display();
    }

    return 0;
}

int PatchProgram()
{
    FILE *file = fopen(Hack::inFilename, "rb");
    if (file == nullptr)             return Hack::FailedOpeningInputBinary;

    char *buffer = (char *) calloc(Hack::filesize + 1, 1);
    if (buffer == nullptr)           return Hack::FailedAllocatingMemory;

    size_t readSize = fread(buffer, 1, Hack::filesize, file);
    if (readSize != Hack::filesize)  return Hack::FailedReadingBinary;

    fclose(file);

    // There is your my own patching
    buffer[0x35] = 0x39;
    buffer[0x36] = 0x02;

    file = fopen(Hack::outFilename, "wb");
    if (file == nullptr)             return Hack::FailedOpeningOutputBinary;

    size_t wroteSize = fwrite(buffer, 1, Hack::filesize, file);
    if (wroteSize != Hack::filesize) return Hack::FailedWritingBinary;

    fclose(file);

    free(buffer);

    return 0;
}

int OutAnswer(sf::String &outString)
{
    static unsigned int windowIndex = 0;
    static sf::Font font;
    if (windowIndex == 0 && !font.loadFromFile(Hack::fontSrc))
        return Hack::FailedLoadingFont;

    static sf::Text text(outString, font, 40);
    if (windowIndex == 0)
    {
        text.setPosition(20, Hack::answerHeight / 2 - 30);
        text.setFillColor(sf::Color::Green);
    }

    sf::RenderWindow window(sf::VideoMode(Hack::answerWidth, Hack::answerHeight), "lol");

    window.setPosition({
                        std::rand() % (Hack::displayWidth  - Hack::answerWidth),
                        std::rand() % (Hack::displayHeight - Hack::answerHeight)
                       });

    window.clear();

    window.draw(text);

    window.display();

    Hack::sleep(30);

    if (++windowIndex != Hack::windowsMaxAmount)
        OutAnswer(outString);

    window.close();

    return 0;
}

void sleep(unsigned int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

}
