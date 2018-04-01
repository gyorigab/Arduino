#include "trace.h"

Trace::Verbosity Trace::m_verbosity = DEBUG;
bool Trace::m_printCallStack = false;
bool Trace::m_printTrace = false;

int Log::m_depth = 0;
