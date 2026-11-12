#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, p, ans=1e9;
int diff[5000005], a[5000005];
signed main(){
	scanf("%d%d",&n,&p);
	for(int i=1; i<=n; i++) {
		scanf("%d",&a[i]);
		
		diff[i]=a[i]-a[i-1];
	}
	for(int i=1; i<=p; i++) {
		int x, y, z;
		scanf("%d%d%d",&x,&y,&z);
		
		diff[x]+=z;
		diff[y+1]-=z;
	}
	for(int i=1; i<=n; i++) {
		a[i]=a[i-1]+diff[i]; 
		ans=min(ans,a[i]);
	}
	printf("%d",ans);
	return 0;
}
