from flask import Flask, render_template, request
import tkinter as tk
from tkinter import messagebox
from functools import partial
import random
import numpy as np
import sys


def randfixedsum(n, m, s, a, b):
    # Check the arguments
    if (m != int(m)) or (n != int(n)) or (m < 0) or (n < 1):
        raise ValueError(
            "n must be a whole number and m a non-negative integer.")
    elif (s < n * a) or (s > n * b) or (a >= b):
        raise ValueError("Inequalities n*a <= s <= n*b and a < b must hold.")

    # Rescale to a unit cube: 0 <= x(i) <= 1
    s = (s - n * a) / (b - a)

    # Construct the transition probability table, t
    k = max(min(int(s), n - 1), 0)  # Must have 0 <= k <= n-1
    s = max(min(s, k + 1), k)  # Must have k <= s <= k+1
    s1 = s - np.arange(k, k - n + 1, -1)  # s1 & s2 will never be negative
    s2 = np.arange(k + n, k, -1) - s
    w = np.zeros((n, n + 1), dtype=np.float64)
    w[0, 1] = np.finfo(np.float64).max  # Scale for full 'double' range
    t = np.zeros((n - 1, n), dtype=np.float64)
    tiny = 2 ** (-1074)  # The smallest positive 'double' number

    for i in range(1, n):
        tmp1 = w[i - 1, 1:i + 1] * s1[:i] / i
        tmp2 = w[i - 1, 0:i] * s2[n - i:n] / i
        w[i, 1:i + 1] = tmp1 + tmp2
        tmp3 = w[i, 1:i + 1] + tiny  # In case tmp1 & tmp2 are both 0,
        # then t is 0 on the left & 1 on the right
        tmp4 = s2[n - i:n] > s1[0:i]
        t[i - 1, 0:i] = (tmp2 / tmp3) * tmp4 + (1 - tmp1 / tmp3) * (~tmp4)

    # Derive the polytope volume v from the appropriate
    # element in the bottom row of w
    v = (n ** (3 / 2)) * (w[n-1, k + 2] / sys.float_info.max) * ((b - a) ** (n - 1)) 
                         
    # v = n^(3/2)*(w(n,k+2)/realmax)*(b-a)^(n-1);


    # Now compute the matrix x
    x = np.zeros((n, m), dtype=np.float64)
    if m == 0:
        return x  # If m is zero, return an empty array
    rt = np.random.rand(n - 1, m)  # For random selection of simplex type
    rs = np.random.rand(n - 1, m)  # For random location within a simplex
    s = np.tile(s, (1, m))
    j = np.tile(k + 1, (1, m))  # For indexing in the t table
    sm = np.zeros((1, m), dtype=np.float64)
    pr = np.ones((1, m))

    for i in range(n - 1, 0, -1):  # Work backwards in the t table
        # Use rt to choose a transition
        e = (rt[n - i - 1, :] <= t[i - 1, j - 1])
        # Use rs to compute next simplex coord.
        sx = rs[n - i - 1, :] ** (1 / i)
        sm = sm + (1 - sx) * pr * s / (i + 1)  # Update sum
        pr = sx * pr  # Update product
        x[n - i - 1, :] = sm + pr * e  # Calculate x using simplex coords.
        s = s - e
        j = j - e  # Transition adjustment

    x[n - 1, :] = sm + pr * s  # Compute the last x

    # Randomly permute the order in the columns of x and rescale
    rp = np.random.rand(n, m)  # Use rp to carry out a matrix 'randperm'
    p = np.argsort(rp, axis=0)  # The values placed in p are ignored
    x = (b - a) * x[p, np.arange(m)] + a  # Permute & rescale x

    return x, v


def generate_task_sets(n_entry, m_entry, s_entry, a_entry, b_entry):
    try:

        n = int(n_entry.get().strip()) if n_entry.get().strip().isdigit() else 0
        m = int(m_entry.get().strip()) if m_entry.get(
        ).strip().isnumeric() else 0
        s = float(s_entry.get().strip()) if s_entry.get(
        ).strip().replace('.', '', 1).isdigit() else 0.0
        a = float(a_entry.get().strip()) if a_entry.get(
        ).strip().replace('.', '', 1).isdigit() else 0.0
        b = float(b_entry.get().strip()) if b_entry.get(
        ).strip().replace('.', '', 1).isdigit() else 0.0

        if n <= 0 or not n_entry.get().isdigit() or m < 0 or not m_entry.get().isnumeric():
            messagebox.showerror(
                "Input Error", "Number of tasks must be a positive whole number and number of task sets must be a non-negative whole number.")
            return

        taskSets, v = randfixedsum(n, m, s, a, b)

        # Display the generated task sets
        for taskSet in taskSets:
            formatted_taskSet = ' '.join(f"{task:.3f}" for task in taskSet)

    except Exception as e:
        messagebox.showerror("Error", str(e))






app = Flask(__name__, template_folder='.')


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/generate_task_sets', methods=['POST'])
def flask_generate_task_sets():
    try:
        n = int(request.form['n'])
        m = int(request.form['m'])
        s = float(request.form['s'])
        a = float(request.form['a'])
        b = float(request.form['b'])

        taskSets, v = randfixedsum(n, m, s, a, b)

        # Round the values in taskSets to 3 decimal places
        rounded_taskSets = [[round(task, 3) for task in taskSet]
                            for taskSet in taskSets]
        rounded_v = round(v, 3)

        return {
            'taskSets': rounded_taskSets,
            'v': rounded_v
        }
    except Exception as e:
        return str(e), 400


if __name__ == '__main__':
    app.run(debug=True)
