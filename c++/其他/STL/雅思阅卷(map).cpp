#include<iostream>
#include<string>
#include<map>
using namespace std;
int n,p,ans;
map<string ,int>a; 
int main(){
	cin>>n>>p;
	string x,w;
	int y;
	while(n--){
		cin>>x>>y;
		a[x]=y;
	}
	getline(cin,w);
	for(int i=1; i<=3; i++){
		getline(cin,w);
		string t="";
		for(int j=0; j<=w.size()-1; j++){
			if(w[j]!=' '&&w[j]!=','&&w[j]!='.'&&w[j]!='!'&&w[j]!='?')  t+=w[j];
			else  {
				if(a.count(t))  ans+=a[t];
				t="";
			}
		}
	}
	cout<<ans%p;
	return 0;
}
