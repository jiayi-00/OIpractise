#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, K, ans;
int cnt[1<<10];
int dp[14][1<<10][90];
bool ok(int x){
	return x&(x<<1) ? 0 : 1;
}
bool okz(int x, int y){
	if (x&y) return 0;
	if (x&(y<<1))  return 0;
	if(x&(y>>1))  return 0;
	return 1;
}
int popcnt(int x){
	int ret=0;
	while(x){
		x&=(x-1);
		ret++;
	}
	return ret;
}
signed main(){
	cin >> n >> K;
	for(int i=0; i<(1<<n); i++){
		if(ok[i]){
			cnt[i]=popcnt(i);
			dp[1][i][cnt[i]]=1;
		}
	}
	for(int i=2; i<=n; i++){
		for(int j=0; j<(1<<n); j++){
			for(int s=cnt[j]; s<=K; s++){
				for(int k=0; k<(1<<n); k++){
					if(ok(j) && ok(k) && okz(j,k)){
						dp[i][j][s]+=dp[i-1][k][s-cnt[j]];
					}
				}
			}
		}
		for(int j=0; j<(1<<n); j++){
			ans+=dp[n][j][K];
		}
	}
	cout << ans;
	return 0;
} 
