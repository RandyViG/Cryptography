#include<iostream>
#include<string>
#include<fstream>
using  namespace std;
string readFile( void );

int lenMessage;
int * matchCharToIndex(string s,string alphabet);
string matchIndexToChar(int *encryptMessage, string alphabet);
int * memoryAllocation( int len );
string cleanString( string alphabet );
void writeF( string encryptVig);

int main( void ){
    string encryptText, decryptText,alphabet,posibleKey;
    int *key, *encrypt, *decrypt;
    cout << "Ingresa el nombre del texto crifrado: ";
    encryptText = readFile();
    cout << "Ingresa el nombre del texto decifrado: ";
    decryptText = readFile();
    cout << "Ingresa el nombre del alfabeto: ";
    alphabet = readFile();
    alphabet = cleanString(alphabet);
    lenMessage = encryptText.length();

    encrypt = matchCharToIndex(encryptText,alphabet);
    decrypt = matchCharToIndex(decryptText,alphabet);
    key = memoryAllocation(lenMessage);

    for (int i = 0; i < lenMessage; i++)
        key[i] = (encrypt[i]-decrypt[i] < 0) 
        ? (alphabet.length() - ( (decrypt[i]-encrypt[i])%alphabet.length()) ) 
        : (encrypt[i]-decrypt[i])% alphabet.length();

    posibleKey = matchIndexToChar(key,alphabet);

    writeF(posibleKey);



}

string readFile( void ){
    string nameFile;
    cin >> nameFile;
    ifstream file( nameFile.c_str() );
    string line;
    string message;
    if(file.fail())
        cerr << "Error, Can't open the file" << nameFile << endl;
    else
        while( !file.eof() ){
            getline(file, line);
            message += line;
        }
    file.close();

    return message;
}

void writeF( string encryptVig){
    ofstream file;
    file.open( "Posiblellave.txt" );
    file << encryptVig;
    file.close();
}

int * matchCharToIndex(string s,string alphabet){
    int *auxS = memoryAllocation( s.length() );
    for(int i = 0; i < s.length() ; i++)
        auxS[i]=  alphabet.find(s[i]);
    return auxS;
}

string matchIndexToChar(int *encryptMessage, string alphabet){
    string auxEncryptMessages;
    int position;
    for ( int i = 0; i < lenMessage ; i++ ){
        position = encryptMessage[i];
        auxEncryptMessages += alphabet[position];
    }
    return auxEncryptMessages;
}

string cleanString( string alphabet ){
    string auxAlphabet;
    for (int i =0; i < alphabet.size() ; i++)
        if ( alphabet[i] != 32)
            auxAlphabet += alphabet[i];

    return auxAlphabet;
}

int * memoryAllocation( int len ) {
	int *memory;
	memory = (int *)malloc(len*sizeof(int)  );
	if( memory == NULL )	{
		perror("Error, Can't reserve memory");
		exit(EXIT_FAILURE);
	}
	return memory;
}