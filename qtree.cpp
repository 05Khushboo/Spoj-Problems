#include<bits/stdc++.h>
using namespace std;
#define ll long long int
vector<pair<ll,ll> > graph[10001],edge[10001];
ll nc[10001],parent[10001],height[10001],cost_tree[10001];
map<ll,ll> node_edge[10001],hl[10001],cost[10001];
ll ans;
void dfs(ll s,ll p,ll hght)
{
  ll mx = 0,idx=0,flag=0;
  height[s] = hght;
  nc[s] = 0;
  for(auto v:graph[s])
  {
    if(v.first==p) continue;
    flag = 1;
    parent[v.first] = s;
    dfs(v.first,s,hght+1);
    nc[s]+=(nc[v.first]+1);
    if(mx<=nc[v.first])
    {
      mx = nc[v.first];
      idx = v.first;
    }
  }
  if(flag) hl[s][idx] = hl[idx][s] = 1;
}
ll top[10001],indx[10001],flag;
vector<ll> tree_arr,chain;
void hld(ll s, ll p)
{  ll f = 0;
  for(auto v:graph[s])
  { 
    if(v.first==p) continue;
    hld(v.first,s);
    if(flag==0) chain.push_back(tree_arr.size()-1);
    flag = 1;
    f=1;
    if(hl[v.first][s]==1)
    {     
      tree_arr.push_back(v.first);
//       cout<<v.first<<" ";
      cost_tree[tree_arr.size()-1]=cost[s][v.first];
      indx[v.first] = tree_arr.size()-1;
      top[v.first] = v.first;
    }
  }
  if(f==0) flag = 0;
}
void set_top()
{ ll prev = 0;
  for(ll i=1;i<chain.size();i++)
  { 
    ll ik = chain[i];
    top[tree_arr[ik]] = tree_arr[ik];
    for(ll j = prev;j<=ik;j++)
    {
      top[tree_arr[j]] = tree_arr[ik];
    }
    prev = chain[i]+1;
  }
}
ll plca[10001][1001];
void build_lca(ll n)
{
  for(ll i=0;i<n;i++) 
    for(ll j=0;1<<j < n;j++) plca[i][j]=-1;
  for(ll i=0;i<n;i++) plca[i][0] = parent[i+1];
  for(ll j = 1;1<<j <n;j++)
    for(ll i =0;i<n;i++)
      if(plca[i][j-1]!=-1)
        plca[i][j]=plca[plca[i][j-1]][j-1];
}
ll lca(ll p,ll q)
{
  ll log;
  ll temp;
  if(height[p]<height[q]) temp = p,p=q,q=temp;
  for(log = 1;1<<log<=height[p];log++); log--;
  for(ll i = log;i>=0;i--)
    if(height[p]-(1<<i)>=height[q])
      p = plca[p-1][i];
  if(p==q) return p;
  for(ll i =log;i>=0;i--)
    if((plca[p-1][i]!=-1)&&(plca[p-1][i]!=plca[q-1][i]))
      p = plca[p-1][i],q=plca[q-1][i];
  return parent[p];
}
ll tree[10000001];
void build(ll k,ll st,ll en)
{
  if(st==en) 
  {
    tree[k] = cost_tree[st];
    return ;
  }
  ll mid =(st+en)/2;
  build(2*k+1,st,mid);
  build(2*k+2,mid+1,en);
  tree[k] = max(tree[2*k+1],tree[2*k+2]);
}
void seg_query(ll k,ll st, ll en,ll L,ll R)
{
  if(st==L&&en==R)
  {
    ans = max(ans,tree[k]);
    return;
  }
  ll mid = (st+en)/2;
  if(R<=mid) {  seg_query(2*k+1,st,mid,L,R); return;}
  else if(L>mid) { seg_query(2*k+2,mid+1,en,L,R); return;}
  else{
    seg_query(2*k+1,st,mid,L,mid);
    seg_query(2*k+2,mid+1,en,mid+1,R);
  }
}
void update(ll k,ll st,ll en,ll inx,ll value)
{
  if(st==en&&inx==st) 
  {
    tree[k] = value;
    return ;
  }
  ll mid = (st+en)/2;
  if(inx<st||inx>en||st>en) return;
  update(2*k+1,st,mid,inx,value);
  update(2*k+2,mid+1,en,inx,value);
  tree[k] = max(tree[2*k+1],tree[2*k+2]);
}
void query(ll x,ll y)
{ 
  while(1)
  {
    if(x==y) return;
    ll par = parent[x];
    if(hl[x][par]==0) // if edge is light  
    { 
//       cout<<x<<" "<<par<<" ";
      ans=max(ans,cost[x][par]);
//       cout<<cost[x][par]<<" "<<ans<<endl;;
      x = parent[x];
           continue;
    }
    else // if edge is heavy
    { 
      if(parent[top[x]]==y) // y is the top element of the chain
      {
//         cout<<parent[top[x]]<<" "<<x<<endl;
        seg_query(0,0,tree_arr.size()-1,indx[x],indx[top[x]]);
        x = y;
        return;
      }
      else if((top[x]==top[y])) // y and x are in the same chain
      { 
        seg_query(0,0,tree_arr.size()-1,indx[parent[x]],indx[y]);
        x = y;
        return;
      }
      else // y and x are not in the same chain
      {
        seg_query(0,0,tree_arr.size()-1,indx[x],indx[top[x]]);
        x = parent[top[x]];
      }
    }
  }
}
int main()
{
  ll t; scanf("%lld",&t);
  while(t--)
  {
    ll n; scanf("%lld",&n);
    for(ll i = 0;i<n-1;i++)
    {
      ll a,b,c; scanf("%lld %lld %lld",&a,&b,&c);
      node_edge[a][b] = i+1;
      node_edge[b][a] = i+1;
      hl[a][b] = 0;
      hl[b][a] = 0;
      cost[a][b] = cost[b][a] = c;
      edge[i+1].push_back(make_pair(a,b));
      graph[a].push_back(make_pair(b,c));
      graph[b].push_back(make_pair(a,c));
    }
    dfs(1,-1,0);
    parent[1] = -1;
//          top[1] = 1;
    hld(1,-1);
    chain.push_back(tree_arr.size()-1);
    set_top();
//     for(ll i=1;i<=5;i++) cout<<top[i]<<" ";
    build_lca(n);
    build(0,0,tree_arr.size()-1);
    for(ll i = 0;i<tree_arr.size();i++) cout<<tree[i]<<" ";
    char qry[101]; scanf("%s",qry);
    while(qry[0]!='D')
    { ll x,y;
      scanf("%lld %lld",&x,&y);
      if(qry[0]=='Q')
      { ll temp;
        if(height[y]>height[x]) temp= x,x=y,y=temp;
        ll lca_node = lca(x,y);
//         cout<<lca_node<<" ";
//         if(lca_node==y) query(x,y);
//         else
//         {
//           query(x,lca_node);
//           query(y,lca_node);
//         }
        printf("%lld\n",ans);
        ans = 0;
      }
      else
      {
        ll x1 = edge[x][0].first;
        ll y1 = edge[x][0].second;
       cost_tree[indx[x1]] = y;
       cost_tree[indx[y1]] = y;
       cost[x1][y1] = y;
       cost[y1][x1] = x;
       if(indx[x1]!=0) update(0,0,tree_arr.size()-1,indx[x1],y);
       if(indx[y1]!=0) update(0,0,tree_arr.size()-1,indx[y1],y);
      }
      scanf("%s",qry);
    }
    for(ll i =0;i<=n;i++) {
    graph[i].clear();
    edge[i].clear();
    hl[i].clear();
    cost[i].clear();
    node_edge[i].clear();
    top[i] = indx[i]= nc[i] = parent[i] = height[i] = cost_tree[i] = 0;
    }
    ans = 0;
    flag = 0;
    tree_arr.clear();
    chain.clear();
  }
  return 0;
}
