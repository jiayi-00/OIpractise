#include<iostream>
using namespace std;

int n,k=1,d,ans_n;

int main(){
	
	cin>>n;
	while(n>0){
		d++;
		if(ans_n==0&&n%3==1){
			ans_n=d;
		}
		n-=(n+2)/3;
	}
	cout<<d<<' '<<ans_n;
	
	return 0;
}
