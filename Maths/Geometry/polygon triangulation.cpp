/*
 * Algorithm : Polygon Triangulation
 * Complexity : O( N^2 );
 * Note : Prints out N-3 diagonals (as pairs of integer indices)
 *        which form a triangulation of Poly of counterclockwise order.
 */
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<vector>
using namespace std;
struct POINT{
    long x,y;
    bool Ear;
    long Next,Prev;
};
vector<POINT> Poly;
/* Returns TRUE iff (a,b) is a proper internal *or* external
diagonal of P, *ignoring edges incident to a and b*. */
bool Diagonalie( POINT a,POINT b ){
    long i;
    /* For each edge (c,c1) of P */
    for( i=0;i<Poly.size();i++ ){
        /* Skip edges incident to a or b */
        POINT c = Poly[i],c1 = Poly[(i+1)%Poly.size()];
        /*Intersect( a, b,c,d ) return TRUE iff segments ab and cd intersect, properly or improperly.*/
        if( (c!=a) and (c1!=a) and (c!=b) and (c1!=b) and Intersect( a,b,c,c1 )) return false;
    }
    return true;
}
/* Returns TRUE iff the diagonal (a,b) is strictly internal to the
polygon in the neighborhood of the a endpoint. */
bool InCone( POINT a,POINT b ){
   POINT a0,a1; /* a0,a,a1 are consecutive vertices. */
   a1 = Poly[a.Next];
   a0 = Poly[a.Prev];
   /* If a is a convex vertex ... */
   if( Area2( a,a1,a0 )>=0 ) return Area2( a,b,a0 )>0 and Area2( b,a,a1 )>0;
   /* Else a is reflex: */
   else return !( Area2( a,b,a1 )>=0 and Area2( b,a,a0 )>=0 );
}
/* Returns TRUE iff (a,b) is a proper internal diagonal.*/
bool Diagonal( POINT a,POINT b ){
   return InCone( a,b ) and InCone( b,a ) and Diagonalie( a,b );
}
void Triangulate( void ){
    long v0,v1,v2,v3,v4;/* Index of five consecutive vertices */
    long i,N = Poly.size();
    for( i=0;i<Poly.size();i++ ){
        Poly[i].Next = (i+1)%N;
        Poly[i].Prev = (i-1+N)%N;
        Poly[i].Ear = Diagonal( Poly[Poly[i].Next],Poly[Poly[i].Prev] );
    }
    /* Each step of outer loop removes one Ear. */
    long StartPoint = 0;
    while( N > 3 ){    
        /* Inner loop searches for an Ear. */
        v2 = StartPoint;
        do{
            if( Poly[v2].Ear ){
                /* Ear found. Fill variables. */
                v3 = Poly[v2].Next;v4 = Poly[v3].Next;
                v1 = Poly[v2].Prev;v0 = Poly[v1].Prev;
                /* (v1,v3) is a diagonal */
                Poly[v1].Ear = Diagonal( Poly[v0], Poly[v3] );
                Poly[v3].Ear = Diagonal( Poly[v1], Poly[v4] );
                /* Cut off the Ear v2 */
                Poly[v1].Next = v3;
                Poly[v3].Prev = v1;
                StartPoint = v3;
                N--;
                break;
            }/* end if Ear found */
            v2 = Poly[v2].Next;
        } while( v2 != StartPoint );
    }
}