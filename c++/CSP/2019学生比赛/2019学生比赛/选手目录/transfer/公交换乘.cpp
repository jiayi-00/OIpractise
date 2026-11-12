#include<iostream>
#include<cstdio>
using namespace std;
int n,p,k=1,sum,used[100001],l=1;
struct transfer{
	int w;
	int p,t;
};
transfer bus[100001],sub[100001];
int main(){
	freopen("transfer.in","r",stdin);
	freopen("transfer.out","w",stdout);
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>bus[i].w>>bus[i].p>>bus[i].t;
		if(bus[i].w==0){
			sum+=bus[i].p;
			sub[k].p=bus[i].p;sub[k].w=bus[i].w;sub[k].t=bus[i].t;
			used[k]=1;
			k++;
		} 
		if(bus[i].w==1){
			int f=0;
			for(int j=l; j<=k; j++){
				if(used[j]==0) continue;
				if(bus[i].t-sub[j].t>45){
					used[j]=0;
					l=j;
					continue;
				}
				if(bus[i].t-sub[j].t<=45 && bus[i].p<=sub[j].p){
					used[j]=0;
					f=1;
					break;
				}
			}
			if(f==0) sum+=bus[i].p;
		}
	} 
	cout<<sum;
	return 0;
}
