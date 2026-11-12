#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, p;
int quickm(int a, int b, int p){
	int ans=1;
	while(b){
		if(b%2==1)  ans=ans*a%p;
		a=a*a%p;
		b/=2;
	}
	return ans;
}
signed main(){
	cin >> n >> p;
	for(int i=1; i<=n; i++){
		printf("%d\n",quickm(i, p-2, p));
	}
	return 0;
}
