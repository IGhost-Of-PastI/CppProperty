#pragma once
#include <boost/signals2.hpp>
#include <functional>

template <class T>
using getter_t = std::function<T(T)>;
template <class T>
using setter_t = std::function<T(T)>;
template <class T>
using on_changed_t = boost::signals2::signal<void(T)>;
