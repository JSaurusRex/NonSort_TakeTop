#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <vector>

#define ARRAY1_SIZE 1024*1024*256

int main() {
  std::vector<int> vRandom;
  vRandom.reserve(ARRAY1_SIZE);
  for (int i = 0; i < ARRAY1_SIZE; ++i)
    vRandom.emplace_back(rand());
  auto StartTime = std::chrono::steady_clock::now();
  std::sort(vRandom.begin(), vRandom.end());
  auto EndTime = std::chrono::steady_clock::now();
  printf("Time: %ld\n", std::chrono::duration_cast<std::chrono::milliseconds>(
                            EndTime - StartTime)
                            .count());
}