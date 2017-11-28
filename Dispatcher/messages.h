#ifndef MESSAGES_H
#define MESSAGES_H
#include <string>


struct BinaryMsg
{
    int type;
    std::string data;
};

struct Hello
{
    static constexpr int type() { return 100; }
};

struct Say
{
    static constexpr int type() { return 101; }
};

struct Bye
{
    static constexpr int type() { return 102; }
};

#endif // MESSAGES_H
