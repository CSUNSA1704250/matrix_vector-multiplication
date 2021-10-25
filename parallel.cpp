#include <iostream>
#include <thread>
#include <vector>

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
  int thread_count = 2;

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

int main() {
  std::vector<std::vector<int>> A{{1, 2, 3}, {4, 5, 6}};
  std::vector<int> x{7, 8, 9};

  std::vector<int> y = ProcessOperation1D(A, x);

  for (auto yi : y) {
    std::cout << yi << std::endl;
  }

  return 0;
}
