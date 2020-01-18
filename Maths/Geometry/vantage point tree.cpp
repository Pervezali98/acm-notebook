#include <bits/stdc++.h>

using namespace std;

const int N = 1<<17;
const long long INF = 2000000000000000007;

struct vp_node {
    long long threshold;
    pair < int, int > center;
    vp_node *left, *right;
};

typedef vp_node *node_ptr;

int tests,n;
pair < int, int > pts[N],arr[N];
long long ans;
node_ptr root;

long long squared_distance(pair < int, int > a, pair < int, int > b) {
    return (a.first-b.first)*1ll*(a.first-b.first) + (a.second-b.second)*1ll*(a.second-b.second);
}

struct cmp_points {
    pair < int, int > a;
    cmp_points(){}
    cmp_points(pair < int, int > p): a(p) {}
    bool operator () (const pair < int, int > &x, const pair < int, int > &y) const {
        return squared_distance(a,x)<squared_distance(a,y);
    }
};

void build(node_ptr &node, int a, int b) {
    if(a>b) {
        node=NULL;
        return;
    }
    node=new vp_node();
    if(a==b) {
        node->threshold=0;
        node->center=arr[a];
        node->left=NULL;
        node->right=NULL;
        return;
    }
    int pos=a+rand()%(b-a+1);
    swap(arr[a],arr[pos]);
    node->center=arr[a];
    sort(arr+a+1,arr+b+1,cmp_points(arr[a]));
    node->threshold=squared_distance(arr[a],arr[(a+b)>>1]);
    build(node->left,a,(a+b)>>1);
    build(node->right,((a+b)>>1)+1,b);
}

void query(node_ptr &node, pair < int, int > q, long long &ans) {
    if(node==NULL) return;
    if(node->center!=q) ans=min(ans,squared_distance(node->center,q));
    if(node->left==NULL && node->right==NULL) {
        return;
    }
    if(squared_distance(q,node->center)<=node->threshold) {
        query(node->left,q,ans);
        if(sqrt(squared_distance(node->center,q))+sqrt(ans)>sqrt(node->threshold)) 
            query(node->right,q,ans);
    }
    else {
        query(node->right,q,ans);
        if(sqrt(squared_distance(node->center,q))-sqrt(ans)<sqrt(node->threshold)) 
            query(node->left,q,ans);
    }
}

int main() {
    int i;
    
    scanf("%d", &tests);
    while(tests--) {
        scanf("%d", &n);
        for(i=1;i<=n;i++) {
            scanf("%d %d", &arr[i].first, &arr[i].second);
            pts[i]=arr[i];
        }

        build(root,1,n);

        for(i=1;i<=n;i++) {
            ans=INF;
            query(root,pts[i],ans);
            printf("%lld\n", ans);
        }
    }

    return 0;
}
