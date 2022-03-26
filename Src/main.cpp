#include "hack.hpp"

int main()
{
    int result = Hack::BouncingWindow();

    result += Hack::PolishCowWindow();


    sf::String patchingSuccess("Patching Completed");
    sf::String patchingUnsuccess("Cannot Hack This");

    if (!result) result = Hack::OutAnswer(patchingSuccess);
    else
    {
        result = Hack::OutAnswer(patchingUnsuccess);
        return result;
    }

    result += Hack::PatchProgram();

    return result;
}
