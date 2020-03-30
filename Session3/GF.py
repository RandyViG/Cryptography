
def calculateTable( n , r ):
    title = [ 0 ]
    table = [ ]
    polynomialsI = [ 11 , 19 , 37 , 67 , 131 , 283 ]
    module = polynomialsI[ n - 3 ]
    valuesArchived = [ ]
    for t in range( 1 , 2**n):
        title.append(t)
    table.append(title)
    for i in range( 1, 2**n ): 
        valuesArchived.append( calculateValues( i , n , module ) )
    for j in range( 1 , ( 2**n ) ):
        table.append( calculateRow( j,  valuesArchived , n ) )
    
    if r == 'h':
        table = hexadecimal( table )
    else:
        table = polynomial( table )
    
    return table

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


def calculateRow( val , rowValues , n ):
    row = [ val ]
    for i in range(1,2**n):
        decompose = [ ]
        for j in range(n):
            aux = rowValues[ val-1 ]
            if( i & 2**j ):
                decompose.append( aux[j] )
        xor = 0
        for a in range( len(decompose) ):
            xor = xor ^ decompose[a]
        row.append(xor)
    return row

def hexadecimal( table ):
    tableHexa = [ ]
    for t in table:
        row = [ ]
        for r in t:
            row.append( hex( r ) )
        tableHexa.append( row )
    return tableHexa

def polynomial( table ):
    tablePol = [ ]
    for t in table:
        row = [ ]
        for r in t:
            row.append( convert( r ) )
        tablePol.append( row )
    return tablePol

def convert( pol ):
    polynom = ''
    for i in range(7):
        if ( pol & 2**i ):
            if ( i == 0 ):
                cad = '1'
            else:
                cad = 'X^'+str(2**i)
            
            polynom =  cad + '+' + polynom  
    return polynom[:-1]