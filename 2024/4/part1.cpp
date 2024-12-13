#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  const auto start = chrono::high_resolution_clock::now();
  ifstream myfile("data.txt");
  auto result = 0;
  string line;
  vector<vector<char>> charGrid;

  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      charGrid.emplace_back(line.begin(), line.end());
    }
    myfile.close();

    int n_lines = charGrid.size();

    for(auto i = 0; i < n_lines; ++i) {
      auto n_cols = charGrid[i].size();
      for(auto j = 0; j < n_cols; ++j) {
        if (charGrid[i][j] == 'X') {
          for (auto k = max(i - 1, 0); k < min(i + 2, n_lines); k++) {
            for (auto l = max(j - 1, 0); l < min(j + 2, n_lines); l++) {
              if (charGrid[k][l] == 'M') {
                if (k + 2*(k - i) >= 0 && k + 2*(k - i) < n_lines &&  l + 2*(l - j) >= 0 && l + 2*(l - j) < n_cols &&
                  charGrid[k + (k - i)][l + (l - j)] == 'A' &&
                  charGrid[k + 2*(k - i)][l + 2*(l - j)] == 'S')
                  result++;
              }
            }
          }
        }
      }
    }
    cout << result << endl;
    const auto end = chrono::high_resolution_clock::now();
    const auto time_elapsed =
        chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
    cout << "Time in us: " << time_elapsed << endl;
  }

  else
    cout << "Unable to open file";

  return 0;
}
