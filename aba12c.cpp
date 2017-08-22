#include<bits/stdc++.h>
using namespace std;
#define ll long long int
int main()
{
  ll t; cin>>t;
  while(t--)
  {
    ll n,k; cin>>n>>k;
    ll arr[k+1],dp[k+1],val[k+1];
    for(ll i = 0;i<k;i++) cin>>arr[i];
    for(ll i = 0;i<=k;i++) dp[i] = 1E15,val[i] = i+1;
    for(ll i = 0;i<=k;i++)
    {
     if(i!=0&&arr[i-1]!=-1) dp[i] = arr[i-1];
      for(ll j=0;j<k;j++)
      { 
        if(((val[j]<=i)&&arr[j]!=-1)&&dp[i-val[j]]!=1E15)
        { 

          dp[i] = min(dp[i],dp[i-val[j]] + arr[j]);
        }
      }
    }
    if(dp[k]==1E15) dp[k] = -1;
    cout<<dp[k]<<endl;
  }
  return 0;
}
