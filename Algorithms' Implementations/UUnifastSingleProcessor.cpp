#include<bits/stdc++.h>

#define int long long int
#define ff first
#define ss second
#define pb push_back
#define pii pair<int, int>

using namespace :: std;

vector<double> uunifast(int n, double U) {
    vector<double> utilizations(n);
    double sumU = U;

    random_device rd;                // seeds the generator
    mt19937 gen(rd());               // Mersenne Twister Algorithm to create a random number generator
    uniform_real_distribution<double> dis(0.0, 1.0);           // creates a random number between 0.0 and 1.0
    
    for (int i = 1; i <= n - 1; i++) {
        double nextSumU = sumU * pow(dis(gen), 1.0 / (n - i));            // pow(dis(gen), 1.0 / (n - i)) is the utilisation factor for remaining tasks
        utilizations[i - 1] = sumU - nextSumU;                            // sum of n utilisations will be equal to U (initial value of sumU)
        sumU = nextSumU;
    }

    utilizations[n - 1] = sumU;
    return utilizations;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n = 5;
    double U = 0.8;
    
    vector<double> utilizations = uunifast(n, U);
    for (double u : utilizations) {
        cout << u << " ";
        
    }

    cout << endl;
    return 0;
}

