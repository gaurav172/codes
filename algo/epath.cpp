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
map<ll,ll> H;
const ll M=2e5+5;
ll b[M],c[M],rm[M],vis[M];
multiset<ll> vtr[M];
std::vector<ll> ans;
void dfs(ll x)
{
	vis[x]=1;
	while(sz(vtr[x]))
	{
		auto it=vtr[x].begin();
		ll z=*it;
		vtr[x].erase(it);
		vtr[z].erase(vtr[z].find(x));
		dfs(z);
	}
	ans.pb(x);
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll n;
	cin>>n;
	for(ll i=1;i<n;i++)
	{
		cin>>b[i];
		H[b[i]];
	}
	for(ll i=1;i<n;i++)
	{
		cin>>c[i];
		H[c[i]];
	}
	ll curr=1;
	for(auto it=H.begin();it!=H.end();it++)
	{
		rm[curr]=it->ff;
		it->ss=curr++;
	}
	for(ll i=1;i<n;i++)
	{
		if(b[i]>c[i])
		{
			cout<<"-1\n";
			return 0;
		}
		vtr[H[b[i]]].insert(H[c[i]]);
		vtr[H[c[i]]].insert(H[b[i]]);
	}
	std::vector<ll> odd;
	for(ll i=1;i<curr;i++)
		if(sz(vtr[i])%2)
			odd.pb(i);
	if(sz(odd)>2)
	{
		cout<<"-1\n";
		return 0;
	}
	if(sz(odd)==0)
		odd.pb(1);
	dfs(odd[0]);
	for(ll i=1;i<curr;i++)
		if(!vis[i])
		{
			cout<<"-1\n";
			return 0;
		}
	for(auto it:ans)
		cout<<rm[it]<<" ";
	cout<<"\n";
	return 0;
}