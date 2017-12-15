#ifndef _DIP_Types_hpp_
#define _DIP_Types_hpp_

#include <DIP/Config.hpp>
#include <complex>
#include <Eigen/Eigen>

namespace DIP {
	typedef EIGEN_DEFAULT_DENSE_INDEX_TYPE Index;
	typedef _DIP_SCALAR_TYPE Scalar;
	typedef std::complex<Scalar> Complex;
	typedef Eigen::Array<
		Scalar,
		Eigen::Dynamic,
		Eigen::Dynamic,
		Eigen::RowMajor
			>
			ScalarArray;
	typedef Eigen::Array<
		std::complex<Scalar>,
		Eigen::Dynamic,
		Eigen::Dynamic,
		Eigen::RowMajor
			>
			ComplexArray;
};

#endif
