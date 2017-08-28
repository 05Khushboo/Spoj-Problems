#include<bits/stdc++.h>
using namespace std;
const int N = 1E4 + 1;
const int M = 101;
vector<int> chains[101],graph[N];
map<int,pair<int,int> > edgeno[N];
int etn[N],cost[N],ans = 0,arr[5*N],tree[5*N],sizearr,chainno;
int n,plca[N][14],dep[N],sub[N],parent[N],cno[N],chead[N],bpos[N];
void dfs(int s,int p,int hght)
{
  dep[s] = hght;
  sub[s] = 1;
  for(auto v:graph[s])
  {
    if(v==p) continue;
    parent[v] = s;
    int idx = edgeno[s][v].first;
    etn[idx] = v;
    cost[v] = edgeno[s][v].second;
    dfs(v,s,hght+1);
    sub[s]+=sub[v];
  }
}
void build_lca()
{
  for(int i=0;i<n;i++) 
    for(int j=0;1 << j < n;j++) plca[i][j]=-1;
  for(int i=0;i<n;i++) plca[i][0] = parent[i];
  for(int j = 1;1<<j <n;j++)
    for(int i =0;i<n;i++)
      if(plca[i][j-1]!=-1)
        plca[i][j]=plca[plca[i][j-1]][j-1];
}
int lca(int p,int q)
{
  int log;
  if(dep[p]<dep[q]) swap(p,q);
  for(log = 1;1<<log<=dep[p];log++); log--;
  for(int i = log;i>=0;i--)
    if(dep[p]-(1<<i)>=dep[q])
      p = plca[p][i];
  if(p==q) return p;
  for(int i =log;i>=0;i--)
    if((plca[p][i]!=-1)&&(plca[p][i]!=plca[q][i]))
      p = plca[p][i],q=plca[q][i];
  return parent[p];
}
void hld(int cur,int p)
{
  if(chead[chainno]==-1) chead[chainno] = cur;
  chains[chainno].push_back(cur);
  cno[cur] = chainno;
  int ind = -1,mx = -1;
  for(auto adj: graph[cur])
  {
    if((sub[adj]>mx)&&adj!=p)
    {
      mx = sub[adj];
      ind = adj;
    }
  }
  if((ind>=0)&&ind!=p)
    hld(ind,cur);
  for(auto adj:graph[cur])
  {
    if(adj==ind) continue;
    if(adj==p) continue;
    chainno++;
    hld(adj,cur);
  }
}
void buildarr()
{
  int idx = 0;
  for(int i = 0;i<M;i++)
  {
    for(auto k : chains[i])
    {
      arr[idx++] = k;
      bpos[k] = idx-1;
    }
  }
  sizearr = idx;
}
void buildtree(int k,int st,int en)
{
  if(st==en) tree[k] = cost[arr[st]];
  else
  {
    int mid = (st+en)/2;
    buildtree(2*k+1,st,mid);
    buildtree(2*k+2,mid+1,en);
    tree[k] = max(tree[2*k+1],tree[2*k+2]);
  }
}
void update(int k,int st,int en,int idx)
{
  if(st>en||idx>en||idx<st) return ;
  if(st==en) tree[k] = cost[arr[st]];
  else
  {
    int mid = (st+en)/2;
    update(2*k+1,st,mid,idx);
    update(2*k+2,mid+1,en,idx);
    tree[k] = max(tree[2*k+1],tree[2*k+2]);
  }
}
int query_tree(int k,int st,int en,int L,int R)
{
  if(st>en||L>en||R<st) return 0;
  if(st==L&&en==R) return tree[k];
  int mid = (st+en)/2;
  if(R<=mid) return query_tree(2*k+1,st,mid,L,R);
  if(L>mid) return query_tree(2*k+2,mid+1,en,L,R);
  return max(query_tree(2*k+1,st,mid,L,mid),query_tree(2*k+2,mid+1,en,mid+1,R));
}
int query_up(int a,int b)
{
  while(a!=b)
  {
    int cha = chead[cno[a]];
    int chb = chead[cno[b]];
    if(cha==chb)
    {
      int bpa = bpos[a];
      for(auto adj : graph[b])
      {
        if(adj==parent[b]) continue;
        int ch = chead[cno[adj]];
        if(ch==cha)
        {
          b = adj; break;
        }
      }
      int bpb = bpos[b];
      if(bpa<bpb) swap(bpa,bpb);
      int res = query_tree(0,0,sizearr,bpb,bpa);
      ans = max(ans,res);
      break;
    }
    else
    {
      int bpa = bpos[a];
      int bpb = bpos[chead[cno[a]]];
      if(bpa<bpb) swap(bpa,bpb);
      int res = query_tree(0,0,sizearr,bpb,bpa);
      ans = max(ans,res);
      a = parent[chead[cno[a]]];
    }
  }
  return ans;
}
int query(int u,int v)
{
  int lc = lca(u,v);
  return max(query_up(u,lc),query_up(v,lc));
}
int main()
{
  ios::sync_with_stdio(false);
    cin.tie(NULL);
  int t; 
  scanf("%d",&t);
  while(t--)
  {
    scanf("%d",&n);
    for(int j = 0;j<M;j++) chains[j].clear();
      for(int i = 0;i<=n;i++)
      {
        graph[i].clear();
        edgeno[i].clear();
        chead[i] = -1;
        etn[i] = cost[i] = dep[i] = sub[i] = 0;
        parent[i] = cno[i] = bpos[i] = 0;
      }
    for(int i = 0;i<(n-1);i++)
    {
      int a,b,c; 
      scanf("%d %d %d",&a,&b,&c);
      a--;b--;
      graph[a].push_back(b);
      graph[b].push_back(a);
      edgeno[a][b].first = i+1;
      edgeno[b][a].first = i+1;
      edgeno[a][b].second = c;
      edgeno[b][a].second = c;
    }
    parent[0] = -1;
    sizearr = chainno = 0;
    dfs(0,-1,0);
    cost[0] = -1E9;
    hld(0,-1);
    build_lca();
    buildarr();
    buildtree(0,0,sizearr);
    char qry[8];
    scanf("%s",qry);
    while(qry[0]!='D')
    {
      if(qry[0]=='Q')
      {
        int a,b; 
        scanf("%d %d",&a,&b);
        a--; b--;
        ans = -1E9;
        if(a==b) ans = 0;
        else ans = query(a,b);
        printf("%d\n",ans);
      }
      else
      {
        int idx,ti; 
        scanf("%d %d",&idx,&ti);
        int node = etn[idx];
        cost[node] = ti;
        update(0,0,sizearr,bpos[node]);
      }
      scanf("%s",qry);
    }
  }
  return 0;
}

