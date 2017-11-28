#ifndef IDISPATCHER_HPP
#define IDISPATCHER_HPP

#include "messages.h"
struct IDispatcher
{
    virtual ~IDispatcher() = default;
    virtual void dispatch(const BinaryMsg& bin) = 0;
};
#endif // IDISPATCHER_HPP
