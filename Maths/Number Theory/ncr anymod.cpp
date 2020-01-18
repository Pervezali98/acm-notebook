#include <bits/stdc++.h>
#define MAXN 2000000LL

using namespace std;
typedef long long ll;

bitset<MAXN+7>siv;
vector<ll>primes;
void Sieve()
{
    for(ll i=2;i<=MAXN;i++)    {
        if(!siv.test(i))    {
            primes.push_back(i);
            for(ll j=i+i;j<=MAXN;j+=i)    siv.set(j);
        }
    }
}

void PrimePowerFactorization(ll x,vector<pair<ll,ll> >&factors)
{
    if(x<=MAXN*MAXN)    {
        //Complexity O(Number of Primes Upto MAXN)
        for(int i=0;i<primes.size();i++)    {
            ll cnt=0;
            while(x%primes[i]==0)    {
                cnt++;
                x/=primes[i];
            }
            if(cnt!=0)    factors.push_back(make_pair(primes[i],cnt));
        }
        if(x!=1)    factors.push_back(make_pair(x,1));
    }
    else    {
        //Complexity O(Number of Primes Upto MAXN)
    }
}

//handles overflow while multiplicating
ll SafeMul(ll a,ll b,ll mod)
{
    a%=mod;b%=mod;
    bool sgn=0;
    if(b<0)    {sgn=1;b*=-1;}
    if(a<0)    {sgn^=1;a*=-1;}
    unsigned long long B=b;

    ll ans=0;
    while(B)    {
        if(B&(1ULL))    {
            ans+=a;
            if(ans>=mod)    ans-=mod;
        }
        a+=a;
        if(a>=mod)    a-=mod;
        B>>=(1ULL);
    }
    if(sgn && ans!=0)    {
        ans=mod-ans;
    }
    return ans;
}

ll BigMod(ll a,ll r,ll mod)
{
    if(r<0)    return 0;
    ll ret=1;
    unsigned long long k=r;
    while(k)    {
        if(k&(1ULL))    {
            ret*=a;
            ret%=mod;
            //ret=SafeMul(ret,a,mod);    //handles overflow
        }
        a=a*a;
        a=a%mod;
        //a=SafeMul(a,a,mod);
        k>>=(1ULL);
    }
    return ret;
}

ll Egcd(ll a,ll b,ll& x,ll& y)
{
    if(a==0)    {
        x=0;y=1;
        return b;
    }

    ll x1,y1;
    ll gcd=Egcd(b%a,a,x1,y1);

    x=y1-(b/a)*x1;
    y=x1;

    return gcd;
}

ll InvMod(ll a,ll mod)
{
    ll x,y;
    ll g=Egcd(a,mod,x,y);
    if(g!=1 && g!=-1)    {
        cout<<"Trying to find inverse of non co-prime pairs!"<<endl;
        return -1;
    }
    if(x<0)    {
        x+=mod;
        x%=mod;
    }
    return x;
}

//calculates invmod(i)%mod for all i upto lim in O(lim) where mod is a PRIME.
void genAllInvUptoPrime(ll lim,ll mod,ll* inv)
{
    inv[1]=1;
    for(ll i=2;i<=lim;++i)    {
        inv[i]=(mod-(mod/i)*inv[mod%i]%mod)%mod;
    }
}


//This is the weak form. Mods contains all ai,mi pairs such that
// x=ai mod mi, all mi are co-prime and product all mi<10^18.
// Complexity O(number of mods*log of their Product)
ll CRT(vector<pair<ll,ll> >&mods,ll Product)
{
    ll ret=0;
    for(int i=0;i<mods.size();i++)    {
        ll cur=mods[i].first;
        ll cof=Product/mods[i].second;
        ll invcof=InvMod(cof,mods[i].second);
        cur*=cof;cur%=Product;
        //cur=SafeMul(cur,cof,Product);    //handles overflow
        cur*=invcof;cur%=Product;
        //cur=SafeMul(cur,invcof,Product);
        ret+=cur;ret%=Product;
    }
    return ret;
}



//calculates N!(ignoring P's POWERS) % mod.Here mod=P^M(P is a Prime).
//O(mod) preprocessing and O(logP N) query using Gauss Generalization of Wilson's Theorem
//and also returns maximum power of P that divides N!.
//fact[i] holds i!(ignoring P's MULTIPLES) % mod for all i upto P^M-1
//helps in calculating NCR % MOD where MOD is small prime power. i.e. P<=10^6
pair<ll,ll> FactorialModPrimePowerIgnoringPrimeFactors(ll N,ll mod,ll P,ll M,ll* fact)
{
    ll ret1=1;
    ll ret2=0;
    while(N)    {
        ll res=N%mod;
        ret1*=fact[res];
        ret1%=mod;
        if(P!=2||M<3)    {
            if((N/mod)%2)    ret1*=-1;
        }
        N/=P;
        ret2+=N;
    }
    ret1=(ret1+mod)%mod;
    return make_pair(ret1,ret2);
}



//N<10^6 and mod is any PRIME. Complexity: O(N) preprocessing. O(1) query.
ll fact[MAXN+7];
ll inv[MAXN+7];
ll NCRforSmallNPrimeMod(ll N,ll R,ll mod)
{
    ll ret=fact[N];
    ret*=inv[fact[R]];ret%=mod;
    //ret=SafeMul(ret,inv[fact[R]],mod);    //handles overflow
    ret*=inv[fact[N-R]];ret%=mod;
    //ret=SafeMul(ret,inv[fact[N-R]],mod);
    return ret;
}
void PreprocessNCRforSmallNPrimeMod(ll lim,ll mod)
{
    fact[0]=1;
    for(ll i=1;i<=lim;i++)    {
        fact[i]=i*fact[i-1];fact[i]%=mod;
    }
    genAllInvUptoPrime(lim,mod,inv);
}



//N<10^18 and mod=P^R where P is a mod<10^6.
//Complexity: O(mod) preprocessing. O(logP N) query.
//factIgnoringP[i] holds i!(ignoring P's MULTIPLES) % mod for all i upto P^R-1

ll NCRforPrimePower(ll N,ll R,ll mod,ll P,ll M,ll* factIgnoringP)
{
    if(R>N)    return 0;

    ll up,down1,down2;
    ll primePowerFactor=0;
    ll ret;
    pair<ll,ll>tmp;


    tmp=FactorialModPrimePowerIgnoringPrimeFactors(N,mod,P,M,factIgnoringP);
    up=tmp.first;primePowerFactor+=tmp.second;

    tmp=FactorialModPrimePowerIgnoringPrimeFactors(R,mod,P,M,factIgnoringP);
    down1=InvMod(tmp.first,mod);primePowerFactor-=tmp.second;

    tmp=FactorialModPrimePowerIgnoringPrimeFactors(N-R,mod,P,M,factIgnoringP);
    down2=InvMod(tmp.first,mod);primePowerFactor-=tmp.second;

    if(primePowerFactor>=M)    return 0;

    ret=up;
    ret*=down1;ret%=mod;
    ret*=down2;ret%=mod;

    ll pFactor=1;
    for(ll i=1;i<=primePowerFactor;i++)    {
        pFactor*=P;
    }

    ret*=pFactor;ret%=mod;
    ret=(ret+mod)%mod;

    return ret;
}



//N<10^18 and mod is any INTEGER so that all of its prime divisors are <10^6.
//Complexity: O(MOD) preprocessing. O(log N) query.
vector<pair<ll,ll> >PFactors;
vector<ll>Pmods;
ll factIgnoringP[22][MAXN];
ll NCRforAnyMOD(ll N,ll R,ll mod)
{
    vector<pair<ll,ll> >crt;
    for(int i=0;i<PFactors.size();i++)    {
        ll m=Pmods[i];
        ll prm=PFactors[i].first;
        ll pwr=PFactors[i].second;
        ll a=NCRforPrimePower(N,R,m,prm,pwr,factIgnoringP[i]);
        crt.push_back(make_pair(a,m));
    }
    return CRT(crt,mod);

}
void preporcessNCRforAnyMOD(ll mod)
{
    PFactors.clear();Pmods.clear();
    PrimePowerFactorization(mod,PFactors);
    for(int i=0;i<PFactors.size();i++)    {
        ll prm=PFactors[i].first;
        ll pwr=PFactors[i].second;
        ll m=1;
        for(ll j=1;j<=pwr;j++)    m*=prm;
        Pmods.push_back(m);
        factIgnoringP[i][0]=1;
        for(ll j=1;j<m;j++)    {
            ll now=j;
            if(now%prm==0)    now=1;
            factIgnoringP[i][j]=(factIgnoringP[i][j-1]*now)%m;
        }
    }
}





int main()
{
    //freopen("testcases.txt","r",stdin);
    int t;
    cin>>t;
    Sieve();

    while(t--)    {
        ll N,R,M;
        cin>>N>>R>>M;
        preporcessNCRforAnyMOD(M);
        cout<<CRforAnyMOD(N,R,M)<<endl;
    }



    return 0;
}
