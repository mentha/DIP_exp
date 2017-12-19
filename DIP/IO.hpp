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

		inline void
		getRGB(Quantum *&px, Scalar &r, Scalar &g, Scalar &b, size_t ch)
		{
			switch (ch) {
				case 1: {
					r = (Scalar)*px++ / QuantumRange;
					g = r;
					b = r;
					break;
				};
				case 3: {
					r = (Scalar)*px++ / QuantumRange;
					g = (Scalar)*px++ / QuantumRange;
					b = (Scalar)*px++ / QuantumRange;
					break;
				};
				case 4: {
					r = (Scalar)*px++ / QuantumRange;
					g = (Scalar)*px++ / QuantumRange;
					b = (Scalar)*px++ / QuantumRange;
					px++;
					break;
				};
				default:
					throw Exception::
						UnknownColorFormatError();
			};
		}

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
			Image im(uri);
			im.type(TrueColorType);
			A.resize(im.rows(), im.columns());
			B.resize(im.rows(), im.columns());
			C.resize(im.rows(), im.columns());
			Scalar *pA = A.data(), *pB = B.data(), *pC = C.data();
			Quantum *pixels =
				im.getPixels(0, 0, im.columns(), im.rows());
			size_t channels = im.channels();
			for (Index c = 0; c < A.size(); c++) {
				Scalar r, g, b;
				getRGB(pixels, r, g, b, channels);

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
			img.type(TrueColorType);
			A.resize(img.rows(), img.columns());
			Scalar *pA = A.data();
			Quantum *pixels =
				img.getPixels(0, 0, img.columns(), img.rows());
			size_t channels = img.channels();
			for (Index c = 0; c < A.size(); c++) {
				Scalar r, g, b;
				getRGB(pixels, r, g, b, channels);

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
			im.type(TrueColorType);
			Quantum *pixels =
				im.setPixels(0, 0, im.columns(), im.rows());
			auto pA = A.data(), pB = B.data(), pC = C.data();
			for (Index i = 0; i < A.size(); i++) {
				Scalar a, b, c;
				a = *(pA++);
				b = *(pB++);
				c = *(pC++);

				ColorSpace::RGB oc = CS(a, b, c);

				*pixels++ = QuantumRange * oc.Red;
				*pixels++ = QuantumRange * oc.Green;
				*pixels++ = QuantumRange * oc.Blue;
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
			im.type(TrueColorType);
			Quantum *pixels =
				im.setPixels(0, 0, im.columns(), im.rows());
			auto pA = A.data();
			for (Index c = 0; c < A.size(); c++) {
				Scalar a = *(pA++);

				ColorSpace::RGB oc = CS(a);

				*pixels++ = QuantumRange * oc.Red;
				*pixels++ = QuantumRange * oc.Green;
				*pixels++ = QuantumRange * oc.Blue;
			};
			im.syncPixels();
			im.write(uri);
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
