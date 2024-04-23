#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstdio>
#include "field.hpp"
#include "buffer.hpp"
#include "setup.hpp"
#include "colour.hpp"
#include "display.hpp"

int main()
{
    system("clear");
    setGameMode();
    getQuickClearSettings();

    Field field;
    timerDisp.startTimer();  // Start the timer thread

    auto lastTime = std::chrono::steady_clock::now();
    
    while (true)
    {
        if (std::chrono::steady_clock::now() - lastTime >= std::chrono::seconds(1)) {
            system("clear");
            lastTime = std::chrono::steady_clock::now();

            dispBanner();
            field.drawField();
            dispFlagCounter();
            dispTimerCounter();

            if (gameState != RUNNING)
                dispVictoryOrDefeat();
            else
                dispControls();

            writeBuf.disp();
            writeBuf.clear();

            if (gameState == RUNNING)
                field.getMove();
            else
                break;
        }
    }

    std::cout << endl << reset;
    return 0;
}