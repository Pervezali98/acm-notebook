int Par[MAX];
 
int Find(int x)
{
    if (x==Par[x]) return x;
    return Par[x]=Find(Par[x]);
}
 
void Union(int x, int y)
{
    x=Find(x);
    y=Find(y);
    if(x!=y) Par[x]=y;
}


