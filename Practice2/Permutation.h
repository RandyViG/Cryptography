#ifndef __PERMUTATION_H__
#define __PERMUTATION_H__

#include<iostream>

using namespace std;

typedef struct Table{
    int origin,target;
    bool check=false;
} table;

int inversePermutation(table *, int,int*);
table* generatePermutation(int);
void displayTable(table *,int);
table * memoryAllocation(int);
string encrypt(table *,string,int);
string decrypt(table *,string,int);

#endif