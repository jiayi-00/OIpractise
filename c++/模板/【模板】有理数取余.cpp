#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=19260817;
string sa, sb;
int rd(string s){
	int x=0;
	for(int i=0; i<s.size(); i++) {
		x=x*10+s[i]-'0';
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
signed main(){
	cin >> sa >> sb;
	int a=rd(sa), b=rd(sb);
	if(b%p==0) {
		cout << "Angry!";
		return 0;
	}
	cout << a*quickm(b, p-2, p)%p;
	return 0;
}
