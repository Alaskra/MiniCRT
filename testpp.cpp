#include "minicrt.h"

using namespace std;

void my_init() {
    printf("call my_init\n");
}

void_func __attribute__((section (".init_array"))) my_init_p[1] = {&my_init};

class Stu{
public:
    int age;
    Stu(int a) {
        age=a;
        printf("Stu init\n");
    }
};

Stu a(10);

int main(int argc, char* argv[])
{
    string* msg = new string("Hello World!");
    cout<<*msg<<endl;
    delete msg;

    Stu *ps = new Stu(10);
    delete ps;
    return 0;
}
