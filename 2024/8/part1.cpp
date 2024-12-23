#include <chrono>
#include <iostream>
#include "8.h"

int main() {
  const auto start = std::chrono::high_resolution_clock::now();
  auto [grid_size, antennas_positions] = process_char_grid("data.txt");
  
  std::cout << count_antinodes(grid_size, antennas_positions) << std::endl;
  const auto end = std::chrono::high_resolution_clock::now();
  const auto time_elapsed =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();
  std::cout << "Time in us: " << time_elapsed << std::endl;
  return 0;
}
