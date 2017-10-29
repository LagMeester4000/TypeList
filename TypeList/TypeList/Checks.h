#pragma once
#include "TypeListClass.h"

namespace lag
{
	//check if contains type
	template <typename T, typename... Types>
	constexpr bool ContainsType = false;
	template <typename T, typename... Rest>
	constexpr bool ContainsType<T, T, Rest...> = true;
	template <typename T, typename J, typename... Rest>
	constexpr bool ContainsType<T, J, Rest...> = ContainsType<T, Rest...>;

	template<typename ... Types>
	constexpr bool contains_type(TypeList<Types...>)
	{
		return ContainsType<Types...>;
	}


	//get size
	template<unsigned int I, typename ... Types>
	struct SizeBack;

	template<unsigned int I, typename First, typename ... Types>
	struct SizeBack<I, First, Types...>
	{
		static constexpr unsigned int func()
		{
			return SizeBack<I + 1, Types...>::func();
		}
	};

	template<unsigned int I, typename First>
	struct SizeBack<I, First>
	{
		static constexpr unsigned int func()
		{
			return I;
		}
	};

	template<typename ... Types>
	constexpr unsigned int Size = SizeBack<1, Types...>::func();

	template<typename ... Types>
	constexpr unsigned int get_size(TypeList<Types...>)
	{
		return Size<Types...>;
	}


	//get type index
	template<unsigned int I, typename Match, typename ... Types>
	struct TypeIndexBack;

	template<unsigned int I, typename Match, typename First, typename ... Types>
	struct TypeIndexBack<I, Match, First, Types...>
	{
		static constexpr unsigned int func()
		{
			return TypeIndexBack<I + 1, Match, Types...>::func();
		}
	};

	template<unsigned int I, typename Match, typename ... Types>
	struct TypeIndexBack<I, Match, Match, Types...>
	{
		static constexpr unsigned int func()
		{
			return I;
		}
	};

	template<typename Matching, typename ... Types>
	constexpr unsigned int TypeIndex = TypeIndexBack<0, Matching, Types...>;

	template<typename Matching, typename ... Types>
	constexpr unsigned int get_type_index(TypeList<Types...> t)
	{
		return TypeIndex<Matching, Types...>;
	}
}