#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
 
int n;
int A[300005];
int K[300005][25];

void buildSparseforMIN(){
    for(int i=1;i<=n;i++) K[i][0]=A[i];
    for(int j=1; (1<<j)<=n ;j++){
        for(int i=1; (i+ (1<<j)-1) <=n; i++)
            K[i][j]=min(K[i][j-1],K[i + (1<<(j-1))][j - 1]);
    }
}
int MIN(int i,int j){
    int k=log2(j-i+1);
    return min(K[i][k],K[j-(1<<k)+1][k]);
}
