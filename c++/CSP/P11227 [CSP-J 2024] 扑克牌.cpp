#include<bits/stdc++.h>
using namespace std;

int n,ans,f[53];
string a;

int main(){
	
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>a;
		int cont=0;
		if(a[0]=='D')  cont=0;
		else if(a[0]=='C')  cont=13;
		else if(a[0]=='H')  cont=26;
		else if(a[0]=='S')  cont=39;
		if(a[1]=='T')  cont+=10;
		else if(a[1]=='A')  cont+=1;
		else if(a[1]=='J')  cont+=11;
		else if(a[1]=='Q')  cont+=12;
		else if(a[1]=='K')  cont+=13;
		else  cont+=(a[1]-'0');
		f[cont]=1;
	}
	for(int i=1; i<=52; i++){
		if(f[i]==1) ans++;
	}
	cout<<52-ans;
	
	return 0;
}
