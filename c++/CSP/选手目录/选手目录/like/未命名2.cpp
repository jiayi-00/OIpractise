#include<iostream>
#include<algorithm>
#include<cstdio> 
using namespace std;

int n,m,d,k,cnt[1005][1005],ts,id;

int main(){
	
	//freopen("like.in","r",stdin);
	//freopen("like.out","w",stdout);
	cin>>n>>m>>d>>k;
	for(int i=1; i<=m; i++){
		cin>>ts>>id;
		cnt[id][ts]++;
	}
	for(int i=1; i<=n; i++){
		bool is=0;
		for(int t=0; t<=100; t++){
			int from=t;
			int to=t+d-1;
			if(to>100) break;
			int zan=0;
			for(int l=from; l<=to; l++){
				zan+=cnt[i][l];
			}
			if(zan>=k){
				is=1;
				break;
			}
		}
		if(is){
			cout<<i<<endl;
		}
	}
	
	return 0;
}
