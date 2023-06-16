#include<bits/stdc++.h>

#define int long long int
#define ff first
#define ss second
#define pb push_back
#define pii pair<int, int>

using namespace :: std;

vector<double> uunifast_discard_mp(int n, double U, int m) {
    vector<double> utilizations(n);
    double sumU = U;

    for (int i = 1; i < n; i++) {
        double nextSumU = sumU * pow(rand() / (double)RAND_MAX, 1.0 / (n - i));
        utilizations[i - 1] = sumU - nextSumU;
        sumU = nextSumU;
    }

    utilizations[n - 1] = sumU;

    vector<double> max_utilizations(m, U / m);
    random_shuffle(max_utilizations.begin(), max_utilizations.end());

    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < m && utilizations[i] > max_utilizations[j]) {
            
            j++;
        }
        if (j == m) {
            utilizations[i] = 0;
        }
        else {
            max_utilizations[j] -= utilizations[i];
        }
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


    srand(time(NULL));

    int n = 10;
    double U = 1.0;
    int m = 4;

    vector<double> utilizations = uunifast_discard_mp(n, U, m);

    for (int i = 0; i < n; i++) {
        cout << "Task " << i << " utilization: " << utilizations[i] << endl;
    }

    return 0;
}
