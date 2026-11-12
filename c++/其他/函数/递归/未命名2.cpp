#include<iostream>
#include<algorithm>
using namespace std;
int w,n,p[10001],s;
int main(){
	cin>>w>>n;
	for(int i=1; i<=n; i++) cin>>p[i];
	sort(p+1,p+n+1);
	int l=1,r=n;
	while(l<=r){
		if(p[l]+p[r]<=w) l++;
		r--; 
		s++;
	}
	cout<<s;
	return 0;
}
