#include <iostream>
#include <thread>
#include <vector>

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

int main() {
  std::vector<std::vector<int>> A{{1, 2, 3}, {4, 5, 6}};
  std::vector<int> x{7, 8, 9};

  std::vector<int> y = ProcessOperation2D(A, x);

  for (auto yi : y) {
    std::cout << yi << std::endl;
  }

  return 0;
}
