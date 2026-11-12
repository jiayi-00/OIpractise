#include<bits/stdc++.h>
#define ull unsigned long long
#define get(l,r) (hsh[r]-hsh[l-1]*p[r-l+1])
using namespace std;
const int B=131;
int len;
char s[1000005];
ull hsh[1000005],p[1000005];
void init(){
	p[0]=1;
	for(int i=1; i<=len; i++){
		hsh[i]=hsh[i-1]*B+s[i];
		p[i]=p[i-1]*B;
	}
}
void solve(){
	for(int i=1; i<=len; i++){
		int l=i+1,r=len;
		ull v1=hsh[i];
		ull v2=hsh[r]-hsh[l-1]*p[r-l+1];
		ull v=v2*p[i]+v1;
		if(v==hsh[len]) {
			cout<<len/i<<endl;
			return;
		} 
	}
}
int main(){
	scanf("%s",s+1);
	len=strlen(s+1);
	init();
	solve();
	return 0;
}
