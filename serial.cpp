#include <iostream>
#include <vector>

std::vector<int> multiply(std::vector<std::vector<int>>& A,
                          std::vector<int>& x) {
  int m = A.size();     // rows
  int n = A[0].size();  // columns

  std::vector<int> y(m, 0);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      y[i] += A[i][j] * x[j];
    }
  }

  return y;
}

int main() {
  std::vector<std::vector<int>> A{{1, 2, 3}, {4, 5, 6}};
  std::vector<int> x{7, 8, 9};

  std::vector<int> y = multiply(A, x);

  for (auto yi : y) {
    std::cout << yi << std::endl;
  }

  return 0;
}
