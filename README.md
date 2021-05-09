# Interest

#### Test library written in C++ using last features for parsing ini formatted streams

> Requires C++ 20 standard

### Example:
```c++
#include <iostream>
#include <sstream>

#include <Ini.hpp>

using namespace std;

int main()
{
    stringstream ini_stream;
    ini_stream << "[Greeting.1]"   << endl
               << "name   = World" << endl
               << "phrase = Hello" << endl;

    ES::Ini my_ini;
    my_ini.parseFromStream(ini_stream);

    cout << my_ini["Greeting.1"]["phrase"]
              << ", "
              << my_ini["Greeting.1"]["name"]
              << endl;
    return 0;
}

```
