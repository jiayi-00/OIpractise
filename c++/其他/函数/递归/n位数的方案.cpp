#include<iostream>
using namespace std;
int used[10],n,m,s,pai[10];
void go(int i){
	if(i==n+1){
		for(int j=1; j<=n; j++){
			s+=pai[j];
		}
		if(s==m){
			for(int j=1; j<=n; j++){
				cout<<pai[j]<<' ';
			}
			cout<<endl;
		}
		s=0;
		return;
	}
	for(int j=1; j<=m; j++){
		pai[i]=j;
		go(i+1);
	}
}
int main(){
	cin>>m>>n;
	go(1);
	return 0;
} 
