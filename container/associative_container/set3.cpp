// 위와 같이 기본 타입들 말고, 여러분이 만든 클래스의 객체를 셋의 원소로 사용할 때 한 가지 주의해야 할 점이 있습니다.
//  아래는 할 일 (Todo) 목록을 저장하기 위해 셋을 사용하는 예시 입니다. 
//  Todo 클래스는 2 개를 멤버 변수로 가지는데 하나는 할 일의 중요도이고, 하나는 해야할 일의 설명 입니다.

// 앞서 셋은 원소들을 저장할 때 내부적으로 정렬된 상태를 유지한다고 하였습니다. 
// 즉 정렬을 하기 위해서는 반드시 원소 간의 비교를 수행해야 겠지요. 하지만, 우리의 Todo 클래스에는 operator< 가 정의되어 있지 않습니다.
//  따라서 컴파일러는 < 연산자를 찾을 수 없기에 위와 같은 오류를 뿜어내는 것입니다.

// 그렇다면 직접 Todo 클래스에 operator< 를 만들어주는 수 밖에 없습니다.

#include <iostream>
#include <set>
#include <string>

template <typename T>
void print_set(std::set<T>& s) {
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

  bool operator<(const Todo& t) const {//마지막 const는 A<B 에서 A가 const임을 나타냄
    if (priority == t.priority) {
      return job_desc < t.job_desc;
    }
    return priority > t.priority;
  }

  friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};

std::ostream& operator<<(std::ostream& o, const Todo& td) {
  o << "[ 중요도: " << td.priority << "] " << td.job_desc;
  return o;
}
int main() {
  std::set<Todo> todos;

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

// 셋이서 < 를 사용하기 위해서는 반드시 위와 같은 형태로 함수를 작성해야 합니다. 
// 즉 const Todo 를 레퍼런스로 받는 const 함수로 말이지요. 
// 이를 지켜야 하는 이유는 셋 내부적으로 정렬 시에 상수 반복자를 사용하기 때문입니다. 
// (상수 반복자는 상수 함수만을 호출할 수 있습니다 . 이를 지켜야 하는 이유는 셋 내부적으로 정렬 시에 상수 반복자를 사용하기 때문입니다
// . (상수 반복자는 상수 함수만을 호출할 수 있습니다)

// 한 가지 유의해야 할 점은 셋 내부에서 두 개의 원소가 같냐 다르냐를 판별하기 위해서 == 를 이용하지 않는다는 점입니다. 
// 두 원소 A 와 B 가 셋 내부에서 같다는 의미는 A.operator<(B) 와 B.operator<(A) 가 모두 false 라는 뜻입니다. 
// (예를 들어서 a 와 b 가 값이 같다고 하면 a < b 가 false 이고 b < a 도 false 이므로 a == b 이라 생각함)

// 만약에 우리가 중요도가 같을 때 따로 처리하지 않고 그냥
// bool operator<(const Todo& t) const { return priority > t.priority; }
// 게 했다면 어떻게 되었을까요? 그 결과는 아래와 같습니다.
// 중요도가 같은 애들은 추가 되지 않습니다. 왜냐하면 앞서 말했듯이 셋에는 중복된 원소를 허락하지 않습니다.