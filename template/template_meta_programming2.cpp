// 다시 한 번 말하지만, 마치 Ratio 클래스의 객체를 생성한 것 같지만, 
// 실제로 생성된 객체는 한 개도 없고, 단순히 타입들을 컴파일러가 만들어낸 것 뿐입니다.

// 마찬가지 방법으로 모든 사칙연산들을 구현하자면 아래와 같습니다.

#include <iostream>

template <int X, int Y>
struct GCD {
  static const int value = GCD<Y, X % Y>::value;
};

template <int X>
struct GCD<X, 0> {
  static const int value = X;
};

template <int N, int D = 1>
struct Ratio {
 private:
  const static int _gcd = GCD<N, D>::value;

 public:
  typedef Ratio<N / _gcd, D / _gcd> type;
  static const int num = N / _gcd;
  static const int den = D / _gcd;
};
template <class R1, class R2>
struct _Ratio_add {
  using type = Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den>;//typedef 대신 using을 쓸 수 있음
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_subtract {
  using type = Ratio<R1::num * R2::den - R2::num * R1::den, R1::den * R2::den>;
};

template <class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_multiply {
  using type = Ratio<R1::num * R2::num, R1::den * R2::den>;
};

template <class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_divide {
  using type = Ratio<R1::num * R2::den, R1::den * R2::num>;
};

template <class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};

int main() {
  using r1 = Ratio<2, 3>;
  using r2 = Ratio<3, 2>;

  using r3 = Ratio_add<r1, r2>;
  std::cout << "2/3 + 3/2 = " << r3::num << " / " << r3::den << std::endl;

  using r4 = Ratio_multiply<r1, r3>;
  std::cout << "13 / 6 * 2 /3 = " << r4::num << " / " << r4::den << std::endl;
}