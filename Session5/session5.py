from Crypto.Util.number import isPrime

g = [ 11 , 5 , 2 , 3 , 3 ]
p = [ 1009 , 10007 , 100000000003 , 500000009 , 500000009 ]
r = [ 400 , 5225 , 1922556950 , 406870124 , 187776257 ]

print( '\nDiscrete logarithm\n' )

for i in range( len((g)) ):
    prev = g[i]
    for j in range(2, p[i]-1 ):
        res = ( g[i] * prev ) % p[i]
        if res == r[i]:
            print(' {} ^ {} % {} = {} '.format( g[i] , j , p[i] , r[i] ) )
            break
        prev = res

print( '\nPrime Factors\n' )

numbers = [ 100160063 , 10006200817 , 250035001189 , 250000009000000081 ]

d = 0
d1 = 0
for n in numbers:
    for i in range( n ):
        if isPrime( i ) == True:
            d = n / i
            if d % 2 == 1:
                d1 = i
                break
    if d != 0:
        print( ' {} * {} = {}'.format( d , d1 , n ) )

