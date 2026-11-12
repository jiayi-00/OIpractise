#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=666623333;
int l, r, ans;
int euler(int x) {
	int res=x;
	for(int i=2; i*i<=x; i++){
		if(x%i==0) {
			res=res-res/i;
		}
		while(x%i==0) {
			x/=i;
		}
	} 
	if(x>1)  res=res-res/x;
	return res;
}
int qiandao(int x) {
	return x-euler(x);
}
signed main(){
	cin >> l >> r;
	for(int i=l; i<=r; i++){
		(ans+=qiandao(i))%mod;
	}
	cout << ans;
	return 0;
}
