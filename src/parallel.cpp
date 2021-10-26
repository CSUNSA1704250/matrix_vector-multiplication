#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include "utils.cpp"

void Multiply(std::vector<std::vector<int>>& A, int first, int last,
              std::vector<int>& x, std::vector<int>& y) {
  int n = A[0].size();  // columns

  for (int i = first; i <= last; i++) {
    for (int j = 0; j < n; j++) {
      y[i] += A[i][j] * x[j];
    }
  }
}

std::vector<int> ProcessOperation1D(std::vector<std::vector<int>>& A,
                                    std::vector<int>& x) {
  int m = A.size();
  int thread_count = 5;

  // NOTE! Asumming m is divisible by t
  int local_m = m / thread_count;

  // Ax = y
  std::vector<int> y(m, 0);

  // spawn threads
  std::vector<std::thread> pool_threads;
  for (int i = 0; i < thread_count; i++) {
    int first_component = i * local_m;
    int last_component = (i + 1) * local_m - 1;
    pool_threads.push_back(std::thread(Multiply, std::ref(A), first_component,
                                       last_component, std::ref(x),
                                       std::ref(y)));
  }

  // sync threads
  for (auto& t : pool_threads) {
    t.join();
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
  std::vector<int> y = ProcessOperation1D(A, x);
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
