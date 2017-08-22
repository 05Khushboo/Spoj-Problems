#include<bits/stdc++.h>
using namespace std;
#define ll long long int
vector<ll> sp;
ll checkprime(ll n)
{
  if(n<=1) return 0;
  if(n>=2&&n<=3) return 1;
  for(ll i = 2;i<=sqrt(n);i++)
  {
    if(n%i==0) return 0;
  }
  return 1;
}
void prime()
{
  sp.push_back(2);
  for(ll i = 1;sp.size()<501;i++)
  {
    ll value = i*4 + 1;
    if(checkprime(value)) sp.push_back(value);
  }
//    cout<<sp.size()<<" ";
  //   for(auto k:sp) cout<<k<<" ";
}
ll pfun(ll n,ll k)
{
  if(k==1) return 1;
  ll ans = n/2;
  ans+=1;
  if(k==2) return ans;
  while(n>k)
  {
    n-=k;
    ans+=pfun(n,2);
  }
  if(n==k) ans++;
  return ans;
}
int main()
{
  prime();
  ll t; cin>>t;
  while(t--)
  {
    ll n,k; cin>>n>>k;
    n = sp[n-1];
//     cout<<n<<" ";
    cout<<pfun(n,k)<<endl;
  }
  return 0;
}
