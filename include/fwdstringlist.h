/*
 * File:   fwdstringlist.h
 * Author: raoul
 *
 * Created on January 17, 2018, 2:40 PM
 */

#ifndef FWDSTRINGLIST_H
#define FWDSTRINGLIST_H

#include <boost/optional.hpp>
#include <vector>
#include <valarray>
#include <iostream>
#include <string>
#include <memory>

using boost::optional;
using unique_smart_strlist = std::shared_ptr<std::vector<std::string>>;

namespace impl {

    struct listNode {
        listNode* next{ nullptr };
        std::string value{ ""};

        listNode(listNode* ndNext, std::string myvalue) {
            next = ndNext;
            value = myvalue;
        }

        listNode() {

        }
    };

    // Iterator traits, previously from std::iterator.
    using value_type = std::string;
    using difference_type = std::ptrdiff_t;
    using pointer = std::string*;
    using reference = std::string&;
    using iterator_category = std::bidirectional_iterator_tag;

    class fwdstringlistIterator {
    public:

        // Default constructible.
        fwdstringlistIterator() = default;
        explicit fwdstringlistIterator(listNode* node, unique_smart_strlist strlist);

        // Dereferencable.
        reference operator*() const;
        reference operator->() const;

        // Pre- and post-incrementable.
        fwdstringlistIterator& operator++();
        fwdstringlistIterator operator++(int);

        // Equality / inequality.
        bool operator==(const fwdstringlistIterator& rhs);
        bool operator!=(const fwdstringlistIterator& rhs);

    private:
        // Since we're not concerned with optimal performance, we'll simply
        // store the sorted sequence in a vector.
        using Nodes = std::vector<listNode*>;

        // Helper function, will in-order traverse the tree and store the
        // nodes in sorted order.
        void retrievenodes(unique_smart_strlist strlist);

        // Our sorted nodes.
        Nodes nodes;

        // The node this iterator references.
        Nodes::size_type current {0};
    };

} // namespace impl

class fwdstringlist {
private:
    unique_smart_strlist listdata = nullptr;
    int defaultassignedSize = 0;
    bool defaultAssigned = false;
public:
    using iterator = impl::fwdstringlistIterator;

    fwdstringlist();
    fwdstringlist(int allocsize, std::string defaultstr = "", bool setdefault = false, int defaultsize = 0);
    fwdstringlist(std::string input, std::string fieldseparator = "");
    fwdstringlist(const fwdstringlist& initstrlist);
    size_t count();
    void addarray(std::valarray<std::string>& arraystrings);
    void add(std::string item);
    int remove(std::string item, int count = 1);
    optional<std::string> getitem(int index);
    void parsefromstring(std::string parsetext, std::string separator);

    iterator begin() const;
    iterator end() const;
};

#endif /* FWDSTRINGLIST_H */
