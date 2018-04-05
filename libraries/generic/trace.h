#ifndef TRACE_H
#define TRACE_H

#include <Arduino.h>

#define TRACE_FUNCTION() Log logFunction(__FUNCTION__,__FILE__, __LINE__)

#define TRACE(message, verbosity)          Trace::print(message,verbosity)
#define TRACE_VAR(message, var, verbosity) Trace::print(message, var, verbosity)
#define TRACING(verbosity)                 Trace::verbosity(verbosity)

#define DBG Trace::DEBUG
#define WRN Trace::WARNING
#define INF Trace::INFO
#define ERR Trace::ERROR

class Trace
{
public:
	
    enum Verbosity{ERROR, WARNING, INFO, DEBUG, STACK};
	
	Trace(){}
    ~Trace(){}
	
    template<typename T>
    static void println(T message, Verbosity v = Trace::DEBUG)
    {
        if(m_printTrace)
        {
            switch(v)
            {
                case STACK:
                    if(m_printCallStack)
                    {
                        Serial.println(message);
                        Serial.flush();
                    }
                    break;
                case DEBUG:
                    if(m_verbosity > 2) printData("[DEBUG]   ", message, "");
                    break;
                case INFO:
                    if(m_verbosity > 1) printData("[INFO]    ", message, "");
                    break;
                case WARNING:
                    if(m_verbosity > 0) printData("[WARNING] ", message, "");
                    break;
                case ERROR:
                    printData("[ERROR]   ", message, "");
                    break;
                default:
                    printData("[DEBUG]   ", message, "");
                    break;
            }
        }
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
                        Serial.print(message);
                        Serial.print(var);
                        Serial.flush();
                    }
                    break;
                case DEBUG:
                    if(m_verbosity > 2) printData("[DEBUG]   ", message, var);
                    break;
                case INFO:
                    if(m_verbosity > 1) printData("[INFO]    ", message, var);
                    break;
                case WARNING:
                    if(m_verbosity > 0) printData("[WARNING] ", message, var);
                    break;
                case ERROR:
                    printData("[ERROR]   ", message, var);
                    break;
                default:
                    printData("[DEFAULT] ", message, var);
                    break;
            }
        }
    }

    template<typename T>
    static void print(T message, Verbosity v = Trace::DEBUG)
    {
        print(message,"",v);
    }

    template<typename T, typename V>
    static void printData(const char* verb, T message, V var)
    {
        Serial.print(verb);
        Serial.print(message);
        Serial.println(var);
        Serial.flush();
    }

    void init()
    {
        Serial.begin(9600);
    }

    static void verbosity(Verbosity v)
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

private:
    static Verbosity m_verbosity;
    static bool m_printCallStack;
    static bool m_printTrace;
};

class Log
{
public:
    Log(const char* function, const char* file, int line):
        m_function(function), m_file(file), m_line(line)
    {
        m_depth++;
        Trace::print("[ENTER] -> ", Trace::STACK);
        print();
    }

    ~Log()
    {
        Trace::print("[EXIT]  <- ", Trace::STACK);
        print();
        m_depth--;
    }

    void print()
    {
        space("#");
        Trace::print(m_function, Trace::STACK);
        Trace::print(" file: ", m_file, Trace::STACK);
        Trace::print(" line: ", m_line, Trace::STACK);
        Trace::println("", Trace::STACK);
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
