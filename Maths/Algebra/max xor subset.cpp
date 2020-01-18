// Gaussian Elimination Online
struct maxxor{
    vector<ll> basis;
    void init() {basis.clear();}

    void add(ll x){
        // Keep the basis sorted in increasing order
        for(ll b : basis) x = min(x, x ^ b);
        for(ll &b : basis) b = min(b, x ^ b);

        if(x){
            basis.push_back(x);
            for(ll i = basis.size() - 1; i> 0 ; i--){
                if(basis[i] < basis[i - 1]) swap(basis[i], basis[i - 1]);
                else break;
            }
        }
    }

    //returns max subset xor
    ll getMax(){
        ll ans=0;
        for(ll b : basis) ans ^= b;
        return ans;
    }
}ds;
