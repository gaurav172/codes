#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;   
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
#define ll int
#define ld double
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define sz(a) (ll)(a.size())
const ll M=1e5+5;
ll p[M][20],phi[M],LCP[M],PLCP[M],csum[M];
std::vector<ll> ct2[M];
std::vector<pair<ll,ll> > ct1[M];
std::vector<ll> SA;
string s;
void computSA()
{
    ll n=sz(s);
	for(ll i=0;i<n;i++)
    	p[i][0]=s[i]-'a'+1;
    for(ll j=1;j<20;j++)
    {
    	for(ll i=0;i<M;i++)
    	{
    		ct1[i].clear();
    		ct2[i].clear();
    	}
    	for(ll i=0;i<n;i++)
    	{
    		ll z=i+(1<<(j-1));
    		if(z>=n)
    			ct2[0].pb(i);
    		else
    			ct2[p[z][j-1]].pb(i);
    	}
    	for(ll i=0;i<M;i++)
    	{
    		for(ll k=0;k<sz(ct2[i]);k++)
    		{
    			ll z=ct2[i][k];
    			ct1[p[z][j-1]].pb(mp(z,i));
    		}
    	}
    	ll rk=0;
    	for(ll i=0;i<M;i++)
    	{
    		for(ll k=0;k<sz(ct1[i]);k++)
    		{
    			if(k)
    			{
    				if(ct1[i][k].ss!=ct1[i][k-1].ss)
    					rk++;
    			}
    			p[ct1[i][k].ff][j]=rk;
    		}
    		rk++;
    	}
	}	
	for(ll i=0;i<M;i++)
		for(ll k=0;k<sz(ct1[i]);k++)
			SA.pb(ct1[i][k].ff);
}
void computeLCP()
{
	ll n=sz(s);
  	phi[SA[0]]=-1;
	for(ll i=1;i<n;i++)
		phi[SA[i]]=SA[i-1];
	ll L=0;
	for(ll i=0;i<n;i++)
	{
    	if(phi[i]==-1)
    	{
    		PLCP[i]=0;
    		continue;
    	}
    	while(s[i+L]==s[phi[i]+L])
    		L++;
    	PLCP[i]=L;
    	L=max(L-1,(ll)0);
    }
    for(ll i=0;i<n;i++)
    	LCP[i]=PLCP[SA[i]]; // Longest common prefix between suffixes SA[i] and SA[i-1].
}
int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll type;
    cin>>type;
    if(type==1)
    {
        cout<<"abcabc\n";
        return 0;
    }
    cin>>s;
    ll n1=sz(s);
    // string str;
    // cin>>str;
    // ll n2=sz(str);
    // s=s+'0'+str;
    computSA();
    for(auto u:SA)
        cout<<u<<" ";
    cout<<"\n";
    return 0;
} 