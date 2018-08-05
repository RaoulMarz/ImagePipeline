#ifndef STRING_FRAMEWORK_H
#define STRING_FRAMEWORK_H

#include <vector>
#include <string>

class stringframework {
private:
    std::string version;
public:
    stringframework();
    static std::unique_ptr<std::vector<std::string>> getTokensOnDelimiter(std::string input, std::string delimiter);
    static std::string replacetextinwords(std::string input, std::string delimiter, std::string matchpattern, std::string replacepattern);
    static int matchStringInVector(std::string input, std::vector<std::string>& matchlist, int offset = 0);
};

#endif /* end of include guard:STRING_FRAMEWORK_H */
