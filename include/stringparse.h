/* 
 * File:   stringparse.h
 * Author: raoul
 *
 * Created on April 14, 2017, 8:57 PM
 */

#ifndef STRINGPARSE_H
#define STRINGPARSE_H

#include <vector>
#include <string>

using namespace std;

class stringparse {
public:
    stringparse();
    stringparse(const stringparse& orig);
    virtual ~stringparse();
    
    static vector<string>* splitwords(string findstring, string fieldseparator);
    static string inttostr(int aVal);
    static unsigned char hexcharval(char charMain);
    static unsigned char strtobyte(string mainStr);
    static bool strtobool(string boolStrVal);
    static int strtoint(string numVal);
private:

};

#endif /* STRINGPARSE_H */

