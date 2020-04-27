// 마지막으로 보여드릴 것은, 클래스 자체에 operator< 를 두지 않더라도 셋을 사용하는 방법입니다. 
// 예를 들어서 우리가 외부 라이브러리를 사용하는데, 만약에 그 라이브러리의 한 클래스의 객체를 셋에 저장하고 싶다고 해봅시다. 
// 우리가 사용하는 외부 클래스에 operator< 가 정의되어 있지 않다는 점입니다. 
// 이럴 경우, 셋을 사용하기 위해서는 따로 객체를 비교할 수 있는 방법을 알려주어야 합니다.

// 아래 예제를 보실까요.

#include <iostream>
#include <set>
#include <string>

template <typename T, typename C>
void print_set(std::set<T, C>& s) {
  // 셋의 모든 원소들을 출력하기
  for (const auto& elem : s) {
    std::cout << elem << " " << std::endl;
  }
}
class Todo {
  int priority;
  std::string job_desc;

 public:
  Todo(int priority, std::string job_desc)
      : priority(priority), job_desc(job_desc) {}

  friend struct TodoCmp;

  friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};
struct TodoCmp {
  bool operator()(const Todo& t1, const Todo& t2) const {//마지막 const는 연산 후 값이 수정되지 못하게 막아줌 즉 누가 true, false값을 변경 못하게함
    if (t1.priority == t2.priority) {
      return t1.job_desc < t2.job_desc;
    }
    return t1.priority > t2.priority;
  }
};

std::ostream& operator<<(std::ostream& o, const Todo& td) {
  o << "[ 중요도: " << td.priority << "] " << td.job_desc;
  return o;
}
int main() {
  std::set<Todo, TodoCmp> todos;
//   위 클래스는 정확히 함수 객체를 나타내고 있습니다. 이 TodoCmp 타입을
//   std::set<Todo, TodoCmp> todos;
// 위 처럼 set 에 두번째 인자로 넘겨주게 되면 셋은 이를 받아서 TodoCmp 클래스에 정의된 함수 객체를 바탕으로 모든 비교를 수행하게 됩니다. 
// 실제로 set 클래스의 정의를 살펴보면;
// template <class Key, class Compare = std::less<Key>,
//           class Allocator = std::allocator<Key>  // ← 후에 설명하겠습니다
//           >
// class set;
// 와 같이 생겼는데, 두 번째 인자로 Compare 를 받는 다는 것을 알 수 있습니다. 
// (템플릿 디폴트 인자로 std::less<Key> 가 들어있는데 이는 Key 클래스의 operator< 를 사용한다는 의미와 같습니다. 
// Compare 타입을 전달하지 않으면 그냥 Key 클래스의 operator< 로 비교를 수행합니다.)

// 결과적으로 셋은 원소의 삽입과 삭제를 O(log N) 원소의 탐색도 O(log N) 에 수행하는 자료 구조 입니다.

  todos.insert(Todo(1, "농구 하기"));
  todos.insert(Todo(2, "수학 숙제 하기"));
  todos.insert(Todo(1, "프로그래밍 프로젝트"));
  todos.insert(Todo(3, "친구 만나기"));
  todos.insert(Todo(2, "영화 보기"));

  print_set(todos);

  std::cout << "-------------" << std::endl;
  std::cout << "숙제를 끝냈다면!" << std::endl;
  todos.erase(todos.find(Todo(2, "수학 숙제 하기")));
  print_set(todos);
}