#ifndef VIGENERE_H_
#define VUGENERE_H_

#include <iostream>
using namespace std;

static string keyVigenere;
static int lenKey, lenAlphabet,lenMessage;

int * generateKey(string,string);
int * encryptVigenere(int *,int  *);
int * decryptVigenere(int *,int *);
int  * matchCharToIndex(string,string);
string matchIndexToChar(int  *, string);
int  * memoryAllocation( int );
void setLength(string,string,string);

#endif