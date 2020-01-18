#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX 100
 
using namespace std;
typedef long long ll;

ll BigMod(ll a,ll r,ll Mod) {
    ll ret=1;
    while(r)    {
        if(r&1)    {
            ret=ret*a;ret=ret%Mod;
        }
        a=a*a;a=a%Mod;
        r>>=1;
    }
    return ret;
}


ll InverseMod(ll a,ll Mod)
{
    return BigMod(a,Mod-2,Mod);
}

ll Mul(ll x,ll y) {
    return (x*y)%MOD;
}

ll Div(ll x,ll y) {
    return (x*InverseMod(y, MOD))%MOD;
}

//1-based
struct Matrix{
    int row, col;
    ll m[MAX][MAX];
    Matrix() {memset(m,0,sizeof(m));}
    void Set(int r,int c) {row = r; col = c;}
    Matrix(int r,int c) {memset(m,0,sizeof(m)); Set(r,c);}
    void normalize(){
        for(int i=1; i<=row; i++){
            for(int j=1; j<=col; j++){
                m[i][j] %= MOD;
                if(m[i][j] < 0) m[i][j] += MOD;
            }
        }
    }
};

ll Det(Matrix mat){
    assert(mat.row == mat.col);
    int n = mat.row;
    mat.normalize();

    ll ret = 1;
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            while(mat.m[j][i]){
                ll t = Div(mat.m[i][i], mat.m[j][i]);
                for(int k = i; k <= n; ++k){
                    mat.m[i][k] -= Mul(mat.m[j][k] , t);
                    if(mat.m[i][k] < 0) mat.m[i][k] += MOD;
                    swap(mat.m[j][k], mat.m[i][k]);
                }
                ret = MOD - ret;
            }
        }

        if(mat.m[i][i] == 0) return 0;
        ret = Mul(ret, mat.m[i][i]);
    }

    if(ret < 0) ret += MOD;
    return ret;
}

ll Tmp[MAX<<1][MAX<<1];
Matrix Inverse(Matrix mat){
    assert(mat.row == mat.col);
    assert(Det(mat) != 0);

    int n = mat.row;
    mat.normalize();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) Tmp[i][j] = mat.m[i][j];
        for(int j=n+1; j<=2*n; j++) Tmp[i][j] = 0;
        Tmp[i][i+n] = 1;
    }

    for(int i=1; i<=n; i++){
        assert(Tmp[i][i] != 0);

        for(int j=1; j<=n; j++){
            if(i == j) continue;
            ll c = Div(Tmp[j][i], Tmp[i][i]);
            for(int k=i; k<=2*n; k++){
                Tmp[j][k] = Tmp[j][k] - Mul(Tmp[i][k], c);
                if(Tmp[j][k] < 0) Tmp[j][k] += MOD;
            }
        }
    }

    Matrix Inv(n,n);
    for(int i=1; i<=n; i++){
        for(int j = 1; j <= n; j++){
            Inv.m[i][j] = Div(Tmp[i][j+n], Tmp[i][i]);
        }
    }
    return Inv;
}