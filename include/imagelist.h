/* 
 * File:   imagelist.h
 * Author: raoul
 *
 * Created on April 14, 2017, 3:35 PM
 */

#ifndef IMAGELIST_H
#define IMAGELIST_H

#include <boost/optional.hpp>
#include <string>
#include "fwdstringlist.h"

using boost::optional;

namespace userinterface {

class imagelist {
public:
    imagelist();
    imagelist(const imagelist& orig);
    virtual ~imagelist();
    
    size_t count();
    std::pair<bool, std::string> getImageAtIndex(int index);
    std::pair<bool, int> findFirstMatch(std::string imagefile);
    void addImage(std::string imagefile);
    optional<fwdstringlist> findmatching(std::string pattern);
private:
    fwdstringlist imagefilelist;   
};

}

#endif /* IMAGELIST_H */

