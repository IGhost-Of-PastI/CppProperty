#pragma once
#include <functional>
#include <boost/signals2.hpp>

template<class T, T defaultVal, class friendClass>
class rwproperty
{
public:
	friend typename friendClass;

	rwproperty(T val = defaultVal, std::function < T(T) > getter = nullptr, std::function < T(T) > setter = nullptr);
	rwproperty(const T& val = defaultVal, std::function < T(T) > getter = nullptr, std::function < T(T) > setter = nullptr);
	rwproperty(T&& val = defaultVal, std::function < T(T) > getter = nullptr, std::function < T(T) > setter = nullptr) noexcept;

	rwproperty<T, defaultVal, friendClass>& operator=(T val);
	rwproperty<T, defaultVal, friendClass>& operator=(const T& val);
	rwproperty<T, defaultVal, friendClass>& operator=(T&& val) noexcept;

	operator T() const;

	boost::signals2::signal<void(T)> onChanged;
private:
	void _setSetter(std::function<T(T)> setter);
	void _setGetter(std::function<T(T)> getter);
	T _value;
	std::function<T(T)> _setter;
	std::function<T(T)> _getter;
};

template<class T, T defaultVal, class friendClass>
inline rwproperty<T, defaultVal, friendClass>::rwproperty(T val, std::function<T(T)> getter, std::function<T(T)> setter)
{
	_setGetter(getter);
	_setSetter(setter);
	_value = val;
}

template<class T, T defaultVal, class friendClass>
inline rwproperty<T, defaultVal, friendClass>::rwproperty(const T& val, std::function<T(T)> getter, std::function<T(T)> setter)
{
	_setGetter(getter);
	_setSetter(setter);
	_value = val;
}

template<class T, T defaultVal, class friendClass>
inline rwproperty<T, defaultVal, friendClass>::rwproperty(T&& val, std::function<T(T)> getter, std::function<T(T)> setter) noexcept
{
	_setGetter(getter);
	_setSetter(setter);
	_value = val;
}

template<class T, T defaultVal, class friendClass>
inline rwproperty<T, defaultVal, friendClass>& rwproperty<T, defaultVal, friendClass>::operator=(T val)
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, T defaultVal, class friendClass>
inline rwproperty<T, defaultVal, friendClass>& rwproperty<T, defaultVal, friendClass>::operator=(const T& val)
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, T defaultVal, class friendClass>
inline rwproperty<T, defaultVal, friendClass>& rwproperty<T, defaultVal, friendClass>::operator=(T&& val) noexcept
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, T defaultVal, class friendClass>
inline rwproperty<T, defaultVal, friendClass>::operator T() const
{
	return _getter(_value);
}

template<class T, T defaultVal, class friendClass>
inline void rwproperty<T, defaultVal, friendClass>::_setSetter(std::function<T(T)> setter)
{
	if (setter == nullptr) _setter = [](T val) { return val; };
	else _setter = setter;
}

template<class T, T defaultVal, class friendClass>
inline void rwproperty<T, defaultVal, friendClass>::_setGetter(std::function<T(T)> getter)
{
	if (getter == nullptr) _getter = [](T val) { return val; };
	else _getter = getter;
}
