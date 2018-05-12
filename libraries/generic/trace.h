#ifndef TRACE_H
#define TRACE_H

#ifdef GDEBUG
#include <iostream>
#else
#include <Arduino.h>
#endif

#include "bytebuffer.h"

#define TRACE_FUNCTION() Log logFunction(__FUNCTION__,__FILE__, __LINE__)

#define TRACE(message, verbosity)          Trace::print(F(message),verbosity)
#define TRACE_VAR(message, var, verbosity) Trace::print(F(message), var, verbosity)
#define TRACE_BUF(message, var, verbosity) Trace::printBuffer(F(message), var, verbosity)
#define TRACING(verbosity)                 VerbositySetter verbSetter(verbosity)
#define TRACE_MEM()                        Trace::printFreeMemory()

#define DBG Trace::DEBUG
#define WRN Trace::WARNING
#define INF Trace::INFO
#define ERR Trace::ERROR

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

class Trace
{
public:
	
    enum Verbosity{ERROR, WARNING, INFO, DEBUG, STACK};
	
     Trace(){}
    ~Trace(){}

    static void printFreeMemory()
    {
        Serial.print(F("[INFO]    Free Memory: "));
        Serial.print(freeMemory());
        Serial.println(F(" bytes"));
    }
	
    template<typename T, typename V>
    static void print(T message, V var, Verbosity v = Trace::DEBUG)
    {
        if(m_printTrace)
        {
            switch(v)
            {
                case STACK:
                    if(m_printCallStack)
                    {
                        printData("", message, var);
                    }
                    break;
                case DEBUG:
                    if(m_verbosity > 2) printDataLn("[DEBUG]   ", message, var);
                    break;
                case INFO:
                    if(m_verbosity > 1) printDataLn("[INFO]    ", message, var);
                    break;
                case WARNING:
                    if(m_verbosity > 0) printDataLn("[WARNING] ", message, var);
                    break;
                case ERROR:
                    printDataLn("[ERROR]   ", message, var);
                    break;
                default:
                    printDataLn("[DEFAULT] ", message, var);
                    break;
            }
        }
    }

    template<typename T>
    static void printBuffer(T message, const ByteBuffer &buff, Verbosity v = Trace::DEBUG)
    {
        if(m_printTrace)
        {
            switch(v)
            {
                case DEBUG:
                    if(m_verbosity > 2) printData("[DEBUG]   ", message, buff);
                    break;
                case INFO:
                    if(m_verbosity > 1) printData("[INFO]    ", message, buff);
                    break;
                case WARNING:
                    if(m_verbosity > 0) printData("[WARNING] ", message, buff);
                    break;
                case ERROR:
                    printData("[ERROR]   ", message, buff);
                    break;
                default:
                    printData("[DEFAULT] ", message, buff);
                    break;
            }
        }
    }

    static void newline(Verbosity v = Trace::DEBUG)
    {
        if(m_printTrace)
        {
            switch(v)
            {
                case STACK:
                    if(m_printCallStack) newln();
                    break;
                case DEBUG:
                case INFO:
                case WARNING:
                case ERROR:
                    newln();
                    break;
                default:
                    newln();
            }
        }
    }

    template<typename T>
    static void print(T message, Verbosity v = Trace::DEBUG)
    {
        print(message,"",v);
    }

    template<typename T>
    static void printData(const char* verb, T message, const ByteBuffer &buff)
    {
#ifdef GDEBUG  // PC
        std::cout << std::dec;
        std::cout << verb << message << std::endl;
        std::cout << "Size: " << buff.size() << std::endl;
        std::cout << std::hex;

        for(int i=0; i<buff.size(); i++)
        {
            std::cout << buff[i]<<" ";
        }

#else   // Arduino
        Serial.print(verb);
        Serial.print(message);
        Serial.print(F("Size: "));
        Serial.print(buff.size());
        Serial.print(F(" Data: "));

        for(int i=0; i<buff.size(); i++)
        {
            Serial.print(buff[i], HEX);
            Serial.print(' ');
        }

        Serial.println(F(""));
        Serial.flush();
#endif
    }

    template<typename T, typename V>
    static void printDataLn(const char* verb, T message, V var)
    {
        printData(verb,message,var);
        newln();
    }

    template<typename T, typename V>
    static void printData(const char* verb, T message, V var)
    {
#ifdef GDEBUG
        std::cout << verb << message << var << std::endl;
#else
        Serial.print(verb);
        Serial.print(message);
        Serial.print(var);
        Serial.flush();
#endif
    }

    static void newln()
    {
#ifdef GDEBUG
        std::cout << std::endl;
#else
        Serial.println(F(""));
        Serial.flush();
#endif
    }

    void init()
    {
#ifndef GDEBUG
        Serial.begin(9600);
#endif
    }

    static void setVerbosity(Verbosity v)
    {
        m_verbosity = v;
    }

    static void enableCallStack(bool enable)
    {
        m_printCallStack = enable;
    }

    static void enableTrace(bool enable)
    {
        m_printTrace = enable;
    }

    static Verbosity getVerbosity() {return m_verbosity;}

private:

    static int freeMemory()
    {
        char top;
        #ifdef __arm__
        return &top - reinterpret_cast<char*>(sbrk(0));
        #elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
        return &top - __brkval;
        #else  // __arm__
        return __brkval ? &top - __brkval : &top - __malloc_heap_start;
        #endif  // __arm__
    }

    static Verbosity m_verbosity;
    static bool m_printCallStack;
    static bool m_printTrace;
};

class VerbositySetter
{
public:
    VerbositySetter(Trace::Verbosity v)
    {
        m_lastVerbosity = Trace::getVerbosity();
        Trace::setVerbosity(v);
    }

    ~VerbositySetter()
    {
        Trace::setVerbosity(m_lastVerbosity);
    }

private:
    Trace::Verbosity m_lastVerbosity;
};

class Log
{
public:
    Log(const char* function, const char* file, int line):
        m_function(function), m_file(file), m_line(line)
    {
        m_depth++;
        Trace::print(F("[ENTER] -> "), Trace::STACK);
        print();
    }

    ~Log()
    {
        Trace::print(F("[EXIT]  <- "), Trace::STACK);
        print();
        m_depth--;
    }

    void print()
    {
        space("#");
        Trace::print(m_function, Trace::STACK);
        Trace::print(F(" file: "), m_file, Trace::STACK);
        Trace::print(F(" line: "), m_line, Trace::STACK);
        Trace::newline(Trace::STACK);
    }

    void space(const char *token)
    {
        for(int i=0; i < m_depth; i++)
        {
            Trace::print(token, Trace::STACK);
        }
    }

private:
    const char* m_function;
    const char* m_file;
    int         m_line;

    static int m_depth;
};

#endif
