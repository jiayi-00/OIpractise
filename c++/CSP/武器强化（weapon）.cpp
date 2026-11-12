#include<bits/stdc++.h>
using namespace std;
int n,m,t[1001],p[1001][1001],cnt[1001];
long long min_ans;
int main(){
	
//	freopen("weapon.in","r",stdin);
//	freopen("weapon.out","w",stdout);
	
	cin>>n>>m;
	int a,b;
	for(int i=1; i<=m; i++){
		cin>>a>>b;
		cnt[a]++;
		p[a][cnt[a]]=b;
	}
	for(int i=1; i<=n; i++){
		sort(p[i]+1,p[i]+cnt[i]+1);
	}
	for(int i=max(1,cnt[1]); i<=m; i++){
		int num1=cnt[1],t1=0;
		long long ans=0;
		for(int j=2; j<=n; j++){
			if(cnt[j]>=i){
				int num=cnt[j]-i+1;
				for(int k=1; k<=num; k++){
					ans+=p[j][k];
					num1++;
				}
				for(int k=num+1; k<=cnt[j]; k++)  t[++t1]=p[j][k];
			}
			else {
				for(int k=1; k<=cnt[j]; k++)  t[++t1]=p[j][k];
			}
			if(num1<i){
				if(t1<i-num1) continue;
				sort(t+1,t+t1+1);
				for(int k=1; k<=i-num1; k++){
					ans+=t[k];
				}	
			}
		}
		min_ans=min(min_ans,ans);
	}
	
	cout<<min_ans;
	
	return 0;
}
