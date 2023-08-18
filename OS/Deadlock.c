#include <bits/stdc++.h>
using namespace std ;
int req [ 10 ][ 10 ] = {
{ 0 , 1 , 0 },
{ 2 , 0 , 0 },
{ 3 , 0 , 2 },
{ 2 , 1 , 1 },
{ 0 , 0 , 2 }};
int alloc [ 10 ][ 10 ] = {
{ 0 , 0 , 1 },
{ 3 , 2 , 0 },
{ 3 , 0 , 3 },
{ 2 , 1 , 1 },
{ 0 , 0 , 2 }};
int need [ 10 ][ 10 ];
bool finish [ 10 ];
int avail [ 10 ] = { 3 , 3 , 2 };
int dead [ 10 ];
int n = 5 , r = 3 ;
void display ()
{
cout << "Process \t Allocation \t\t Requested \t\t Available \t " ;
for ( int i = 0 ; i < n ; i ++)
{
cout << " \n P" << i + 1 << " \t " ;
for ( int j = 0 ; j < r ; j ++)

{
cout << alloc [ i ][ j ] << " " ;
}
cout << " \t\t " ;
for ( int j = 0 ; j < r ; j ++)
{
cout << req [ i ][ j ] << " " ;
}
cout << " \t " ;
if ( i == 0 )
{
for ( int j = 0 ; j < r ; j ++)
cout << avail [ j ] << " " ;
}
}
cout << endl;
}
void needMatrix ()
{
for ( int i = 0 ; i < n ; i ++)
{
for ( int j = 0 ; j < r ; j ++)
{
need [ i ][ j ] = req [ i ][ j ] - alloc [ i ][ j ];
}
}
}
void getDeadlock ()
{
int j = 0 ;
int flag = 0 ;
for ( int i = 0 ; i < n ; i ++)
{
if ( finish [ i ] == false )
{
dead [ j ] = i ;
j ++;
flag = 1 ;

}
}
if ( flag == 1 )
{
cout << " \n\n There is Deadlock " << endl;
cout << "Deadlock process are " << endl;
for ( int i = 0 ; i < n ; i ++)
{
cout << "P" << dead [ i ] + 1 << " \t " ;
}
}
else
{
cout << " \n There is No Deadlock" << endl;
}
}
void calc ()
{
int flag = 1 ;
while ( flag )
{
flag = 0 ;
for ( int i = 0 ; i < n ; i ++)
{
int c = 0 ;
for ( int j = 0 ; j < r ; j ++)
{
if (( finish [ i ] == false ) && ( need [ i ][ j ] <= avail [ j ]))
{
c ++;
if ( c == r )
{
for ( int k = 0 ; k < r ; k ++)
{
avail [ k ] += alloc [ i ][ j ];
finish [ i ] = true ;
flag = 1 ;
}
if ( finish [ i ] == true )

{
i = n ;
}
}
}
}
}
}
}
int main ()
{
cout << " ---------------------------------Deadlock Detection
Algorithm -------------------------------------" << endl;
display ();
for ( int i = 0 ; i < n ; i ++)
{
finish [ i ] = false ;
}
calc ();
needMatrix ();
getDeadlock ();
cout << " ---------------------------------Deadlock Detection
Algorithm -------------------------------------" << endl;
return 0 ;
}
