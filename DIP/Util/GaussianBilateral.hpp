#ifndef _DIP_Util_GaussianBilateral_hpp_
#define _DIP_Util_GaussianBilateral_hpp_

#include <DIP/Config.hpp>
#include <DIP/Math/Gaussian.hpp>
#include <DIP/Spatial/Bilateral.hpp>
#include <DIP/Types.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Util {
		using namespace std;

		struct BilateralGaussianRangeFilter {
			Scalar sigma;
			inline Scalar apply(Scalar ref, Scalar v) {
				return Math::Gaussian(ref - v, sigma);
			};
		};

		struct BilateralGaussianSpatialFilter {
			Index rows;
			Index cols;
			ScalarArray skern;
			inline Scalar apply(
					Index x, Index y,
					Index kx, Index ky
					) {
				return skern(ky, kx);
			};
		};

		F_MEDIUM ScalarArray
		GaussianBilateralFilter(ScalarArray &in, Scalar sr, Scalar ss)
		{
			Index sz = ss * 6;
			if (sz % 2 == 0)
				sz += 1;
			BilateralGaussianRangeFilter rf;
			rf.sigma = sr;
			BilateralGaussianSpatialFilter sf;
			sf.rows = sz; sf.cols = sz;
			sf.skern = Math::Gaussian2D(ss, sf.rows, sf.cols);
			return Spatial::BilateralFilter<
					BilateralGaussianRangeFilter,
					BilateralGaussianSpatialFilter
					>(in, rf, sf);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
