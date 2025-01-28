#pragma once
#include <functional>

template<class T, T defaultVal, class friendClass>
class rproperty final
{
public:
	friend typename friendClass;

	rproperty(T _val = defaultVal, std::function < T(T) > getter = nullptr);
	~rproperty() = default;
	rproperty& operator=(T _val) = delete;
	rproperty& operator=(T& _val) = delete;
	rproperty& operator=(T&& _val) = delete;
	operator T() const;
private:
	void _setGetter(std::function<T(T)> getter);
	T _value;
	std::function<T(T)> _getter;
};

template<class T, T defaultVal, class friendClass>
inline  rproperty<T, defaultVal, friendClass>::rproperty(T val, std::function<T(T) > getter)
{
	_setGetter(getter);
	_value = val;
}

template<class T, T defaultVal, class friendClass>
inline  rproperty<T, defaultVal, friendClass>::operator T() const
{
	return _getter(_value);
}

template<class T, T defaultVal, class friendClass>
inline void rproperty<T, defaultVal, friendClass>::_setGetter(std::function<T(T)> getter)
{
	if (getter == nullptr) _getter = [](T val) { return val; };
	else _getter = getter;
}
