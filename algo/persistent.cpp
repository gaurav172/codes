#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;   
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
#define ll long long int
#define ld double
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define sz(a) (ll)(a.size())
const ll M=1e5+5,LOGM=20;
ll seg[M*LOGM],lt[M*LOGM],rt[M*LOGM];
ll a[M],root[M],rm[M],node;
map<ll,ll> m;
ll update(ll i,ll s,ll e,ll x)
{
	if(s==e)
	{
		node++;
		seg[node]=seg[i]+1;
		return node;		
	}
	node++;
	ll curr=node;
	lt[curr]=lt[i];
	rt[curr]=rt[i];
	ll m=(s+e)/2;
	if(x<=m)
		lt[curr]=update(lt[i],s,m,x);
	else
		rt[curr]=update(rt[i],m+1,e,x);
	seg[curr]=seg[lt[curr]]+seg[rt[curr]];
	return curr;		
}
ll query(ll x,ll y,ll s,ll e,ll k)
{
	ll m=(s+e)/2;
	if(s==e)
		return s;
	if(seg[lt[y]]-seg[lt[x]]>=k)
		return query(lt[x],lt[y],s,m,k);
	return query(rt[x],rt[y],m+1,e,k-seg[lt[y]]+seg[lt[x]]);
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll n,q;
	cin>>n>>q;
	for(ll i=1;i<=n;i++)
	{
		cin>>a[i];
		m[a[i]];
	}
	ll ln=1;
	for(auto it=m.begin();it!=m.end();it++)
	{
		rm[ln]=it->ff;
		it->ss=ln++;
	}
	ln--;
	for(ll i=1;i<=n;i++)
	{
		root[i]=update(root[i-1],1,ln,m[a[i]]);
	}
	while(q--)
	{
		ll i,j,k;
		cin>>i>>j>>k;
		cout<<rm[query(root[i-1],root[j],1,ln,k)]<<"\n";
	}
	return 0;
}