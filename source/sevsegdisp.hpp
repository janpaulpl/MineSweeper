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
        "╻══╻",
        "║  ║",
        "║  ║",
        "║  ║",
        "╹══╹"
    },

    {
        "   ╻",
        "   ║",
        "   ║",
        "   ║",
        "   ╹"
    },

    {
        " ══╻",
        "   ║",
        "╻══╹",
        "║   ",
        "╹══ "
    },

    {
        " ══╻",
        "   ║",
        " ══║",
        "   ║",
        " ══╹"
    }, 

    {
        "╻  ╻",     
        "║  ║",     
        "╹══║",     
        "   ║",     
        "   ╹"
    },

    {
        "╻══ ",
        "║   ",
        "╹══╻",
        "   ║",
        " ══╹"
    },

    {
        "╻══ ",
        "║   ",
        "║══╻",
        "║  ║",
        "╹══╹"
    },

    {
        " ══╻",
        "   ║",
        "   ║",
        "   ║",
        "   ╹"
    },

    {
        "╻══╻",
        "║  ║",
        "║══║",
        "║  ║",
        "╹══╹"
    },
    
    {
        "╻══╻",
        "║  ║",
        "╹══║",
        "   ║",
        " ══╹"
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

    void updateTimer() {
        int num = number;
        int digits[noOfDigits];
        for (int i = noOfDigits - 1; i >= 0; --i) {
            digits[i] = num % 10;
            num /= 10;
        }
        for (int row = 0; row < 5; ++row) {
            for (int dig = 0; dig < noOfDigits; ++dig) {
                std::cout << numbers[digits[dig]][row] << " ";
            }
            std::cout << std::endl;
        }
    }

    void updateTimerNumber() {
        while (number < 999) {
            system("clear"); // Clear the console screen (use "cls" on Windows)
            updateTimer();
            std::this_thread::sleep_for(std::chrono::seconds(1));
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
            writeBuf << red_fg << str << " " << endl << reset;
        }
        if(i != noOfDigits -1) writeBuf.goToLine(homeLine); 
    }
}