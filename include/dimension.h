/*
 * File:   dimension.h
 * Author: raoul
 *
 */

#ifndef _DIMENSION_H
#define	_DIMENSION_H

#include <sstream>

#include "stringmanipulation.h"
#include "stringparse.h"
#include "coordinate.h"

namespace userinterface {

template <class T>
class dimension {
public:
    dimension();
    dimension(coordinate<T> topleft, coordinate<T> bottomright, bool isHeightWidth = false);
    dimension(T X1, T Y1, T X2, T Y2);
    dimension(T X1, T Y1, T X2, T Y2, bool isHeightWidth);
    dimension(const dimension<T>& orig);
    dimension(dimension<T>* orig);
    virtual ~dimension();
    bool equals(dimension<T> anDim);
    int compare(dimension<T> another);
    T getHeight();
    T getWidth();
    void setTopLeft(coordinate<T> topleft);
    void setBottomRight(coordinate<T> bottomright);
    void read(string textvalue);
    coordinate<T> getTopLeft();
    coordinate<T> getBottomRight();
    string print();
private:
    coordinate<T> top_Left;
    coordinate<T> bottom_Right;
};

template <class T>
dimension<T>::dimension() {
    top_Left.setcoord(0, 0);
    bottom_Right.setcoord(0, 0);
}

template <class T>
dimension<T>::dimension(T X1, T Y1, T X2, T Y2) {
    top_Left.setcoord(X1, Y1);
    bottom_Right.setcoord(X2, Y2);
}

template <class T>
dimension<T>::dimension(T X1, T Y1, T X2, T Y2, bool isHeightWidth) {
    if (isHeightWidth) {
        top_Left.setcoord(X2, Y2);
        bottom_Right.setcoord(X2 + X1, Y2 + Y1);
    } else {
        top_Left.setcoord(X1, Y1);
        bottom_Right.setcoord(X2, Y2);
    }
}

template <class T>
dimension<T>::dimension(coordinate<T> topleft, coordinate<T> bottomright, bool isHeightWidth) {
    top_Left = topleft;
    if (isHeightWidth) {
        bottom_Right.setcoord(top_Left.getX() + bottomright.getX(), top_Left.getY() + bottomright.getY());
    } else {
        bottom_Right = bottomright;
    }
}

template <class T>
dimension<T>::dimension(const dimension<T>& orig) {
    top_Left = orig.top_Left;
    bottom_Right = orig.bottom_Right;
}

template <class T>
dimension<T>::dimension(dimension<T>* orig) {
    top_Left.setcoord(orig->getTopLeft().getX(), orig->getTopLeft().getY());
    bottom_Right.setcoord(orig->getBottomRight().getX(), orig->getBottomRight().getY());
}

template <class T>
dimension<T>::~dimension() {
}

template <class T>
bool dimension<T>::equals(dimension<T> anDim) {
    bool res = (top_Left.equals(anDim.top_Left)) && (bottom_Right.equals(anDim.bottom_Right));
    return res;
}

template <class T>
T dimension<T>::getHeight() {
    return (bottom_Right.getY() - top_Left.getY() ) + 1;
}

template <class T>
T dimension<T>::getWidth() {
    return (bottom_Right.getX() - top_Left.getX() ) + 1;
}

template <class T>
void dimension<T>::setTopLeft(coordinate<T> topleft) {
    top_Left = topleft;
}

template <class T>
void dimension<T>::setBottomRight(coordinate<T> bottomright) {
    bottom_Right = bottomright;
}

template <class T>
int dimension<T>::compare(dimension<T> another) {
    int ires = 0;

    coordinate<T> firstCoord = getTopLeft();
    coordinate<T> secondCoord = another.getTopLeft();
    ires = firstCoord.compare(secondCoord);
    if (ires == 0) {
        firstCoord = getBottomRight();
        secondCoord = another.getBottomRight();
        ires = firstCoord.compare(secondCoord);
    }
    return ires;
}

template <class T>
void dimension<T>::read(string textvalue) {
    if (textvalue.length() > 2) {
        string val = stringmanipulation::stringbetween(textvalue, "<", ">");
        vector<string>* parts = stringparse::splitwords(val, ",");
        //int intval, intval2;
        T value1, value2;
        if (parts != nullptr) {
            if (parts->size() >= 4) {
                //intval = stringparse::strtoint((*parts)[0]);
                //intval2 = stringparse::strtoint((*parts)[1]);
                setTopLeft(coordinate<T>(value1, value2));
                /*
                intval = stringparse::strtoint((*parts)[2]) + intval - 1;
                intval2 = stringparse::strtoint((*parts)[3]) + intval2 - 1;
                 * */
                setBottomRight(coordinate<T>(value1, value2));
            }
        }
    }
}

template <class T>
coordinate<T> dimension<T>::getTopLeft() {
    return top_Left;
}

template <class T>
coordinate<T> dimension<T>::getBottomRight() {
    return bottom_Right;
}

template <class T>
std::string dimension<T>::print() {
    //Must fix for generic type
    std::ostringstream ss;
    ss << "<";
    ss << getTopLeft().getX();
    ss << ",";
    ss << getTopLeft().getY();
    ss << ">";
    return ss.str();
}

}

#endif	/* _DIMENSION_H */

