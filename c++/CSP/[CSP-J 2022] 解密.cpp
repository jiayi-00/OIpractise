#include<iostream>
#include<cstdio>
using namespace std;

void go(long long n,long long  e,long long d){
	long long sum=n-e*d+2;
	long long l=1,h=sum/2,p=-1,q=-1;
	while(l<=h){
		long long int mid=(l+h)/2,o=sum-mid,s=mid*o;
		if(s==n){
			p=mid;
			q=o;
			break;
		}
		else if(s<n)  l=mid+1;
		else  h=mid-1;
	}
	if(p!=-1&&q!=-1&&p*q==n) cout<<p<<' '<<q<<endl;
	else cout<<"NO"<<endl;
}

int main(){
	
	long long int n,k,e,d;
	cin>>k;
	while(k--){
		cin>>n>>e>>d;
		go(n,e,d);
	}
	
	return 0;
} 
