#ifndef _DIP_Spatial_Smoothing_hpp_
#define _DIP_Spatial_Smoothing_hpp_

#include <DIP/Config.hpp>
#include <DIP/Types.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Spatial {
		using namespace std;

		F_SHORT ScalarArray
		Smoothing(Index sz)
		{
			assert(sz % 2 == 1);
			ScalarArray ret(sz, sz);
			Scalar v = (Scalar)1 / ret.size();
			Scalar *p = ret.data();
			for (Index i = 0; i < ret.size(); i++)
				*(p++) = v;
			return ret;
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
