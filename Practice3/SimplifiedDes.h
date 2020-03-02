#ifndef __SIMPLIFIEDDES_H__
#define __SIMPLIFIEDDES_H__

typedef struct Permutation{
    int origin,target;
} Permutation;

#include <iostream>
#include <cmath>
#include "SimplifiedDes.h"

using namespace std;

char encrypt( unsigned short int , char );
char decrypt( unsigned short int , char );
void generateSubKeys( unsigned short int , unsigned short int * , unsigned short int * );
unsigned short int round( unsigned short int message , unsigned short int );
void generateP10( Permutation *);
void generateP8( Permutation * );
void generateP4( Permutation * );
void generateIP( Permutation * );
void generateIPInverse( Permutation * );
void generateEP( Permutation * );
void generateEP2( Permutation * );
unsigned short int generateS( unsigned short int  );
unsigned short int generateKey1( unsigned short int , Permutation * );
unsigned short int generateKey2( unsigned short int , Permutation * );
unsigned short int makePermutation( unsigned short int , Permutation *  , short int );
unsigned char makeExpantion( unsigned short int  , Permutation * , short int );
Permutation * memoryAllocation( int );
void displayTable( Permutation * t, int len);

#endif