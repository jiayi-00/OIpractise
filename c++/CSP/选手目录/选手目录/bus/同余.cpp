#include<iostream>
#include<cstdio>
using namespace std;

long long int a,m;
long long int n,s;

int main(){
	
	freopen("mod.in","r",stdin);
	freopen("mod.out","w",stdout);
	cin>>a>>m>>n;
	long long int am=a%m;
	if(n%m==am){
		s=(n-am)/m+1;
	}else if(am>n){
		s=0;
	}else{
		s=(n-am)/m+1;
	}
	cout<<s;
	
	return 0;
}
