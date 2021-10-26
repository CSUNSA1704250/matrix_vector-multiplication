[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6091620&assignment_repo_type=AssignmentRepo)

## Run
```sh
chmod +x test.sh
./test.sh
```

## Results
```sh
~PD/Practices/matrix_vector-multiplication main* ⇡
❯ ./test.sh      
> Generate test matrices and vectors if no test data found.
generate 5x4 matrix...
generate 4x1 vector...
generate 1000x1000 matrix...
generate 1000x1 vector...

> Compile source code.
g++-11 -std=c++17 -fopenmp -o bin/serial.out src/serial.cpp
g++-11 -std=c++17 -fopenmp -o bin/parallel.out src/parallel.cpp
g++-11 -std=c++17 -fopenmp -o bin/parallel2D.out src/parallel2D.cpp

> Calculate.
5x1
* Serial:
Elapsed time in milliseconds: 0.001

* Parallel:
Elapsed time in milliseconds: 0.165

* 2D partitioning:
Elapsed time in milliseconds: 0.533


1000x1
* Serial:
Elapsed time in milliseconds: 4.888

* Parallel:
Elapsed time in milliseconds: 1.605
```
