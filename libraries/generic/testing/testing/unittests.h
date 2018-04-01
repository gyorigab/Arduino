#ifndef UNITTESTS_H
#define UNITTESTS_H

#include <stdint.h>
#include <cstddef>
#include <stdio.h>

class UnitTests
{
public:
    UnitTests();
    void checkEquality(bool current, bool expected);
    void checkSizeEquality(size_t current, size_t expected);
    void checkEquality(uint8_t current, uint8_t expected);
    void checkEquality(const uint8_t* current, const uint8_t* expected, size_t size);


    void printPassed();
    void printFailed();

private:
    int m_count;
};

#endif // UNITTESTS_H
