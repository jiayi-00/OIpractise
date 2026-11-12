#include<bits/stdc++.h>
#define int long long
using namespace std;
int a, m, fip, flag=0;
string sb;
int euler(int x) {
	int ans=x;
	for(int i=2; i*i<=x; i++){
		if(x%i==0) {
			ans=ans-ans/i;
		}
		while(x%i==0) {
			x/=i;
		}
	} 
	if(x>1)  ans=ans-ans/x;
	return ans;
}
int rd(string s, int p){
	int x=0;
	for(int i=0; i<s.size(); i++) {
		x=x*10+s[i]-'0';
		if(x>fip)  flag=1;
		x%=p;
	}
	return x;
}
int quickm(int a, int b, int p){
	int ans=1;
	while(b){
		if(b%2==1)  ans=ans*a%p;
		a=a*a%p;
		b/=2;
	}
	return ans;
}

int gcd(int x, int y){
	return y==0 ? x : gcd(y,x%y); 
}
signed main(){
	cin >> a >> m >> sb;
	fip=euler(m);
	int b=rd(sb, fip);
	if(gcd(a,m)==1 || !flag){
		cout << quickm(a, b, m)%m;
	}
	else {
		cout << quickm(a, b%fip, m)%m;
	}
	
	return 0;
}
