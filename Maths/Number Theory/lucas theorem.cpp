void convertBase( vector < ll > &V , ll x  , ll b )
{
    while( x > 0 )
    {
        V.push_back(x%b) ;
        x /= b ;
    }
}

ll fac[100005],invFac[100005] ;
ll lucas( ll n , ll m , ll p )
{
    fac[0] = 1 ;
    for( int i = 1 ; i < p ; i++ )fac[i] = i * fac[i-1] , fac[i] %= p ;
    for( int i = 1 ; i < p ; i++ )invFac[i] = invMod(fac[i] , p ) ;
    vector < ll > N , M ;
    convertBase(N,n,p);
    convertBase(M,m,p);
    int size = min( N.size() , M.size() ) ;
    ll ans = 1 ;
    for( int i = 0 ; i < size ; i++ )
    {
        if( N[i] < M[i] ) return 0 ;
        else
        {
            ans *= fac[N[i]] ;
            ans %= p ;
            ans *= invFac[M[i]] ;
            ans %= p ;
            ans *= invFac[N[i] - M[i] ] ;
            ans %= p ;
        }
    }
 
    return ans ;
}