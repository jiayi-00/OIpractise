#include<bits/stdc++.h>
using namespace std;

int main() {
    int x, i=2;
    cin >> x;
    while(x!=1){
        if(x%i==0){
            cout << i << " ";
            while(x%i==0){
                x/=i;
            }
        } 
        i++;

    }
    return 0;
}