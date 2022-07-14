#include<iostream>
int main(int argc, char *argv[])
{
    int temp = 15;
    const int &ref = temp;
    std::cout << "before : " << temp << std::endl;

    int & r = const_cast<int&>(ref);
    r = 30;
    std::cout << "after : " << temp << std::endl;
    return 0;
}