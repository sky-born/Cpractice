#include <iostream>
#include <string>
#include <memory>

/* 
smart pointer
which pointers don't require free memory or resource

type: unique_ptr, shared_ptr
*/
int main() {
  int i;
  // use of unique_ptr
  auto ints = std::make_unique<int[]>(10);
  auto ints_2 = std::make_unique<int>();
  *ints_2 = 5;
  for(i=0;i<10;i++)
  {
    ints[i]=i;
  }
  std::cout<< ints[4]<<std::endl;
  std::cout<< *ints_2<<std::endl;

  //use of shared_ptr
  std::shared_ptr<int[]> ints_3(new int[10]);
  auto ints_4 = std::make_shared<int>();
  *ints_4 = 7;
  for(i=0;i<10;i++)
  {
    ints_3[i]=i;
  }
  std::cout<< ints_3[2]<<std::endl;
  std::cout<< *ints_4<<std::endl;

  return 0;
}