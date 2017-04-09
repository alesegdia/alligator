#pragma once

#include <functional>

template <typename T>
class Action {

    typedef Args ...T;
    typedef Fn std::function<Args>;

public:
    Action( Fn callback ) {

    }

private:
    Fn m_callback;

};
