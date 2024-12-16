#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main() {
  const auto start = chrono::high_resolution_clock::now();
  ifstream myfile("data.txt");
  auto result = 0;
  string line;
  string number;
  auto update_section = false;
  map<int, set<int>> order_rules;

  if (myfile.is_open()) {
    while(getline(myfile, line)) {
      istringstream ss(line);
      vector<int> numbers;
      if (line.empty()) {
        update_section = true;
        continue;
      }
      if (update_section) {
        auto valid_update = true;

        while(getline(ss, number, ','))
          numbers.push_back(stoi(number));

        for (auto it = numbers.rbegin(); it != numbers.rend(); ++it) {
          for (auto jt = it + 1; jt != numbers.rend(); ++jt) {
            if (order_rules[*it].contains(*jt)) {
              valid_update = false;
              swap(*it, *jt);
              jt = it;
            }
          }
        }

        if (!valid_update) {
          result += numbers[(int)numbers.size() / 2];
        }

      } else {  
        while(getline(ss, number, '|'))
          numbers.push_back(stoi(number));
        order_rules[numbers[0]].insert(numbers[1]);
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
