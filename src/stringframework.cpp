#include <boost/tokenizer.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include "stringframework.h"

using namespace std;

std::unique_ptr<std::vector<std::string>> stringframework::getTokensOnDelimiter(std::string input, std::string delimiter) {
  std::unique_ptr<std::vector<std::string>> result = make_unique<std::vector<std::string>>();

  typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
  boost::char_separator<char> sep{/*" "*/delimiter.c_str()};
  tokenizer tok{input, sep};
  stringstream ss;
  for (const auto &t : tok) {
      ss.clear();
      ss << t;
      string strtokenout;
      ss >> strtokenout;
      result->push_back(strtokenout);
      //std::cout << t << '\n';
  }

  return result;
}

std::string stringframework::replacetextinwords(std::string input, std::string delimiter, std::string matchpattern, std::string replacepattern) {
    std::string res = input;
    if ( (input.length() > 0) && (matchpattern.length() > 0) ) {
        std::unique_ptr<std::vector<std::string>> wordComponents = stringframework::getTokensOnDelimiter(input, delimiter);
        if (wordComponents != nullptr) {
            for (auto& wordx : *wordComponents) {
                //optional<string> replacevalue = replaceText(wordx, matchpattern, replacepattern);
            }
        }
    }
    return res;
}

int stringframework::matchStringInVector(std::string input, std::vector<std::string>& matchlist, int offset) {
    int res = -1;
    if ( (offset >= 0) && (matchlist.size() > 0) ) {
        int idxrun = 0;
        for (auto& item : matchlist) {
            if (input.compare(item) == 0)
                return idxrun + offset;
            idxrun++;
        }
    }
}
