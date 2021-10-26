#include <fstream>
#include <iostream>
#include <vector>

#include "utils.cpp"

std::vector<int> Multiply(std::vector<std::vector<int>>& A,
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

  std::vector<int> y = Multiply(A, x);

  for (auto yi : y) {
    std::cout << yi << std::endl;
  }

  return EXIT_SUCCESS;
}
