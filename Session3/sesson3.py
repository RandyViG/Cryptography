from GF import *

def  menu():
    print('\t\t************* Finete Fields *************')
    print('\t\t1. GF(2^n) Multuplication Table')
    print('\t\t2. Key schedule AES 128')
    print('\t\t3. Key schedule AES 192')
    print('\t\t4. Exit')
    option = int( input("\t\tChoose a option: " ) )
    return option

if __name__ == "__main__":
    while(True):
        option = menu()
        if option == 1:
            n = int( input("\t\tEnter the n for GF in a range of 3 to 8: ") )
            calculateTable( n )

        elif option == 2:
            pass
        elif option == 3:
            pass
        else:
            break
    