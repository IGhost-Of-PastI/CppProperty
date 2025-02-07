#pragma once
#include <boost/signals2.hpp>
//#include <functional>
#include "property_types.h"

template<class T, class friendClass>
class wproperty final
{
public:
	friend typename friendClass;

	wproperty(T val, setter_t<T> setter = nullptr);
	wproperty(const wproperty& other);
	wproperty(wproperty&& other) noexcept;

	wproperty& operator=(T val);
	wproperty& operator=(const T& val);
	wproperty& operator=(T&& val) noexcept;

	on_changed_t<T> onChanged;
private:
	void _setSetter(setter_t<T> setter);
	setter_t<T> _setter;
	T _value;
};

template<class T, class friendClass>
inline wproperty<T,friendClass>::wproperty(T val, setter_t<T> setter)
{
	_setSetter(setter);
	_value = val;
}

template<class T, class friendClass>
inline wproperty<T, friendClass>::wproperty(const wproperty& other)
{
	_setSetter(other._setter);
	_value = other._value;
	onChanged = other.onChanged;
}

template<class T, class friendClass>
inline wproperty<T, friendClass>::wproperty(wproperty&& other) noexcept
{
	_setSetter(other._setter);
	_value = other._value;
	onChanged = other.onChanged;
}

template<class T, class friendClass>
inline wproperty<T, friendClass>& wproperty<T, friendClass>::operator=(T val)
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, class friendClass>
inline wproperty<T, friendClass>& wproperty<T, friendClass>::operator=(const T& val)
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, class friendClass>
inline wproperty<T, friendClass>& wproperty<T, friendClass>::operator=(T&& val) noexcept
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, class friendClass>
inline void wproperty<T, friendClass>::_setSetter(setter_t<T> setter)
{
	if (setter == nullptr) _setter = [](T val) { return val; };
	else _setter = setter;
}

