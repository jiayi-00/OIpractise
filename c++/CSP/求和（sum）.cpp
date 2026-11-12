#include<bits/stdc++.h>
using namespace std;
long long int n,m,ans;
struct s{
	int t,c;
}a[100001];
int main(){
		
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	cin>>n>>m;
	for(int i=1; i<=n; i++)  cin>>a[i].t;
	for(int i=1; i<=n; i++){
		cin>>a[i].c;
	}
	for(int x=1; x<=n; x++){
		for(int z=x+2; z<=n; z+=2){
			int y=(x+z)/2;
			if(a[x].c==a[z] .c){
				ans=(ans+(x+z)*(a[x].t+a[z].t))%10007;
			}
		}
	}
	cout<<ans%10007;
	
	return 0;
}
