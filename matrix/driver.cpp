#include <ctime>

#include <cstdlib>
using std::rand;



#include <iostream>
using std::cout;
using std::endl;
using std::fixed;

#include <iomanip>
using std::setprecision;

#include <math.h>


#include "matrix.cpp"
#include "testDriver.h"

void testIt(void);
void demoIt(void);

int main(int argc, char *argv[])
{
	demoIt();
	//testDriver myTester;

 //   //int myInt[2][4] = {{1,2,3,4},{5,6,7,8}};
 //   //matrix<int> myMatrix(*myInt, 2,4);

 //   //cout<<myInt[0][0]<<myInt[1][0]<<myInt[1][2]<<myInt[0][3]<<endl;
 //   
	//srand(time(NULL));

	//int prec = cout.precision();
	////cout << setprecision(3);
	////cout << fixed;

	//int columns = 6;
	//int rows = 6;

 //   matrix<double> myMatrix(rows,columns,0,0);

	////int myArray[]= {0,1,2,3,4,5,6,7,8,9,11,12};
	////double myArray[]= {1,1,2,8,-1,-2,3,1,3,-7,4,10};
	////double myArray[]= {3,2,-1,-15,5,3,2,0,3,1,3,11,-6,-4,2,30};
	////double myArray[]= {2,2,2,0,-2,5,2,1,8,1,4,-1};

	////for(int i=0; i<rows*columns; i++)
	////{
	////	myArray[i] = i;
	////}

	////myMatrix.transpose();

	////myMatrix.initialize( myArray,rows,columns);

	////matrix<int> myMatrix2(columns, rows);
	////matrix<int> myMatrix3(rows,columns);

	////myMatrix.transpose();

	////cout << myMatrix << "\n\n";
	////cout << myMatrix.getSubmatrix(0,rows-1,rows,1) << endl;

	////cout << "myMatrix.at(2,3) = " << myMatrix.at(2,3) << "\n\n";
	////cout << "myMatrix.column(2) = " << myMatrix.column(2) << "\n";

 //   int i,j;
 //   for(i=0;i<rows;i++)
 //   {
 //       for(j=0;j<columns;j++)
 //       {
 //           //myMatrix[i][j]=2*(i*columns+j);
	//		myMatrix[i][j]=rand()*time(NULL);
	//		//myMatrix2[j][i] = i*columns+j;
 //       }
 //   }
	//
	//myMatrix.printmatrix();

	//myTester.testFunction(false,1);

	//myMatrix2.transpose();
	//cout << myMatrix << "\n\n";
    //system("Pause");

	//for(int i=0; i<1000; ++i)
	//{
	//	myMatrix *= myMatrix;
	//}
	//matrix<double> myMatrix4 = myMatrix.getSubmatrix(0,0,rows,columns-1);
	//cout << myMatrix4 << endl;
	//myMatrix4.compact();

	//cout << "myMatrix4.det() = " << myMatrix4.det() << endl;

	//int *index = myMatrix.gauss();
    //system("Pause");

	//cout << myMatrix << "\n\n";

	//matrix<double> answer = myMatrix.getSubmatrix(0,columns-1,rows,1);
	//answer.compact();

	//cout << myMatrix4.backSubstitution(index, answer) << "\n\n";

	//double *temp = myMatrix4.backSubstitution(index, answer);

	//for(int i=0; i<rows; ++i)
	//{
	//	cout << temp[i] << endl;
	//}

	//matrix<double> temp1 = myMatrix.getSubmatrix(0,0,rows,columns-1).inverse();

	//cout << temp1 << endl;

	//cout << myMatrix.getSubmatrix(0,0,rows,columns-1).lower() << "\n\n";
	//cout << myMatrix.getSubmatrix(0,0,rows,columns-1).upper() << "\n\n";
	//cout << myMatrix4.lower(index) << "\n\n";
	//cout << myMatrix4.upper(index) << "\n\n";

	//cout << "myMatrix4.upper(index).det() = " << myMatrix4.upper(index).det() << endl;
	//cout << "mymatrix4.gauss().det(index) = " << myMatrix4.det(index) << endl;

	//for(int i=0; i<rows; ++i)
	//{
	//	cout << index[i] << " ";
	//}

	//cout << endl;

	//delete [] temp;
	//delete [] index;

	//cout << myMatrix2 << "\n\n";

	//cout << (myMatrix2.isSymmetric() ) << endl;

	//myMatrix -= myMatrix2;

	//cout << (myMatrix/=5) << "\n\n";
	//int val = -1;
	//matrix<int> myMatrix3 =  val - myMatrix - val + myMatrix2;
	
	//myMatrix2.zeros(6,2);
	//cout << myMatrix3 << "\n\n";
	//cout << (myMatrix2.isSymmetric() ) << endl;

	//myMatrix.transpose();	
	//cout << myMatrix<<endl;

	//myMatrix.resize(4,2);
	//cout << myMatrix<<endl;

	//myMatrix.compact();

	//myMatrix.reserve(5,2);
	////myMatrix.transpose();	
	//myMatrix.resize(8,9);

	//cout << myMatrix<<endl;

	//cout<< myMatrix(3,1)<<endl;

	//for( int i = 0; i<4; i++)
	//{
	//	for( int j = 0; j<6; j++)
	//	{
	//		cout<< "myMatrix(" << i << "," << j << ")["<< i*myMatrix.getMaxColumns()+j << "] = " << myMatrix(i,j) << endl;
	//	}
	//}

	//myMatrix.transpose();

	//matrix<int> myMatrix2( myMatrix.transpose() );
	//matrix<int> myMatrix2 = myMatrix.transpose();

	//myMatrix.transpose();

	//myMatrix.at(3,2) = 99;


	//bool test = myMatrix==myMatrix2;


	//cout << test << endl;

    //myMatrix.printmatrix();

    //cout<<myMatrix.at(2)<<endl;

    //cout<<myMatrix.getNumberOfColumns()<<endl;
    //cout<<myMatrix.getNumberOfRows()<<endl;
    //cout<<myMatrix.getMaxColumns()<<endl;
    //cout<<myMatrix.getMaxRows()<<endl;
    //cout<<"transposed? "<<myMatrix.getTransposed()<<endl;
    //cout<<myMatrix.columns()<<endl;
    //cout<<myMatrix.rows()<<endl;
    //myMatrix.transpose();

    //cout<<"transposed? "<<myMatrix.getTransposed()<<endl;

	//myMatrix*myMatrix;

    //system("Pause");

	//cout << (myMatrix*myMatrix) <<endl;
    //cout << setprecision( prec );

#ifdef _WIN32
    system("Pause");
#endif 

    return 0;    

}

void testIt()
{
	testDriver myTester;
   
	srand(time(NULL));


	int columns = 6;
	int rows = 6;

    matrix<double> myMatrix(rows,columns,0,0);

	//int myArray[]= {0,1,2,3,4,5,6,7,8,9,11,12};
	//double myArray[]= {1,1,2,8,-1,-2,3,1,3,-7,4,10};
	//double myArray[]= {3,2,-1,-15,5,3,2,0,3,1,3,11,-6,-4,2,30};
	//double myArray[]= {2,2,2,0,-2,5,2,1,8,1,4,-1};

	//for(int i=0; i<rows*columns; i++)
	//{
	//	myArray[i] = i;
	//}

	//myMatrix.transpose();

	//myMatrix.initialize( myArray,rows,columns);

	//matrix<int> myMatrix2(columns, rows);
	//matrix<int> myMatrix3(rows,columns);

	//myMatrix.transpose();

	//cout << myMatrix << "\n\n";
	//cout << myMatrix.getSubmatrix(0,rows-1,rows,1) << endl;

	//cout << "myMatrix.at(2,3) = " << myMatrix.at(2,3) << "\n\n";
	//cout << "myMatrix.column(2) = " << myMatrix.column(2) << "\n";

    int i,j;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            //myMatrix[i][j]=2*(i*columns+j);
			myMatrix[i][j]=rand()*time(NULL);
			//myMatrix2[j][i] = i*columns+j;
        }
    }
	
	myMatrix.printmatrix();

	matrix<double> myMatrix2( myMatrix.rows(),myMatrix.columns() );

	myTester.testFunction( (myMatrix+myMatrix)==(myMatrix*2.0) );
	myTester.testFunction( (myMatrix+myMatrix)==(2.0*myMatrix) );
	myTester.testFunction( (myMatrix+2.0)==(2.0+myMatrix) );
	myTester.testFunction( (myMatrix-2.0)==(2.0-myMatrix) * -1.0);
	myTester.testFunction( (myMatrix/4.0)==(myMatrix*( 1 / 4.0) ) );
	myTester.testFunction( (myMatrix/=4.0)==(myMatrix*( 1 / 4.0) ) );
	myTester.testFunction( (myMatrix+=2.0)==(2.0+myMatrix) );
	myTester.testFunction( (myMatrix-=2.0)==(myMatrix-2.0) );
	myTester.testFunction( (myMatrix*=2.0)==(2.0*myMatrix) );
	myTester.testFunction( (myMatrix-=myMatrix)==(myMatrix*0.0) );
	myTester.testFunction( (myMatrix)!=(myMatrix+1.0) );

	myTester.testFunction( (myMatrix-myMatrix)==myMatrix2 );
	myTester.testFunction( ( (-1.0 * myMatrix ) +myMatrix)==(myMatrix2) );
	myTester.testFunction( ( (myMatrix * -1.0) +myMatrix)==(myMatrix2) );
	myTester.testFunction( ( 0.0 * myMatrix )==(myMatrix2) );
	myTester.testFunction( ( myMatrix * 0.0)==(myMatrix2) );
	myTester.testFunction( ( myMatrix * myMatrix2)==(myMatrix2) );
	myTester.testFunction( ( myMatrix2 * myMatrix )==(myMatrix2) );

	for(int i = 0; i<rows; ++i)
	{
		for(int j=0; j<columns; ++j)
		{
			myTester.testFunction( ( myMatrix(i)(j) )==( myMatrix[i][j] ) );
			myTester.testFunction( ( myMatrix[i](j) )==( myMatrix(i)[j] ) );
			myTester.testFunction( ( myMatrix(i)[j] )==( myMatrix[i](j) ) );
			myTester.testFunction( ( myMatrix[i][j] )==( myMatrix.at(i,j) ) );
		}
	}

	for(int i = 0; i<rows; ++i)
	{
		for(int j=0; j<columns; ++j)
		{
			myTester.testFunction( ( myMatrix(i)(j) )==( myMatrix.transpose()[j][i] ) );
		}
	}

	myTester.testFunction( !( myMatrix.getTransposed() ) );
	myTester.testFunction( myMatrix.getNumberOfColumns() == columns );
	myTester.testFunction( myMatrix.getNumberOfRows() == rows );
	myTester.testFunction( myMatrix.columns() == columns );
	myTester.testFunction( myMatrix.rows() == rows );

	matrix<double> myMatrix3 = myMatrix;
	matrix<double> myMatrix4(myMatrix);

	myTester.testFunction( myMatrix3 == myMatrix4 );

	myMatrix3.zeros(rows,columns);
	myTester.testFunction( (myMatrix3 )==(myMatrix4 * 0.0 ) );
	
	myMatrix4.ones(rows);
	myTester.testFunction( myMatrix4.trace() == rows );
	myTester.testFunction( myMatrix4.isSymmetric() );

	matrix<double> myMatrix5 = myMatrix;
	matrix<double> myMatrix6 = myMatrix;

	myMatrix5.resize(4,4);
	myTester.testFunction( (myMatrix5)==(myMatrix6.getSubmatrix(0,0,4,4)) );

	double rndm[] = {-0.828086926377683, 0.085874677068508, 0.066944444568689, -0.181170637654914, -0.274207851449750, 
		-0.172309870072814, -0.678717415685931, 0.458492117517613, -0.260156468687149, -0.354633449830035, 
		-0.465392215073789, 0.089972945905521, -0.933103236912369, -0.084541947312265, 0.126307086598186, 
		0.003733394042113, -0.705379280948205, -0.294587178873713, -0.926099243144299, -0.159022066872996, 
		0.187916732933510, 0.171851514476732, -0.657328361912591, -0.259264087434320, -1.225881594940523, 
		0.359557728946960, -0.100234758859479, -0.106335089222668, -0.644470150240571, 0.019825283323601, 
		-0.933589978016528, 0.276375886124461, -0.257755357013177, -0.380873103483522, -0.742062220062598, 
		-0.128842045992379 };

	double rndm2[] = {1.229772357330422, -0.154804164662110, -0.031467158705973, 0.183472596359431, 
		0.563553324964913, 0.194428521202726, 1.308546956334902, 0.087850046306290, -0.240759747867417, 
		-0.086329288838631, 0.622516456389300, 0.305965243165817, 1.848490754513613, -0.465205059587174, 
		0.122818049476833, 0.387352356244369, 0.876858837313768, 0.138970896906356, 1.588177547170108, 
		-0.503655702059763, 0.168116267388390, 0.423054832441051, 0.698454463644722, 0.065727964612943, 
		1.734640062914409, -0.141279127551738, -0.148761497342080, 0.136913364179089, 0.710041763296412, 
		0.285347577764460, 2.208717239796094, -0.173520245886489, -0.130938239316134, 0.132690758003461, 
		1.133394262908486, 0.362299940589228};

	matrix<double> myMatrix7(6,6,0,0);
	matrix<double> myMatrix8(6,6,0,0);
	myMatrix7.initialize(rndm,6,6)*=1000;
	myMatrix8.initialize(rndm2,6,6)*=1000000;
	matrix<double> myMatrix9 = myMatrix7*myMatrix7;

	for(int i=0;i<rows;++i)		//ignore rounding errors
	{	
		for(int j=0;j<columns;++j)
		{
			int mult = 10000000;		//truncate after 7 decimal places
			myMatrix9.at(i,j)*=mult;
			myMatrix8.at(i,j)*=mult;

			myMatrix9.at(i,j)=floor(myMatrix9.at(i,j));
			myMatrix8.at(i,j)=floor(myMatrix8.at(i,j));

			myMatrix9.at(i,j)/=mult;
			myMatrix8.at(i,j)/=mult;
		}
	}


	cout << myMatrix8 << "\n\n";
	cout << myMatrix9 << "\n\n";


	myTester.testFunction( (myMatrix9)==(myMatrix8) );

	//test gauss
	double answer[] = {-0.001730406085388, -0.021501659781341, 0.010002903150001, -0.017170967545145, 
		-0.006788030731001, 0.028726303389328};
	double bArray[] = {0.278498218867048, 0.546881519204984, 0.957506835434298, 0.964888535199277, 
		0.157613081677548, 0.970592781760616};
	matrix<double> B(6,1,0,0);
	B.initialize(bArray,6,1);
	matrix<double> A = myMatrix7;

	int *order = A.gauss();
	double *X = A.backSubstitution(order,B);

	matrix<double> Xmatrix(6,1,0,0);
	Xmatrix.initialize(X,6,1);

	delete [] X;
	X = 0;

	delete [] order;
	order = 0;

	cout << Xmatrix << endl;

	for(int i=0;i<rows;++i)		//ignore rounding errors
	{	
			int mult = 1000000000;		//truncate after 9 decimal places
			Xmatrix.at(i,0)*=mult;
			answer[i]*=mult;

			Xmatrix.at(i,0)=floor(Xmatrix.at(i,0));
			answer[i]=floor(answer[i]);

			Xmatrix.at(i,0)/=mult;
			answer[i]/=mult;
	}

	for(int i=0; i<rows; ++i)
	{
		myTester.testFunction( (Xmatrix.at(i,0))==(answer[i]) );
	}


}

void demoIt()
{
	cout << "Matrix class demo.\n\n";
	cout << "First, create a 6x6 matrix of ones and change a few values." << endl;

	matrix<double> demoMatrix(6,6);
	demoMatrix = 1.0;
	demoMatrix.at(2,3) = 5.6;
	demoMatrix(4)(1) = 8.4;
	demoMatrix(5,4) = 7.2;
	demoMatrix[1][0] = 3.5;
	cout << demoMatrix << "\n\n";

#ifdef _WIN32
    system("Pause");
#endif 

	cout << "\nNext add two to the matrix:\n";
	
	demoMatrix = 2.0 + demoMatrix;
	demoMatrix.printmatrix();
	cout << "\n\n";
	demoMatrix /=2.0;
	cout << "Then divide the matrix by 2.0\n";
	cout << demoMatrix << "\n\n";

#ifdef _WIN32
    system("Pause");
#endif 
	

	matrix<double> twosMatrix;
	cout << "\nCreate a new matrix with ones() function:\n";
	twosMatrix.ones(6);
	cout << twosMatrix << "\n\n";
	cout << "twosMatrix.trace(): " << twosMatrix.trace() << endl;
	demoMatrix *= (twosMatrix *= 2.0);
	cout << "twosMatrix *= 2.0:\n" << twosMatrix << "\n\n" << "demoMatrix *= twosMatrix\n" << demoMatrix << "\n\n";

#ifdef _WIN32
    system("Pause");
#endif 

	cout << "\nResize the demoMatrix to 7x9:\n";
	demoMatrix.resize(7,9);
	cout << demoMatrix << "\n\n";
	demoMatrix.transpose();
	cout << "Now transpose it:\n" << demoMatrix << endl << endl;

#ifdef _WIN32
    system("Pause");
#endif 

	int rows = demoMatrix.getNumberOfRows();
	int columns = demoMatrix.getNumberOfColumns();

	for(double i=0; i<rows; ++i)
	{
		for(double j=0; j<columns; ++j)
		{
			demoMatrix[i][j] = i*rows+j;
		}
	}
	
	cout << "\nLoad the demoMatrix with some new values:\n" << demoMatrix << "\n\n";
	matrix<double> bMatrix(6,1,0,0);
	bMatrix.initialize(	(demoMatrix.getSubmatrix(0,6,6,1)).getArray(),6	);

	cout << "Take the last non-zero 6x1 column for our bMatrix:\n" << bMatrix << "\n\n";
	demoMatrix = demoMatrix.getSubmatrix(0,0,6,6);
	cout << "Take a 6x6 submatrix:\n" << demoMatrix << "\n\n";


#ifdef _WIN32
    system("Pause");
#endif 

	cout << "\nNow transpose it and change a few values:\n";
	demoMatrix.transpose();
	demoMatrix.at(2,3) = 5.6;
	demoMatrix(4)(1) = 8.4;
	demoMatrix(5,4) = 7.2;
	demoMatrix[1][0] = 3.5;
	cout << demoMatrix << endl;

	cout << "\nNow perform Gaussian elimination with scaled partial pivoting:\n";
	int* order = demoMatrix.gauss();
	cout << demoMatrix <<"\n\n";
	cout << "order of rows:\n";
	for(int i=0;i<6;++i)
	{
		cout << order[i] << " ";
	}
	cout << "\n\n";

	cout << "upper:\n" << demoMatrix.upper(order) << "\n\n";
	cout << "lower:\n" << demoMatrix.lower(order) << "\n\n";

#ifdef _WIN32
    system("Pause");
#endif 
	
	double* Xarray = demoMatrix.backSubstitution(order, bMatrix, demoMatrix);
	cout << "\nSolution array:\n";
	for(int i=0;i<6;++i)
	{
		cout << Xarray[i] << "\n";
	}
	cout << "\n";

}


