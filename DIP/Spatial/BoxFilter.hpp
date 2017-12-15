#ifndef _DIP_Spatial_BoxFilter_hpp_
#define _DIP_Spatial_BoxFilter_hpp_

#include <DIP/Config.hpp>
#include <DIP/Types.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace Spatial {
		using namespace std;

		inline Scalar
		inAKUL(
				ScalarArray &in,
				ScalarArray &kernel,
				Index x,
				Index y
				)
		{
			Index krh, kch;
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			Scalar ret = 0;
			for (Index i = 0; i < kernel.rows(); i++)
				for (Index j = 0; j < kernel.cols(); j++) {
					Index inr, inc;
					if (y + i < krh) {
						inr = 0;
					} else {
						inr = y - krh + i;
					};
					if (x + j < kch) {
						inc = 0;
					} else {
						inc = x - kch + j;
					};
					ret += kernel(i, j) * in(inr, inc);
				};
			return ret;
		}

		inline Scalar
		inAKUM(
				ScalarArray &in,
				ScalarArray &kernel,
				Index x,
				Index y
				)
		{
			Index krh, kch;
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			Scalar ret = 0;
			for (Index i = 0; i < kernel.rows(); i++)
				for (Index j = 0; j < kernel.cols(); j++) {
					Index inr, inc;
					if (y + i < krh) {
						inr = 0;
					} else {
						inr = y - krh + i;
					};
					inc = x - kch + j;
					ret += kernel(i, j) * in(inr, inc);
				};
			return ret;
		}

		inline Scalar
		inAKUR(
				ScalarArray &in,
				ScalarArray &kernel,
				Index x,
				Index y
				)
		{
			Index krh, kch;
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			Scalar ret = 0;
			for (Index i = 0; i < kernel.rows(); i++)
				for (Index j = 0; j < kernel.cols(); j++) {
					Index inr, inc;
					if (y + i < krh) {
						inr = 0;
					} else {
						inr = y - krh + i;
					};
					inc = x - kch + j;
					if (inc >= in.cols())
						inc = in.cols() - 1;
					ret += kernel(i, j) * in(inr, inc);
				};
			return ret;
		}

		inline Scalar
		inAKML(
				ScalarArray &in,
				ScalarArray &kernel,
				Index x,
				Index y
				)
		{
			Index krh, kch;
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			Scalar ret = 0;
			for (Index i = 0; i < kernel.rows(); i++)
				for (Index j = 0; j < kernel.cols(); j++) {
					Index inr, inc;
					inr = y - krh + i;
					if (x + j < kch) {
						inc = 0;
					} else {
						inc = x - kch + j;
					};
					ret += kernel(i, j) * in(inr, inc);
				};
			return ret;
		}

		inline Scalar
		inAKMM(
				ScalarArray &in,
				ScalarArray &kernel,
				Index x,
				Index y
				)
		{
			Index krh, kch;
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			Scalar ret = 0;
			for (Index i = 0; i < kernel.rows(); i++)
				for (Index j = 0; j < kernel.cols(); j++) {
					Index inr, inc;
					inr = y - krh + i;
					inc = x - kch + j;
					ret += kernel(i, j) * in(inr, inc);
				};
			return ret;
		}

		inline Scalar
		inAKMR(
				ScalarArray &in,
				ScalarArray &kernel,
				Index x,
				Index y
				)
		{
			Index krh, kch;
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			Scalar ret = 0;
			for (Index i = 0; i < kernel.rows(); i++)
				for (Index j = 0; j < kernel.cols(); j++) {
					Index inr, inc;
					inr = y - krh + i;
					inc = x - kch + j;
					if (inc >= in.cols())
						inc = in.cols() - 1;
					ret += kernel(i, j) * in(inr, inc);
				};
			return ret;
		}

		inline Scalar
		inAKDL(
				ScalarArray &in,
				ScalarArray &kernel,
				Index x,
				Index y
				)
		{
			Index krh, kch;
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			Scalar ret = 0;
			for (Index i = 0; i < kernel.rows(); i++)
				for (Index j = 0; j < kernel.cols(); j++) {
					Index inr, inc;
					inr = y - krh + i;
					if (inr >= in.rows())
						inr = in.rows() - 1;
					if (x + j < kch) {
						inc = 0;
					} else {
						inc = x - kch + j;
					};
					ret += kernel(i, j) * in(inr, inc);
				};
			return ret;
		}

		inline Scalar
		inAKDM(
				ScalarArray &in,
				ScalarArray &kernel,
				Index x,
				Index y
				)
		{
			Index krh, kch;
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			Scalar ret = 0;
			for (Index i = 0; i < kernel.rows(); i++)
				for (Index j = 0; j < kernel.cols(); j++) {
					Index inr, inc;
					inr = y - krh + i;
					if (inr >= in.rows())
						inr = in.rows() - 1;
					inc = x - kch + j;
					ret += kernel(i, j) * in(inr, inc);
				};
			return ret;
		}

		inline Scalar
		inAKDR(
				ScalarArray &in,
				ScalarArray &kernel,
				Index x,
				Index y
				)
		{
			Index krh, kch;
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			Scalar ret = 0;
			for (Index i = 0; i < kernel.rows(); i++)
				for (Index j = 0; j < kernel.cols(); j++) {
					Index inr, inc;
					inr = y - krh + i;
					if (inr >= in.rows())
						inr = in.rows() - 1;
					inc = x - kch + j;
					if (inc >= in.cols())
						inc = in.cols() - 1;
					ret += kernel(i, j) * in(inr, inc);
				};
			return ret;
		}

		F_LONG ScalarArray
		boxInMajor(ScalarArray &in, ScalarArray &kernel)
		{
			Index ir, ic, krh, kch;
			ir = in.rows();
			ic = in.cols();
			krh = kernel.rows() / 2;
			kch = kernel.cols() / 2;
			ScalarArray ret(ir, ic);
			Index y = 0;
			for (; y < krh; y++) {
				Index x = 0;
				for (; x < kch; x++)
					ret(y, x) = inAKUL(in, kernel, x, y);
				for (; x < ic - kch; x++)
					ret(y, x) = inAKUM(in, kernel, x, y);
				for (; x < ic; x++)
					ret(y, x) = inAKUR(in, kernel, x, y);
			};
			for (; y < ir - krh; y++) {
				Index x = 0;
				for (; x < kch; x++)
					ret(y, x) = inAKML(in, kernel, x, y);
				for (; x < ic - kch; x++)
					ret(y, x) = inAKMM(in, kernel, x, y);
				for (; x < ic; x++)
					ret(y, x) = inAKMR(in, kernel, x, y);
			};
			for (; y < ir; y++) {
				Index x = 0;
				for (; x < kch; x++)
					ret(y, x) = inAKDL(in, kernel, x, y);
				for (; x < ic - kch; x++)
					ret(y, x) = inAKDM(in, kernel, x, y);
				for (; x < ic; x++)
					ret(y, x) = inAKDR(in, kernel, x, y);
			};
			return ret;
		}

		F_PROXY ScalarArray
		BoxFilter(ScalarArray &in, ScalarArray &kernel)
		{
			assert(kernel.rows() % 2 == 1);
			assert(kernel.cols() % 2 == 1);
			return boxInMajor(in, kernel);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
