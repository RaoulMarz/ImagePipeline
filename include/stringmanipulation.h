/* 
 * File:   stringmanipulation.h
 * Author: raoul
 *
 * Created on April 14, 2017, 8:40 PM
 */

#ifndef STRINGMANIPULATION_H
#define STRINGMANIPULATION_H

#include <locale>
#include <string>

using namespace std;

class stringmanipulation {
public:
    static string trim(string anotherstr);
    static void lefttrim(string& str, const std::locale& loc);
    static void righttrim(string& str, const std::locale& loc);
    static string stringbetween(string mainStr, string first, string last);
    static string stringbetween(string mainStr, char first, char last);
private:

};

#endif /* STRINGMANIPULATION_H */

