#include <istream>
#include <sstream>
#include <string>
#include <vector>

void LoadVector(std::istream* s, std::vector<int>* vector) {
  int num;
  while (*s >> num) {
    vector->push_back(num);
  }
}
void LoadMatrix(std::istream* s, std::vector<std::vector<int>>* matrix) {
  std::string lineData;

  while (getline(*s, lineData)) {
    int d;
    std::vector<int> row;
    std::stringstream lineStream(lineData);

    while (lineStream >> d) row.push_back(d);

    matrix->push_back(row);
  }
}