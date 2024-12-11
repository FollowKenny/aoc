#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>

#include "utils.h"
using namespace std;

int main() {
  const auto start = chrono::high_resolution_clock::now();
  string line;
  ifstream myfile("data.txt");

  int result = 0;
  regex mul_regex("mul\\([0-9]+,[0-9]+\\)");
  regex number_regex("[0-9]+");

  if (myfile.is_open()) {
    while (getline(myfile, line)) {

        auto mul_iterator = sregex_iterator(line.begin(), line.end(), mul_regex);
        auto mul_endit = sregex_iterator();

        for (sregex_iterator i = mul_iterator; i != mul_endit; ++i)
        {
            vector<int> numbers;
            auto mul = i->str();
            auto num_iterator = sregex_iterator(mul.begin(), mul.end(), number_regex);
            auto num_endit = sregex_iterator();

            for (;num_iterator != num_endit; ++num_iterator)
                numbers.push_back(stoi(num_iterator->str()));
            
            result += numbers[0] * numbers[1];
        }

    }
    myfile.close();

    cout << result << endl;
    const auto end = chrono::high_resolution_clock::now();
    const auto time_elapsed =
        chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
    cout << "Time in us: " << time_elapsed << endl;
  } else
    cout << "Unable to open file";

  return 0;
}
