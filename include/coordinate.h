/*
 * File:   coordinate.h
 * Author: raoul
 *
 */

#ifndef _COORDINATE_H
#define	_COORDINATE_H

#include <string>
#include "stringmanipulation.h"
#include "stringparse.h"

using namespace std;

template <class T>
class coordinate {
public:
    coordinate<T>();
    coordinate<T>(T x, T y, int printStyle = 1, int sortFlag = 1);
    coordinate<T>(const coordinate<T>& orig);
    virtual ~coordinate();
    void setcoord(T x, T y);
    void read(string textvalue);
    coordinate<T> add(T x, T y);
    T compare(coordinate<T> another);
    string print();

    T getX();
    T getY();
    int getsortflag();
    bool equals(coordinate another);
    coordinate<T> operator - (coordinate<T> another);
    coordinate<T> operator + (coordinate<T> another);
    bool operator == (coordinate<T> another);
    //static bool sortcoordinatepredicate(coordinate<T> crd1, coordinate<T> crd2);
    //static void setfixedcolumns(int fixedcols);
private:
    T X, Y;
    int printstyle;
    int sortflag;
};

template <class T>
coordinate<T>::coordinate() {
    printstyle = 1;
    sortflag = 1;
}

template <class T>
coordinate<T>::coordinate(T x, T y, int printStyle, int sortFlag) {
    X = x;
    Y = y;
    printstyle = printStyle;
    sortflag = sortFlag;
}

template <class T>
coordinate<T>::coordinate(const coordinate<T>& orig) {
    X = orig.X;
    Y = orig.Y;
    printstyle = orig.printstyle;
    sortflag = orig.sortflag;
}

template <class T>
void coordinate<T>::setcoord(T x, T y) {
    X = x;
    Y = y;
}

template <class T>
void coordinate<T>::read(string textvalue) {
    if (textvalue.length() > 2) {
        string val = stringmanipulation::stringbetween(textvalue, "<", ">");
        vector<string>* parts = stringparse::splitwords(val, ",");
        if (parts != nullptr) {
            if (parts->size() >= 2) {

            }
            delete parts;
        }
    }
}

template <class T>
coordinate<T>::~coordinate() {
}

template <class T>
T coordinate<T>::getX() {
    return X;
}

template <class T>
T coordinate<T>::getY() {
    return Y;
}

template <class T>
coordinate<T> coordinate<T>::add(T x, T y) {
    coordinate res(getX(), getY());
    res = res + coordinate(x, y);
    return res;
}

template <class T>
T coordinate<T>::compare(coordinate<T> another) {
    //int ires = 0;

    //(getY() - another.getY()) * fixedcolumns) + (getX() - another.getX());
    T res = ((getY() - another.getY()) ) + (getX() - another.getX());
    return res;
}

template <class T>
string coordinate<T>::print() {
    string res = "";
    /*
    if (printstyle <= 1)
        res = "<" + stringparse::inttostr(getX()) + "," + stringparse::inttostr(getY()) + ">";
    else {
        res = "<coordinate>" + string("X=") + stringparse::inttostr(getX()) + "Y=" + stringparse::inttostr(getY());
    }
     * */
    return res;
}

template <class T>
bool coordinate<T>::equals(coordinate<T> another) {
    bool res = (getY() == another.getY()) && (getX() == another.getX());
    return res;
}

template <class T>
int coordinate<T>::getsortflag() {
    return sortflag;
}

template <class T>
coordinate<T> coordinate<T>::operator - (coordinate<T> another) {
    T iy = Y - another.getY();
    T ix = X - another.getX();
    return coordinate(ix, iy);
}

template <class T>
coordinate<T> coordinate<T>::operator + (coordinate<T> another) {
    T iy = Y + another.getY();
    T ix = X + another.getX();
    return coordinate(ix, iy);
}

template <class T>
bool coordinate<T>::operator == (coordinate<T> another) {
    return (X == another.getX()) && (Y == another.getY());
}
/*
template <class T>
void coordinate<T>::setfixedcolumns(int fixedcols) {
    fixedcolumns = fixedcols;
}

template <class T>
bool coordinate<T>::sortcoordinatepredicate(coordinate<T> crd1, coordinate<T> crd2) {
    bool res = false;
    int sortflag1 = crd1.getsortflag();
    if (sortflag1 <= 1)
        res = (crd1.getX() < crd2.getX());
    else if (sortflag1 == 2)
        res = (crd1.getY() < crd2.getY());
    return res;
}*/

#endif	/* _COORDINATE_H */

