#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

long long int n,x,y,cnt,s,ans=1;

int main(){
	
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	cin>>n>>x>>y;
	long long int a=min(x,n-x+1),b=min(y,n-y+1),k=min(a,b);
	for(int i=1; i<=k-1; i++){
		s+=4*(n-(i-1)*2)-4;
	}
	if(x<=y)  ans+=s+x-k+y-k;
	else{
		int c=n-(k-1)*2;
		int p=c*2-2,kk=n-k+1;
		ans+=s+p+kk-x+kk-y;
	}
	cout<<ans;
	
	return 0;
} 
