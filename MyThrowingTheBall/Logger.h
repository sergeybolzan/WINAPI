#ifndef LOGGER_INCLUDE_DEFINE_23897LFKH
#define LOGGER_INCLUDE_DEFINE_23897LFKH


// export variant for using from outer dlls

class LoggerInterface
{
public:
    virtual void Out(const char* const msg,...) = 0;
};



// we can use this inside our module

#ifdef TROWING_BALL_EXECUTABLE

extern LoggerInterface* const g_pLogger;
#define WLOGFILE             g_pLogger->Out

#endif
//+------------------------------------------------------------------+


#endif

