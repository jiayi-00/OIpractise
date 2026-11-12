#include<iostream>
#include<algorithm>
using namespace std;
int n,k,l[100001],a[100001],sum;
bool cmd(int x,int y){
	return x>y;
}
int main(){
	cin>>n>>k;
	for(int i=1; i<=n; i++) cin>>l[i];
	sort(l+1,l+n+1,cmd);
	for(int i=1; i<=n-1; i++) a[i]=l[i]-l[i+1];
	sort(a+1,a+n+1);
	for(int i=1; i<=k+1; i++) sum+=a[i];
	cout<<sum;
	return 0;
}
