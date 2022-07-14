// 다행이도 C++ 에서는 protected 라는 public 과 private 에 중간 위치에 있는 접근 지시자를 지원합니다. 이 키워드는, 상속받는 클래스에서는 접근 가능하고 그 외의 기타 정보는 접근 불가능 이라고 보시면 됩니다. 부모(기반 클래스) 와 자식(파생 클래스) 으로 쉽게 비유하자면

// private : (부모님들한테 안가르쳐 주는) 자신만의 비밀번호

// protected : 집 현관문 비밀번호 ( 가족들은 알지만 그 외의 사람들은 접근불가)

// public : 집 주소 (가족 뿐만이 아니라 다른 사람들도 알 수 있다)

// class Derived : public Base
// 에서 이 public 키워드의 의미를 밝힐 때가 됐군요. 사실 저 키워드가 public 이냐 protected 냐 private 이냐에 따라 상속 받는 클래스에서 기반 클래스의 멤버들이 실제로 어떻게 작동하는지 영향을 줍니다. 이게 무슨 말이냐면

// 만일 위처럼 public 형태로 상속 하였다면 기반 클래스의 접근 지시자들에 영향 없이 그대로 작동합니다. 즉 파생 클래스 입장에서 public 은 그대로 public 이고, protected 는 그대로 protected 이고, private 은 그대로 private 입니다.

// 만일 protected 로 상속하였다면 파생 클래스 입장에서 public 은 protected 로 바뀌고 나머지는 그대로 유지됩니다.

// 만일 private 으로 상속하였다면 파생 클래스 입장에서 모든 접근 지시자들이 private 가 됩니다.

#include <iostream>
#include <string>

class Employee {
 protected:
  std::string name;
  int age;

  std::string position;  // 직책 (이름)
  int rank;              // 순위 (값이 클 수록 높은 순위)

 public:
  Employee(std::string name, int age, std::string position, int rank)
      : name(name), age(age), position(position), rank(rank) {}

  // 복사 생성자
  Employee(const Employee& employee) {
    name = employee.name;
    age = employee.age;
    position = employee.position;
    rank = employee.rank;
  }

  // 디폴트 생성자
  Employee() {}

  void print_info() {
    std::cout << name << " (" << position << " , " << age << ") ==> "
              << calculate_pay() << "만원" << std::endl;
  }
  int calculate_pay() { return 200 + rank * 50; }
};
//상속하는 클래스
class Manager : public Employee {
  int year_of_service;

 public:
  Manager(std::string name, int age, std::string position, int rank,
          int year_of_service)
      : Employee(name, age, position, rank), year_of_service(year_of_service) {}

  // 복사 생성자
  Manager(const Manager& manager)
      : Employee(manager.name, manager.age, manager.position, manager.rank) {
    year_of_service = manager.year_of_service;
  }

  // 디폴트 생성자
  Manager() : Employee() {}

  int calculate_pay() { return 200 + rank * 50 + 5 * year_of_service; }
  void print_info() {
    std::cout << name << " (" << position << " , " << age << ", "
              << year_of_service << "년차) ==> " << calculate_pay() << "만원"
              << std::endl;
  }
};
class EmployeeList {
  int alloc_employee;  // 할당한 총 직원 수

  int current_employee;  // 현재 직원 수
  int current_manager;   // 현재 매니저 수

  Employee** employee_list;  // 직원 데이터
  Manager** manager_list;    // 매니저 데이터

 public:
  EmployeeList(int alloc_employee) : alloc_employee(alloc_employee) {
    employee_list = new Employee*[alloc_employee];
    manager_list = new Manager*[alloc_employee];

    current_employee = 0;
    current_manager = 0;
  }
  void add_employee(Employee* employee) {
    // 사실 current_employee 보다 alloc_employee 가 더
    // 많아지는 경우 반드시 재할당을 해야 하지만, 여기서는
    // 최대한 단순하게 생각해서 alloc_employee 는
    // 언제나 current_employee 보다 크다고 생각한다.
    // (즉 할당된 크기는 현재 총 직원수 보다 많음)
    employee_list[current_employee] = employee;
    current_employee++;
  }
  void add_manager(Manager* manager) {
    manager_list[current_manager] = manager;
    current_manager++;
  }
  int current_employee_num() { return current_employee + current_manager; }

  void print_employee_info() {
    int total_pay = 0;
    for (int i = 0; i < current_employee; i++) {
      employee_list[i]->print_info();
      total_pay += employee_list[i]->calculate_pay();
    }
    for (int i = 0; i < current_manager; i++) {
      manager_list[i]->print_info();
      total_pay += manager_list[i]->calculate_pay();
    }
    std::cout << "총 비용 : " << total_pay << "만원 " << std::endl;
  }
  ~EmployeeList() {
    for (int i = 0; i < current_employee; i++) {
      delete employee_list[i];
    }
    for (int i = 0; i < current_manager; i++) {
      delete manager_list[i];
    }
    delete[] employee_list;
    delete[] manager_list;
  }
};
int main() {
  EmployeeList emp_list(10);
  emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
  emp_list.add_employee(new Employee("하하", 34, "평사원", 1));
  emp_list.add_manager(new Manager("유재석", 41, "부장", 7, 12));
  emp_list.add_manager(new Manager("정준하", 43, "과장", 4, 15));
  emp_list.add_manager(new Manager("박명수", 43, "차장", 5, 13));
  emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
  emp_list.add_employee(new Employee("길", 36, "인턴", -2));
  emp_list.print_employee_info();
  return 0;
}