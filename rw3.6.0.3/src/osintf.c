#include "gameware/osintf.h"

int _rwpathisabsolute(char *arg0)
{
    if (arg0[1] == ':' && (('A' <= *arg0 && *arg0 <= 'Z') || ('a' <= *arg0 && *arg0 <= 'z'))) {
        return 1;
    } else if (*arg0 == '\\') {
        return 1;
    } else {
        return 0;
    }
}
