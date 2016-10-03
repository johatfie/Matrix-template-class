#include "matrix.h"


#pragma region Constructors

template< typename T>
matrix<T>::matrix(void)
:vPtr(0),transposed(false),spareRows(4),spareColumns(4)				//initialize pointers to NULL
{
	initializeMembers( 1, 1 );
}


template< typename T>
matrix<T>::matrix( int columns)									// construct empty matrix of size 1 x n
:vPtr(0),transposed(false),spareRows(4),spareColumns(4)			// initialize pointers to NULL
{
	initializeMembers( 1, columns );
}


template< typename T>
matrix<T>::matrix( int rows, int columns)
:vPtr(0),transposed(false),spareRows(4),spareColumns(4)			// initialize pointers to NULL
{
	initializeMembers( rows, columns );
}


template< typename T>
matrix<T>::matrix( int rows, int columns, int extraRows, int extraColumns)
:vPtr(0),transposed(false),spareRows(extraRows),
	spareColumns(extraColumns)									//initialize pointers to NULL
{
	initializeMembers( rows, columns );
}


template< typename T>
matrix<T>::matrix( const matrix<T> &m)   //copy constructor
:vPtr(0),transposed(m.transposed),spareRows(m.spareRows),
	spareColumns(m.spareColumns)								//initialize pointers to NULL
{
	initializeMembers( m.numOfRows,m.numOfColumns );


	(*vPtr) += *(m.vPtr);
}


template< typename T>
matrix<T>::~matrix(void)
{
	delete vPtr;
    vPtr = 0;
}


#pragma endregion //Constructors


template< typename T>
matrix<T> &matrix<T>::initialize( const T inputArray[], int size)
{
	initialize( inputArray, size, 1);

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::initialize( const T inputArray[], int rows, int columns)	// m*n should equal the size of the array
																				// there's no bounds checking on the array
{
	*vPtr = 0;

	for(int i=0; i<rows; i++)
	{
		slice_iter<T> currentRow = row(i);

		for(int j=0; j<columns; j++)
		{
			currentRow(j) = inputArray[i*columns+j];
		}
	}

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::initialize( const valarray<T> &val)
{
	*vPtr = 0;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {0,0};
	size_t strides[] = {0,0};

	if( !transposed )
	{
		lengths[0] = numOfRows;
		lengths[1] = numOfColumns;
		strides[0] = maxColumns;
		strides[1] = 1;
	}
	else
	{
		lengths[0] = numOfColumns;
		lengths[1] = numOfRows;
		strides[0] = 1;
		strides[1] = maxColumns;
	}


	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );

	// if val is too long, extra elements are ignored
	// if val is too short, then out of bounds elements will be used!  No bounds checking.
	(*vPtr)[currentElements] += val;

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::initialize( const vector<T> &vec)		// vectors that are too small will throw an exception
															// vectors that are too large will have some elements ignored
{
	*vPtr = 0;

	int rows = getNumberOfRows();
	for(int i=0; i<rows; i++)
	{
		slice_iter<T> currentRow = row(i);
		int columns = currentRow.getSize();

		for(int j=0; j<columns; j++)
		{
			currentRow(j) = vec.at(i*columns+j);
		}
	}

	return *this;
}


template< typename T>
void matrix<T>::initializeMembers( int rows, int columns)
{
    setNumberOfColumns(columns);
    setNumberOfRows(rows);
    setMaxColumns(columns + spareColumns);
    setMaxRows(rows + spareRows);

    size_t val = 0;

	//create valarray of zeros
    vPtr = new valarray<T>( val,(size_t) maxRows * (size_t) maxColumns );

}


template< typename T>
void matrix<T>::printmatrix() const
{

	for(int i = 0; i<numOfRows; i++)
	{
		cslice_iter<T> currentRow = row(i);
		size_t size = currentRow.getSize();

		for(int j = 0; j<size; j++)
		{
			cout << currentRow[j] << "\t";
		}

		cout << "\n";
	}

}


#pragma region Operator overloads


template< typename T>
slice_iter<T> matrix<T>::operator[]( int index)
{
#if CHECK_BOUNDS
    if( ( index<0) || ( index>=(size_t) numOfRows * (size_t) numOfColumns ) )
    {
        throw out_of_range( "Index out of bounds" );
    }
#endif

    return row( index );
}


template< typename T>
cslice_iter<T> matrix<T>::operator[]( int index) const
{
#if CHECK_BOUNDS
    if( (index<0) || (index>=(size_t) numOfRows * (size_t) numOfColumns ) )
    {
        throw out_of_range( "Index out of bounds" );
    }
#endif

	return row( index );
}


template< typename T>
slice_iter<T> matrix<T>::operator()( int index)
{
#if CHECK_BOUNDS
    if( ( index<0) || ( index>=(size_t) numOfRows * (size_t) numOfColumns ) )
    {
        throw out_of_range( "Index out of bounds" );
    }
#endif

	//if(numOfRows == 1)			// if the matrix is one dimensional (a mathematical vector)
	//{
	//	return at(0,index);		//doesn't work
	//}
	//else
	//{
		return row( index );
	//}
}


template< typename T>
cslice_iter<T> matrix<T>::operator()( int index) const
{
#if CHECK_BOUNDS
    if( (index<0) || (index>=(size_t) numOfRows * (size_t) numOfColumns ) )
    {
        throw out_of_range( "Index out of bounds" );
    }
#endif

	//if(numOfRows == 1)
	//{
	//	return at(0,index);
	//}
	//else
	//{
		return row( index );
	//}
}


template< typename T>
T &matrix<T>::operator()(int i, int j)
{
	return row(i)[j];
}

template< typename T>
matrix<T> &matrix<T>::operator=(const matrix<T> &right)
{
	if(*this == right)
	{
		return *this;
	}
	numOfRows = right.numOfRows;
	numOfColumns = right.numOfColumns;
	maxRows = right.maxRows;
	maxColumns = right.maxColumns;
	transposed = right.transposed;
	spareRows = right.spareRows;
	spareColumns = right.spareColumns;

	delete vPtr;

	size_t val = 0;
	vPtr = new valarray<T>( val,(size_t) maxRows * (size_t) maxColumns );			//check this.
																					// should be maxRows*maxColumns

	(*vPtr) += *(right.vPtr);

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::operator=(const T &val)
{
	*vPtr = 0;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {numOfRows,numOfColumns};
	size_t strides[] = {maxColumns,1};


	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );

	(*vPtr)[currentElements] = val;

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::operator=(const valarray<T> &val)
{
	initialize(val);

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::operator=(const vector<T> &vec)
{
	initialize(vec);

	return *this;
}


template< typename T>
bool matrix<T>::operator==(const matrix<T> &right) const
{
	// this function does not check that the extra space in the matrices are of equal size
	// But, once fully implemented, automatic resizing should make that irrelevant

    if( ( numOfRows != right.getNumberOfRows() ) ||
        ( numOfColumns != right.getNumberOfColumns() )  )
    {
        return false;
    }

	// gslice_arrays have no == operator, so we must compare element by element
    for(int i = 0; i<numOfRows; i++)
    {
		cslice_iter<T> currentRow = row(i);
		cslice_iter<T> currentRightRow = right.row(i);
		size_t size = currentRow.getSize();

		for(int j = 0; j<size; j++)
        {
            if( currentRow[j] != currentRightRow[j] )
            {
                return false;
            }
        }
    }

    return true;
}

template< typename T>
bool matrix<T>::operator!=(const matrix<T> &right) const
{
    return !(*this==right);
}

#pragma endregion //Operator overloads


#pragma region arithmetic_operator_overloads

//template< typename T>
//matrix<T> matrix<T>::operator+( const matrix<T> &rhs)
//{
//#if CHECK_SIZE
//	if( ( getNumberOfColumns() != rhs.getNumberOfColumns() ) ||
//		( getNumberOfRows()	   != rhs.getNumberOfRows()    ) )
//	{
//		throw invalid_argument("Matrices must have the same dimensions.");
//	}
//#endif
//
//	matrix<T> temp = *this;
//
//	// selecting the current (non-reserved) elements of the matrix
//	size_t start = 0;
//	size_t lengths[] = {numOfRows,numOfColumns};
//	size_t strides[] = {maxColumns,1};
//	size_t lengthsRhs[] = {0,0};
//	size_t stridesRhs[] = {0,0};
//
//	if( (transposed  &&  rhs.transposed ) ||
//		(!transposed && !rhs.transposed ) )
//	{
//		lengthsRhs[0] = rhs.numOfRows;
//		lengthsRhs[1] = rhs.numOfColumns;
//		stridesRhs[0] = rhs.maxColumns;
//		stridesRhs[1] = 1;
//	}
//	else
//	{
//		lengthsRhs[0] = rhs.numOfColumns;
//		lengthsRhs[1] = rhs.numOfRows;
//		stridesRhs[0] = 1;
//		stridesRhs[1] = rhs.maxColumns;
//	}
//
//
//	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );
//	const gslice currentElementsRhs( start, valarray<size_t>(lengthsRhs,2), valarray<size_t>(stridesRhs,2) );
//
//
//	// unfortunately gslice_arrays do not have a += operator for gslice_arrays, thus the valarray is necessary :(
//	(*(temp.vPtr))[currentElements] += valarray<T>( (*(rhs.vPtr) )[currentElementsRhs] );
//
//	return temp;
//}


template< typename T>
matrix<T> operator+( const matrix<T> &lhs, const matrix<T> &rhs)
{
#if CHECK_SIZE
	if( ( lhs.getNumberOfColumns() != rhs.getNumberOfColumns() ) ||
		( lhs.getNumberOfRows()	   != rhs.getNumberOfRows()    ) )
	{
		throw invalid_argument("Matrices must have the same dimensions.");
	}
#endif

	matrix<T> temp = lhs;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {lhs.numOfRows,lhs.numOfColumns};
	size_t strides[] = {lhs.maxColumns,1};
	size_t lengthsRhs[] = {0,0};
	size_t stridesRhs[] = {0,0};

	if( (lhs.transposed  &&  rhs.transposed ) ||
		(!lhs.transposed && !rhs.transposed ) )
	{
		lengthsRhs[0] = rhs.numOfRows;
		lengthsRhs[1] = rhs.numOfColumns;
		stridesRhs[0] = rhs.maxColumns;
		stridesRhs[1] = 1;
	}
	else
	{
		lengthsRhs[0] = rhs.numOfColumns;
		lengthsRhs[1] = rhs.numOfRows;
		stridesRhs[0] = 1;
		stridesRhs[1] = rhs.maxColumns;
	}


	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );
	const gslice currentElementsRhs( start, valarray<size_t>(lengthsRhs,2), valarray<size_t>(stridesRhs,2) );


	// unfortunately gslice_arrays do not have a += operator for gslice_arrays, thus the valarray is necessary :(
	(*(temp.vPtr))[currentElements] += valarray<T>( (*(rhs.vPtr) )[currentElementsRhs] );

	return temp;
}


//template< typename T>
//matrix<T> matrix<T>::operator+( const T &rhs)		// yes I know that 'const T &rhs' is overkill for 'T rhs'
//													// but anything for more efficiency
//{
//	matrix<T> temp = *this;
//
//	// selecting the current (non-reserved) elements of the matrix
//	size_t start = 0;
//	size_t lengths[] = {numOfRows,numOfColumns};
//	size_t strides[] = {maxColumns,1};
//
//	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );
//
//
//	// unfortunately gslice_arrays do not have a += operator for constants, thus the valarray is necessary :(
//	(*(temp.vPtr))[currentElements] += valarray<T>( rhs, (size_t) numOfRows * (size_t) numOfColumns );
//
//	return temp;
//}


template< typename T>
matrix<T> operator+( const matrix<T> &lhs, const T &rhs)		// yes I know that 'const T &rhs' is overkill for 'T rhs'
																// but anything for more efficiency
{
	matrix<T> temp = lhs;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {lhs.numOfRows,lhs.numOfColumns};
	size_t strides[] = {lhs.maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a += operator for constants, thus the valarray is necessary :(
	//(*(temp.vPtr))[currentElements] += valarray<T>( rhs, (size_t) lhs.getNumberOfRows() * (size_t) lhs.getNumberOfColumns() );
	(*(temp.vPtr))[currentElements] += valarray<T>( rhs, (size_t) lhs.numOfRows * (size_t) lhs.numOfColumns );

	return temp;
}


template< typename T>
matrix<T> operator-(const matrix<T> &lhs, const matrix<T> &rhs)
{
#if CHECK_SIZE
	if( ( lhs.getNumberOfColumns() != rhs.getNumberOfColumns() ) ||
		( lhs.getNumberOfRows()	   != rhs.getNumberOfRows()    ) )
	{
		throw invalid_argument("Matrices must have the same dimensions.");
	}
#endif

	matrix<T> temp = lhs;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {lhs.numOfRows,lhs.numOfColumns};
	size_t strides[] = {lhs.maxColumns,1};
	size_t lengthsRhs[] = {0,0};
	size_t stridesRhs[] = {0,0};

	if( (lhs.transposed  &&  rhs.transposed ) ||
		(!lhs.transposed && !rhs.transposed ) )
	{
		lengthsRhs[0] = rhs.numOfRows;
		lengthsRhs[1] = rhs.numOfColumns;
		stridesRhs[0] = rhs.maxColumns;
		stridesRhs[1] = 1;
	}
	else
	{
		lengthsRhs[0] = rhs.numOfColumns;
		lengthsRhs[1] = rhs.numOfRows;
		stridesRhs[0] = 1;
		stridesRhs[1] = rhs.maxColumns;
	}


	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );
	const gslice currentElementsRhs( start, valarray<size_t>(lengthsRhs,2), valarray<size_t>(stridesRhs,2) );


	// unfortunately gslice_arrays do not have a -= operator for gslice_arrays, thus the valarray is necessary :(
	(*(temp.vPtr))[currentElements] -= valarray<T>( (*(rhs.vPtr) )[currentElementsRhs] );

	return temp;
}


template< typename T>
matrix<T> operator-( const matrix<T> &lhs, const T &rhs)
{
	matrix<T> temp = lhs;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {lhs.numOfRows,lhs.numOfColumns};
	size_t strides[] = {lhs.maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a -= operator for constants, thus the valarray is necessary :(
	(*(temp.vPtr))[currentElements] -= valarray<T>( rhs, (size_t) lhs.numOfRows * (size_t) lhs.numOfColumns );

	return temp;
}


template< typename T>
matrix<T> operator*(const matrix<T> &lhs, const matrix<T> &rhs)
{
#if CHECK_SIZE
	if(  lhs.getNumberOfColumns() != rhs.getNumberOfRows() )
	{
		throw invalid_argument("The number of columns in the left matrix must equal the number of rows in the right matrix.");
	}
#endif

	matrix<T> temp( lhs.getNumberOfRows(), rhs.getNumberOfColumns() );


	for( int i=0; i<temp.numOfRows; i++)
	{
		cslice_iter<T> currentRow = lhs.row(i);
		cslice_iter<T> currentRowEnd = currentRow.end();

		for(int j=0; j<temp.numOfColumns; j++)
		{
			T init = 0;
			cslice_iter<T> currentColumn = rhs.column(j);

			//while( currentRow != currentRow.end() )
			//{
			//	init = init + *currentRow++ * *currentColumn++;
			//}

			for(; currentRow != currentRowEnd; ++currentRow, ++currentColumn )
			{
				init = init + *currentRow * *currentColumn;
			}

			//(*(temp.vPtr))[i*temp.maxColumns+j] = inner_product(currentRow,currentRow.end(),rhs.column(j), val);

			(*(temp.vPtr))[i*temp.maxColumns+j] = init;
			currentRow.setCurrentIndex(0);		// reset cslice_iter to beginning
		}

	}

	return temp;
}


template< typename T>
matrix<T> operator*( const matrix<T> &lhs, const T &rhs)
{
	matrix<T> temp = lhs;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {lhs.numOfRows,lhs.numOfColumns};
	size_t strides[] = {lhs.maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a *= operator for constants, thus the valarray is necessary :(
	(*(temp.vPtr))[currentElements] *= valarray<T>( rhs, (size_t) lhs.numOfRows * (size_t) lhs.numOfColumns );

	return temp;
}


template< typename T>
matrix<T> matrix<T>::operator/( const T &rhs)
{
	matrix<T> temp = *this;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {numOfRows,numOfColumns};
	size_t strides[] = {maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a /= operator for constants, thus the valarray is necessary :(
	(*(temp.vPtr))[currentElements] /= valarray<T>( rhs, (size_t) (size_t) numOfRows * (size_t) numOfColumns );

	return temp;
}


template< typename T>
matrix<T> matrix<T>::operator%( const T &rhs)
{
	matrix<T> temp = *this;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {numOfRows,numOfColumns};
	size_t strides[] = {maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a %= operator for constants, thus the valarray is necessary :(
	(*(temp.vPtr))[currentElements] %= valarray<T>( rhs, (size_t) numOfRows * (size_t) numOfColumns );

	return temp;
}


template< typename T>
matrix<T> &matrix<T>::operator+=(const matrix<T> &rhs)
{
#if CHECK_SIZE
	if( ( getNumberOfColumns() != rhs.getNumberOfColumns() ) ||
		( getNumberOfRows()	   != rhs.getNumberOfRows()    ) )
	{
		throw invalid_argument("Matrices must have the same dimensions.");
	}
#endif

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {numOfRows,numOfColumns};
	size_t strides[] = {maxColumns,1};
	size_t lengthsRhs[] = {0,0};
	size_t stridesRhs[] = {0,0};

	if( (transposed  &&  rhs.transposed ) ||
		(!transposed && !rhs.transposed ) )
	{
		lengthsRhs[0] = rhs.numOfRows;
		lengthsRhs[1] = rhs.numOfColumns;
		stridesRhs[0] = rhs.maxColumns;
		stridesRhs[1] = 1;
	}
	else
	{
		lengthsRhs[0] = rhs.numOfColumns;
		lengthsRhs[1] = rhs.numOfRows;
		stridesRhs[0] = 1;
		stridesRhs[1] = rhs.maxColumns;
	}


	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );
	const gslice currentElementsRhs( start, valarray<size_t>(lengthsRhs,2), valarray<size_t>(stridesRhs,2) );


	// unfortunately gslice_arrays do not have a += operator for gslice_arrays, thus the valarray is necessary :(
	(*vPtr)[currentElements] += valarray<T>( (*(rhs.vPtr) )[currentElementsRhs] );

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::operator+=( const T &rhs)
{
	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {numOfRows,numOfColumns};
	size_t strides[] = {maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a += operator for constants, thus the valarray is necessary :(
	(*vPtr)[currentElements] += valarray<T>( rhs, (size_t) numOfRows * (size_t) numOfColumns );

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::operator-=(const matrix<T> &rhs)
{
#if CHECK_SIZE
	if( ( getNumberOfColumns() != rhs.getNumberOfColumns() ) ||
		( getNumberOfRows()	   != rhs.getNumberOfRows()    ) )
	{
		throw invalid_argument("Matrices must have the same dimensions.");
	}
#endif

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {numOfRows,numOfColumns};
	size_t strides[] = {maxColumns,1};
	size_t lengthsRhs[] = {0,0};
	size_t stridesRhs[] = {0,0};

	if( (transposed  &&  rhs.transposed ) ||
		(!transposed && !rhs.transposed ) )
	{
		lengthsRhs[0] = rhs.numOfRows;
		lengthsRhs[1] = rhs.numOfColumns;
		stridesRhs[0] = rhs.maxColumns;
		stridesRhs[1] = 1;
	}
	else
	{
		lengthsRhs[0] = rhs.numOfColumns;
		lengthsRhs[1] = rhs.numOfRows;
		stridesRhs[0] = 1;
		stridesRhs[1] = rhs.maxColumns;
	}


	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );
	const gslice currentElementsRhs( start, valarray<size_t>(lengthsRhs,2), valarray<size_t>(stridesRhs,2) );


	// unfortunately gslice_arrays do not have a -= operator for gslice_arrays, thus the valarray is necessary :(
	(*vPtr)[currentElements] -= valarray<T>( (*(rhs.vPtr) )[currentElementsRhs] );

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::operator-=( const T &rhs)
{
	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {numOfRows,numOfColumns};
	size_t strides[] = {maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a -= operator for constants, thus the valarray is necessary :(
	(*vPtr)[currentElements] -= valarray<T>( rhs, (size_t) numOfRows * (size_t) numOfColumns );

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::operator*=(const matrix<T> &rhs)
{
#if CHECK_SIZE
	if(  getNumberOfColumns() != rhs.getNumberOfRows() )
	{
		throw invalid_argument("The number of columns in the left matrix must equal the number of rows in the right matrix.");
	}
#endif

	matrix<T> temp( getNumberOfRows(), rhs.getNumberOfColumns() );

	//(*(temp.vPtr))[i*temp.maxColumns+j] = inner_product(currentRow,currentRow.end(),rhs.column(j), val);


	for( int i=0; i<temp.numOfRows; i++)
	{
		slice_iter<T> currentRow = row(i);
		slice_iter<T> currentRowEnd = currentRow.end();

		for(int j=0; j<temp.numOfColumns; j++)
		{
			T init = 0;
			cslice_iter<T> currentColumn = rhs.column(j);

			//while( currentRow != currentRow.end() )
			//{
			//	init = init + *currentRow++ * *currentColumn++;
			//}

			for(; currentRow != currentRowEnd; ++currentRow, ++currentColumn )	// optimized
			{
				init = init + *currentRow * *currentColumn;
			}


			(*(temp.vPtr))[i*temp.maxColumns+j] = init;

			currentRow.setCurrentIndex(0);		// reset cslice_iter to beginning
		}
	}

	*this = temp;

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::operator*=( const T &rhs)
{
	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {numOfRows,numOfColumns};
	size_t strides[] = {maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a *= operator for constants, thus the valarray is necessary :(
	(*vPtr)[currentElements] *= valarray<T>( rhs, (size_t) numOfRows * (size_t) numOfColumns );

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::operator/=( const T &rhs)
{
	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {numOfRows,numOfColumns};
	size_t strides[] = {maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a /= operator for constants, thus the valarray is necessary :(
	(*vPtr)[currentElements] /= valarray<T>( rhs, (size_t) numOfRows * (size_t) numOfColumns );

	return *this;
}

template< typename T>
matrix<T> operator+( const T &lhs, const matrix<T> &rhs)
{
	matrix<T> temp = rhs;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {rhs.numOfRows,rhs.numOfColumns};
	size_t strides[] = {rhs.maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a += operator for constants, thus the valarray is necessary :(
	(*(temp.vPtr))[currentElements] += valarray<T>( lhs, (size_t) (rhs.numOfRows * rhs.numOfColumns) );

	return temp;
}


template< typename T>
matrix<T> operator-( const T &lhs, const matrix<T> &rhs)
{
	matrix<T> temp(rhs.numOfRows, rhs.numOfColumns, rhs.spareRows, rhs.spareColumns);
	temp.setTransposed(rhs.transposed);

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {rhs.numOfRows,rhs.numOfColumns};
	size_t strides[] = {rhs.maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a -= operator for constants, thus the valarray is necessary :(
	//(*(temp.vPtr))[currentElements] -= valarray<T>( lhs, (size_t) (rhs.numOfRows * rhs.numOfColumns) );
	(*(temp.vPtr))[currentElements] = lhs;

	return temp - rhs;
}


template< typename T>
matrix<T> operator*( const T &lhs, const matrix<T> &rhs)
{
	matrix<T> temp = rhs;

	// selecting the current (non-reserved) elements of the matrix
	size_t start = 0;
	size_t lengths[] = {rhs.numOfRows,rhs.numOfColumns};
	size_t strides[] = {rhs.maxColumns,1};

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	// unfortunately gslice_arrays do not have a *= operator for constants, thus the valarray is necessary :(
	(*(temp.vPtr))[currentElements] *= valarray<T>( lhs, (size_t) (rhs.numOfRows * rhs.numOfColumns) );

	// Yes, I know that spare elements should all be equal to zero and I could just multiply the entire valarray by the constant
	// but I chose not to do that here in case the matrix has somehow become inconsistent and some spare elements are not equal to zero

	return temp;
}


//matrix<T> &operator(const matrix<T> &rhs);
//matrix<T> operator( const T &rhs);
//matrix<T> &operator(const matrix<T> &rhs);
//matrix<T> operator( const T &rhs);

#pragma endregion


#pragma region utility_functions

template< typename T>
void matrix<T>::resize( int m, int n )
{
#if CHECK_SIZE
	if(m<1)
    {
        throw invalid_argument("Number of rows cannot be less than one.");
    }

	if(n<1)
    {
        throw invalid_argument("Number of columns cannot be less than one.");
    }
#endif

	if( (getMaxRows() < m) || (getMaxColumns() < n) )
	{
		resizeValarray( m, n);	// this must come before resizeRows() & resizeColumns()
	}

	resizeColumns( n );
	resizeRows( m );

}

template< typename T>
void matrix<T>::resizeColumns( int n )
{
	if( getNumberOfColumns() < n )
	{
		setNumberOfColumns(n);			// the "new" column should be full of zeros already
	}
	else if( getNumberOfColumns() > n )
	{
		// we need to zero out the "deleted" columns
		if(!transposed)
		{
			size_t start = n;
			size_t lengths[] = {numOfRows,numOfColumns - n};
			size_t strides[] = {maxColumns,1};

			const gslice deletedSlice( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );

			(*vPtr)[deletedSlice]=0;

			numOfColumns = n;
		}
		else
		{
			(*vPtr)[slice( (size_t) ( n * maxColumns ),
				(size_t) ( numOfRows - n ) * (size_t) maxColumns , (size_t) 1) ]=0;

			numOfRows = n;
		}

	}

}


template< typename T>
void matrix<T>::resizeRows( int m )
{
	if( getNumberOfRows() < m )
	{
		setNumberOfRows( m );				// "new" row should be full of zeros already
	}
	else if( getNumberOfRows() > m )
	{
		// we need to zero out the "deleted" rows
		if(!transposed)
		{
			(*vPtr)[slice( (size_t) ( m * maxColumns ),
				(size_t)( numOfRows - m ) * (size_t) maxColumns , (size_t) 1) ]=0;

			numOfRows = m;
		}
		else
		{
			size_t start = m;
			size_t lengths[] = {numOfRows,numOfColumns-m};
			size_t strides[] = {maxColumns,1};

			const gslice deletedSlice( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );

			(*vPtr)[deletedSlice]=0;

			numOfColumns = m;
		}

	}

}

// This function was extremely difficult to get correct.  Don't mess with it.
template< typename T>
void matrix<T>::resizeValarray( int m, int n)		// assumes m = getNumberOfRows() & n = getNumberOfColumns()
{
		//create new valarray of zeros

		size_t val = 0;
		valarray<T> *temp = new valarray<T>( val, (size_t)(m+spareRows)*(size_t)(n+spareColumns) );

		// ignoring transposed status and copy underlying valarray
		size_t start = 0;
		size_t oldLengths[] = {numOfRows,numOfColumns};
		size_t oldStrides[] = {maxColumns,1};
		size_t newLengths[] = {numOfRows,numOfColumns};
		size_t newStrides[] = {0,1};
		if(!transposed)
		{
			newStrides[0] = n+spareColumns;		// this is correct
		}
		else
		{
			newStrides[0] = m+spareRows;
		}

		const gslice oldMatrix( start, valarray<size_t>(oldLengths,2), valarray<size_t>(oldStrides,2) );
		const gslice newMatrix( start, valarray<size_t>(newLengths,2), valarray<size_t>(newStrides,2) );


		(*temp)[newMatrix] = valarray<T>((*vPtr)[oldMatrix]);	// I don't understand why the valarray<T> is necessary

		delete vPtr;
		vPtr = temp;


		if(!transposed)
		{
			maxRows = m + spareRows;
			maxColumns = n + spareColumns;
		}
		else
		{
			maxRows = n + spareColumns;
			maxColumns = m + spareRows;
		}

		//setMaxRows( getNumberOfRows() + spareRows );
		//setMaxColumns( getNumberOfColumns() + spareColumns );

		//setMaxRows( n + spareRows );
		//setMaxColumns( m + spareColumns );

}


template< typename T>
void matrix<T>::compact()
{
	spareRows = 0;
	spareColumns = 0;

	resizeValarray( getNumberOfRows(),getNumberOfColumns() );
}


template< typename T>
void matrix<T>::reserve(int extraRows, int extraColumns)
{
#if CHECK_SIZE
	if(extraRows<0)
    {
        throw invalid_argument("Number of reserved rows cannot be less than zero.");
    }

	if(extraColumns<0)
    {
        throw invalid_argument("Number of reserved columns cannot be less than zero.");
    }
#endif

	spareRows = extraRows;
	spareColumns = extraColumns;
	resizeValarray(getNumberOfRows(),getNumberOfColumns());

}

#pragma endregion


#pragma region access_functions

template< typename T>
T& matrix<T>::at( int index)
{
	return at(0,index);
}


template< typename T>
T& matrix<T>::at( int i, int j)
{
    if( (i<0) || ( i>=getNumberOfRows() ) )
    {
        throw out_of_range( "Index out of bounds" );
    }

	return row(i).at(j);
}


template< typename T>
slice_iter<T> matrix<T>::column( int index)
{
	if(!transposed)
	{
		return slice_iter<T>(vPtr,slice( (size_t) index, (size_t) numOfRows, (size_t) maxColumns) );
	}
	else
	{
		return slice_iter<T>(vPtr,slice( (size_t) (index*maxColumns), (size_t) numOfColumns, (size_t) 1) );
	}
}


template< typename T>
cslice_iter<T> matrix<T>::column( int index) const
{
	if(!transposed)
	{
		return cslice_iter<T>(vPtr,slice( (size_t) index, (size_t) numOfRows, (size_t) maxColumns) );
	}
	else
	{
		return cslice_iter<T>(vPtr,slice( (size_t) (index*maxColumns), (size_t) numOfColumns, (size_t) 1) );
	}
}


template< typename T>
slice_iter<T> matrix<T>::row( int index)
{
	if(!transposed)
	{
		return slice_iter<T>(vPtr,slice( (size_t) (index*maxColumns), (size_t) numOfColumns, (size_t) 1) );
	}
	else
	{
		return slice_iter<T>(vPtr,slice( (size_t) index, (size_t) numOfRows, (size_t) maxColumns) );
	}
}


template< typename T>
cslice_iter<T> matrix<T>::row( int index) const
{
	if(!transposed)
	{
		return cslice_iter<T>(vPtr,slice( (size_t) (index*maxColumns), (size_t) numOfColumns, (size_t) 1) );
	}
	else
	{
		return cslice_iter<T>(vPtr,slice( (size_t) index, (size_t) numOfRows, (size_t) maxColumns) );
	}
}


template< typename T>
matrix<T> matrix<T>::getSubmatrix( int startRow, int startColumn, int rows, int columns)
{
	matrix<T> subMatrix(rows, columns);

	size_t startSub = 0;
	size_t lengthsSub[] = {rows,columns};
	size_t stridesSub[] = {subMatrix.maxColumns,1};
	size_t start = 0;
	size_t lengths[] = {0,0};
	size_t strides[] = {0,0};

	if( !transposed )
	{
		start = startRow*maxColumns+startColumn;
		lengths[0] = rows;
		lengths[1] = columns;
		strides[0] = maxColumns;
		strides[1] = 1;
	}
	else
	{
		start = startColumn*maxColumns+startRow;
		lengths[0] = rows;
		lengths[1] = columns;
		strides[0] = 1;
		strides[1] = maxColumns;
	}


	const gslice subElements( startSub, valarray<size_t>(lengthsSub,2), valarray<size_t>(stridesSub,2) );
	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );

	// this should not need to be wrapped in a valarray
	( *(subMatrix.vPtr) )[subElements] = valarray<T>( (*vPtr )[currentElements] );

	return subMatrix;
}


#pragma endregion


#pragma region linear_algebra_functions

template< typename T>
matrix<T> &matrix<T>::toggleTransposed()
{
    setTransposed(!getTransposed());

	return *this;
}


template< typename T>
matrix<T> &matrix<T>::transpose()
{
    toggleTransposed();

	return *this;
}

template< typename T>
T matrix<T>::trace()
{
#if 0
	if(  numOfColumns != numOfRows )						// maybe they want to trace an augmented matrix
	{														// or one with multiple "b" arrays included
		throw invalid_argument("Non-square matrix");
	}
#endif

	size_t val = 0;
	cslice_iter<T> diag( vPtr,slice(val, (size_t) numOfRows, (size_t) (maxColumns+1) ) );
	cslice_iter<T> diagEnd = diag.end();
	T init = 0;

	for(; diag != diagEnd; ++diag )
	{
		init += *diag;
	}

	return init;
}

template< typename T>
void matrix<T>::ones( int m)
{
	transposed = false;
	resize(m,m);

	*vPtr = 0;

	size_t val = 0;
	(*vPtr)[slice(val, (size_t) m, (size_t) (maxColumns+1) ) ] = 1;

}


template< typename T>
void matrix<T>::zeros( int m)
{
	zeros(m,m);
}


template< typename T>
void matrix<T>::zeros ( int m, int n)
{
	transposed = false;
	resize(m,n);

	*vPtr = 0;
}


template< typename T>
bool matrix<T>::isSymmetric()
{
	matrix<T> temp = *this;

	return (*this == temp.transpose() );		// this is a very inefficient (lazy) way to test this
}


template< typename T>
matrix<T> matrix<T>::inverse( int *indexArray)
{
	T *inverseColumn;
	matrix<T> inverseMatrix(numOfRows,numOfRows,spareRows,spareColumns);
	matrix<T> tempMatrix(numOfRows,numOfRows,0,0);

	tempMatrix.ones(numOfRows);

	for(int i=0; i<numOfRows; i++)
	{
		inverseColumn = backSubstitution( indexArray,tempMatrix.getSubmatrix(0,i,numOfRows,1) );
		slice_iter<T> currentColumn = inverseMatrix.column(i);

		for(int j=0; j<numOfRows; j++)
		{
			currentColumn[j] = inverseColumn[j];
		}
	}

	return inverseMatrix;
}


template< typename T>
matrix<T> matrix<T>::inverse()
{
	matrix<T> temp = *this;

	int *indexArray = temp.gauss();


	T *inverseColumn;
	matrix<T> inverseMatrix(numOfRows,numOfRows,spareRows,spareColumns);
	matrix<T> tempMatrix(numOfRows,numOfRows,0,0);

	tempMatrix.ones(numOfRows);

	for(int i=0; i<numOfRows; i++)
	{
		inverseColumn = backSubstitution( indexArray,tempMatrix.getSubmatrix(0,i,numOfRows,1),temp );
		slice_iter<T> currentColumn = inverseMatrix.column(i);

		for(int j=0; j<numOfRows; j++)
		{
			currentColumn[j] = inverseColumn[j];
		}
	}

	return inverseMatrix;
}


template< typename T>
int *matrix<T>::gauss()			// this will likely have unexpected effects if floating point numbers are not used
{
	if( numOfRows > numOfColumns )
	{
		throw invalid_argument("Too many rows");
	}

	int *indexArray = new int[numOfRows];

	T *scaleArray = new T[numOfRows];

	// build scaleArray and indexArray
	for(int i=0; i<numOfRows; i++)
	{
		indexArray[i] = i;
		T scaleMax = 0;

		slice_iter<T> currentRow = row(i);

		for(int j=0; j<numOfColumns; j++)
		{
			scaleMax = max(scaleMax, abs( currentRow(j) ) );
		}
		scaleArray[i] = scaleMax;
	}

	for(int k=0; k<numOfColumns-1; k++)
	{
		T maxRatio = 0;
		T ratio;
		int j = k;

		slice_iter<T> currentColumn = column(k);

		// find the with the greatest ratio of element/scale
		for(int i=k; i<numOfRows; i++)
		{
			T ratio = abs( currentColumn( indexArray[i] ) /  scaleArray[ indexArray[1] ] );

			if(ratio > maxRatio)
			{
				maxRatio = ratio;
				j = i;
			}
		}

		// if we found a new maxRatio, swap elements on the indexArray
		if(j != k)
		{
			int temp = indexArray[j];
			indexArray[j] = indexArray[k];
			indexArray[k] = temp;
		}

		slice_iter<T> pivotRow = row( indexArray[k] );
		for(int i=k+1; i<numOfRows; i++)
		{
			slice_iter<T> currentColumn = column(k);
			T xmult = currentColumn[ indexArray[i] ] / currentColumn[ indexArray[k] ];
			currentColumn[ indexArray[i] ] = xmult;		// store the multiplier for later LU decomposition

			slice_iter<T> reduceRow = row( indexArray[i] );
			for(int j=k+1; j<numOfColumns; j++)
			{
				reduceRow[j] -= xmult*pivotRow[j];
			}
		}
	}

	delete [] scaleArray;
	scaleArray = 0;

	return indexArray;
}


template< typename T>
T* matrix<T>::backSubstitution( int *indexArray, matrix<T> &b)		// Using integer numbers will cause this to throw
																	// divide by zero exceptions
{
	T *temp = backSubstitution( indexArray, b, *this);

	return temp;
}


template< typename T>
T *matrix<T>::backSubstitution( int *indexArray, matrix<T> &b, matrix<T> &m)	// Ax=b
																				// Using integer numbers will cause this
																				// to throw divide by zero exceptions
{
	slice_iter<T> bColumn = b.column(0);

	// forward elimination phase for bColumn
	// this for loop repeats the forward elimination done on the matrix and applies it to the bColumn
	for(int k=0; k<m.numOfRows-1; ++k)
	{
		slice_iter<T> currentColumn = m.column( k );

		for(int i=k+1; i<m.numOfRows; ++i)
		{
			bColumn[ indexArray[i] ] -= currentColumn[ indexArray[i] ] * bColumn[ indexArray[k] ];
		}
	}

	// back substitution phase
	T *solution = new T[m.numOfRows];
	int n = m.numOfRows-1;
	solution[n]= bColumn[ indexArray[n] ]/m.row( indexArray[n] )[n];

	for( int i=m.numOfRows-1; i>=0; i--)
	{
		T sum = bColumn[ indexArray[i] ];
		slice_iter<T> currentColumn = m.row( indexArray[i] );

		for(int j=i+1; j<m.numOfRows; ++j)
		{
			sum -= currentColumn[j] * solution[j];
		}

		solution[i] = sum / currentColumn[i];
	}

	return solution;
}


template< typename T>
matrix<T> matrix<T>::lower( int *indexArray)
{
	matrix<T> temp(numOfRows,numOfColumns,spareRows,spareColumns);
	temp.setTransposed(transposed);

	for(int i=0; i<numOfRows; ++i)
	{
		slice_iter<T> currentRowNew = temp.row(i);
		slice_iter<T> currentRow = row( indexArray[i] );
		int size = currentRowNew.getSize() - i;

		int j;
		for(j=0; j<i; ++j)
		{
			currentRowNew[j]=currentRow[j];
		}

		currentRowNew[j] = 1;
	}

	return temp;
}


template< typename T>
matrix<T> matrix<T>::upper( int *indexArray )
{
	matrix<T> temp(numOfRows,numOfColumns,spareRows,spareColumns);
	temp.setTransposed(transposed);

	for(int i=0; i<numOfRows; ++i)
	{
		slice_iter<T> currentRowNew = temp.row(i);
		slice_iter<T> currentRow = row( indexArray[i] );
		int size = currentRowNew.getSize();

		for(int j=i; j<size; ++j)
		{
			currentRowNew[j]=currentRow[j];
		}
	}

	return temp;
}


template< typename T>
matrix<T> matrix<T>::lower()
{
	matrix<T> temp = *this;
	matrix<T> tempNew(numOfRows,numOfColumns,spareRows,spareColumns);
	tempNew.setTransposed(transposed);

	int *indexArray = temp.gauss();

	for(int i=0; i<numOfRows; ++i)
	{
		slice_iter<T> currentRowNew = tempNew.row(i);
		slice_iter<T> currentRow = temp.row( indexArray[i] );
		int size = currentRowNew.getSize() - i;

		int j;
		for(j=0; j<i; ++j)
		{
			currentRowNew[j]=currentRow[j];
		}

		currentRowNew[j] = 1;
	}

	return tempNew;
}


template< typename T>
matrix<T> matrix<T>::upper()
{
	matrix<T> temp = *this;
	matrix<T> tempNew(numOfRows,numOfColumns,spareRows,spareColumns);
	tempNew.setTransposed(transposed);

	int *indexArray = temp.gauss();

	for(int i=0; i<numOfRows; ++i)
	{
		slice_iter<T> currentRowNew = tempNew.row(i);
		slice_iter<T> currentRow = temp.row( indexArray[i] );
		int size = currentRowNew.getSize();

		for(int j=i; j<size; ++j)
		{
			currentRowNew[j]=currentRow[j];
		}
	}

	return tempNew;
}

template< typename T>
T matrix<T>::det()
{
	matrix<T> temp = *this;

	int *indexArray = temp.gauss();

	T determinant = 1;

	for(int i=0; i<temp.numOfRows; ++i)
	{
		int index = indexArray[i];
		determinant *= temp.at(index,i);
	}

	return determinant;
}


template< typename T>
T matrix<T>::det( int *indexArray )
{
	T determinant = 1;

	for(int i=0; i<numOfRows; ++i)
	{
		int index = indexArray[i];
		determinant *= at(index,i);
	}

	return determinant;
}


#pragma endregion


//Public Properties
#pragma region Public Properties

template< typename T>
int matrix<T>::rows() const
{
    return getNumberOfRows();
}


template< typename T>
int matrix<T>::columns() const
{
    return getNumberOfColumns();
}



template< typename T>
int matrix<T>::getNumberOfRows() const
{
	if (!transposed)
	{
		return numOfRows;
	}
	else
	{
		return numOfColumns;
	}
}


template< typename T>
matrix<T> &matrix<T>::setNumberOfRows( int m)
{
#if CHECK_SIZE
	if(m<1)
    {
        throw invalid_argument("Number of rows cannot be less than one.");
    }
#endif

	if (!transposed)
	{
		numOfRows = m;
	}
	else
	{
		numOfColumns = m;
	}

	return *this;
}


template< typename T>
int matrix<T>::getNumberOfColumns() const
{
	if (!transposed)
	{
		return numOfColumns;
	}
	else
	{
		return numOfRows;
	}
}


template< typename T>
matrix<T> &matrix<T>::setNumberOfColumns( int n)
{
#if CHECK_SIZE
    if(n<1)
    {
        throw invalid_argument("Number of columns cannot be less than one.");
    }
#endif

	if (!transposed)
	{
		numOfColumns = n;
	}
	else
	{
		numOfRows = n;
	}

	return *this;
}


template< typename T>
int matrix<T>::getMaxRows() const
{
	if (!transposed)
	{
		return maxRows;
	}
	else
	{
		return maxColumns;
	}
}


template< typename T>
matrix<T> &matrix<T>::setMaxRows( int m)
{
	if (!transposed)
	{
		maxRows = m;
	}
	else
	{
		maxColumns = m;
	}

	return *this;
}


template< typename T>
int matrix<T>::getMaxColumns() const
{
	if (!transposed)
	{
		return maxColumns;
	}
	else
	{
		return maxRows;
	}
}


template< typename T>
matrix<T> &matrix<T>::setMaxColumns( int n)
{
	if (!transposed)
	{
		maxColumns = n;
	}
	else
	{
		maxRows = n;
	}

	return *this;
}


template< typename T>
bool matrix<T>::getTransposed() const
{
    return transposed;
}


template< typename T>
matrix<T> &matrix<T>::setTransposed( bool t)
{
    transposed = t;

	return *this;
}


template< typename T>
valarray<T> matrix<T>::getValarray()
{
	valarray<T> temp( (size_t) numOfRows* (size_t) numOfColumns );

	size_t start = 0;
	size_t lengths[] = {0,0};
	size_t strides[] = {0,0};

	if(!transposed)
	{
		lengths[0] = numOfRows;
		lengths[1] = numOfColumns;
		strides[0] = maxColumns;
		strides[1] = 1;
	}
	else
	{
		lengths[0] = numOfColumns;
		lengths[1] = numOfRows;
		strides[0] = 1;
		strides[1] = maxColumns;
	}

	const gslice currentElements( start, valarray<size_t>(lengths,2), valarray<size_t>(strides,2) );


	temp = (*vPtr)[currentElements];

	return temp;
}


template< typename T>
T* matrix<T>::getArray()
{
	T *temp = new T[ numOfColumns*numOfRows ];

	int rows = getNumberOfRows();
	int columns = getNumberOfColumns();

	for(int i=0; i<rows; i++)
	{
		slice_iter<T> currentRow = row(i);

		for(int j=0; j<columns; j++)
		{
			temp[ i*columns+j ] = currentRow(j);
		}
	}

	return temp;
}


template< typename T>
vector<T> matrix<T>::getVector()
{
	vector<T> temp( numOfColumns*numOfRows );

	int rows = getNumberOfRows();
	int columns = getNumberOfColumns();

	for(int i=0; i<rows; i++)
	{
		cslice_iter<T> currentRow = row(i);

		for(int j=0; j<columns; j++)
		{
			temp[ i*columns+j ] = currentRow(j);
		}
	}

	return temp;
}


#pragma endregion //Public Properties


template< typename T>
ostream &operator<< ( ostream &output, const matrix<T> &m )
{
	for(int i = 0; i<m.getNumberOfRows(); i++)
	{
		cslice_iter<T> currentRow = m.row(i);
		size_t size = currentRow.getSize();

		for(int j = 0; j<size; j++)
		{
			//if(numOfRows == 1)
			//{
			//	output <<
			output << currentRow[j] << "\t";
		}

		output << "\n";
	}

	return output;
}


