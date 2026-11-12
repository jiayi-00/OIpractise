#include<bits/stdc++.h>
using namespace std;

long long sum;
int n,x,a[10001];

int main(){
	
	cin>>n>>x;
	for(int i=1; i<=n; i++) cin>>a[i];
	if(a[1]>x){
		sum+=a[1]-x;
		a[1]=x;
	}
	for(int i=2; i<=n; i++){
		if(a[i-1]+a[i]>x){
			sum+=a[i-1]+a[i]-x;
			a[i]=x-a[i-1];
		}
	}
	cout<<sum;
	
	return 0;
} 
