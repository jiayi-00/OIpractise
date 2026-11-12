#include <bits/stdc++.h>
using namespace std;

int main() {
    int TestsNumT;
    cin >> TestsNumT;
    while (TestsNumT--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<int> c, s;
        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && a[j] == a[i]) j++;
            c.push_back(a[i]);
            s.push_back(j - i);
            i = j;
        }

        int k = c.size();
        int ans = k;

        bool gain2 = false;
        for (int i = 0; i + 1 < k; i++) {
            if (s[i] >= 2 && s[i + 1] >= 2) {
                gain2 = true;
                break;
            }
        }

        if (gain2) {
            ans = k + 2;
        } else {
            bool gain1 = false;
            for (int i = 0; i < k; i++) {
                if (s[i] >= 2) {
                    bool can_right = (i + 1 < k) && (i + 2 >= k || c[i] != c[i + 2]);
                    bool can_left = (i > 0) && (i - 2 < 0 || c[i - 2] != c[i]);
                    if (can_right || can_left) {
                        gain1 = true;
                        break;
                    }
                }
            }
            if (gain1) ans = k + 1;
        }

        cout << ans << "\n";
    }
    return 0;
}
