#include<bits/stdc++.h>
using namespace std;
string s, st;
int cnt;
int main(){
	cin >> s;
	bool f=0;
	for(int i=0; i<s.size(); i++) {
		if(s[i]=='('){
			st+='(';
			++cnt;
		}
		if(s[i]==')') {
			if(cnt==0) {
				f=1;
				break;
			}
			st[--cnt]=' ';
		}
	}
	if(f || cnt>0)  cout << "NO";
	else cout << "YES";
	return 0;
}
