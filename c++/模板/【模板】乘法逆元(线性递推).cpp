#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, p;
    scanf("%d %d", &n, &p);
    vector<long long> inv(n+1);
    inv[1] = 1;
    for(int i = 2; i <= n; i++)
        inv[i] = (long long)(p - p/i) * inv[p % i] % p;
    for(int i = 1; i <= n; i++)
        printf("%lld\n", inv[i]);
    return 0;
}