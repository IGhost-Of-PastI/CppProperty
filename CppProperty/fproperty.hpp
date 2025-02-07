#pragma once
#include "property_types.h"

//Тестовый класс
//Вопервых нужно предусмотреть то что не все функциимогут быть инициализированы а глвное нужны


template<class T, class friendClass>
class [[maybe_unused]] fproperty final
{
public:
	friend typename friendClass;

	fproperty(getter_t<T> getter, setter_t<T> setter);
	fproperty(const fproperty& other);
	fproperty(fproperty&& other) noexcept;

	fproperty& operator=(T val);
	fproperty& operator=(const T& val);
	fproperty& operator=(T&& val) noexcept;

	operator T() const;

	on_changed_t<T> onChanged;
private:
	setter_t<T> _setter;
	getter_t<T> _getter;
};

template<class T, class friendClass>
inline fproperty<T, friendClass>::fproperty(getter_t<T> getter, setter_t<T> setter)
{
	_getter = getter;
	_setter=setter;
}

template<class T, class friendClass>
inline fproperty<T, friendClass>::fproperty(const fproperty& other)
{
	_getter=other._getter;
	_setter=other._setter;
	onChanged = other.onChanged;
}

template<class T, class friendClass>
inline fproperty<T, friendClass>::fproperty(fproperty&& other) noexcept
{
	_getter=other._getter;
	_setter=other._setter;
	onChanged = other.onChanged;
}

template<class T, class friendClass>
inline fproperty<T, friendClass>& fproperty<T, friendClass>::operator=(T val)
{
	if (_setter)
	{
		_setter(val);
		onChanged(_value);
	}
	return *this;
}

template<class T, class friendClass>
inline fproperty<T, friendClass>& fproperty<T, friendClass>::operator=(const T& val)
{
	if (_setter)
	{
		_setter(val);
		onChanged(_value);
	}
	return *this;
}

template<class T, class friendClass>
inline fproperty<T, friendClass>& fproperty<T, friendClass>::operator=(T&& val) noexcept
{
	if (_setter)
	{
		_setter(val);
		onChanged(_value);
	}
	return *this;
}

template<class T, class friendClass>
inline fproperty<T, friendClass>::operator T() const
{
	return _getter(_value);
}