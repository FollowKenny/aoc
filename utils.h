#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>
#include <vector>

using namespace std;

inline vector<int> splitOnSpaces(const string &input) {
  stringstream stream(input);
  string s;
  vector<int> res;
  while (stream >> s) {
    res.push_back(stoi(s));
  }
  return res;
}

#endif
