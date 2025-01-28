#pragma once
#include <boost/signals2.hpp>
#include <functional>

template<class T, T defaultVal, class friendClass>
class wproperty final
{
public:
	friend typename friendClass;

	wproperty(std::function < T(T) > setter = nullptr);
	wproperty(std::function < T(T) > setter = nullptr);
	wproperty(std::function < T(T) > setter = nullptr) noexcept;

	wproperty<T>& operator=(T val);
	wproperty<T>& operator=(const T& val);
	wproperty<T>& operator=(T&& val) noexcept;

	boost::signals2::signal<void(T)> onChanged;
private:
	void _setSetter(std::function<T(T)> setter);
	T _value;
	std::function<T(T)> _setter;
};

template<class T>
inline wproperty<T>::wproperty(std::function<T(T)> setter)
{
	_setSetter(setter);
}

template<class T>
inline wproperty<T>::wproperty(std::function<T(T)> setter)
{
	_setSetter(setter);
}

template<class T>
inline wproperty<T>::wproperty(std::function<T(T)> setter) noexcept
{
	_setSetter(setter);
}

template<class T>
inline wproperty<T>& wproperty<T>::operator=(T val)
{
	_value = _setter(val);
	return *this;
}

template<class T>
inline wproperty<T>& wproperty<T>::operator=(const T& val)
{
	_value = _setter(val);
	return *this;
}

template<class T>
inline wproperty<T>& wproperty<T>::operator=(T&& val) noexcept
{
	_value = _setter(val);
	return *this;
}

template<class T>
inline void wproperty<T>::_setSetter(std::function<T(T)> setter)
{
	if (setter == nullptr) _setter = [](T val) { return val; };
	else _setter = setter;
}
