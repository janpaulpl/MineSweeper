#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstdio>
#include "field.hpp"
#include "buffer.hpp"
#include "setup.hpp"
#include "colour.hpp"
#include "display.hpp"

// Missing some cucked non-blocking input to make the timer refresh with the screen, but it's a terminal so this is kinda scuffed

// void makeNonBlocking(int fd) {
//     struct termios settings;
//     tcgetattr(fd, &settings);
//     settings.c_lflag &= ~(ICANON | ECHO); // Disable echo and canonical mode
//     settings.c_cc[VMIN] = 0;
//     settings.c_cc[VTIME] = 0;
//     tcsetattr(fd, TCSANOW, &settings);
//     fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
// }

// // Usage in the main game loop
// makeNonBlocking(STDIN_FILENO);
// char c;
// if (read(STDIN_FILENO, &c, 1) > 0) {
//     // Handle input
// }


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