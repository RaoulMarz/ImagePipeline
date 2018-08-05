/* 
 * File:   imagelist.cpp
 * Author: raoul
 * 
 * Created on April 14, 2017, 3:35 PM
 */

#include "imagelist.h"
using namespace std;

namespace userinterface {

imagelist::imagelist() {
}

imagelist::imagelist(const imagelist& orig) {
}

imagelist::~imagelist() {
}

size_t imagelist::count() {
    return imagefilelist.count();
}

std::pair<bool, std::string> imagelist::getImageAtIndex(int index) {
    if (index < imagefilelist.count()) {
        optional<std::string> imagefile = imagefilelist.getitem(index);
        if (imagefile) {
            std::string imgFile = static_cast<std::string>(*imagefile);
            return make_pair(imgFile.length() > 0, imgFile);
        }
    }
    return make_pair(false, "");
}

std::pair<bool, int> imagelist::findFirstMatch(string imagefile) {
    //returns a pair value with a flag indicating if image found and a index value
    if (imagefile.length() > 0) {
        
    }
    return make_pair(false, -1);
}

void imagelist::addImage(string imagefile) {
    imagefilelist.add(imagefile);
}

optional<fwdstringlist> imagelist::findmatching(string pattern) {
    optional<fwdstringlist> res = optional<fwdstringlist> {};
    return res;
}

}
