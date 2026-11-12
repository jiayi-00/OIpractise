#include<iostream>
#include<algorithm>
using namespace std;

int n,k,dp[510][110],ans;
struct point{
	int x,y;
}p[505];

bool cmp(point a,point b){
	if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}

int main(){
	
	cin>>n>>k;
	int a,b;
	for(int i=1; i<=n; i++){
		cin>>p[i].x>>p[i].y;
	}
	sort(p+1,p+n+1,cmp);
	for(int i=1; i<=n; i++){
		for(int j=0; j<=k; j++){
			dp[i][j]=j+1;
			for(int l=1; l<=i; l++){
				if(p[l].x>p[i].x||p[l].y>p[i].y)  continue;
				int d=p[i].x-p[l].x+p[i].y-p[l].y-1;
				if(j>=d){
					dp[i][j]=max(dp[i][j],dp[l][j-d]+d+1);
				}
			}
			ans=max(ans,dp[i][j]);
		}
	}
	cout<<ans;
	
	return 0;
}
