#include "strUtils.h"

using namespace std;

bool strUtils_isAlpha(const string &str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97 && str[i] <= 122))
            return (false);
        else
            return (true);
    }
    return (true);
}
