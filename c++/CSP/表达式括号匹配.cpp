#include<iostream>
#include<string>
using namespace std;

string a;
int k=0;

int main(){
	
	getline(cin,a);
	for(int i=0; i<a.length() && a[i]!='@'; i++){
		if(a[i]=='('){
			k++;
		}
		if(a[i]==')'){
			k--;
		}
	}
	if(k==0)  cout<<"YES";
	else  cout<<"NO";
	
	return 0;
}
