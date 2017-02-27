#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+

// automatic lock & unlock
// in constructor & destructor

class CAutoSync
{
private:
   CAutoSync(); // not necessary
   std::mutex& m_rSync;
public:
   CAutoSync(std::mutex& arsync); // transfer by reference - for sure - exists
   ~CAutoSync();
};

