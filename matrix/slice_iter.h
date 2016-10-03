#pragma once

#ifndef SLICE_ITER_H
#define SLICE_ITER_H

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

template< typename T> class slice_iter;
template< typename T> ostream &operator<< ( ostream&, slice_iter<T>& );
template< typename T> bool operator==( const slice_iter<T>&, const slice_iter<T>& );
template< typename T> bool operator!=( const slice_iter<T>&, const slice_iter<T>& );
template< typename T> bool operator< ( const slice_iter<T>&, const slice_iter<T>& );

template< typename T>
class slice_iter
	: public std::iterator<std::random_access_iterator_tag, T>
{
public:

    friend ostream &operator<< <T>( ostream& output, slice_iter& slc ); 
	friend bool operator==<>( const slice_iter& p, const slice_iter& q);
	friend bool operator!=<>( const slice_iter& p, const slice_iter& q);
	friend bool operator< <>( const slice_iter& p, const slice_iter& q);

    slice_iter( valarray<T> *vv, slice ss);
    ~slice_iter(void);

    T& ref(int) const;
    slice_iter<T> end();
    slice_iter<T> begin();
    slice_iter<T> &operator++();
    slice_iter<T> operator++(int);
    slice_iter<T> &operator--();
    slice_iter<T> operator--(int);
    T &operator[]( int );
    T &operator()( int ) ;
    T &operator*();
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


