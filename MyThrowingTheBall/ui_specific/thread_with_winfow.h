#ifndef THREAD_WITH_WINFOW_H_345H25DF
#define THREAD_WITH_WINFOW_H_345H25DF

#include "message_queue.h"

namespace ttb_thread
{

    // structure with messages from and to thread
    //
    //     Actually, we can use only 1 queue, and send the data in to UI thread with WM_COPYDATA for example
    //       or with ::PostMessage
    //    but calculation thread will spam a lot of messages in this case.
    //    no need to update a window more often then he can
    //
    struct SThreadInitialData
    {
        CMessageQueue m_toUIThread;
        CMessageQueue m_fromUIThread;
    };


    // thread will be started with this function
    void UIThreadFunction(SThreadInitialData* const a_pInitialData);

};

#endif

