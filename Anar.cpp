#include<bits/stdc++.h>
using namespace std;
#define ll long long int
int main()
{
  string s; cin>>s;
  ll t = 0;
  while(s[0]!='-')
  {
    t++; cout<<t<<". ";
    stack<char> stck;
    ll open = 0,close=0;
    for(ll i = 0;i<s.size();i++)
    {
      if(!stck.empty()&&(stck.top()=='{')&&s[i]=='}')
      {
        stck.pop();
        open--;
      }
      else
      {
        stck.push(s[i]);
        if(s[i]=='}') close++;
        else open++;
      }
    }
    ll ans = open/2 + close/2 + open%2 + close%2;
    cout<<ans<<endl;
    cin>>s;
  }
  return 0;
}
