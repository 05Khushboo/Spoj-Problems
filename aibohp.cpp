#include<bits/stdc++.h>
using namespace std;
#define ll long long int
int main()
{  
  ll t; cin>>t;
  while(t--)
  {
    string s,revs; cin>>s;
    revs = s;
    reverse(revs.begin(),revs.end());
    ll n = s.size();
    ll dp[n][n];
    for(ll i = 0;i<n;i++)
    {
      for(ll j = 0;j<n;j++)
      {
        if(i==0||j==0)
        {
          if(s[i]==revs[j]) dp[i][j] = 1;
          else dp[i][j] = 0;
        }
        else if(s[i]==revs[j]) dp[i][j] = 1+dp[i-1][j-1];
        else
        {
          dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
        }
      }
    }

    ll ans = n - dp[n-1][n-1];
    cout<<ans<<endl;
  }
  return 0;
}
