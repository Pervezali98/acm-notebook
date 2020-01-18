//SCC-TARJAN [Everything is 1 based here]
#include <bits/stdc++.h>
#define MAX 100000
using namespace std;
int n,m;
int sccidCount;//# of SCCs
vector<int>grf[MAX+7];//Input Graph
vector<int>scc[MAX+7];//Contains Same SCCs together under their 1-based indexed sccid
int sccid[MAX+7];//Maps a node to its SSC
bool visit[MAX+7],instk[MAX+7];
int ind[MAX+7],low[MAX+7],leb;
stack<int>stk;
void TarjanDfs(int u)
{
    leb++;
    visit[u]=true;
    instk[u]=true;
    ind[u]=leb;
    low[u]=leb;
    stk.push(u);
 
    for(int i=0;i<grf[u].size();i++)    {
        int v=grf[u][i];
        if( !visit[v] )    {
            TarjanDfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instk[v])    {
            low[u]=min(low[u],ind[v]);
        }
    }
    if(low[u]!=ind[u])    return;
    //Found new SCC
    sccidCount++;
    while(stk.top()!=u)    {
        int v=stk.top();
        stk.pop();
        instk[v]=false;
        sccid[v]=sccidCount;
        scc[sccidCount].push_back(v);
    }
    stk.pop();
    instk[u]=false;
    sccid[u]=sccidCount;
    scc[sccidCount].push_back(u);
}
void Tarjan()
{
    memset(visit,0,sizeof(visit));
    memset(instk,0,sizeof(instk));
    memset(ind,0,sizeof(ind));
    memset(low,0,sizeof(low));
    memset(sccid,0,sizeof(sccid));
    for(int i=1;i<=n;i++)    scc[i].clear();
    sccidCount=0;
    leb=0;
    for(int i=1;i<=n;i++){
        if(visit[i]) continue;
        TarjanDfs(i);
    }
}
//Example dfs on SCC
bool vis[MAX+7];
void dfs(int sccNode)
{
    if(vis[sccNode])    return;
    vis[sccNode]=1;
    for(int i=0;i<scc[sccNode].size();i++)    {
        for(int j=0;j<grf[scc[sccNode][i]].size();j++)    {
            int now=grf[scc[sccNode][i]][j];
            if(sccid[now]!=sccNode)    {
                dfs(sccid[now]);
            }
        }
    }
}