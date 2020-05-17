#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;   
#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update> 
#define ll long long int
#define ld double
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define sz(a) (ll)(a.size())
const ll M=1e5+3;
vector<ll> vtr[M];
ll cpt[M];
bool vis[M];
ll n;
ll sub[M];
void dfs(ll x,ll p)
{
    sub[x]=1;
    for(ll i=0;i<vtr[x].size();i++)
    {
        ll v=vtr[x][i];
        if(v!=p && !vis[v])
        {
            dfs(v,x);
            sub[x]+=sub[v];
        }
    }
}
ll findctr(ll x,ll par,ll elem)
{
    for(ll i=0;i<vtr[x].size();i++)
    {
        ll v=vtr[x][i];
        if(v!=par && !vis[v]) 
        {
            if(sub[v]>elem/2)
                return findctr(v,x,elem);
        }
    }
    return x;
}
void decompose(ll v,ll par)
{
    dfs(v,par);
    ll elem=sub[v];
    ll cent=findctr(v,par,elem);
    cpt[cent]=par;
    vis[cent]=1;
    for(ll i=0;i<vtr[cent].size();i++)
    {
        if(vtr[cent][i]!=par && !vis[vtr[cent][i]])
            decompose(vtr[cent][i],cent);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll i,u,v,m,x,y;
    cin>>n>>m;
    for(i=1;i<n;i++)
    {
        cin>>u>>v;
        vtr[u].pb(v);
        vtr[v].pb(u);
    }
    decompose(1,-1);
    y=1;
    x=1;
    //Iterating from node x to root of centroid tree O(LogN)
    for(ll i=1;i<=n;i++)
    {
        ll y=i;
        while(y!=-1)
        {
            cout<<y<<" ";
            y=cpt[y];
        }
        cout<<endl;
    }
}