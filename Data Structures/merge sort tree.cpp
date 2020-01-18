//MERGERSORT-TREE
#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;
int n,ara[MAXN];
vector<int>tree[4*MAXN];
void buildTree(int cur=1,int l=1,int r=n)
{
     if(l==r)    {tree[cur].push_back(ara[l]);return ;}
     int mid=(l+r)/2;
     buildTree(2*cur,l,mid);
     buildTree(2*cur+1,mid+1,r);
     merge(tree[2*cur].begin(),tree[2*cur].end(),tree[2*cur+1].begin(),tree[2*cur+1].end(),back_inserter(tree[cur]));
}
int query(int cur,int l,int r,int L,int R,int k)
{
    if(r<L || l>R)    return 0;
    if(L>=l && R<=r)    return upper_bound(tree[cur].begin(),tree[cur].end(),k)-tree[cur].begin();
    int mid=(l+r)/2;
    return query(2*cur,l,mid,L,R,k)+query(2*cur+1,mid+1,r,L,R,k);
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)    cin>>ara[i];
    buildTree();
    int q;
    cin>>q;
    for(int i=0;i<q;i++)    {
        int l,r,k;
        cin>>l>>r>>k;
        cout<<query(1,1,n,l,r,k)<<endl;
    }
    return 0;
}
