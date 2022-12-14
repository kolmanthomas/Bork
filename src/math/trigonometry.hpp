#pragma once

namespace bork {
namespace math {

template<typename T>
T degrees_to_radians(T degrees)
{
	return degrees * static_cast<T> (0.01745329251994329576923690768489);
}

} // namespace closure of "math"
} // namespace closure of "bork"
