#include "unittests.h"
#include <iostream>

using namespace std;

UnitTests::UnitTests()
{
    m_count = 0;
}

void UnitTests::checkEquality(bool current, bool expected)
{
    if(current == expected) printPassed();
    else                    printFailed();
}

void UnitTests::checkEquality(int current, int expected)
{
    if(current == expected) printPassed();
    else                    printFailed();
}

void UnitTests::checkSizeEquality(size_t current, size_t expected)
{
    if(current == expected) printPassed();
    else                    printFailed();
}

void UnitTests::checkEquality(const uint8_t* current, const uint8_t* expected, size_t size)
{
    cout << "Testing array content: ";
    for(size_t i = 0; i < size; i++)
    {
        cout << hex << static_cast<int>(current[i]) << " ";

        if(current[i] != expected[i])
        {
            cout << endl;
            printFailed();
            return;
        }
    }
    cout << endl;
    printPassed();
}

void UnitTests::checkEquality(const uint8_t current, const uint8_t expected)
{
    if(current != expected)
    {
        printFailed();
    }
    else
    {
        printPassed();
    }
}

void UnitTests::printPassed()
{
    cout << "Test no: " << m_count++ << " PASSED" << endl;
}

void UnitTests::printFailed()
{
    cout << "Test no: " << m_count++ << " FAILED" << endl;
}
