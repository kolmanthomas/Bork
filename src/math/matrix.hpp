#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <memory>

namespace bork {

template<typename T, size_t M, size_t N> class Matrix_base
{
protected:
	T* elements;
	const size_t size;
	mutable bool owns;
	mutable bool xfer;
public:
	Matrix_base(size_t n) : elements(new T[n]), size(n), owns(true), xfer(false) {}

	Matrix_base(size_t n, T* p) : elements(p), size(n), owns(false), xfer(false) {}

	~Matrix_base()
	{
		if (owns) {
			delete[] elements;
		}
	}

};

/*
template<typename T> class Matrix<T, 4, 4> : public Matrix_base<T, 4, 4> {

	Matrix(size_t n, T* p) : Matrix_base<t>



}
*/

}

#endif
