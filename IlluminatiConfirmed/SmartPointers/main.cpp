#include <iostream>
#include <vector>
#include <algorithm>
#include "auto_ptr.h"
#include "unique_ptr.h"

#include "gtest/gtest.h"

#define TEST(str) do { std::cout << "Start testing " << str << std::endl; } while(0);
#define END() do { std::cout << "Test complete " << std::endl; } while(0);

using IlluminatiConfirmed::auto_ptr;
using IlluminatiConfirmed::unique_ptr;
using std::string;
using std::vector;

struct Foo {
    explicit Foo(): m_str("aazazz") { std::cout << "Foo\n"; }
    ~Foo() { std::cout << "~Foo\n"; }
    string m_str;
};

std::ostream& operator<<(std::ostream& os, const Foo& obj)
{
    (void) obj;
    os << "speech of foo";
    return os;
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    TEST("auto_ptr")
    {
        vector<auto_ptr<Foo>> p(3);
        for (auto & it : p)
            it.reset(new Foo());

        //auto_ptr<Foo> IWhantToCreateThisPointer = p.at(0); //There is crash

        std::for_each(p.begin(), p.end(), [](auto_ptr<Foo>& p) { std::cout<<*p<<"\n"; });
    }
    END()

    TEST("unique_ptr")
    {
        vector<unique_ptr<Foo>> p(3);
        for (auto & it : p)
            it.reset(new Foo());

        //unique_ptr<Foo> IWhantToCreateThisPointer = p.at(0); // It does not compile
        //unique_ptr<Foo> IWhantToCreateThisPointer2; IWhantToCreateThisPointer2 = p.at(0); // It does not compile

        std::for_each(p.begin(), p.end(), [](unique_ptr<Foo>& p) { std::cout << *p << "\n"; });
    }
    END()




    ::testing::InitGoogleTest(&argc, argv);
    // запускаем только определённый тест (чтобы проще смотреть дампы)
    //::testing::GTEST_FLAG(filter) = "VectorTest3*";
    RUN_ALL_TESTS();



    return 0;
}
