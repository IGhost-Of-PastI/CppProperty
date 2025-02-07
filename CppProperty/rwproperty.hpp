#pragma once
#include <functional>
#include <boost/signals2.hpp>
#include "property_types.h"

template<class T, class friendClass>
class rwproperty
{
public:
	friend typename friendClass;

	rwproperty(T val = defaultVal, getter_t getter = nullptr, setter_t setter = nullptr);
	rwproperty(const rwproperty& other);
	rwproperty(rwproperty&& other) noexcept;

	rwproperty& operator=(T val);
	rwproperty& operator=(const T& val);
	rwproperty& operator=(T&& val) noexcept;

	operator T() const;

	on_changed_t onChanged;
private:
	void _setSetter(setter_t setter);
	void _setGetter(getter_t getter);
	T _value;
	setter_t _setter;
	getter_t _getter;
};

template<class T, class friendClass>
inline rwproperty<T, friendClass>::rwproperty(T val, getter_t<T> getter, setter_t<T> setter)
{
	_setGetter(getter);
	_setSetter(setter);
	_value = val;
}

template<class T, class friendClass>
inline rwproperty<T, friendClass>::rwproperty(const rwproperty& other)
{
	_setGetter(other._getter);
	_setSetter(other._setter);
	_value = other._value;
	onChanged = other.onChanged;
}

template<class T, class friendClass>
inline rwproperty<T, friendClass>::rwproperty(rwproperty&& other) noexcept
{
	_setGetter(other._getter);
	_setSetter(other._setter);
	_value = other._value;
	onChanged = other.onChanged;
}

template<class T, class friendClass>
inline rwproperty<T, friendClass>& rwproperty<T, friendClass>::operator=(T val)
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, class friendClass>
inline rwproperty<T, friendClass>& rwproperty<T, friendClass>::operator=(const T& val)
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, class friendClass>
inline rwproperty<T, friendClass>& rwproperty<T, friendClass>::operator=(T&& val) noexcept
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, class friendClass>
inline rwproperty<T, friendClass>::operator T() const
{
	return _getter(_value);
}

template<class T, class friendClass>
inline void rwproperty<T, friendClass>::_setSetter(setter_t<T> setter)
{
	if (setter == nullptr) _setter = [](T val) { return val; };
	else _setter = setter;
}

template<class T, class friendClass>
inline void rwproperty<T, friendClass>::_setGetter(getter_t<T> getter)
{
	if (getter == nullptr) _getter = [](T val) { return val; };
	else _getter = getter;
}
