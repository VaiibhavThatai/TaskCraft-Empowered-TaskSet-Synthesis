# TaskCraft-Empowered-TaskSet-Synthesis

INTRODUCTION
Real-time taskset generation algorithms are essential for simulating and evaluating the performance of real-time systems. This repository provides a set of algorithms that generate synthetic tasksets with various characteristics such as task utilization, period distribution, and task dependencies. These tasksets can be used for benchmarking scheduling algorithms, evaluating system performance, and conducting research in real-time systems.

# Algorithms
The repository currently includes the following taskset generation algorithms:

1. RandFixedSum: This algorithm generates an n by m array of random values, subject to the condition that their sum be equal to a specified value. The distribution of values is uniform, and the algorithm ensures that the generated tasksets satisfy the sum constraint.

2. Uunifast Algorithm for Single Processor: This algorithm generates a set of tasksets for a single processor based on the Uunifast algorithm. It allows you to specify the total utilization and the number of tasks, and it generates tasksets with random utilization values that follow the Uunifast distribution.

3. Uunifast Algorithm for Multi Processors: This algorithm extends the Uunifast algorithm for generating tasksets for multi-processor systems. It takes into account the number of processors and generates tasksets with random utilization values that are distributed across the processors.

4. Uunifast Discard Algorithm: This algorithm is an improvement over the basic Uunifast algorithm. It generates tasksets by iteratively discarding invalid tasksets that do not satisfy certain constraints, such as the maximum utilization or deadline requirements. This algorithm ensures that the generated tasksets are more realistic and applicable to real-time systems.

# Usage

To use the taskset generation algorithms in your project, follow these steps:

1. Clone the repository to your local machine using the following command:
```
git clone https://github.com/VaiibhavThatai/TaskCraft-Empowered-TaskSet-Synthesis.git
```
2. Navigate to the downloaded repository directory
```
cd TaskCraft-Empowered-TaskSet-Synthesis
```
3. Import the required algorithm file into your project

# GUI
In addition to the command-line usage, this repository also provides a graphical user interface (GUI) for the randfixedsum algorithm. The GUI allows users to interactively specify the parameters and generate tasksets using the algorithm.

To use the GUI:
1. Open app.py
2. Open the terminal and run the following command:
```
python app.py
```
3. The GUI will run at the following address: http://127.0.0.1:5000


![image](https://github.com/VaiibhavThatai/TaskCraft-Empowered-TaskSet-Synthesis/assets/85902487/28f86656-ec04-40a5-a6e4-0ef8c1cae5db)


# Contributing
Contributions to this repository are welcome! If you have additional taskset generation algorithms or improvements to the existing ones, feel free to fork the repository and submit a pull request with your changes.


