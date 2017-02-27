#ifndef PARAMETER_PARSER_INCL2345987235GSL
#define PARAMETER_PARSER_INCL2345987235GSL


namespace ttb_thread
{



    class Parameter_Parser
    {

    protected:
        std::map< std::basic_string<TCHAR>, double*> m_map;
    public:

        // fills inner map with T_STRING and pointer for your double to fill
        // beware: p_value should be not null
        // no inner check
        void AddParameterNamePointer(TCHAR* aparameter, double * p_value);

        // receive application argument
        // parse it according AddParameterNamePointer options
        //
        // form is "parameterName:123.123"
        //
        // return false if an argument can not be founded in the map
        //   or an argument is wrong formed
        //
        bool Parse(TCHAR* const anArgument);
    };


};


#endif
