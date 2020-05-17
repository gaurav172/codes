#include <bits/stdc++.h>
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp> 
// #include <ext/pb_ds/tree_policy.hpp> 
// using namespace __gnu_pbds;   
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
#define ll long long int
#define ld double
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define sz(a) (ll)(a.size())
struct node
{
	ll suff;
	ll len;
	ll num;
	ll next[26];
};
const ll M=1e5+5;
node tree[M];
int tot,suff;
string s;
void init_tree()
{
	tree[1].len=-1;
	tree[1].suff=1;
	tree[2].len=0;
	tree[2].suff=1;
	tot=2;
	suff=1;
}
bool add_letter(ll x)
{
	ll z=s[x]-'a';
	while(1)
	{
		ll ln=tree[suff].len;
		if(x-ln-1>=0 && s[x]==s[x-ln-1])
			break;
		suff=tree[suff].suff;
	}
	if(tree[suff].next[z])
	{
		suff=tree[suff].next[z];
		return 0;
	}
	tot++;
	ll curr=suff;
	tree[tot].len=tree[curr].len+2;
	tree[curr].next[z]=tot;
	if(tree[tot].len==1)
	{
		tree[tot].suff=2;
		suff=tot;
		return 1;
	}
	while(true)
	{
		curr=tree[curr].suff;
		ll ln=tree[curr].len;
		if(x-ln-1>=0 && s[x-ln-1]==s[x])
			break;
	}
	tree[tot].suff=tree[curr].next[z];
	suff=tot;
	return true;
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll test;
	cin>>test;
	for(ll tt=1;tt<=test;tt++)
	{
		for(ll i=0;i<M;i++)
		{
			for(ll j=0;j<26;j++)
				tree[i].next[j]=0;
		}
		init_tree();
		cin>>s;
		// ll ans=0;
		for(ll i=0;i<sz(s);i++)
		{
			add_letter(i);
		}
		cout<<"Case #"<<tt<<": "<<tot-2<<"\n";
	}
	return 0;
}