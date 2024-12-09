#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils.h"
using namespace std;

pair<bool, int> analyzeTransition(const int &currN, const int &prevN,
                                  const int &prevT, const int &nTransition) {
  auto currT = currN - prevN;
  auto absCurrT = abs(currT);
  auto isTValid = true;

  if ((absCurrT == 0 || absCurrT > 3) ||
      (nTransition > 2 && (signbit(currT) != signbit(prevT)))) {
    isTValid = false;
  }

  return pair(isTValid, currT);
}

int main() {
  const auto start = chrono::high_resolution_clock::now();
  char c;
  string readNumber;
  auto previousNumber = -1;
  auto currentNumber = -1;
  ifstream myfile("data.tsv");
  auto isSequenceValid = true;
  int numberOfValidSequence = 0;
  int lastTransition = 0;
  int numberOfTransition = 0;

  if (myfile.is_open()) {
    while (myfile.get(c)) {
      if (!isSequenceValid) {
        if (c == '\n') {
          previousNumber = currentNumber = -1;
          lastTransition = numberOfTransition = 0;
          readNumber.clear();
          isSequenceValid = true;
        } else {
          continue;
        }
      } else {
        if (c == '\n' || c == ' ') {
          numberOfTransition++;
          previousNumber = currentNumber;
          currentNumber = stoi(readNumber);
          readNumber.clear();
          if (numberOfTransition > 1)
            tie(isSequenceValid, lastTransition) =
                analyzeTransition(currentNumber, previousNumber, lastTransition,
                                  numberOfTransition);
          if (c == '\n') {
            if (isSequenceValid) numberOfValidSequence++;
            previousNumber = currentNumber = -1;
            lastTransition = numberOfTransition = 0;
            isSequenceValid = true;
          }
        } else
          readNumber.push_back(c);
      }
    }
    myfile.close();

    cout << numberOfValidSequence << endl;
    const auto end = chrono::steady_clock::now();
    const auto time_elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
    cout << "Time in us: " << time_elapsed << endl;
  }

  else
    cout << "Unable to open file";

  return 0;
}
