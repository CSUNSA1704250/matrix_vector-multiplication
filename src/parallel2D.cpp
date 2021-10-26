#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include "utils.cpp"

void PartialResults(int a, int b, std::vector<int>& temp, int i) {
  temp[i] = a * b;
}

std::vector<int> ProcessOperation2D(std::vector<std::vector<int>>& A,
                                    std::vector<int>& x) {
  int m = A.size();
  int n = A[0].size();

  // number of processes
  int processes = m * n;

  // temporal for partial results
  std::vector<int> temp(processes, 0);

  // spawn threads
  std::vector<std::thread> pool_threads;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      pool_threads.push_back(std::thread(PartialResults, A[i][j], x[j],
                                         std::ref(temp), i * n + j));
    }
  }

  // sync threads
  for (auto& t : pool_threads) {
    t.join();
  }

  // Ax = y
  std::vector<int> y(m, 0);

  // start reduction
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      y[i] += temp[i * n + j];
    }
  }

  return y;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Please follow template. Specify two files." << std::endl;
    std::cout << "./serial.out <matrix_A> <vector_x>" << std::endl;

    return EXIT_FAILURE;
  }

  std::ifstream is1(argv[1]);
  std::ifstream is2(argv[2]);

  std::vector<std::vector<int>> A;
  LoadMatrix(&is1, &A);

  std::vector<int> x;
  LoadVector(&is2, &x);

  auto start = std::chrono::steady_clock::now();
  std::vector<int> y = ProcessOperation2D(A, x);
  auto end = std::chrono::steady_clock::now();

  auto diff = end - start;

  std::cout << "Elapsed time in milliseconds: "
            << std::chrono::duration<double, std::milli>(diff).count()
            << std::endl;
  std::cout << std::endl;

  /*
  for (auto yi : y) {
    std::cout << yi << std::endl;
  }
  */

  return 0;
}
