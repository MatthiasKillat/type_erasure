#include <iostream>
#include <string>
#include <vector>

#include "type_erasure/stringref.hpp"
#include "user/string.hpp"

using namespace std;

int main(int argc, char **argv)
{
    std::string s("some string");
    StringRef sref(s);

    cout << "s: " << s << "\nsref: " << sref.c_str() << endl;

    String<37> s37;
    String<73> s73;

    //StringRef can deal with all types implementing StringInterface
    std::vector<StringRef> v;

    v.push_back(s);
    v.push_back(s37);
    v.push_back(s73);
    v.push_back(sref); //StringRef also adheres to the interface itself

    std::vector<StringRef> v_copy(v);

    cout << "\nstringref vector:" << endl;
    for (auto ref : v)
    {
        cout << ref.c_str() << endl;
    }

    cout << "\nmodify s" << endl;
    s.append("s attached");

    cout << "s: " << s << "\nsref: " << sref.c_str() << endl;

    cout << "\nstringref vector:" << endl;
    for (auto ref : v)
    {
        cout << ref.c_str() << endl;
    }

    cout << "\nstringref vector copy:" << endl;
    for (auto ref : v_copy)
    {
        cout << ref.c_str() << endl;
    }

    return 0;
}
