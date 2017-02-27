#pragma once


#include "stdafx.h"
#include "sync.h"
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+


CAutoSync::CAutoSync(std::mutex& arsync):m_rSync(arsync)
{
    m_rSync.lock();
}
CAutoSync::~CAutoSync()
{
    m_rSync.unlock();
};

