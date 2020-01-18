#include <bits/stdc++.h>
#define MAXN 100005
 
using namespace std;
typedef long long ll;
 
string s;
int z[MAXN];
void Z_Algo()
{
    int L=0,R=0;
    z[0]=s.length();    // should be set to 0 if the problem demands only proper substrings.
    for(int i=1;i<s.length();i++)    {
        if(i>R)    {
            L=i;
            R=i;
            while(R<s.length() && s[R-L]==s[R])    R++;
            z[i]=R-L;
            R--;
        }
        else    {
            int k=i-L;
            if(z[k]<R-i+1)    z[i]=z[k];
            else    {
                L=i;
                while(R<s.length() && s[R-L]==s[R])    R++;
                z[i]=R-L;
                R--;
            }
        }
    }
}