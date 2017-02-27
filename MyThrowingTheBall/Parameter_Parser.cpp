#include "stdafx.h"
#include "Parameter_Parser.h"

namespace ttb_thread
{


    void Tokenize(TCHAR* str, const TCHAR* splitstr, std::vector<std::basic_string<TCHAR> >& a_rTokens)
    {

        TCHAR* t_Pos = 0;
        TCHAR* Token = _tcstok_s( str, splitstr, &t_Pos); // Get first token
 
        while (nullptr != Token )
        {
            a_rTokens.push_back(Token);
 
            // Get next token, note that first parameter is NULL
            Token = _tcstok_s( 0, splitstr, &t_Pos );
        }
    }
    // fills inner map with T_STRING and pointer for your double to fill
    // beware: p_value should be not null
    // no inner check
    void Parameter_Parser::AddParameterNamePointer(TCHAR* aparameter, double * p_value)
    {
        m_map[aparameter] = p_value;
    }

    // receive application argument
    // parse it according AddParameterNamePointer options
    //
    // form is "parameterName:123.123"
    //
    // return false if an argument can not be founded in the map
    //   or an argument is wrong formed
    //
    bool Parameter_Parser::Parse(TCHAR* const anArgument)
    {
        std::vector<std::basic_string<TCHAR> > rTokens;
        Tokenize(anArgument, TEXT(":"), rTokens);

        if (rTokens.size() < 2)
            return false;

        auto t_it = m_map.find(rTokens.at(0));
        if (t_it == m_map.end())
            return false;

        *t_it->second = _ttof(rTokens.at(1).c_str());

        return true;
    }


};