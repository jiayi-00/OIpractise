#include<bits/stdc++.h>
using namespace std;
int a[114514],n,x,T,maxx,minn;
double ans;
int main() {
	cin>>T;
	while(T--) {
		cin>>n;
		for(int i=1; i<=n; i++) cin>>a[i];
		maxx=-1000000007,minn=1000000007;
		for(int i=1; i<=n; i++) {
			cin>>x;
			maxx=max(maxx,a[i]+x);
			minn=min(minn,a[i]-x);
		}
		ans=(maxx+minn)/2.0;
		if(floor(ans)==ans) printf("%d\n",(int)ans);
		else printf("%.1f\n",ans);
	}
	return 0;
}

