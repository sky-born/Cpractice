// const[1] data-type operator operator-name (const[2] operand) const[3] { function activity ... }
// (ex) const Time operator + (const Time&) const { 임시 Time 객체를 이용하여 처리한 뒤 임시 객체를 반환 }
// 보다시피, 익숙한 연산자 오버로딩 문장이다. 여기서 const는 총 3번 사용되었으며, 각각의 const는 다 쓰임이 다르다. 
// 쉬운 이해를 위해 순서대로 설명하지 않겠다. 여기서는 시간 데이터를 저장하는 자료형 Time을 가정하여, Time 객체끼리의 더하기 연산을 오버로딩하는 상황을 가정해보겠다. 
// 즉, Time 객체 A,B,C가 있다고 가정할 때, A=B+C; 같은 문장이 유효하게끔 하는 처리이다.
// [3] 위의 연산자는 클래스 메소드로서 연산자를 정의한 것이다. 따라서 이 const가 영향을 미치는 것은 {} 내에서 활동하는 호출 객체에 영향을 미치는 것이다.
//  즉 B+C라는 수식이 있다면, B에 영향을 미치는 것이 [3]의 const이다. 호출 객체의 값이 method 실행 과정에서 수정되는 일이 없도록 제한을 걸어준다.
// [2] 피연산자에 영향을 미치는 const이다. 즉 B+C라는 수식이 있다면, C에 영향을 미치는 것이 [2]의 const이다. 
// 일반적으로 피연산자는 매개변수로서 넘어올 때 레퍼런스(&)로 넘어오기 때문에 값이 수정될 가능성이 있다. 따라서 const를 걸어줌으로써 값이 수정될 여지를 없애주는 것이다.
// [1] 연산이 완료된 뒤 반환(return)되는 값이 수정되지 않도록 해준다. 즉 B+C라는 수식이 있다면, (B+C) = 5; 와 같은 수식이 성립되지 않도록 하는 것이다.
//  위에 예시에 적었듯이 연산이 완료된 뒤에 반환되는 것은 임시 객체, 즉 변수이다. 지역 변수이기에 오류인 것은 두말할 것도 없고, 
//  설사 전역 변수가 반환된다고 할 지라도 쓰기가 안되게 만들어야 연산 결과를 보장할 수 있다.


// 상수 멤버 함수
#include <iostream>

class Marine {
  static int total_marine_num;//static은 class 전체에 하나밖에 존재안함
  const static int i = 0;//const는 변하지 않음

  int hp;                // 마린 체력
  int coord_x, coord_y;  // 마린 위치
  bool is_dead;

  const int default_damage;  // 기본 공격력

 public:
  Marine();              // 기본 생성자
  Marine(int x, int y);  // x, y 좌표에 마린 생성
  Marine(int x, int y, int default_damage);

  int attack() const;                    // 데미지를 리턴한다. const function 선언 -> 함수이름뒤 const
  Marine& be_attacked(int damage_earn);  // 입는 데미지 Marine ref를 리턴함
  void move(int x, int y);               // 새로운 위치

  void show_status();  // 상태를 보여준다.
  static void show_total_marine();
  ~Marine() { total_marine_num--; }
};
int Marine::total_marine_num = 0;
void Marine::show_total_marine() {
  std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}
Marine::Marine()
    : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
  total_marine_num++;
}

Marine::Marine(int x, int y)
    : coord_x(x),
      coord_y(y),
      hp(50),

      default_damage(5),
      is_dead(false) {
  total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage)
    : coord_x(x),
      coord_y(y),
      hp(50),
      default_damage(default_damage),
      is_dead(false) {
  total_marine_num++;
}

void Marine::move(int x, int y) {
  coord_x = x;
  coord_y = y;
}
int Marine::attack() const { return default_damage; }//const 함수
Marine& Marine::be_attacked(int damage_earn) {
  hp -= damage_earn;//== this->hp -= datmage_earn;
  if (hp <= 0) is_dead = true;//== if(this->hp<=0) this->is_dead = true;

  return *this;//this pointer는 함수를 부른 객체를 지정 포인터기때문에 *을 붙여 사용
}
void Marine::show_status() {
  std::cout << " *** Marine *** " << std::endl;
  std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
            << std::endl;
  std::cout << " HP : " << hp << std::endl;
  std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

int main() {
  Marine marine1(2, 3, 5);
  marine1.show_status();

  Marine marine2(3, 5, 10);
  marine2.show_status();

  std::cout << std::endl << "마린 1 이 마린 2 를 두 번 공격! " << std::endl;
  marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());//attacked 함수가 Marin class reference를 리턴하기 때문에 이렇게 할 수 있음

  marine1.show_status();
  marine2.show_status();
}