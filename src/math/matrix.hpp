#pragma once

#include <vector>
#include <memory>

namespace math {

template<typename T, std::size_t N>
class Matrix
{
public:
	const std::size_t size;

	Matrix();

	template<typename E ...>
	~Matrix();

private:
	std::unique_ptr<float> elements { new float[size] };

};
}
