/* 
const_cast
It is used when you want to eliminate const type of pointer or reference temporary.

method : const_cast<new_type>(expression)
*/
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