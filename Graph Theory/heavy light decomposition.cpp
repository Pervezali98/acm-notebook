int tree[300005];
int segtree_query(int node,int l,int r,int L,int R)
{
    if (L>r || R<l)    return 0;
    if (l>=L && r<=R)    return tree[node];
    int mid=(l+r)/2;
    int ql=segtree_query(2*node,l,mid,L,R);
    int qr=segtree_query(2*node+1,mid+1,r,L,R);
    return max(ql,qr);
}
void segtree_update(int node,int l,int r,int idx,int val)
{
    if (idx>r || idx<l) return;
    if (l==r)    {tree[node]=val;return;}
    int mid=(l+r)/2;
    segtree_update(2*node,l,mid,idx,val);
    segtree_update(2*node+1,mid+1,r,idx,val);
    tree[node]=max(tree[2*node],tree[2*node+1]);
}
vector<int> parent, depth, heavy, head, pos;
int cur_pos;
int dfs(int v, vector<vector<int> > const& adj) {
    int size = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c, adj);
            size += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
    }
    return size;
}
void decompose(int v, int h, vector<vector<int>> const& adj) {
    head[v] = h, pos[v] = cur_pos++;
    if (heavy[v] != -1)
        decompose(heavy[v], h, adj);
    for (int c : adj[v]) {
        if (c != parent[v] && c != heavy[v])
            decompose(c, c, adj);
    }
}
void init(vector<vector<int> > const& adj) {
    int n = adj.size();
    parent = vector<int>(n);
    depth = vector<int>(n);
    heavy = vector<int>(n, -1);
    head = vector<int>(n);
    pos = vector<int>(n);
    cur_pos = 1;
 
    dfs(0, adj);
    decompose(0, 0, adj);
}
int query(int a, int b) {
    int res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        int cur_heavy_path_max = segtree_query(1,1,cur_pos,pos[head[b]], pos[b]);
        res = max(res, cur_heavy_path_max);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    int last_heavy_path_max = segtree_query(1,1,cur_pos,pos[a], pos[b]);
    res = max(res, last_heavy_path_max);
    return res;
}
void update(int a,int val)    {
    segtree_update(1,1,cur_pos,pos[a],val);
}