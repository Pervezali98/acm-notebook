//DIJKSTRA'S
#include <bits/stdc++.h>
#define MAXN 100000
#define INF 1000000000000000000
 
using namespace std;
typedef long long int ll;
 
int n,m;
int s;//source
vector<pair<int,ll> >grf[MAXN+7];
 
ll sd[MAXN+7];//distance array
bool vis[MAXN+7];
 
void djs()
{
    memset(vis,0,sizeof(vis));
    sd[s]=0;
    multiset<pair<ll,int> >ms;
    ms.insert(make_pair(0,s));
 
    while(!ms.empty())    {
        pair<ll,int>pr=*ms.begin();
        ms.erase(ms.begin());
        int now=pr.second;
        if(vis[now])    continue;
        vis[now]=1;
        for(int i=0;i<grf[now].size();i++)    {
            int e=grf[now][i].first;
            ll w=grf[now][i].second;
            if(sd[now]+w<sd[e])    {
                sd[e]=sd[now]+w;
                ms.insert(make_pair(sd[e],e));
            }
        }
    }
}