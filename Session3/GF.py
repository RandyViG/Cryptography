
def calculateTable( n ):
    #polynomialsI = [ [3,1,0],[4,1,0],[5,2,0],[6,1,0],[7,1,0],[8,4,3,1,0] ]
    polynomialsI = [ 11 , 19 , 37 , 67 , 131 , 283 ]
    module = polynomialsI[ n - 3 ]
    valuesArchived = [ ]
    for i in range( 1, 2**n ): 
        valuesArchived.append( calculateValues( i , n , module ) )
    print(  valuesArchived )
    #for j in range( 1 , ( 2 ** n ) ):

    
    return


def calculateValues( i , n , module ):
    values = [ ]
    prev = i
    values.append( prev )
    for j in range( 2 , n+1 ):
        aux = prev << 1
        if ( prev & (2**(n-1)) ):
            aux = ( aux ^ module ) & (2**n-1)
        prev = aux
        values.append( aux )
    return values
