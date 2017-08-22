#include<bits/stdc++.h>
using namespace std;
#define ll long long int
int main()
{
  ll n;
  cin>>n;
  ll d[2][2];
  d[0][0] = d[0][1] = 1;
  for(ll i = 2;i<=n;i++)
  {
    d[1][1] = d[0][0] + d[0][1];
    d[1][0] = d[0][1];
    d[0][0] = d[1][0];
    d[0][1] = d[1][1];
  }
  ll sum = d[0][0] + d[0][1];
  cout<<sum;
  return 0;
}
