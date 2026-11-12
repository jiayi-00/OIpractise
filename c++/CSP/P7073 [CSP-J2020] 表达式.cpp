#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int x[10001],se[10001];
void ca(int k){
	int p=0;
	for(int i=0; i<=size(s)-1; i++){
		if(s[i]==x){
			se[++p]=x[s[++i]];
		}
		else{
			int a=se[p],b=[--p];
			if(s[i]=='&') se[p]=a&b;
			if(s[i]=='|') se[p]=a|b;
			if(s[i]=='!') se[++p]=!a;
		}
		++i;
	}
	cout<<se[p]<<endl;
	return; 	
}
int main(){
	int k;
	cin>>s;
	cin>>n;
	for(int i=1; i<=n; i++) cin>>x[i];
	cin>>q;
	for(int i=1; i<=q; i++){
		cin>>k;
		ca[k];
	}
	return 0;
} 
