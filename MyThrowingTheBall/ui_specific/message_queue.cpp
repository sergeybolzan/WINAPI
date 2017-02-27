
#include "stdafx.h"
#include "message_queue.h"
#include "sync.h"

namespace ttb_thread
{

    //typedef std::shared_ptr<CMessage> T_Message;
    //std::mutex m_locker;
    //std::queue<T_Message > m_messages;


    void CMessageQueue::AddMessage(T_Message a_rMessage)
    {
        CAutoSync t_sync(m_locker);
        m_messages.push(a_rMessage);
    };

    CMessageQueue::T_Message CMessageQueue::NextMessage(void)
    {
        T_Message t_ret;
        CAutoSync t_sync(m_locker);
        if (!m_messages.empty())
        {
            t_ret = m_messages.front();
            m_messages.pop();
        }

        return t_ret;
    };

    void CMessageQueue::NextMessages(T_MessageSequence& a_rMessages)
    {
        CAutoSync t_sync(m_locker);
        m_messages.swap(a_rMessages);
    }



};

