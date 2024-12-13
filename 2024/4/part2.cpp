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
        if (charGrid[i][j] == 'A' && i > 0 && i < n_lines - 1 && j > 0 && j < n_cols - 1) {
          auto count_mas = 0;
          auto possible_lines = {i-1, i+1};
          auto possible_cols = {j-1, j+1};
          for (const auto l : possible_lines){
            for (const auto c : possible_cols){
              if (charGrid[l][c] == 'M') {
                if (charGrid[i - (l-i)][j - (c-j)] == 'S') {
                  count_mas++;
                }
              }
            }
          }
          if (count_mas == 2) result++;
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
