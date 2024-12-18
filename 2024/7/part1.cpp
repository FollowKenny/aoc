#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <functional>

using namespace std;

int main() {
  const auto start = chrono::high_resolution_clock::now();
  ifstream myfile("data.txt");
  long result = 0;
  string line;
  auto add = [](int a, int b){return a + b;};
  auto mult = [](int a, int b){return a * b;};


  if (myfile.is_open()) {
    while(getline(myfile, line)) {
      stringstream stream(line);
      string s;
      vector<long> numbers;

      while (stream >> s) {
        if (numbers.empty())
          s.pop_back();
        numbers.push_back(stol(s));
      }
      
      vector<long> cumulators = {numbers[1]};

      for (auto it = numbers.begin() + 2; it != numbers.end(); ++it) {
        vector<long> new_cum;
        for (auto &cumulator: cumulators) {
          new_cum.push_back(cumulator * (*it));
          new_cum.push_back(cumulator + (*it));
        }
        cumulators = new_cum;
      }

      for (const auto &cumulator: cumulators) { 
        if (cumulator == numbers[0]) {
          result += numbers[0];        
          break;
        }

      }
    }
    myfile.close();

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
