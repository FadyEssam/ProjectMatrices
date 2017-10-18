#include <iostream>
#include "Matrix.h"
using namespace std;

int main()
{
 Matrix a(3,3);

 // for(int i=0; i<3; i++)
 // 	for(int j=0; j<3; j++)
 // 		a[i][j]=rand()%21;
a[0][0] = -1;
a[0][1] = -2;
a[0][2] = 2;
a[1][0] = 2;
a[1][1] = 1;
a[1][2] = 1;
a[2][0] = 3;
a[2][1] = 4;
a[2][2] =6;


cout<<a;
cout<<a.inverse();
return 0;
}