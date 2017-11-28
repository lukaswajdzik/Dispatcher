#include <iostream>
#include "messages.h"
#include "autodistatcher.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    DoableDispatcher dd;
    BinaryMsg msg;
    msg.type = 100;

    dd.dispatch(msg);
    msg.type = 101;
    dd.dispatch(msg);
    msg.type = 102;
    dd.dispatch(msg);
    return 0;
}
