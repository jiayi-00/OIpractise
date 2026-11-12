#include<iostream>
#include<cstdio>
#include<string>
using namespace std;

int n,s;
string a;

int main(){
	
	freopen("name.in","r",stdin);
	freopen("name.out","w",stdout);
	cin>>n;
	getline(cin,a);
	for(int i=1; i<=n; i++){
		s=0;
		getline(cin,a);
		for(int j=0; j<=a.length()-1; j++){
			if(j==0 || a[j-1]==' '){
				if(a[j]>='A' && a[j]<='Z'){
					s++;
				}
			}
		}
		cout<<s<<endl;
	}
	
	return 0;
}
