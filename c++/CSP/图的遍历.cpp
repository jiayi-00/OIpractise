#include<iostream>
using namespace std;

int n,m,l[1001][1001]={1},s;

int main(){
	
	cin>>n>>m;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			cin>>l[i][j];
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(l[i+1][j]!=0&&l[i-1][j]!=0&&l[i][j-1]!=0&&l[i][j+1]!=0){
				s++;
			}
		}
	}
	cout<<s;
	
	return 0;
}
