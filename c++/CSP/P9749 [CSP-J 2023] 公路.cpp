#include<iostream>
#include<algorithm>
using namespace std;

int v[10001],a[10001];
long long ans,s,n,d;

int main(){
	
	cin>>n>>d;
	for(int i=1; i<n; i++)  cin>>v[i];
	int min_p=100000;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
		s+=v[i];
		min_p=min(a[i],min_p);
		if(s>0){
			ans+=(s+d-1)/d*min_p;
			s-=(s+d-1)/d*d;
		}
	}
	cout<<ans;
	
	return 0;
}
