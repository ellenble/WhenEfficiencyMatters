#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class BigArray {
public:
  BigArray(size_t len)
  : len_{len}
  , data_{new int[len]}
  {}

  BigArray(const BigArray& other)
  : len_{other.len_}
  , data_{new int[other.len_]}
  {
    cout << "Copy construction of " << other.len_ << " elements " << endl;
    std::copy(other.data_, other.data_ + len_, data_);
  }

  BigArray& operator=(const BigArray& other)
  {
    cout << "Copy assignment of " << other.len_ << " elements " << endl;
    if(this != &other) {
      delete[] data_;

      len_  = other.len_;
      data_ = new int[len_];
      std::copy(other.data_, other.data_ + len_, data_);
    }

    return *this;
  }

  BigArray(BigArray&& other)
  : len_{other.len_}
  , data_{other.data_}
  {
    cout << "Move construction of " << other.len_ << " elements " << endl;
    other.len_  = 0;
    other.data_ = nullptr;
  }

  BigArray& operator=(BigArray&& other)
  {
    cout << "Move assignment of " << other.len_ << " elements " << endl;
    if(this != &other) {
      int* tmp = data_;

      len_  = other.len_;
      data_ = other.data_;

      other.data_ = tmp;
      other.len_  = 0;
    }

    return *this;
  }

  ~BigArray() { delete[] data_; }

private:
  size_t len_;
  int*   data_;
};

int main()
{
  std::vector<BigArray> myVec{};
  myVec.reserve(2);

  myVec.push_back(BigArray{1'000'000'000});
}
