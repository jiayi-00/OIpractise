#include<bits/stdc++.h>
using namespace std;

int n,a[31],ans; 

int main(){
	
	cin>>n;
	for(int i=1; i<=n; i++)  cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=2; i<=n; i++){
		ans+=a[i]*pow(2,n-i);
	}
	ans+=a[1]*pow(2,n-2);
	cout<<ans;
	
	return 0;
} 
