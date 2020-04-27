//에러코드!!
#include <iostream>
#include <vector>

template <typename T>
void print_vector(std::vector<T>& vec) {
  // 전체 벡터를 출력하기
  std::cout << "[ ";
  for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
       ++itr) {
    std::cout << *itr << " ";
  }
  std::cout << "]";
}
int main() {
  std::vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);
  vec.push_back(40);
  vec.push_back(20);

  std::cout << "처음 벡터 상태" << std::endl;
  print_vector(vec);

  std::vector<int>::iterator itr = vec.begin();
  std::vector<int>::iterator end_itr = vec.end();

  for (; itr != end_itr; ++itr) {
    if (*itr == 20) {
      vec.erase(itr);
    }
  }

  std::cout << "값이 20 인 원소를 지운다!" << std::endl;
  print_vector(vec);
}

// for (; itr != end_itr; itr++) {
//   if (*itr == 20) {
//     vec.erase(itr);
//   }
// }

// 문제는 바로 위 코드에서 발생합니다. 컨테이너에 원소를 추가하거나 제거하게 되면 기존에 사용하였던 모든 반복자들을 사용할 수 없게됩니다. 
// 다시 말해 위 경우 vec.erase(itr) 을 수행하게 되면 더이상 itr 은 유효한 반복자가 아니게 되는 것이지요. 또한 end_itr 역시 무효화 됩니다.

// 따라서 itr != end_itr 이 영원히 성립되며 무한 루프에 빠지게되어 위와 같은 오류가 발생합니다.

// 그렇다면

// std::vector<int>::iterator itr = vec.begin();
// for (; itr != vec.end(); itr++) {
//   if (*itr == 20) {
//     vec.erase(itr);
//   }
// }
// 와 같이 코드를 고치면 오류가 없어질까요? 실행해보시면 알겠지만 여전히 위와 같은 오류가 발생합니다. 
// 왜냐하면 itr 이 유효한 반복자가 아니기 때문에 vec.end() 로 올바른 end 반복자 값을 매번 가지고 와도 for 문이 끝나지 않게 되는 것입니다. 
// 결과적으로 코드를 제대로 고치려면 다음과 같이 해야 합니다.

// std::vector<int>::iterator itr = vec.begin();

// for (; itr != vec.end(); ++itr) {
//   if (*itr == 20) {
//     vec.erase(itr);
//     itr = vec.begin();
//   }
// }

// 사실 생각해보면 위 바뀐 코드는 꽤나 비효율적임을 알 수 있습니다. 
// 왜냐하면 20 인 원소를 지우고, 다시 처음으로 돌아가서 원소들을 찾고 있기 때문이지요. 
// 그냥 20 인 원소 바로 다음 위치 부터 찾아나가면 될 텐데 말입니다.

// for (std::vector<int>::size_type i = 0; i != vec.size(); i++) {
//   if (vec[i] == 20) {
//     vec.erase(vec.begin() + i);
//     i--;
//   }
// }

// 그렇다면 아예 위 처럼 굳이 반복자를 쓰지 않고 erase 함수에만 반복자를 바로 만들어서 전달하면 됩니다.
// vec.erase(vec.begin() + i);
// 를 하게 되면 vec[i] 를 가리키는 반복자를 erase 에 전달할 수 있습니다. 
// 하지만 사실 위 방법은 그리 권장하는 방법은 아닙니다. 
// 기껏 원소에 접근하는 방식은 반복자를 사용하는 것으로 통일하였는데, 
// 위 방법은 이를 모두 깨버리고 그냥 기존의 배열 처럼 정수형 변수 i 로 원소에 접근하는 것이기 때문입니다.

// 하지만 후에 C++ 알고리즘 라이브러리에 대해 배우면서 이 문제를 깔끔하게 해결 하는 방법에 대해 다루도록 할 것입니다. 
// 일단 임시로는 위 방법 처럼 처리하도록 하세요 :)

// vector 에서 지원하는 반복자로 const_iterator 가 있습니다. 이는 마치 const 포인터를 생각하시면 됩니다. 
// 즉, const_iterator 의 경우 가리키고 있는 원소의 값을 바꿀 수 없습니다. 예를 들어서