#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int ara[100005];
int tree[400005];

void buildTree(int node,int l,int r)
{
    if (l==r)    {tree[node]=ara[l];return;}
    int mid=(l+r)/2;
    buildTree(2*node,l,mid);
    buildTree(2*node+1,mid+1,r);
    tree[node]=tree[2*node]+tree[2*node+1];
}

int query(int node,int l,int r,int L,int R)
{
    if (L>r || R<l)    return 0;
    if (l>=L && r<=R)    return tree[node];
    int mid=(l+r)/2;
    int ql=query(2*node,l,mid,L,R);
    int qr=query(2*node+1,mid+1,r,L,R);
    return ql+qr;
}

void update(int node,int l,int r,int idx,int val)
{
    if (idx>r || idx<l) return;
    if (l==r)    {tree[node]=val;return;}
    int mid=(l+r)/2;
    update(2*node,l,mid,idx,val);
    update(2*node+1,mid+1,r,idx,val);
    tree[node]=tree[2*node]+tree[2*node+1];
}

//lazy propagation
int lazy[400005];
void lazyPropagation(int node,int l,int r)
{
    if(lazy[node])    {
        tree[node]+=(r-l+1)*lazy[node];
        if(l!=r)    {lazy[2*node]+=lazy[node];lazy[2*node+1]+=lazy[node];}
        lazy[node]=0;
    }
}

void updateRange(int node,int l,int r,int L,int R,int val)
{
    lazyPropagation(node,l,r);
    if(l>r)    return;
    else if(l>R || r<L)    return;
    if(l>=L && r<=R)    {lazy[node]+=val;lazyPropagation(node,l,r);return;}
    int mid=(l+r)/2;
    updateRange(2*node,l,mid,L,R,val);
    updateRange(2*node+1,mid+1,r,L,R,val);
    tree[node]=tree[2*node]+tree[2*node+1];
}

int queryRange(int node,int l,int r,int L,int R)
{
    if(l>r)    return 0;
    else if(l>R || r<L)    return 0;
    lazyPropagation(node,l,r);
    if(l>=L && r<=R)    return tree[node];
    int mid=(l+r)/2;
    int ql=queryRange(2*node,l,mid,L,R);
    int qr=queryRange(2*node+1,mid+1,r,L,R);
    return ql+qr;
}

int main()
{

    return 0;
}
