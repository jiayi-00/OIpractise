#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int n,a[101],sum,f[101];

int main(){
	
	freopen("count3.in","r",stdin);
	freopen("count.out","w",stdout);
	cin>>n;
	for(int i=1; i<=n; i++)   cin>>a[i]; 
	sort(a+1,a+n+1);
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			int t=a[i]+a[j];
			for(int k=j+1; k<=n; k++){
				if(a[k]==t && f[k]==0){
					f[k]=1;
					sum++;
				}
			}
		}
	}
	cout<<sum;
	
	return 0;
} 
