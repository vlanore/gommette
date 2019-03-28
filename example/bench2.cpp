#include <iostream>
#include "decl_utils.hpp"
using namespace std;

struct MyStruct {
    int a{2}, b{3};

    template <class Info>
    void declare_interface(Info info) {
        declare(info, "a", a);
        declare(info, "b", b);
    }
};

struct Sum {
    int sum{0};

    void process_declaration(int v) { sum += v; }
};

int main() {
    Sum user;
    MyStruct provider;

    // using namespace processing;
    // provider.declare_interface(make_processing_info<NoNameEnd>(user));
    user.sum += 3;
    // user.sum = provider.a + provider.b;

    cout << user.sum << endl;
}