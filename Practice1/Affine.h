#ifndef VIGENERE_H_
#define VUGENERE_H_

#include <iostream>
using namespace std;

static int lenAlphabetAffine, lenKeyAffine, lenMessageAffine;

int validateKey(int *);
int gcd(int,int);
int modInverse(int, int);
int euclideanAlgorithm(int,int,int *,int *);
int* generateKeyAffine(string,string);
int * encryptAffine(int *,int *);
int * decryptAffine(string, int *, int*,string);
string matchIndexToCharAffine(int *, string);
int * matchCharToIndexAffine(string s,string alphabet);
int * memoryAllocationAffine(int);

#endif