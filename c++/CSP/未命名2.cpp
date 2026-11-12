#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

long long int a,b;

int main(){
	
	freopen("pow.in","r",stdin);
	freopen("pow.out","w",stdout);
	cin>>a>>b;
	if(a==1) cout<<1;
	else{
		long long int s=1;
		for(int i=1; i<=b; i++){
			s*=a;
			if(s>1e9){ 
				cout<<-1;
				return 0; 
			}
		}
		cout<<s;
	} 
	
	return 0;
}
