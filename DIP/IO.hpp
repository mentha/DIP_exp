#ifndef _DIP_IO_hpp_
#define _DIP_IO_hpp_

#include <DIP/Config.hpp>
#include <Magick++.h>
// Fix garbages from ImageMagick
#undef Intensity

#include <cmath>
#include <cstdlib>
#include <string>
#include <DIP/ColorSpace.hpp>
#include <DIP/Exceptions.hpp>
#include <DIP/Types.hpp>

using namespace std;
using namespace Magick;

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace IO {
		using namespace std;

		bool magickNeedInit = true;

		F_MEDIUM void
		magickInit()
		{
			if (!magickNeedInit)
				return;
			magickNeedInit = false;
			char defdllpath[] = ".";
			char *dllpath = getenv("MAGICK_DLLPATH");
			if (dllpath == nullptr)
				dllpath = defdllpath;
			InitializeMagick(dllpath);
		};

		template <class CS = ColorSpace::HSI>
		F_LONG void
		Load(
				std::string uri,
				ScalarArray &A,
				ScalarArray &B,
				ScalarArray &C
				)
		{
			magickInit();
			Image img(uri);
			A.resize(img.rows(), img.columns());
			B.resize(img.rows(), img.columns());
			C.resize(img.rows(), img.columns());
			Scalar *pA = A.data(), *pB = B.data(), *pC = C.data();
			auto pixels =
				img.getPixels(0, 0, img.columns(), img.rows());
			for (Index c = 0; c < A.size(); c++) {
				Color p(*pixels++);
				Scalar r, g, b;
				r = (Scalar)p.redQuantum() / MaxRGB;
				g = (Scalar)p.greenQuantum() / MaxRGB;
				b = (Scalar)p.blueQuantum() / MaxRGB;

				CS rc = ColorSpace::RGB(r, g, b);;
				*(pA++) = rc.First();
				*(pB++) = rc.Second();
				*(pC++) = rc.Third();
			};
		}

		template <class CS = ColorSpace::Grayscale>
		F_LONG void
		Load(std::string uri, ScalarArray &A)
		{
			magickInit();
			Image img(uri);
			A.resize(img.rows(), img.columns());
			Scalar *pA = A.data();
			auto pixels =
				img.getPixels(0, 0, img.columns(), img.rows());
			for (Index c = 0; c < A.size(); c++) {
				Color p(*pixels++);
				Scalar r, g, b;
				r = (Scalar)p.redQuantum() / MaxRGB;
				g = (Scalar)p.greenQuantum() / MaxRGB;
				b = (Scalar)p.blueQuantum() / MaxRGB;

				CS rc = ColorSpace::RGB(r, g, b);
				*(pA++) = rc.First();
			};
		}

		template <class CS = ColorSpace::HSI>
		F_LONG void
		Save(
				std::string uri,
				ScalarArray &A,
				ScalarArray &B,
				ScalarArray &C
				)
		{
			magickInit();
			Image im(Geometry(A.cols(), A.rows()), Color("white"));
			auto pixels =
				im.getPixels(0, 0, im.columns(), im.rows());
			auto pA = A.data(), pB = B.data(), pC = C.data();
			for (Index i = 0; i < A.size(); i++) {
				Scalar a, b, c;
				a = *(pA++);
				b = *(pB++);
				c = *(pC++);

				ColorSpace::RGB oc = CS(a, b, c);

				Color col(oc.Red * MaxRGB,
						oc.Green * MaxRGB,
						oc.Blue * MaxRGB);
				*pixels++ = col;
			};
			im.syncPixels();
			im.write(uri);
		}

		template <class CS = ColorSpace::Grayscale>
		F_LONG void
		Save(std::string uri, ScalarArray &A)
		{
			magickInit();
			Image im(Geometry(A.cols(), A.rows()), Color("white"));
			auto pixels =
				im.getPixels(0, 0, im.columns(), im.rows());
			auto pA = A.data();
			for (Index c = 0; c < A.size(); c++) {
				Scalar a = *(pA++);

				ColorSpace::RGB oc = CS(a);

				Color col(oc.Red * MaxRGB,
						oc.Green * MaxRGB,
						oc.Blue * MaxRGB);
				*pixels++ = col;
			};
			im.syncPixels();
			im.write(uri);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
