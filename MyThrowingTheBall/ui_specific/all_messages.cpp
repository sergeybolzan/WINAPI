
#include "stdafx.h"
#include "all_messages.h"

namespace ttb_thread
{
    CMessage::CMessage(const EMESSAGE_TYPE artype):m_type(artype){}
    CMessage::~CMessage(){}

    const EMESSAGE_TYPE CMessage::Type(){return m_type;}



    CMessageTimeEvent::CMessageTimeEvent(SD_VECTOR a_position, double a_at):CMessage(EMESSAGE_TYPE::message_data), m_position(a_position), m_time(a_at){}

    SD_VECTOR CMessageTimeEvent::Position()const throw(){ return m_position;}
    double CMessageTimeEvent::When()const throw(){ return m_time;}


};

