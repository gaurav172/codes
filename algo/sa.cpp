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
ll p[M][20];
void computSA(string s)
{
	ll n=sz(s);
	for(ll i=0;i<n;i++)
		p[i][0]=s[i]-'0';
	for(ll j=1;j<20;j++)
	{
		std::vector<pair<pair<ll,ll> ,ll > > v;	
		for(ll i=0;i<n;i++)
		{
			ll z=i+(1<<(j-1));
			if(z>=n)
				v.pb(mp(mp(p[i][j-1],-1),i));
			else
				v.pb(mp(mp(p[i][j-1],p[z][j-1]),i));
		}
		sort(all(v));
		p[v[0].ss][j]=0;
		for(ll i=1;i<n;i++)
		{
			if(v[i].ff==v[i-1].ff)
				p[v[i].ss][j]=p[v[i-1].ss][j];
			else
				p[v[i].ss][j]=i;
		}
	}	
	std::vector<pair<ll,ll> > SA;
	for(ll i=0;i<n;i++)
		SA.pb(mp(p[i][19],i));
	sort(all(SA));
	for(ll i=0;i<n;i++)
		cout<<SA[i].ss<<"\n";
	return;
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	string s;
	cin>>s;
	computSA(s);
	return 0;
}