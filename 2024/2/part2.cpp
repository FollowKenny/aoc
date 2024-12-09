#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils.h"
using namespace std;

int identifyAnomalies(vector<int> &locations,
                      const int &knownAnomalyLocation = -1) {
  auto lastTransitionPositive = true;
  auto anomalyLocation = -1;
  for (auto const [index, location] : views::enumerate(locations)) {
    if (index == knownAnomalyLocation) continue;
    if (index > 0) {
      auto transitionValue = 0;
      if (index != knownAnomalyLocation + 1)
        transitionValue = location - locations[index - 1];
      else
        transitionValue = location - locations[index - 2];
      const auto absTV = abs(transitionValue);
      const auto currentTransitionPositive = signbit(transitionValue);
      if ((absTV > 3 || absTV == 0) ||
          index > 1 && knownAnomalyLocation != 1 &&
              (currentTransitionPositive != lastTransitionPositive)) {
        anomalyLocation = index;
        break;
      }
      lastTransitionPositive = currentTransitionPositive;
    }
  }
  return anomalyLocation;
}

int main() {
  const auto start = chrono::high_resolution_clock::now();
  string line;
  ifstream myfile("data.tsv");

  int result = 0;

  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      vector<int> locations = splitOnSpaces(line);
      auto anomalyLocation = identifyAnomalies(locations);
      if (anomalyLocation != -1)
        anomalyLocation = identifyAnomalies(locations, anomalyLocation);
      if (anomalyLocation != -1)
        anomalyLocation = identifyAnomalies(locations, anomalyLocation - 1);

      if (anomalyLocation == -1) result++;
    }
    myfile.close();

    cout << result << endl;
    const auto end = chrono::steady_clock::now();
    const auto time_elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
    cout << "Time in us: " << time_elapsed << endl;
  } else
    cout << "Unable to open file";

  return 0;
}
