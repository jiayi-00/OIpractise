#include<iostream>
using namespace std;

int n;

void hua(int i){
	
	if(i==n+1) return;
	for(int j=1; j<=i; j++){
		for(int k=1; k<=j; k++){
			cout<<'*';
		}
		cout<<endl;
	}
	hua(i+1);
	
}

int main(){
	
	cin>>n;
	hua(1);
	
	return 0;
} 
