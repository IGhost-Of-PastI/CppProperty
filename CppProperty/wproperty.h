#pragma once
#include <boost/signals2.hpp>
#include <functional>

template<class T, T defaultVal, class friendClass>
class wproperty final
{
public:
	friend typename friendClass;

	wproperty(T val = defaultVal, std::function < T(T) > setter = nullptr);
	wproperty(const T& val = defaultVal, std::function < T(T) > setter = nullptr);
	wproperty(T&& val = defaultVal, std::function < T(T) > setter = nullptr) noexcept;

	wproperty<T, defaultVal, friendClass>& operator=(T val);
	wproperty<T, defaultVal, friendClass>& operator=(const T& val);
	wproperty<T, defaultVal, friendClass>& operator=(T&& val) noexcept;

	boost::signals2::signal<void(T)> onChanged;
private:
	void _setSetter(std::function<T(T)> setter);
	T _value;
	std::function<T(T)> _setter;
};

template<class T, T defaultVal, class friendClass>
inline wproperty<T,defaultVal,friendClass>::wproperty(T val ,std::function<T(T)> setter)
{
	_setSetter(setter);
	_value = val;
}

template<class T, T defaultVal, class friendClass>
inline wproperty<T, defaultVal, friendClass>::wproperty(const T& val,std::function<T(T)> setter)
{
	_setSetter(setter);
	_value = val;
}

template<class T, T defaultVal, class friendClass>
inline wproperty<T, defaultVal, friendClass>::wproperty(T&& val,std::function<T(T)> setter) noexcept
{
	_setSetter(setter);
	_value = val;
}

template<class T, T defaultVal, class friendClass>
inline wproperty<T, defaultVal, friendClass>& wproperty<T, defaultVal, friendClass>::operator=(T val)
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, T defaultVal, class friendClass>
inline wproperty<T, defaultVal, friendClass>& wproperty<T, defaultVal, friendClass>::operator=(const T& val)
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, T defaultVal, class friendClass>
inline wproperty<T, defaultVal, friendClass>& wproperty<T, defaultVal, friendClass>::operator=(T&& val) noexcept
{
	T oldvalue = _value;
	_value = _setter(val);
	if (_value != oldvalue) onChanged(_value);
	return *this;
}

template<class T, T defaultVal, class friendClass>
inline void wproperty<T, defaultVal, friendClass>::_setSetter(std::function<T(T)> setter)
{
	if (setter == nullptr) _setter = [](T val) { return val; };
	else _setter = setter;
}

