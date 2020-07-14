#include<iostream>
#include<string>
#include<time.h>
#include <bits/stdc++.h>
#include"Permutation.h"

using namespace std;

table * inversePermutation( table * t , int len, int *elements){
    table * auxT;
    auxT = memoryAllocation(len);
    int auxE[len];

    for (int i=0; i < len; i++)
        auxE[i] = elements[i];

    sort(auxE,auxE+len);

    for(int i = 0; i < len ; i++)
        for(int j = 0; j < len ; j++){
            if ( auxE[i] == t[j].target ){
                auxT[i].origin = t[j].target;
                auxT[i].target = t[j].origin;
                break;
            }
        }
    //displayTable(auxT,len);
    
    return auxT;
}

table * generatePermutation(int len){
    table *randomTable;
    int permutation;
    randomTable = memoryAllocation(len);
    for(int i=0 ; i< len ; i++)
        randomTable[i].origin = i+1;

    srand(time(NULL));
    for (int i=0 ; i< len ; i++ ){
        string n;
        do{
            permutation = rand()%len;
        }while( randomTable[permutation].check == true );
        randomTable[i].target = randomTable[permutation].origin;
        randomTable[permutation].check = true;   
    }
    
    displayTable(randomTable,len);
    return randomTable;
}

string encrypt(table *t, string message,int len){
    string auxMessaje,complete;
    int index,range=0,lim=0;
    char *aux;
    aux = (char *)malloc( message.size() * sizeof(char) );

    if ( message.size()%len != 0 ){
        for(int i=0; i<len-1; i++)
            complete += '*';
        message+=complete;
    }

    for (int i=0; i < message.size(); i++){
        if(lim < len){
            index = t[i%len].target;
            aux[(index-1)+range] = message[i];
            lim++;
        }else{
            lim = 0;
            range += len;
            index = t[i%len].target;
            aux[(index-1)+range] = message[i];
            lim++;
        }
    }
    for(int i=0; i<message.size();i++)
        auxMessaje+=aux[i];
    return auxMessaje;
}

string decrypt(table *t,string message ,int len){
    string auxMessaje,complete;
    int index,range=0,lim=0;;
    char *aux;
    aux = (char *)malloc(len*sizeof(char) );

    for (int i=0; i < message.size(); i++){
        if(lim < len){
            index = t[i%len].target;
            aux[(index-1)+range] = message[i];
            lim++;
        }else{
            lim = 0;
            range += len;
            index = t[i%len].target;
            aux[(index-1)+range] = message[i];
            lim++;
        }
    }
    for(int i=0; i<message.size();i++)
        auxMessaje+=aux[i];

    cout << "\n\tMessage: " << auxMessaje << endl;
    return auxMessaje;
}

void displayTable( table * t, int len){

    for(int i = 0; i < len ; i++)
        cout << "\t " << t[i].origin << " | ";
    cout << endl;

    for(int i = 0; i < len ; i++)
        cout << "\t " << t[i].target << " | ";
    cout << endl;
}

table * memoryAllocation( int len ) {
	table *memory;
	memory = (table *)malloc(len*sizeof(table)  );
	if( memory == NULL )	{
		perror("Error, Can't reserve memory");
		exit(EXIT_FAILURE);
	}
	return memory;
}