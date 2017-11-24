#include "TypeStruct.h"
#include <iostream>

using MyTypes = lag::TypeStruct<int, float, double>;

template<typename T>
struct Funco
{
	void operator()(T *ptr, int otherArgs, float knal)
	{
		*ptr = 1;
		std::cout << otherArgs << " " << knal << std::endl;
	}
};

namespace firo
{
	namespace nero
	{
		class Bonki
		{
		public:
			struct Bako
			{

			};
		};
	}
}

std::string removeBullshit(std::string str, bool removeTemplate = false)
{
	unsigned int start = 0;
	size_t size = str.size();
	for (unsigned int i = 0; i < str.size(); ++i)
	{
		if (str[i] == ' ')
		{
			start = i + 1;
		}
		if (str[i] == ':')
		{
			start = i + 1;
		}
		if (removeTemplate)
		{
			if (str[i] == '<')
			{
				size = i;
			}
		}
	}
	return std::string(&str[start], size - start);
}

void main()
{
	MyTypes tor;

	std::string nam = removeBullshit(typeid(Funco<int>).name());

	tor.runFuncFor<Funco>("int", 1, 10.f);

	system("PAUSE");
}