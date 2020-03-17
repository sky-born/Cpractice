#include<iostream>
#include<string>

std::string asdf("Hello world!2");
class Str
{
  private:
  char *str;
  public:
  Str(const char chractor);
  Str(const char *string);
  int strlen();
  int strlen(const char*string);
  // char *strcat(const char *next_string);
  char *itself();
  // bool strcmp(const char *cmp_string);
  ~Str();
};

Str::Str(const char charactor)
{
  str=new char[2];
  *str=charactor;
  *(str+1)='\0';
}

Str::Str(const char *string)
{
  int len=strlen(string);
  str=new char[len+1];
  for(int i=0;i<len;i++)
  {
    *(str+i)=*(string+i);
  }
  *(str+len)='\0';
}

Str::~Str()
{
  delete[] str;
}

int Str::strlen()
{
  int i;
  for(i=0;;i++)
  {
    if(*(str+i)=='\0') break;
  }
  return i;
}

int Str::strlen(const char *string)
{
  int i;
  for(i=0;;i++)
  {
    if(*(string+i)=='\0') break;
  }
  return i;
}

char* Str::itself()
{
  return str;
}

int main()
{
  char s[]="Hello world!";
  Str A(s);
  std::cout<<A.itself()<<std::endl;
  std::cout<<A.strlen()<<std::endl;
  return 0;
}