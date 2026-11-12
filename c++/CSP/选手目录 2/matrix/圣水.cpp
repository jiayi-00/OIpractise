#include<iostream>
#include<algorithm>
using namespace std;

int n,k,sum,v,y,w[1001],s,t;

int main(){
	
//	freopen("water.in","r",stdin);
//	freopen("water.out","w",stdout);
	cin>>n>>k>>s;
	for(int i=1; i<=n; i++)	{
		cin>>w[i];
		t+=w[i];
	}
	
	for(int i=1; i<=k; i++){
		cin>>v>>y;
		sum+=t*(y/n); 
		y%=n;
		for(int i=1; i<=y; i++){
			if(v==0){
				sum+=w[s];
				s++;  
				if(s==n+1)  s=1;
			}
			if(v==1) {
				sum+=w[s];
				s--; 
				if(s==0) s=n;
			}
		}	
	}
	cout<<sum%10007;
	
	return 0;
}
