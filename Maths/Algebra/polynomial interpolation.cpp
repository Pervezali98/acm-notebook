//O(N^2)

#include <bits/stdc++.h>
using namespace std;
#define ll long long int
const int maxn = 5005;
const int mod = 100019;

inline ll add(ll x, ll y) {x += y; return x >= mod ? x - mod : x;}
inline ll sub(ll x, ll y) {x -= y; return x < 0    ? x + mod : x;}
inline ll mul(ll x, ll y) {return (x * y) % mod;}
inline ll bigMod(ll x, ll y){
    ll res = 1;
    while(y){
        if(y & 1) res = mul(res, x);
        y >>= 1;  x = mul(x, x);
    }
    return res;
}
inline ll inv(ll n)       {return bigMod(n, mod-2);}
inline ll Div(ll a, ll b) {return mul(a, inv(b));}

struct Newton{
    ll dp[maxn][maxn];
    vector<ll> coX, coY;
    Newton() {coX.clear(); coY.clear();}

    void Insert(ll x, ll y){
        coX.push_back(x);
        coY.push_back(y);
        int v = coX.size() - 1;

        dp[v][v] = y;
        for(int u=v-1; u>=0; u--){
            dp[u][v] = sub(dp[u+1][v], dp[u][v-1]);
            dp[u][v] = Div(dp[u][v], sub(coX[v], coX[u]));
        }
    }

    ll Query(ll x){
        ll pre = 1;
        ll ans = 0;
        for(int i=0; i<coX.size(); i++){
            ans = add(ans, mul(pre, dp[0][i]));
            pre = mul(pre, sub(x, coX[i]));
        }
        return ans;
    }
};



typedef vector<double> vd;
vd lagrange(vd x, vd y, int n) {
	vd res(n,0), temp(n,0);
	for(int k=0;k<n;k++) for(int i=k+1;i<n;i++)
		y[i] = (y[i] - y[k]) / (x[i] - x[k]);
	double last = 0; temp[0] = 1;
	for(int k=0;k<n;k++) for(int i=0;i<n;i++) {
		res[i] += y[k] * temp[i];
		swap(last, temp[i]);
		temp[i] -= last * x[k];
	}
	return res;
}
