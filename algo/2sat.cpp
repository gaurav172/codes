#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;   
#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update> 
#define ld double
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define sz(a) (ll)(a.size())
const ll M=2e5+5;
std::vector<ll> ord;
std::vector<ll> vtr[M],vtr2[M],sw[M];
vector<pair<ll,ll> > edge;
bool vis[M];
ll comp[M],ans[M],val[M];
void dfs1(ll x)
{
	if(vis[x])
		return;
	vis[x]=1;
	for(auto u:vtr[x])
		dfs1(u);
	ord.pb(x);
	return;
}
void dfs2(ll x,ll c)
{
	if(comp[x])
		return;
	comp[x]=c;
	for(auto u:vtr2[x])
		dfs2(u,c);
	return;
}
void addEdges(ll z)
{
	for(auto pp:edge)
	{
		ll a=pp.ff,b=pp.ss;
		if(a>z)
		{
			vtr[a-z].pb(b);
			vtr2[b].pb(a-z);
		}
		else
		{
			vtr[a+z].pb(b);
			vtr2[b].pb(a+z);
		}
		if(b>z)
		{
			vtr[b-z].pb(a);
			vtr2[a].pb(b-z);
		}
		else
		{
			vtr[b+z].pb(a);
			vtr2[a].pb(b+z);
		}
	}
}
bool solve2Sat(ll n)
{
	addEdges(n/2);
	ord.clear();
	for(ll i=1;i<=n;i++)
	{
		vis[i]=0;
		comp[i]=0;
	}	
	for(ll i=1;i<=n;i++)
		dfs1(i);
	ll c=0;
	for(ll i=n-1;i>=0;i--)
	{
		if(comp[ord[i]])
			continue;
		c++;
		dfs2(ord[i],c);
	}
	for(ll i=1;i<=n/2;i++)
		ans[i]=0;
	for(ll i=1;i<=n/2;i++)
	{
		if(comp[i]==comp[i+n/2])
			return 0;
		if(comp[i]>comp[i+n/2])
			ans[i]=1;
	}
	return 1;
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	// if sat is(avb) add a,b as edge, if (av-b) add a,b+n/2 as edge, n=> no. of variables.
	return 0;
}