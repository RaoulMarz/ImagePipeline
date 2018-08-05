/* 
 * File:   stringmanipulation.cpp
 * Author: raoul
 * 
 * Created on April 14, 2017, 8:41 PM
 */

#include <ctype.h>
#include "stringmanipulation.h"

//Trim functions derived from http://mlawire.blogspot.com/2009/07/c-whitespace-trimming-functions.html
void stringmanipulation::lefttrim(string& str, const locale& loc) {
    string::size_type pos = 0;
    while (pos < str.size() && isspace(str[pos], loc))
        pos++;
    str.erase(0, pos);
}

void stringmanipulation::righttrim(string& str, const locale& loc) {
    string::size_type pos = str.size();
    while (pos > 0 && isspace(str[pos - 1], loc))
        pos--;
    str.erase(pos);
}

string stringmanipulation::trim(string anotherstr) {
    string res = anotherstr;
    const std::locale& loc = std::locale();
    lefttrim(res, loc);
    righttrim(res, loc);
    return res;
}

string stringmanipulation::stringbetween(string mainStr, string first, string last) {
    if ( (mainStr.length() > 0) && (first.length() > 0) && (first.length() <= mainStr.length()) ) {
        string xlast = first;
        if (last.length() > 0)
            xlast = last;
        int slen = mainStr.length();
        int ipos = mainStr.find(first);
        int ipos2 = -1;
        int firstlen = first.length();
        string workStr;
        if (ipos >= 0) {
            workStr = mainStr.substr(ipos + firstlen, slen - ipos - firstlen);
            ipos2 = workStr.find(xlast);
        }
        if (ipos2 >= 0) {
            workStr = workStr.substr(0, ipos2);
            return workStr;
        }
        else
            return mainStr;
    } else
        return mainStr;
}

string stringmanipulation::stringbetween(string mainStr, char first, char last) {
    if ( (mainStr.length() > 0) && (first >= 0) ) {
        int xlast = first;
        if (last > 0)
            xlast = last;
        int slen = mainStr.length();
        for (int isx = 0; isx < slen; isx++) {
            if (mainStr[isx] == first) {
                string workStr = mainStr.substr(isx + 1, slen - isx - 1);
                int wrklen = workStr.length();
                for (int ixx = 1; ixx < wrklen; ixx++) {
                    if (workStr[ixx] == xlast)
                        return workStr.substr(0, ixx - 1);
                }
                break;
            }
        }
        return mainStr;
    } else
        return mainStr;
}

