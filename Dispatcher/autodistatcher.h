#ifndef AUTODISTATCHER_H
#define AUTODISTATCHER_H

#include "idispatcher.hpp"
#include <iostream>
#include <unordered_map>
#include <assert.h>
#include "boost/cast.hpp"


class DoableDispatcher;

template<typename M>
M deserialize(BinaryMsg const& b)
{
    return M();
}

template <typename FinalType, typename M, typename ...Tail>
struct Reg
{
    template <typename C>
    static void call(C& c)
    {
        auto dispatch = [](auto ft, auto const& bin)
            { ft->handle( deserialize<M>(bin) ); };
        c[M::type()] = dispatch;
        Reg<FinalType, Tail...>::call(c);
    }
};

template <typename FinalType>
struct Reg<FinalType, void>
{
    template<typename C>
    static void call(C& c) { }
};

template <typename FinalType, typename ...Msgs>
class AutoDistatcher : public IDispatcher
{
public:
    AutoDistatcher()
    {
        Reg<FinalType, Msgs..., void>::call(_handlers);
    }

    virtual void dispatch(const BinaryMsg& bin) final
    {
        auto it = _handlers.find(bin.type);
        if(it == _handlers.end())
            throw std::runtime_error("Unknown Message!");
        auto h = it->second;
        assert(h);
        (*h)( boost::polymorphic_downcast<FinalType*>(this), bin);
    }

private:
    std::unordered_map<int, void(*)(FinalType*, const BinaryMsg&)> _handlers;
};

struct DoableDispatcher final : public AutoDistatcher<DoableDispatcher,
                                                      Hello,
                                                      Say,
                                                      Bye>
{
    void handle(const Hello& h) {std::cout << "handle Hello!" << std::endl;}
    void handle(const Say& h) {std::cout << "handle Say!" << std::endl;}
    void handle(const Bye& h) {std::cout << "handle bye!" << std::endl;}

};

#endif // AUTODISTATCHER_H
