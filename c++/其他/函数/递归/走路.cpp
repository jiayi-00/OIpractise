#include<iostream>
using namespace std;

int n,ans;

void bian(int i){
	
	if(i==1) return;
	for(int j=1; j<=i-1; j++){
		if(j%2!=0){
			ans++;
			bian(j);
		}
	}
	
}

int main(){
	
	cin>>n;
	bian(n);
	cout<<ans+1;
	
	return 0;
} 
