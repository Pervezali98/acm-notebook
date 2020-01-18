#include <bits/stdc++.h>
#define MOD 1000000007
#define PI acos(-1.0)

using namespace std;
typedef long long ll;


typedef complex<double> base;
void fft (vector<base> & a, bool invert) {
    int n = (int) a.size();

    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }

    for (int len=2; len<=n; len<<=1) {
        double ang = 2*PI/len * (invert ? -1 : 1);
        base wlen (cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            base w (1);
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j],  v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (int i=0; i<n; ++i)
            a[i] /= n;
}

void multiply (const vector<ll> & a, const vector<ll> & b, vector<ll> & res) {
    vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);

    fft (fa, false),  fft (fb, false);
    for (size_t i=0; i<n; ++i)
        fa[i] *= fb[i];
    fft (fa, true);

    res.resize (n);
    for (size_t i=0; i<n; ++i)
        res[i] = ll (fa[i].real() + 0.5);
}


void multiplyModulo ( vector<ll> & a, vector<ll> & b, vector<ll> & res) {
    for(int i=0;i<a.size();i++)
    {
        a[i]%=MOD;
        if(a[i]<0)a[i]+=MOD;
    }
     for(int i=0;i<b.size();i++)
    {
        b[i]%=MOD;
        if(b[i]<0)b[i]+=MOD;
    }
    size_t n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;

    vector<base>a1(n),a2(n),b1(n),b2(n),a3(n),b3(n);

    a.resize(n);
    b.resize(n);
    ll x1=(((1LL<<10)-1)<<20), x2=(((1LL<<10)-1)<<10), x3=((1LL<<10)-1);

    for(int i=0;i<n;i++)
    {
        a1[i]=((a[i]&x1)>>20);
        a2[i]=((a[i]&x2)>>10);
        a3[i]=(a[i]&x3);
        b1[i]=((b[i]&x1)>>20);
        b2[i]=((b[i]&x2)>>10);
        b3[i]=(b[i]&x3);
    }

    fft (a1, false),  fft (a2, false);
    fft (b1, false),  fft (b2, false);
    fft (a3, false),  fft (b3, false);
    vector<base>c0(n),c1(n),c2(n),c3(n),c4(n);

    for(int i=0;i<n;i++)
    {
        c0[i]=a3[i]*b3[i];
        c1[i]=a2[i]*b3[i]+a3[i]*b2[i];
        c2[i]=a2[i]*b2[i]+a1[i]*b3[i]+a3[i]*b1[i];
        c3[i]=a1[i]*b2[i]+a2[i]*b1[i];
        c4[i]=a1[i]*b1[i];
    }
    fft (c0, true);
    fft (c1, true);
    fft (c2, true);
    fft (c3, true);
    fft (c4, true);

    res.resize (n);
    for (size_t i=0; i<n; ++i)
        res[i] =(((((ll)(c0[i].real()+0.5))%MOD)*((1)%MOD))%MOD
        +((((ll)(c1[i].real()+0.5))%MOD)*((1LL<<10)%MOD))%MOD
        +((((ll)(c2[i].real()+0.5))%MOD)*((1LL<<20)%MOD))%MOD
        +((((ll)(c3[i].real()+0.5))%MOD)*((1LL<<30)%MOD))%MOD
        +((((ll)(c4[i].real()+0.5))%MOD)*((1LL<<40)%MOD))%MOD)%MOD;
}
