#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <type_traits>
 
using namespace Eigen;

namespace bork {

template<typename T>
concept floating_point = std::is_floating_point_v<T>;

/*
template<typename T> 
Matrix<T, 4, 4> mvp_matrix(Transform<T, 3, Affine> )
{
	return trans
}
*/

template<floating_point T>
Transform<T, 3, Affine> model_matrix(
		T t_x, 
		T t_y, 
		T t_z, 
		T s_x, 
		T s_y, 
		T s_z)
{
	/*
	Translation<T, 3> {t_x, t_y, t_z};		
	DiagonalMatrix<T, 3> {s_x, s_y, s_z};
	*/
	Translation<T, 3> translation {t_x, t_y, t_z};
	DiagonalMatrix<T, 3> scale {s_x, s_y, s_z};
	return translation * scale;
}

template<floating_point T>
Transform<T, 3, Affine> look_at_matrix(Vector<T, 3> const& eye, Vector<T, 3> const& target, Vector<T, 3> const& up)
{
	Vector<T, 3> v = (eye - target).normalized();
	Vector<T, 3> r = (up.cross(v)).normalized();
	Vector<T, 3> u = v.cross(r);

	Transform<T, 3, Affine> t; 
	t(0, 0) = r(0);	
	t(0, 1) = r(1);	
	t(0, 2) = r(2);	
	t(0, 3) = -r.dot(eye);	
	t(1, 0) = u(0);	
	t(1, 1) = u(1);	
	t(1, 2) = u(2);	
	t(1, 3) = -u.dot(eye);	
	t(2, 0) = v(0);	
	t(2, 1) = v(1);	
	t(2, 2) = v(2);	
	t(2, 3) = -v.dot(eye);	
	/*
	{
		{r[0], r[1], r[2], -r.dot(eye)},
		{u[0], u[1], u[2], -u.dot(eye)},
		{v[0], v[1], v[2], -v.dot(eye)},
	};
	*/

	return t;
}

template<floating_point T>
Transform<T, 3, Affine> orthographic_matrix(
		T left,
		T right,
		T bottom,
		T top,
		T near,
		T far)
{
	Translation<T, 3> transform {
		-(left + right)/2,
		-(top + bottom)/2,
		-(far + near)/2,
	};

	DiagonalMatrix<T, 3> scale {
		2/(right - left),
		2/(top - bottom),
		2/(far - near),
	};

	return scale * transform;
}

template<floating_point T> 
Transform<T, 3, Projective> perspective_matrix(T fov, T aspect, T znear, T zfar)
{
	const T c = (std::tan(fov / static_cast<T>(2)));

	Transform<T, 3, Projective> t; 
	t.matrix() = Matrix<T, 4, 4>::Zero();
	t(0, 0) = static_cast<T>(1) / (c * aspect);
	t(1, 1) = static_cast<T>(1) / c;
	t(2, 2) = - (zfar + znear) / (zfar - znear);
	t(2, 3) = - (static_cast<T>(2) * zfar * znear) / (zfar - znear);
	t(3, 2) = - static_cast<T>(1);
	return t;
}

}
