#include <chrono>
#include <deque>
#include <forward_list>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <string>
#include <vector>

const int SIZE = 100'000'000;

template<typename T>
void sumUp(T& t, const std::string& cont)
{
  std::cout << std::fixed << std::setprecision(10);

  const auto begin = std::chrono::steady_clock::now();
  const auto res   = std::accumulate(t.begin(), t.end(), 0LL);
  const auto last  = std::chrono::steady_clock::now() - begin;
  std::cout << cont << std::endl;
  std::cout << "time: " << last.count() << std::endl;
  std::cout << "res: " << res << std::endl;
  std::cout << std::endl;

  std::cout << std::endl;
}

int main()
{
  std::cout << std::endl;

  std::random_device                 seed;
  std::mt19937                       engine(seed());
  std::uniform_int_distribution<int> dist(0, 100);
  std::vector<int>                   randNum;
  randNum.reserve(SIZE);
  for(int i = 0; i < SIZE; ++i) { randNum.push_back(dist(engine)); }

  {
    std::vector<int> vec(randNum.begin(), randNum.end());
    sumUp(vec, "std::vector<int>");
  }

  {
    std::deque<int> deq(randNum.begin(), randNum.end());
    sumUp(deq, "std::deque<int>");
  }

  {
    std::list<int> lst(randNum.begin(), randNum.end());
    sumUp(lst, "std::list<int>");
  }

  {
    std::forward_list<int> forwardLst(randNum.begin(), randNum.end());
    sumUp(forwardLst, "std::forward_list<int>");
  }
}
