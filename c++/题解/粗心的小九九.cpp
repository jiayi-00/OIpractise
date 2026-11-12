#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int x;
    cin >> s >> x;
    string ans; 
    for(int i=0; i<s.size(); i++){
        while(!ans.empty() && x>0 && ans.back()>s[i]){
            ans.pop_back();
            x--;
        }
        ans.push_back(s[i]);
    }
    while(x>0){
        ans.pop_back();
        x--;
    }
    int pos=0;
    while(pos<ans.size()-1 && ans[pos]=='0'){
        pos++;
    }
    for(int i=pos; i<ans.size(); i++){
        cout<<ans[i];
    }
    cout<<endl;
    
    return 0;
}
