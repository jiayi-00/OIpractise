#include<bits/stdc++.h>
using namespace std;

int k,ans,d=0,a=1;

int main(){
	
	freopen("coin.in","r",stdin);
	freopen("coin.out","w",stdout);
	cin>>k;
	while(d<k){
		ans+=a*a;
		d+=a;
		a++;
	}
	ans-=(a-1)*(d-k);
	cout<<ans;
	
	return 0;
} 
