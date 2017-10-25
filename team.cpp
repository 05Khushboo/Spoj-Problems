#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a,b,c,d=0;
	cin>>n;
	while(n--)
	{
		cin>>a>>b>>c;
		if(a+b+c>1)
			d++;
	}
	cout<<d;
	return 0;
}
