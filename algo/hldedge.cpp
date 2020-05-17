#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;   
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
typedef int ll;
#define ld double
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define sz(a) (ll)(a.size())
const ll M=2e5+5;
ll n;
vector<ll> vtr[M];
ll U[M],V[M],wt[M],sub[M],base[M],ed[M],epos[M],seg[4*M],anc[M][20],lvl[M];
ll chain=0,chainNo[M],pos[M],chainHead[M],ptr=1;
inline ll adj(ll x,ll e)
{
	if(U[e]==x)
		return V[e];
	return U[e];
}
inline void dfs(ll x,ll p=0,ll l=1)
{
	sub[x]=1;
	anc[x][0]=p;
	lvl[x]=l;
	for(ll i=0;i<sz(vtr[x]);i++)
	{
		ll e=vtr[x][i];
		ll u=adj(x,e);
		if(u!=p)
		{
			ed[u]=e;
			dfs(u,x,l+1);
			sub[x]+=sub[u];
		}
	}
}
inline void hld(ll x,ll p,ll cst)
{
	if(chainHead[chain]==0)
	{
		chainHead[chain]=x;
	}
	pos[x]=ptr;
	epos[ed[x]]=ptr;
	chainNo[x]=chain;
	base[ptr]=cst;
	ptr++;
	ll sc=0;
	for(ll i=0;i<vtr[x].size();i++)
	{
		ll e=vtr[x][i];
		ll u=adj(x,e);
		if(u!=p)
		{
			if(sub[u]>sub[sc])
				sc=u;
		}
	}
	if(sc)
	{
		hld(sc,x,wt[ed[sc]]);
	}
	for(ll i=0;i<vtr[x].size();i++)
	{
		ll e=vtr[x][i];
		ll u=adj(x,e);
		if(u!=p && u!=sc)
		{
			chain++;
			hld(u,x,wt[ed[u]]);
		}
	}
}
inline void build(ll i,ll s,ll e)
{
	if(s==e)
	{
		seg[i]=base[s];
		return;
	}
	ll m=(s+e)/2;
	build(2*i,s,m);
	build(2*i+1,m+1,e);
	seg[i]=seg[2*i];
	if(seg[2*i+1]>seg[i])
		seg[i]=seg[2*i+1];
}
inline ll query(ll i,ll s,ll e,ll l,ll r)
{
	if(s>r || l>e)
		return 0;
	if(s>=l && e<=r)
		return seg[i];
	ll m=(s+e)/2;
	ll a=query(2*i,s,m,l,r),b=query(2*i+1,m+1,e,l,r);
	if(a>b)
		return a;
	return b;
}
inline void pre()
{
	for(ll j=1;j<20;j++)
	{
		for(ll i=1;i<=n;i++)
			anc[i][j]=anc[anc[i][j-1]][j-1];
	}
}
inline void update(ll i,ll s,ll e,ll x,ll w)
{
	if(s==e)
	{
		seg[i]=w;
		return;
	}
	ll m=(s+e)/2;
	if(x<=m)
		update(2*i,s,m,x,w);
	else
		update(2*i+1,m+1,e,x,w);
	seg[i]=seg[2*i];
	if(seg[2*i+1]>seg[i])
		seg[i]=seg[2*i+1];
}
inline ll lca(ll u,ll v)
{
	if(lvl[u]<lvl[v])
		swap(u,v);
	for(ll i=19;i>=0;i--)
	{
		if(lvl[u]-(1<<i)>=lvl[v])
		{
			u=anc[u][i];
		}
	}
	if(u==v)
		return u;
	for(ll i=19;i>=0;i--)
	{
		ll p=anc[u][i];
		ll q=anc[v][i];
		if(p!=q && p && q)
		{
			u=p;
			v=q;
		}
	}
	return anc[u][0];
}
inline ll queryup(ll u,ll x)
{
	if(u==x)
		return 0;
	ll val=0;
	while(1)
	{
		if(chainNo[u]==chainNo[x])
		{
			if(u==x)
				break;
			ll t=query(1,1,ptr,pos[x]+1,pos[u]);
			if(t>val)
				val=t;
			break;
		}
		ll t=query(1,1,ptr,pos[chainHead[chainNo[u]]],pos[u]);
		if(t>val)
			val=t;
		u=anc[chainHead[chainNo[u]]][0];
	}
	return val;
}
inline ll ans(ll u,ll v)
{
	ll x=lca(u,v);
	ll a=queryup(u,x),b=queryup(v,x);
	if(a>b)
		return a;
	return b;
}
inline void init()
{
	ptr=1;
	chain=0;
	for(ll i=0;i<=n;i++)
	{
		chainHead[i]=0;
		vtr[i].clear();
		for(ll j=0;j<20;j++)
			anc[i][j]=0;
	}
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll i,j,test,p,l,r,w;
	string s;
	cin>>test;
	while(test--)
	{
		init();
		cin>>n;
		for(ll i=1;i<n;i++)
		{
			cin>>U[i]>>V[i]>>wt[i];
			vtr[U[i]].pb(i);vtr[V[i]].pb(i);
		}
		dfs(1);
		hld(1,0,0);
		ptr--;
		build(1,1,ptr);
		pre();
		while(1)
		{
			cin>>s;
			if(s[0]=='C')
			{
				cin>>p>>w;
				p=epos[p];
				update(1,1,ptr,p,w);
			}
			if(s[0]=='Q')
			{
				cin>>l>>r;
				cout<<ans(l,r)<<"\n";
			}
			if(s[0]=='D')
				break;
		}
	}
	return 0;
}