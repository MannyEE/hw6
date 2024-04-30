#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] = { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[] = {0, 0, 0, 0, 0};
        HASH_INDEX_T final = 0;
        int wordNum = 0;

 

        for(int i = 0; i < k.length(); i++) {
        
            if(i % 6 == 0 && i != 0) wordNum++;
            w[4 - wordNum] += letterDigitToNumber(k[k.length() - i - 1]) * pow(36, i % 6);
        }

        for(int i = 0; i < 5; ++i) {
            final += rValues[i] * w[i];
        }

        return final;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T finalDig = (int)letter;

        if (finalDig >= 97) {
            finalDig -= 97;
        } else if (finalDig >= 65) {
            finalDig -= 65;
        } else {
            finalDig -= 22;
        }

        return finalDig;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i = 0; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
