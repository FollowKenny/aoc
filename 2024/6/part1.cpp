#include <chrono>
#include <iostream>
#include "agent.h"

int main() {
  const auto start = chrono::high_resolution_clock::now();
  auto [char_grid, agent_pos, agent_dir] = process_char_grid("data.txt");
  auto agent = Agent(agent_pos, agent_dir, char_grid);
  agent.run_through();
  
  cout << agent.n_visited << endl;
  const auto end = chrono::high_resolution_clock::now();
  const auto time_elapsed =
      chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();
  cout << "Time in us: " << time_elapsed << endl;
  return 0;
}
