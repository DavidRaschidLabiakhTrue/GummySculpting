#ifndef CircleArray_HPP
#define CircleArray_HPP

#include <vector>
#include "MathDefinitions.hpp"

namespace CircleArray_
{

	template<typename T>
	class CircleArray
	{
		public:
			explicit CircleArray(int resolution)
			{
				this->resolution = resolution;
				impl.reserve(resolution);
				position = 0;
			}
			~CircleArray();
			void load(T& obj);
			void left();
			void right();
			T& current();
		protected:
			int resolution;
			int position = 0;
			std::vector<T> impl;
			
	};

	template<typename T>
	inline CircleArray<T>::~CircleArray()
	{
	}

	template<typename T>
	inline void CircleArray<T>::load(T& obj)
	{
		impl.emplace_back(obj);
	}
	template<typename T>
	inline void CircleArray<T>::left()
	{
		position--;
		if (position < 0)
		{
			while (position < 0)
			{
				position = resolution + position;
			}
		}
		if (position == resolution)
		{
			position = 0;
		}
	}
	template<typename T>
	inline void CircleArray<T>::right()
	{
		position++;
		if (position > resolution)
		{
			while (position > resolution)
			{
				position = position - resolution;
			}
		}
		if (position == resolution)
		{
			position = 0;
		}
	}
	template<typename T>
	inline T& CircleArray<T>::current()
	{
		return impl[position];
	}
}

#endif
