#pragma once

#include <string>
#include <algorithm>

#include "Platform/Types.h"

namespace Helium
{

    /***********************************************************************************************************************
    *  isNum
    *   - returns TRUE if specified character is a number
    ***********************************************************************************************************************/
    inline bool isNum(tchar c)
    {
        return (c >= TXT('0') && c <= TXT('9'));
    }

    /***********************************************************************************************************************
    *  isAlpha
    *   - returns TRUE if specified character is in alphabet
    ***********************************************************************************************************************/
    inline bool isAlpha(tchar c)
    {
        return ((c >= TXT('a') && c <= TXT('z')) || (c >= TXT('A') && c <= TXT('Z')));
    }

    /***********************************************************************************************************************
    *  isNumMod
    *   - returns TRUE if specified character is a numberic modifier character
    ***********************************************************************************************************************/
    inline bool isNumMod(tchar c)
    {
        return ((c == TXT('.')) || (c == TXT('-')));
    }

    /***********************************************************************************************************************
    *  isNumHex
    *   - returns TRUE if specified character is a hex character
    ***********************************************************************************************************************/
    inline bool isNumHex(tchar c)
    {
        return (((c >= TXT('a')) && (c <= TXT('f'))) || ((c >= TXT('A')) && (c <= TXT('F'))));
    }

    /***********************************************************************************************************************
    *  isWS
    *   - returns TRUE if specified character is white space
    ***********************************************************************************************************************/
    inline bool isWS(tchar c)
    {
        return ((c == TXT(' ')) || (c == TXT(',')) || (c == TXT('\t')) || (c == TXT('\r')) || (c == TXT('\n')));
    }

    /***********************************************************************************************************************
    *  atoh
    *   - returns integer value of hex string
    ***********************************************************************************************************************/
    inline int atoh(tstring& s)
    {
        int val = 0;
        for (int i = 2; (i < (int) s.size()) && (isNum(s[i]) || isNumHex(s[i])); i++) 
        {
            val = (val*16);
            if (s[i] >= TXT('a'))
                val += 10 + s[i] - TXT('a');
            else
                if (s[i] >= TXT('A'))
                    val += 10 + s[i] - TXT('A');
                else
                    val += s[i] - TXT('0');
        }
        return val;
    }

    /***********************************************************************************************************************
    *  toLower
    *   - makes all alpha characters in string lower case
    ***********************************************************************************************************************/
    inline void toLower(tstring &s)
    {
        if ( !s.empty() )
        {
            std::transform(s.begin(), s.end(), s.begin(), tolower); 
        }
    }

    /***********************************************************************************************************************
    *  toUpper
    *   - makes all alpha characters in string upper case
    ***********************************************************************************************************************/
    inline void toUpper(tstring &s)
    {
        if ( !s.empty() )
        {
            std::transform(s.begin(), s.end(), s.begin(), toupper); 
        }
    }

}