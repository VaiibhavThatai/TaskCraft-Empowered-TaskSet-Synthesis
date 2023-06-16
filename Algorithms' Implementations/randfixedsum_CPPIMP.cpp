#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

double v;
std::vector<std::vector<double>> randfixedsum(int n, int m, double s, double a, double b)
{
    // Check the arguments
    if (m != static_cast<int>(m) || n != static_cast<int>(n) || m < 0 || n < 1)
    {
        throw std::invalid_argument("n must be a whole number and m a non-negative integer.");
    }
    else if (s < n * a || s > n * b || a >= b)
    {
        throw std::invalid_argument("Inequalities n*a <= s <= n*b and a < b must hold.");
    }

    // Rescale to a unit cube: 0 <= x(i) <= 1
    s = (s - n * a) / (b - a);

    // Construct the transition probability table, t
    int k = std::max(std::min(static_cast<int>(s), n - 1), 0);                     // Must have 0 <= k <= n-1
    s = std::max(std::min(s, static_cast<double>(k + 1)), static_cast<double>(k)); // Must have k <= s <= k+1
    std::vector<double> s1(n), s2(n);
    for (int i = 0; i < n; ++i)
    {
        s1[i] = s - (k - i);
        s2[i] = (k + n - i) - s;
    }
    std::vector<std::vector<double>> w(n, std::vector<double>(n + 1, 0.0));
    w[0][1] = std::numeric_limits<double>::max(); // Scale for full 'double' range
    std::vector<std::vector<double>> t(n - 1, std::vector<double>(n, 0.0));
    double tiny = std::pow(2, -1074); // The smallest positive 'double' number

    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            double tmp1 = w[i - 1][j] * s1[j - 1] / i;
            double tmp2 = w[i - 1][j - 1] * s2[n - i + j - 1] / i;
            w[i][j + 1] = tmp1 + tmp2;
            double tmp3 = w[i][j + 1] + tiny;          // In case tmp1 & tmp2 are both 0,
            bool tmp4 = s2[n - i + j - 1] > s1[j - 1]; // then t is 0 on the left & 1 on the right
            t[i - 1][j - 1] = (tmp2 / tmp3) * tmp4 + (1 - tmp1 / tmp3) * (!tmp4);
        }
    }

    // Derive the polytope volume v from the appropriate
    // element in the bottom row of w
    // v = std::pow(n, 3.0 / 2) * (w[n - 1][k + 1] / std::numeric_limits<double>::max()) * std::pow((b - a), n - 1);
    v = std::pow(n, 3.0 / 2) * (std::accumulate(w[n - 1].begin(), w[n - 1].end(), 0.0) / std::numeric_limits<double>::max()) * std::pow((b - a), n - 1);

    // Now compute the matrix x
    std::vector<std::vector<double>> x(n, std::vector<double>(m, 0.0));
    if (m == 0)
    {
        return x; // If m is zero, return an empty array
    }
    // std::vector<std::vector<double>> rt(n - 1, std::vector<double>(m));
    // std::vector<std::vector<double>> rs(n - 1, std::vector<double>(m));
    // std::vector<std::vector<double>> s_matrix(1, std::vector<double>(m, s));

    std::vector<std::vector<int>> j(1, std::vector<int>(m, k + 1));
    std::vector<std::vector<double>> sm(1, std::vector<double>(m, 0.0));
    std::vector<std::vector<double>> pr(1, std::vector<double>(m, 1.0));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    std::vector<std::vector<double>> s_matrix(1, std::vector<double>(m));
    for (int j = 0; j < m; ++j)
    {
        s_matrix[0][j] = dis(gen) * s;
    }

    for (int i = n - 1; i > 0; --i)
    { // Work backwards in the t table
        std::vector<bool> e(m);
        for (int k = 0; k < m; ++k)
        {
            e[k] = dis(gen) <= t[i - 1][j[0][k] - 1]; // Use rt to choose a transition
            double sx = std::pow(dis(gen), 1.0 / i);  // Use rs to compute next simplex coord.
            for (int l = 0; l < m; ++l)
            {
                sm[0][l] += (1 - sx) * pr[0][l] * s_matrix[0][l] / (i + 1); // Update sum
                pr[0][l] *= sx;                                             // Update product
                x[n - i - 1][l] = sm[0][l] + pr[0][l] * e[l];               // Calculate x using simplex coords.
                s_matrix[0][l] -= e[l];
                j[0][l] -= e[l]; // Transition adjustment
            }
        }
    }

    for (int k = 0; k < m; ++k)
    {
        x[n - 1][k] = sm[0][k] + pr[0][k] * s_matrix[0][k]; // Compute the last x
    }

    // Randomly permute the order in the columns of x and rescale
    std::vector<std::vector<double>> rp(n, std::vector<double>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            rp[i][j] = dis(gen);
        }
    }
    std::vector<std::vector<int>> p(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            p[i][j] = j;
        }
        std::sort(p[i].begin(), p[i].end(), [&](int a, int b)
                  { return rp[i][a] < rp[i][b]; });

        std::vector<double> temp(m);
        for (int j = 0; j < m; ++j)
        {
            temp[j] = x[i][p[i][j]];
        }
        x[i] = temp;
    }
    for (int j = 0; j < m; ++j)
    {
        double min_val = x[0][j];
        double max_val = x[0][j];
        for (int i = 1; i < n; ++i)
        {
            if (x[i][j] < min_val)
                min_val = x[i][j];
            if (x[i][j] > max_val)
                max_val = x[i][j];
        }
        double range = max_val - min_val;
        for (int i = 0; i < n; ++i)
        {
            x[i][j] = a + (x[i][j] - min_val) * (b - a) / range;
        }
    }

    for (int j = 0; j < m; ++j)
    {
        double sum_col = 0.0;
        for (int i = 0; i < n; ++i)
        {
            sum_col += x[i][j];
        }
        double scale_factor = s / sum_col;
        for (int i = 0; i < n; ++i)
        {
            x[i][j] *= scale_factor;
        }
    }

    return x;
}

int main()
{
    int n = 10;     // Number of tasks
    int m = 4;      // Number of task sets
    double s = 3.0; // Total volume constraint
    double a = 0.0; // Lower bound of task values
    double b = 1.0; // Upper bound of task values

    std::vector<std::vector<double>> taskSets = randfixedsum(n, m, s, a, b);

    // Display the generated task sets
    for (const auto &taskSet : taskSets)
    {
        for (const auto &task : taskSet)
        {
            std::cout << task << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}
