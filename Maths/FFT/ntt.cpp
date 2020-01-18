int mod = 998244353, root = 15311432, inv = 469870224, pw = 1<<23;

struct NTT
{
    int N;
    vector<int> perm;

    int mod, root, inv, pw;

    NTT(int mod, int root, int inv, int pw) :
        mod(mod), root(root), inv(inv), pw(pw) {}

    void precalculate() {
        perm.resize(N);
        perm[0] = 0;

        for (int k=1; k<N; k<<=1) {
            for (int i=0; i<k; i++) {
                perm[i] <<= 1;
                perm[i+k] = 1 + perm[i];
            }
        }
    }

    int power(ll a,ll r){
        ll res=1;
        while(r){
            if(r&1) res=(res*a)%mod;
            a=(a*a)%mod;
            r>>=1;
        }
        return res%mod;
    }

    void fft(vector<int> &v, bool invert = false) {
        if (v.size() != perm.size()) {
            N = v.size();
            assert(N && (N&(N-1)) == 0);
            precalculate();
        }

        for (int i=0; i<N; i++)
            if (i < perm[i])
                swap(v[i], v[perm[i]]);

        for (int len = 2; len <= N; len <<= 1) {
            int factor = invert ? inv : root;
            for (int i = len; i < pw; i <<= 1)
                factor = (1LL * factor * factor) % mod;

            for (int i=0; i<N; i+=len) {
                int w = 1;
                for (int j=0; j<len/2; j++) {
                    int x = v[i+j], y = (1LL * w * v[i+j+len/2])%mod;
                    v[i+j] = (x+y)%mod;
                    v[i+j+len/2] = (x-y+mod)%mod;
                    w = (1LL * w * factor)%mod;
                }
            }
        }
        if (invert) {
            int n1 = power(N, mod-2);
            for (int &x : v) x=(1LL*x*n1)%mod;
        }
    }

    vector<int> multiply(vector<int>& a, vector<int>& b) {
        int n = 1;
        while (n < a.size()+ b.size())  n<<=1;
        a.resize(n);
        b.resize(n);

        fft(a);
        fft(b);
        for (int i=0; i<n; i++) a[i] = (1LL * a[i] * b[i])%mod;
        fft(a, true);
        while(a.size() && a.back() == 0) a.pop_back();
        return a;
    }
};