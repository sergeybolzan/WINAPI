#ifndef ALL_MESSAGES_H_TYWOEI234GDE
#define ALL_MESSAGES_H_TYWOEI234GDE

// we need 2 messages actually
//
//  - we got the data
//  - no more data
//
//  so we have 2 of them


namespace ttb_thread
{
    // this it message types we working with
    //
    //  it should not work like a command
    //
    enum class EMESSAGE_TYPE : uint32_t
    {
        message_empty             = 0, // just do nothing
        message_data              = 1, // transfer the data
        message_no_more_data      = 2, // quit request 
    };


    // basic class
    class CMessage // message with data
    {
    protected:
        EMESSAGE_TYPE m_type;
    public:
        CMessage(const EMESSAGE_TYPE artype);
        virtual ~CMessage();

        const EMESSAGE_TYPE Type();
    };



    // event with position data at time
    class CMessageTimeEvent : public CMessage // message_data
    {
    public:
        // actually we can also pass speed data
        // but no need at UI
        CMessageTimeEvent(SD_VECTOR a_position, double a_at);

        SD_VECTOR Position()const throw();
        double When()const throw();

    protected:
        // transfer these
        SD_VECTOR m_position;
        double  m_time;
    };



};

#endif

