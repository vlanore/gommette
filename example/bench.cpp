#include <iostream>
#include "decl_utils.hpp"
using namespace std;

struct MyStruct {
    int a{2}, b{3};

    template <class Info>
    __always_inline void declare_interface(Info info) {
        declare(info, "a", a);
        // declare(info, "b", b);
    }
};

struct Sum {
    int sum{0};

    __always_inline void process_declaration(int v) { sum += v; }
};

struct UserRef {
    Sum& ref;
    UserRef(Sum& ref) : ref(ref) {}
};

class NoNameEnd2 {
  public:
    template <class PrInfo, class DeclInfo, class... Args>
    static void forward_declaration(PrInfo prinfo, DeclInfo, Args&&... args) {
        prinfo.ref.process_declaration(std::forward<Args>(args)...);
    }
};

int main() {
    Sum user;
    MyStruct provider;

    using namespace processing;
    // auto prinfo = make_processing_info<NoNameEnd>(user);
    // provider.declare_interface(make_processing_info<NoNameEnd>(user));
    // declare(make_processing_info<NoNameEnd>(user), "a", provider.a);
    NoNameEnd2::forward_declaration(UserRef(user), 0, provider.a);

    cout << user.sum << endl;
}