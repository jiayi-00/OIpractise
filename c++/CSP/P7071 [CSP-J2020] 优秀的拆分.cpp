#include<iostream>
#include<cstdio>
using namespace std;

int n,t[30],i=1;

int main() {
	
	cin>>n;
	if(n%2!=0 || n==0) cout<<-1;
	else{
		while(n!=0){
			if(n%2) t[i]=1;
			i++;
			n/=2;
		}
		for(int j=i-1; j>=1; j--){
			if(t[j]==1)  cout<<(1<<(j-1))<<' ';
		}
	}
	
	return 0;
}
