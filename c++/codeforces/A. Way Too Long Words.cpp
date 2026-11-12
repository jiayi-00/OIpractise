#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    int n;
    cin >> n;
    while(n--){
        cin >> s;
        int len = s.length();  // 先保存长度
        
        if(len <= 10){
            cout << s << endl;
        }
        else{
            // 确保长度至少为11时才执行这里
            int mid_len = len - 2;
            cout << s[0] << mid_len << s[len-1] << endl;
        }
    }
    return 0;
}