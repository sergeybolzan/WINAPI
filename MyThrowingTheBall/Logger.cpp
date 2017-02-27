#include "stdafx.h"
#include <stdarg.h>       // va_list, va_start, va_arg, va_end

#include "Logger.h"



//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CLogger : public LoggerInterface
{
   std::mutex m_sync;
   FILE *m_file;
   char m_prebuf[32768];
   char m_prebufCon[32768];

   bool m_bLogOn; // set to true if log file created
public:

    CLogger(void);
    ~CLogger(void);


    virtual void Out(const char* const msg,...) override;
};


namespace
{
    //----
    CLogger g_Logger;

}

LoggerInterface* const g_pLogger(&g_Logger);

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CLogger::CLogger(void): m_file(NULL), m_bLogOn(true)
{
//----
    // create log file name
    // like our exe but with _H-M-S.log end
    ::GetModuleFileNameA(::GetModuleHandle(NULL), m_prebuf, sizeof(m_prebuf));


    std::vector<char> drive(_MAX_DRIVE + 1);
    std::vector<char> dir(_MAX_DIR + 1);
    std::vector<char> fname(_MAX_FNAME + 1);


   _splitpath_s(m_prebuf, drive.data(), _MAX_DRIVE, dir.data(), _MAX_DIR, fname.data(), _MAX_FNAME, nullptr, 0);

   SYSTEMTIME st;
   ::GetLocalTime(&st);
   std::stringstream fnameStr;
   fnameStr << fname.data() << "_" << st.wHour << "-" << st.wMinute << "-" << st.wSecond;

    char t_LogFileName[MAX_PATH] = {0};
   _makepath_s(t_LogFileName, MAX_PATH, drive.data(), dir.data(), fnameStr.str().c_str(), "log");

   if (m_file == NULL)
   {
      m_bLogOn = 0 == fopen_s(&m_file, t_LogFileName, "at");
   }

//----
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CLogger::~CLogger(void)
{
//----
   m_bLogOn = false;
   if (m_file != NULL)
   {
      fclose(m_file);
      m_file = NULL;
   }
//----
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CLogger::Out(LPCSTR msg, ...)
{
   if (msg == NULL || m_prebuf == NULL) return;
//----
    CAutoSync dummy(m_sync);

    if (!m_bLogOn)
        return;

   SYSTEMTIME st;
   va_list    arg_ptr;
//----
   GetLocalTime(&st);
//----

   va_start(arg_ptr, msg);
   vsprintf_s(m_prebuf, sizeof(m_prebuf), msg, arg_ptr);
   va_end(arg_ptr);
//----
   if (m_file != NULL)
   {
      wsprintfA(m_prebufCon, "[%04u]%04d.%02d.%02d %02d:%02d:%02d %s\n",
          (unsigned int)::GetCurrentThreadId(),
                    st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,m_prebuf);
      std::cout << m_prebufCon;

      fprintf(m_file, m_prebufCon);
      fflush(m_file);
   }
}
//+------------------------------------------------------------------+




