#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <vector>
#include <cmath>
#include "setup.hpp"
#include "buffer.hpp" 
#include "colour.hpp"

     




     

const std::string numbers[10][5] = {
    {
        " ___  ",
        "|   | ",
        "| | | ",
        "|___| "
    },

    {
        " ___    ",
        "|_  |   ",
        " _| |_  ",
        "|_____| "
    },

    {
        " ___  ",
        "|_  | ",
        "|  _| ",
        "|___| "
    },

    {
        " ___  ",
        "|_  | ",
        "|_  | ",
        "|___| "
    }, 

    {
        " ___  ",     
        "| | | ",     
        "|_  | ",     
        "  |_| "
    },

    {
        " ___  ",
        "|  _| ",
        "|_  | ",
        "|___| "
    },

    {
        " ___  ",
        "|  _| ",
        "| . | ",
        "|___| "
    },

    {
        " ___  ",
        "|_  | ",
        "  | | ",
        "  |_| "
    },

    {
        " ___  ",
        "| . | ",
        "| . | ",
        "|___| "
    },
    
    {
        " ___  ",
        "| . | ",
        "|_  | ",
        "|___| "
    }

};

class SevSegDisp{
    public:
    SevSegDisp(int dig, int n): noOfDigits(dig), number(n) {}

    void operator ++(){
        if(number > int(std::pow(10, noOfDigits)) - 1) return;
        else ++number;
    }

    void operator --(){
        if(number) --number;
    }

    void set(int n) {
        number = n;
    }

    void update(std::string);

    void startTimer() {
        std::thread timerThread([this](){
            while (number < 999) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                increment();
            }
        });
        timerThread.detach(); // Detach the thread to run independently
    }

    void updateTimer(std::string prepend) {
        int num = number; // Capture the current timer value atomically if required
        int digits[noOfDigits];
        int homeLine = writeBuf.getCurrLine();

        for (int i = noOfDigits - 1; i >= 0; --i) {
            digits[i] = num % 10;
            num /= 10;
        }

        for (int row = 0; row < 5; ++row) {
            writeBuf.goToLine(homeLine + row);
            writeBuf << reset << prepend;
            for (int dig = 0; dig < noOfDigits; ++dig) {
                writeBuf << red_fg << numbers[digits[dig]][row] << " ";
            }
            writeBuf << endl;
        }
    }

    void updateTimerNumber() {
        if (number <= 999) {
            increment();
        }
    }


    void increment() {
        if (number < std::pow(10, noOfDigits) - 1) {
            number++;
        }
    }

private:
    int noOfDigits;
    int number;
}flagDisp(5, 0), timerDisp(3, 0);

void SevSegDisp::update(std::string prepend){
    int homeLine = writeBuf.getCurrLine();
    int nos[noOfDigits];
    int num = number;
    int dig = noOfDigits; 
    while(num || dig){
        nos[dig-1] = num % 10;
        num /= 10;
        --dig;
    }
    for(int i = 0; i < noOfDigits; ++i){
        for(auto str : numbers[nos[i]]){
            if(!i) writeBuf << reset << prepend;
            writeBuf << red_fg << str << endl << reset;
        }
        if(i != noOfDigits -1) writeBuf.goToLine(homeLine); 
    }
}