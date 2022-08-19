#include <bits/stdc++.h>

using namespace std;

template<class T>
int fn(int a, int b, T t) {
    return t(a, b);
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << fn(a, b, less<int>());
    // less<int> ls;
    // auto      x = ls(a, b);
    // cout << x << endl;
    // {
        // vector<int> a;
        // sort(a.begin(), a.end(), std::less<int>());
    // }
    return 0;
}