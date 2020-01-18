#include <bits/stdc++.h>
#define MAXN 100000
#define LOGN 18
 
using namespace std;
typedef long long ll;
 
ll n;
vector<int>grf[MAXN+5];
int immpar[MAXN+5];
int par[MAXN+5][LOGN];
int ht[MAXN+5];
 
void dfs(int node,int prv,int h) {
    ht[node]=h;
 
    for(int i=0;i<grf[node].size();i++) {
        int now=grf[node][i];
        if(now==prv) {
            continue;
        }
        immpar[now]=node;
        dfs(now,node,h+1);
    }
 
}
void buildSparseforLCA(){
    for(int i=1;i<=n;i++) par[i][0]=immpar[i];
    for(int j=1;j<LOGN;j++){
        for(int i=1;i<=n; i++) {
            par[i][j]=par[par[i][j-1]][j-1];
        }
    }
}
int LCA(int u,int v) {
    if(ht[u]>ht[v]) {
        swap(u,v);
    }
    int d=ht[v]-ht[u];
    for(int i=0;i<LOGN;i++) {
        if(d&(1<<i)) {
            v=par[v][i];
        }
    }
    if(u==v) {
        return u;
    }
    for(int i=LOGN-1;i>=0;i--) {
        if(par[u][i]!=par[v][i]) {
            u=par[u][i];
            v=par[v][i];
        }
    }
    return par[u][0];
}