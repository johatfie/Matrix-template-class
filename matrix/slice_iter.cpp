#include "slice_iter.h"


template< typename T>
slice_iter<T>::slice_iter(valarray<T> *vv, slice ss)
    :v(vv), s(ss), currentIndex(0)
{
}


template< typename T>
slice_iter<T>::~slice_iter(void)
{
}


template< typename T> inline
T &slice_iter<T>::ref(int index) const
{
    return (*v)[ s.start() + ((size_t) index)*s.stride() ];
}


template< typename T>
slice_iter<T> slice_iter<T>::end()
{
    slice_iter<T> t = *this;
    t.currentIndex = s.size();  // index of last plus one element
    return t;
}


template< typename T>
slice_iter<T> slice_iter<T>::begin()
{
    slice_iter<T> t = *this;
    t.currentIndex = 0;         // index of first element
    return t;
}


template< typename T> 
slice_iter<T> &slice_iter<T>::operator++()    //prefix increment operator overload
{
#if CHECK_BOUNDS
    if(currentIndex >= s.size() )
    {
        throw out_of_range( "Index out of bounds" );
    }
#endif

    currentIndex++;
    return *this;
}


template< typename T> 
slice_iter<T> slice_iter<T>::operator++( int )  //postfix increment operator overload
{
#if CHECK_BOUNDS
    if(currentIndex >= s.size() )
    {
        throw out_of_range( "Index out of bounds" );
    }
#endif

    slice_iter<T> t = *this;
    currentIndex++;
    return t;
}


template< typename T>
slice_iter<T> &slice_iter<T>::operator--()   //prefix decrement operator overload
{
#if CHECK_BOUNDS
    if(currentIndex <= 0)
    {
        throw out_of_range( "Index out of bounds" );
    }
#endif

    currentIndex--;
    return *this;
}


template< typename T>
slice_iter<T> slice_iter<T>::operator--( int )  //postfix decrement operator overload
{
#if CHECK_BOUNDS
    if(currentIndex <= 0)
    {
        throw out_of_range( "Index out of bounds" );
    }
#endif

    slice_iter<T> t = *this;
    currentIndex--;
    return t;
}


template< typename T> inline
T &slice_iter<T>::operator[](int index)        // [] operator overload
{
#if CHECK_BOUNDS
    if( (index<0) || ( (size_t) index>=s.size() ) )
    {
        throw out_of_range( "Index out of bounds" );
    }
#endif

	return ref( index );
}


template< typename T> inline
T &slice_iter<T>::operator() (int index)       // () operator overload
{
#if CHECK_BOUNDS
    if( (index<0) || ( (size_t) index>=s.size() ) )
    {
        throw out_of_range( "Index out of bounds" );
    }
#endif

    return ref( index );
}


template< typename T> inline
T &slice_iter<T>::operator*()          // dereferencing operator overload
{
    return ref(currentIndex);
}


template< typename T> 
T &slice_iter<T>::at( int index)
{
    if( (index<0) || ( (size_t) index>=s.size() ) )
    {
        throw out_of_range( "Index out of bounds" );
    }

	return ref( index );
}


#pragma region public_properties

template< typename T>
slice slice_iter<T>::getSlice() const
{
	return s;
}


template< typename T>
void slice_iter<T>::setSlice( slice ss)
{
	s = ss;
}


template< typename T>
int slice_iter<T>::getCurrentIndex() const
{
	return currentIndex;
}


template< typename T>
void slice_iter<T>::setCurrentIndex( int i)
{
	currentIndex = i;
}


template< typename T>
valarray<T>* slice_iter<T>::getValarray() const
{
	return v;
}


template< typename T>
void slice_iter<T>::setValarray( valarray<T>* vv)
{
	delete v;
	v = vv;
}

template< typename T> inline
int slice_iter<T>::getSize() const
{
	return (int) s.size();
}
#pragma endregion


// global operator overloads
#pragma region global_operator_overloads


template< typename T>
bool operator==(const slice_iter<T>& p, const slice_iter<T>& q)
{
    return ( p.currentIndex == q.currentIndex && p.s.stride()==q.s.stride() && p.s.start()==q.s.start() );
}

template< typename T> 
bool operator!=(const slice_iter<T>& p, const slice_iter<T>& q)
{
    return !(p==q);
}

template< typename T> 
bool operator<(const slice_iter<T>& p, const slice_iter<T>& q)
{
    return (p.currentIndex < q.currentIndex && p.s.stride()==q.s.stride() && p.s.start()==q.s.start() );
}


#pragma endregion

template< typename T>
ostream &operator<<( ostream &output, slice_iter<T> &slc )
{
	for(int i = 0; i<slc.getSize(); i++)
	{
		output << slc[i] << "\t";
	}

	output << "\n";

	return output;
}
