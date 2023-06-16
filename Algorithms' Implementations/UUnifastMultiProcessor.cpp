#include<bits/stdc++.h>

#define int long long int
#define ff first
#define ss second
#define pb push_back
#define pii pair<int, int>

using namespace :: std;

vector<double> uunifast(int n, double U, int m) {
    vector<double> utilizations(n);
    double sumU = U;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < n - 1; i++) {
        double nextSumU = sumU * pow(dis(gen), 1.0 / (n - i));
        utilizations[i] = sumU - nextSumU;
        sumU = nextSumU;
    }

    utilizations[n - 1] = sumU;

    double utilization = U / m;
    double totalUtilization = accumulate(utilizations.begin(), utilizations.end(), 0.0);

    for (int i = 0; i < n; i++) {
        utilizations[i] *= utilization / totalUtilization;
    }

    return utilizations;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif


    int n = 3; // number of tasks
    double U = 1.2; // total utilization
    int m = 2; // number of processors
    vector<double> utilizations = uunifast(n, U, m);
    for (int i = 0; i < n; i++) {
        cout << "Task " << i << " utilization: " << utilizations[i] << endl;
    }
    return 0;
}