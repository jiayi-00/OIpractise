#include<bits/stdc++.h>
using namespace std;

int n; 
struct a{
	int c,num;
}s[100001];
bool cmp(a x,a y){
	if(x.num==y.num) return x.c>y.c;
	return x.num>y.num;
}

int main(){
	
	freopen("salesman.in","r",stdin);
	freopen("salesman.out","w",stdout);
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>s[i].num;
	}
	for(int i=1; i<=n; i++){
		cin>>s[i].c;
	}
	sort(s+1,s+n+1,cmp);
	for(int i=1; i<=n; i++){
		int max_long=0,ans=0;
		for(int j=1; j<=i; j++){
			ans+=s[j].num;
			max_long=max(max_long,s[j].c);
		}
		cout<<ans+max_long*2<<endl;
	}
	
	return 0;
} 
