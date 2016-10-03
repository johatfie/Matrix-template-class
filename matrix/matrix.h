#ifndef matrix_H
#define matrix_H

#define CHECK_BOUNDS 1			// The performance loss with it on appears to be trivial
#define CHECK_SIZE 1

#include <cstdio>

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;


#include <stdexcept>
using std::invalid_argument;
using std::out_of_range;


#include <valarray>
using std::valarray;
using std::slice;
using std::gslice;
using std::gslice_array;


#include <numeric>
using std::inner_product;

#include <vector>
using std::vector;

#include <algorithm>
using std::max;

#include <math.h>
#include <cmath>
using std::abs;

#include <complex>

#include "slice_iter.cpp"
#include "cslice_iter.cpp"

template< typename T> class matrix;
template< typename T> ostream &operator<< ( ostream&, const matrix<T>& );
template< typename T> matrix<T> operator+ ( const T&, const matrix<T>&);
template< typename T> matrix<T> operator+ ( const matrix<T>&, const T&);
template< typename T> matrix<T> operator+ ( const matrix<T>&, const matrix<T>&);
//template< typename T> matrix<T> operator- ( const T &, const matrix<T> &);
template< typename T> matrix<T> operator- ( const matrix<T> &, const T & );
template< typename T> matrix<T> operator- ( const matrix<T> &, const matrix<T> &);
template< typename T> matrix<T> operator* ( const T &, const matrix<T> &);
template< typename T> matrix<T> operator* ( const matrix<T> &, const T & );
template< typename T> matrix<T> operator* ( const matrix<T> &, const matrix<T> &);


template< typename T> 
class matrix
{
public:

    //overloading the << operator as global function
    // used for printing the matrix
    friend ostream &operator<< <T>( ostream &, const matrix & ); 

    
	// constuctors & destructor
    explicit matrix(void);			//default constructor
    matrix(const matrix &);			//copy construstor
    matrix( int );					//construct empty matrix of size 1 x n
    matrix( int, int);				//construct empty matrix of size m x n
	matrix( int, int, int, int);	//construct empty matrix of size m x n and set the spareRows & spareColumns
    ~matrix(void);					//destructor

	matrix& initialize( const T [], int);
	matrix& initialize( const T [], int, int);
	matrix& initialize( const valarray<T> &);
	matrix& initialize( const vector<T> &);
	

	void printmatrix() const;

    //operator overloads
    matrix &operator=(const matrix &);
	matrix &operator=(const T &);
	matrix &operator=(const valarray<T> &);
	matrix &operator=(const vector<T> &);
    bool operator==(const matrix &) const;
    bool operator!=(const matrix &) const;
    slice_iter<T> operator[]( int );
    cslice_iter<T> operator[]( int ) const;	
	slice_iter<T> operator()( int );
    cslice_iter<T> operator()( int ) const;	
    T &operator()( int, int );    
    //T &operator[]( int );


	// arithmetic_operator_overloads
	//matrix operator+(const matrix &);
	//matrix operator+ ( const T &);
	friend matrix operator+ <T>( const T &, const matrix &);
	friend matrix operator+ <T>( const matrix &, const T &);
	friend matrix operator+ <T>( const matrix &, const matrix &);
	friend matrix operator- <T>( const T &, const matrix &);
	friend matrix operator- <T>( const matrix &, const T &);
    friend matrix operator- <T>( const matrix &, const matrix &);
	friend matrix operator*<T>( const T &, const matrix &);
    friend matrix operator*<T>( const matrix &, const T &);
    friend matrix operator*<T>( const matrix &, const matrix &);
    //matrix &operator/(const matrix &);	// Does Not Exist for matrices
	matrix operator/( const T &);
    //matrix &operator%(const matrix &);	// Does Not Exist for matrices
	matrix operator%( const T &);

    matrix &operator+=(const matrix &);
	matrix &operator+=( const T &);
    matrix &operator-=(const matrix &);
	matrix &operator-=( const T &);
    matrix &operator*=(const matrix &);
	matrix &operator*=( const T &);
    //matrix &operator/=(const matrix &);	// Does Not Exist for matrices
	matrix &operator/=( const T &);

	//friend matrix operator-<>( const T &, const matrix &);
	//friend matrix operator*<>( const T &, const matrix &);

	// these could be extended to include all the operators applicable to valarrays, i.e. |,^,~,!,etc.
	//matrix &operator(const matrix &);
	//matrix &operator( T );
	//matrix &operator(const matrix &);
	//matrix &operator( T );



    // utility_functions
    void resize( int, int );
    void compact();
    void reserve( int, int );


	// access_functions
    T& at( int );							// always bounds checked
    T& at( int, int );						// always bounds checked
	slice_iter<T> column( int );
	cslice_iter<T> column( int ) const;
    slice_iter<T> row( int );
    cslice_iter<T> row( int ) const;
	matrix getSubmatrix( int, int, int, int );		// starting row, starting column, number of rows, number of columns

	// linear_algebra_functions
	void ones( int );
	void zeros( int );
	void zeros ( int, int );
	bool isSymmetric();
    matrix inverse( int* );     
    matrix inverse();     
    //matrix<complex> eigenvalues();
	//matrix<complex> eigenvalues( int*);
    //LDL' factorization
	int* gauss();
	T* backSubstitution( int*, matrix& );		// matrix HAS had function gauss() performed on it. 
												// Second parameter is the "b" array of solutions.
	T* backSubstitution( int*, matrix&, matrix& );				// matrix HAS had function gauss() performed on it. 
																// Second parameter is the "b" array of solutions.
	matrix lower( int* );						// matrix HAS had function gauss() performed on it. Parameter is the resulting indexArray.
	matrix upper( int* );						// matrix HAS had function gauss() performed on it. Parameter is the resulting indexArray.
	matrix lower();								// matrix has NOT had function gauss() performed on it
	matrix upper();								// matrix has NOT had function gauss() performed on it
    //nullSpace;
    T det();
	T det( int* );
    matrix& transpose();
    matrix& toggleTransposed();
    T trace();

    // Public properties
    int rows() const;		// getNumberOfRows()
    int columns() const;	// getNumberOfColumns()

	int getNumberOfRows() const;
    int getNumberOfColumns() const;
    int getMaxRows() const;
    int getMaxColumns() const;
    bool getTransposed() const;
    matrix& setTransposed( bool );
	T* getArray();
    valarray<T> getValarray();
	vector<T> getVector();

private:

    void initializeMembers( int, int );			// these are private to insure that the matrix stays in a consistent state
    matrix& setMaxColumns( int );
    matrix& setMaxRows( int );
    matrix& setNumberOfRows( int );
    matrix& setNumberOfColumns( int );

	// utility_functions
	void resizeRows( int );
	void resizeColumns( int );
	void resizeValarray( int, int );


    int numOfRows;
    int numOfColumns;
    int maxRows;
    int maxColumns;
	int spareColumns;
	int spareRows;
    bool transposed;
    valarray<T> *vPtr;     //points to the "matrix"

};


#endif
