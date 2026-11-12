#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int B = 131; 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    unordered_set<ull> st;
    while(n--) {
        string s;
        cin >> s;
        ull h=0;
        for (char c : s) {
            h=h*B+(ull)c;
        }
        st.insert(h);
    }

    cout << st.size() << '\n';
    return 0;
}