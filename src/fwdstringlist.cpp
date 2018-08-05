/*
 * File:   fwdstringlist.cpp
 * Author: raoul
 *
 * Created on January 17, 2018, 1:41 PM
 */

#include <iterator>
#include "fwdstringlist.h"
#include "stringframework.h"

using namespace std;

namespace impl {

    fwdstringlistIterator::fwdstringlistIterator(listNode* node, unique_smart_strlist strlist) {
        // Use internal helper to traverse in-order and store the nodes.
        retrievenodes(strlist);

        // End-of-tree delimiter. This is also what end() ends up being.
        nodes.push_back(nullptr);
    }

    reference fwdstringlistIterator::operator*() const {
        return nodes[current]->value;
    }

    reference fwdstringlistIterator::operator->() const {
        return nodes[current]->value;
    }

    fwdstringlistIterator& fwdstringlistIterator::operator++() {
        ++current;
        return *this;
    }

    fwdstringlistIterator fwdstringlistIterator::operator++(int) {
        fwdstringlistIterator tmp = *this;
        ++current;
        return tmp;
    }

    bool fwdstringlistIterator::operator==(const fwdstringlistIterator& rhs) {
        impl::listNode* lastNode = nullptr;
        if (rhs.nodes.size() > 0)
            lastNode = rhs.nodes[rhs.current];
        return nodes[current] == lastNode;
    }

    bool fwdstringlistIterator::operator!=(const fwdstringlistIterator& rhs) {
        return !(*this == rhs);
    }

    void fwdstringlistIterator::retrievenodes(unique_smart_strlist strlist) {
        if (strlist != nullptr) {
            for (auto &strX : *strlist)
                nodes.push_back(new impl::listNode(nullptr, strX));
        }
    }
}

fwdstringlist::fwdstringlist() {
    listdata = make_shared<std::vector < std::string >> ();
}

fwdstringlist::fwdstringlist(int allocsize, std::string defaultstr, bool setdefault, int defaultsize) :
defaultAssigned(setdefault), defaultassignedSize(defaultsize) {
    listdata = make_shared<std::vector < std::string >> ();
}

fwdstringlist::fwdstringlist(std::string input, std::string fieldseparator) {
    listdata = make_shared<std::vector < std::string >> ();
    if (fieldseparator.length() > 0) {
        std::unique_ptr<std::vector<std::string>> multipleitems = stringframework::getTokensOnDelimiter(input, fieldseparator);
        if (multipleitems != nullptr)
            for (auto &val : *multipleitems) {
                add(val);
            }
    } else {
        add(input);
    }
}

fwdstringlist::fwdstringlist(const fwdstringlist& initstrlist) {
    
}

size_t fwdstringlist::count() {
    int res = 0;
    if (listdata != nullptr) {
        res = listdata->size();
    }
    return res;
}

void fwdstringlist::addarray(std::valarray<std::string>& arraystrings) {
    for (auto& val : arraystrings) {
        listdata->push_back(val);
    }
}

void fwdstringlist::add(std::string item) {
    listdata->push_back(item);
}

int fwdstringlist::remove(std::string item, int count) {
    int res = 0;
    if ( (count > 0) && (item.length() > 0) ) {
        //listdata->get(item);
    }
    return res;
}

optional<std::string> fwdstringlist::getitem(int index) {
    optional<std::string> res = optional<std::string> {};
    if ( (listdata != nullptr) && (index < listdata->size() ) ) {
        res = optional<string> { (*listdata)[index] };
    }
    return res;
}

void fwdstringlist::parsefromstring(std::string parsetext, std::string separator) {
    std::unique_ptr<std::vector<std::string>> mytokens = stringframework::getTokensOnDelimiter(parsetext, separator);
    for (auto& value : *mytokens) {
        listdata->push_back(value);
    }
}

fwdstringlist::iterator fwdstringlist::begin() const {
    string rootText = (*listdata)[0];
    impl::listNode* root = new impl::listNode(nullptr, rootText);
    return impl::fwdstringlistIterator(root, listdata);
}

fwdstringlist::iterator fwdstringlist::end() const {
    return impl::fwdstringlistIterator();
}
