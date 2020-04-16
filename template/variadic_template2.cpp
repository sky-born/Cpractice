#include <cstring>
#include <iostream>
#include <string>

size_t GetStringSize(const char* s) { return strlen(s); }

size_t GetStringSize(const std::string& s) { return s.size(); }

template <typename String, typename... Strings>
size_t GetStringSize(const String& s, Strings... strs) {
  return GetStringSize(s) + GetStringSize(strs...);
}

void AppendToString(std::string* concat_str) { return; }

template <typename String, typename... Strings>
void AppendToString(std::string* concat_str, const String& s, Strings... strs) {
  concat_str->append(s);
  AppendToString(concat_str, strs...);
}

// AppendToString 의 첫 번째 인자로는 합쳐진 문자열을 보관할 문자열을 계속 전달하고, 그 뒤로 합칠 문자열들을 인자로 전달하게 됩니다. 
// 그리고 재귀 호출의 맨 마지막 단계로 strs... 가 아무 인자도 없을 때 까지 진행하므로, 
// 재귀 호출을 끝내기 위해선 AppendToString(std::string* concat_str) 을 만들어줘야 겠지요.

template <typename String, typename... Strings>
std::string StrCat(const String& s, Strings... strs) {
  // 먼저 합쳐질 문자열의 총 길이를 구한다.
  size_t total_size = GetStringSize(s, strs...);

  // reserve 를 통해 미리 공간을 할당해 놓는다.
  std::string concat_str;
  concat_str.reserve(total_size);

  concat_str = s;
  AppendToString(&concat_str, strs...);

  return concat_str;
}

int main() {
  // std::string 과 const char* 을 혼합해서 사용 가능하다.
  std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"),
                      " ", std::string("sentence"));
}