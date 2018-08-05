/* 
 * File:   stringparse.cpp
 * Author: raoul
 * 
 * Created on April 14, 2017, 8:57 PM
 */

#include <sstream>
#include <cmath>
#include "stringparse.h"

stringparse::stringparse() {
}

stringparse::stringparse(const stringparse& orig) {
}

stringparse::~stringparse() {
}

vector<string>* stringparse::splitwords(string findstring, string  fieldseparator) {
    if (findstring.length() > fieldseparator.length()) {
        vector<string>* result = nullptr;
        return result;
    } else
        return nullptr;
}

string stringparse::inttostr(int aVal) {
    char tmpi[128];
    snprintf(tmpi, 128, "%d", aVal);
    return string(tmpi);
}

unsigned char stringparse::hexcharval(char charMain) {
    unsigned char resch = '\0';
    if (charMain >= '0' || charMain <= '9')
        resch = charMain - '0';
    if (charMain >= 'a' || charMain <= 'f')
        resch = (charMain - 'a') + 10;    
    return resch;
}

unsigned char stringparse::strtobyte(string mainStr) {
    unsigned char resch = '\0';
    if (mainStr.length() >= 1) {
        string aStr;
        int slen = mainStr.length();
        if (slen > 2)
            aStr = mainStr.substr(0, 2);
        else
            aStr = mainStr;
        slen = aStr.length();
        unsigned char acx;
        
        for (int si = slen; si > 0; si--) {
            long factorx = 1;
            if (si < slen)
                factorx = (long)pow(16, (unsigned long)(slen - si) );
            acx = (hexcharval(mainStr.at(si - 1))) * (unsigned char)(factorx);
            resch += acx;
        }
    }
    return resch;
}

bool stringparse::strtobool(string boolStrVal) {
    bool res = false;
    if (boolStrVal.length() > 0) {
        res = (boolStrVal.compare("true") == 0);
    }
    return res;
}

int stringparse::strtoint(string numVal) {
    int res = 0;
    if (numVal.length() > 0) {
        istringstream(numVal) >> res;
    }
    return res;
}

