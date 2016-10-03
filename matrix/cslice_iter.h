#pragma once

#ifndef CSLICE_ITER_H
#define CSLICE_ITER_H

#ifndef CHECK_BOUNDS 
#define CHECK_BOUNDS 1
#endif 

#include <valarray>
using std::valarray;
using std::slice;

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <stdexcept>
using std::out_of_range;

#include <iterator>


template< typename T> class cslice_iter;
template< typename T> ostream &operator<< ( ostream&, const cslice_iter<T>& );
template< typename T> bool operator==( const cslice_iter<T>&, const cslice_iter<T>& );
template< typename T> bool operator!=( const cslice_iter<T>&, const cslice_iter<T>& );
template< typename T> bool operator< ( const cslice_iter<T>&, const cslice_iter<T>& );


template< typename T>
class cslice_iter
	: public std::iterator< std::random_access_iterator_tag, T >
{
public:

    friend ostream &operator<< <T>( ostream& output, const cslice_iter& slc ); 
	friend bool operator==<>( const cslice_iter& p, const cslice_iter& q );
	friend bool operator!=<>( const cslice_iter& p, const cslice_iter& q );
	friend bool operator< <>( const cslice_iter& p, const cslice_iter& q );

    cslice_iter( valarray<T> *vv, slice ss);
    ~cslice_iter(void);

    const T& ref(int) const;
    cslice_iter<T> end() const;
    cslice_iter<T> begin() const;
    cslice_iter<T> &operator++();
    cslice_iter<T> operator++(int);
    cslice_iter<T> &operator--();
    cslice_iter<T> operator--(int);
    const T &operator[]( int );
    const T &operator()( int ) ;
    const T &operator*();
	T &at( int );						// always bounds checked

	//public properties
	slice getSlice() const;
	void setSlice( slice );
	int getCurrentIndex() const;
	void setCurrentIndex( int );
	valarray<T>* getValarray() const;
	void setValarray( valarray<T>* );
	int getSize() const;

private:
    valarray<T> *v;
    slice s;
    int currentIndex;

};


#endif

