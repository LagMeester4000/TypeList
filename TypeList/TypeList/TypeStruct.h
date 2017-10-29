#pragma once
#include "Checks.h"

namespace lag
{
	template<typename ... Types>
	struct TypeStruct;

	template<typename Front, typename ... Back>
	struct TypeStruct<Front, Back...>
	{
		using typelist = TypeList<Front, Back...>;
		Front front;
		TypeStruct<Back...> back;
	};

	template<typename Front>
	struct TypeStruct<Front>
	{
		using typelist = TypeList<Front>;
		Front front;
	};


	template<unsigned int I, typename T>
	struct AC
	{
		using type = typename AC<I - 1, decltype(T::back)>::type;
	};

	template<typename T>
	struct AC<0, T>
	{
		using type = decltype(T::front);
	};


	template<unsigned int I, typename R, typename T>
	struct AccessTypeBack
	{
		static R &func(T &t)
		{
			return AccessTypeBack<I - 1, R, decltype(t.back)>::func(t.back);
		}
	};

	template<typename R, typename T>
	struct AccessTypeBack<0, R, T>
	{
		static R &func(T &t)
		{
			return t.front;
		}
	};

	template<unsigned int I, typename T>
	struct AccessType
	{
		using FinalType = typename AC<I, T>::type;
		static FinalType &func(T &t)
		{
			return AccessTypeBack<I, FinalType, T>::func(t);
		}
	};

	template<unsigned int I, typename ... Types>
	auto access_type(TypeStruct<Types...> &typeStruct)
		->typename AccessType<I, TypeStruct<Types...>>::FinalType&
	{ return AccessType<I, TypeStruct<Types...>>::func(typeStruct); }


	
	//get variable by type
	template<typename T, typename ... Types>
	T &access_by_type(TypeStruct<Types...> &typeStruct)
	{
		constexpr unsigned int index = TypeIndex<T, Types...>;
		return access_type<index>(TypeStruct);
	}
}