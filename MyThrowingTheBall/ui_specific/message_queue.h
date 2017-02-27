#ifndef MESSAGEQUEUE_TTB_2359872345FLSDHAZ
#define MESSAGEQUEUE_TTB_2359872345FLSDHAZ


// message queue for transfer data
// guarded my std::mutex


namespace ttb_thread
{
class CMessage; // message with data

    class CMessageQueue
    {
    public:
        typedef std::shared_ptr<CMessage> T_Message;
        typedef std::queue<T_Message> T_MessageSequence;
    
    protected:

        std::mutex m_locker;
        std::queue<T_Message> m_messages;

    public:

        void AddMessage(T_Message a_rMessage); // put message inside queue
        T_Message NextMessage(void); // extract next message from queue

        // swap messages from queue with your queue
        // use in UI for extract a lot of points at once
        //
        // for not overheat processor
        void NextMessages(T_MessageSequence& a_rMessages);

    };


};

#endif

