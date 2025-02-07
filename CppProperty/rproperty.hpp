#pragma once
//#include <functional>
#include "property_types.h"

//Временное выравнивание
//#pragma pack(push, 1)
template<class T, class friendClass>
class rproperty final
{
public:
	friend typename friendClass;

	rproperty(T val, getter_t<T> getter = nullptr);
	~rproperty() = default;
	rproperty& operator=(T _val) = delete;
	rproperty& operator=(T& _val) = delete;
	rproperty& operator=(T&& _val) = delete;
	operator T() const;
private:
	void _setGetter(getter_t<T> getter);
	T _value;
	getter_t<T> _getter;
};

template<class T, class friendClass>
inline  rproperty<T, friendClass>::rproperty(T val, getter_t<T> getter)
{
	_setGetter(getter);
	_value = val;
}

template<class T,  class friendClass>
inline  rproperty<T, friendClass>::operator T() const
{
	return _getter(_value);
}

template<class T, class friendClass>
inline void rproperty<T, friendClass>::_setGetter(getter_t<T> getter)
{
	if (getter == nullptr) _getter = [](T val) { return val; };
	else _getter = getter;
}
//#pragma pack(pop)