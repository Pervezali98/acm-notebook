ll Mul(ll a,ll b,ll Mod){
    ll Ans=0;
    while(b){
        if(b&1) {Ans+=a; if(Ans>=Mod) Ans-=Mod;}
        a+=a; if(a>=Mod) a-=Mod;
        b>>=1;
    }
    return Ans;
}
 
ll bigMod(ll n,ll r,ll Mod){
    if(r==0) return 1LL;
    ll ret=bigMod(n,r/2,Mod);
    ret=Mul(ret,ret,Mod);
    if(r%2==1) ret=Mul(ret,n,Mod);
    return ret;
}
 
bool witness(ll wit,ll n){
  if(wit>=n) return false;
 
  int s=0; ll t=n-1;
  while(t%2==0) s++,t/=2;
 
  wit=bigMod(wit,t,n);
  if(wit==1 || wit==n-1) return false;
 
  for(int i=1;i<s;i++){
    wit=Mul(wit,wit,n);
    if(wit==1) return true;
    if(wit==n - 1) return false;
  }
  return true;
}
 
 
bool miller(ll n){
  if(n==2) return true;
  if(n%2==0 || n<2) return false;
  if(witness(2,n) || witness(7,n) || witness(61,n)) return false;
  return true;
}
 
 
ll rho(ll n,ll a) {
  auto f=[&](ll x) {return (Mul(x,x,n)+a)%n; };
  ll x=2,y=2;
  for(int i=1;;i++){
    x=f(x); y=f(f(y));
    ll d=__gcd(n,abs(x-y));
    if(d!=1) return d;
  }
  return n;
}
 
ll get_factor(ll n){
  if(n%2==0) return 2;
  if(n%3==0) return 3;
  if(n%5==0) return 5;
  while(true){
    ll a=2+rand()%100;
    ll d=rho(n,a);
    if(d!=n) return d;
  }
  return n;
}
 
ll findOneFactor(ll n) {   
    return get_factor(n);
}