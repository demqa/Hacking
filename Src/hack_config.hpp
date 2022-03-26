#ifndef HACK_CONFIG_H_
#define HACK_CONFIG_H_

#include "hack.hpp"

namespace Hack
{
    enum DisplaySettings
    {                              //  |- it is because usually
        displayWidth   = 1920,      //  |  there are some panel
        displayHeight  = 1080 - 80, // <-  in the bottom of screen
    };

    enum WindowSetting
    {
        windowWidth    = 800,
        windowHeight   = 600,
    };

    enum CowSettings
    {
        cowWidth       = 498,       // These are my cow
        cowHeight      = 415,       // pictures options
    };

    enum AnswerSettings
    {
        answerWidth    = 400,
        answerHeight   = 300,
    };

    enum ProgressSettings
    {
        progressWidth  = 300,
        progressHeight = 40,
    };

    enum HackErrors
    {
        FailedLoadingFont = 1,
        FailedLoadingTexture,
        FailedLoadingMusic,
        FailedOpeningInputBinary,
        FailedOpeningOutputBinary,
        FailedAllocatingMemory,
        FailedReadingBinary,
        FailedWritingBinary,
        FloatBecomeNegative,
        TooManyAttemptsToClose,
    };

    float        timeToHack = 2;

    size_t windowsMaxAmount = 100;
    size_t   texturesAmount = 20;
    size_t         filesize = 414; // Yes, I dont want to use stat to
                                   // identify how much this file is.

    const char *    fontSrc = "Src/fonts/UbuntuMono-Regular.ttf";
    const char *   musicSrc = "Src/PolishCow/PolishCow.ogg";
    const char * textureSrc = "Src/PolishCow/frame_%02llu_delay-0.1s.gif";

    const char * inFilename = "asshack.com";
    const char *outFilename = "KAKAHA.com";
}

#endif // HACK_CONFIG_H_
