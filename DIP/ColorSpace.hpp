#ifndef _DIP_ColorSpace_hpp_
#define _DIP_ColorSpace_hpp_

#include <DIP/Config.hpp>
#include <cstdlib>
#include <cmath>
#include <string>
#include <DIP/Exceptions.hpp>
#include <DIP/Types.hpp>

#include <DIP/internal/macros_begin.hpp>

namespace DIP {
	namespace ColorSpace {
		using namespace std;

		struct Base {
			// string Name();
			// void FromStr(string colorString);
			// string Str();
		};

		struct Unitary : Base {
			// F_GETTER Scalar First();
		};

		struct Tenary : Base {
			// F_GETTER Scalar First();
			// F_GETTER Scalar Second();
			// F_GETTER Scalar Third();
		};

		struct Grayscale;

		struct RGB;
		struct HSI;
		struct CIELab;

		struct Grayscale : Unitary {
			Scalar Intensity;
			F_SHORT Grayscale(Scalar i);
			F_SHORT Grayscale(RGB c);
			F_SHORT Grayscale(HSI c);
			F_SHORT Grayscale(CIELab c);
			F_GETTER string Name() {
				return "Grayscale";
			};
			F_GETTER Scalar First() {
				return Intensity;
			};
		};

		struct RGB : Tenary {
			Scalar Red;	// 0 .. 1
			Scalar Green;	// 0 .. 1
			Scalar Blue;	// 0 .. 1
			F_SHORT RGB(Scalar r, Scalar g, Scalar b);
			F_SHORT RGB(Grayscale c);
			F_SHORT RGB(HSI c);
			F_SHORT RGB(CIELab c);
			F_GETTER string Name() {
				return "RGB";
			};
			F_GETTER Scalar First() {
				return Red;
			};
			F_GETTER Scalar Second() {
				return Green;
			};
			F_GETTER Scalar Third() {
				return Blue;
			};
		};
		struct HSI : Tenary {
			Scalar Hue;	// 0 .. 2 * Pi
			Scalar Saturation;	// 0 .. 1
			Scalar Intensity;	// 0 .. 1
			F_SHORT HSI(Scalar h, Scalar s, Scalar i);
			F_SHORT HSI(Grayscale c);
			F_SHORT HSI(RGB c);
			F_SHORT HSI(CIELab c);
			F_GETTER string Name() {
				return "HSI";
			};
			F_GETTER Scalar First() {
				return Hue;
			};
			F_GETTER Scalar Second() {
				return Saturation;
			};
			F_GETTER Scalar Third() {
				return Intensity;
			};
		};
		struct CIELab : Tenary {
			// CIE L*a*b*
			Scalar L;	// 0 .. 100
			Scalar a;
			Scalar b;
			F_SHORT CIELab(Scalar L, Scalar a, Scalar b);
			F_SHORT CIELab(Grayscale c);
			F_SHORT CIELab(RGB c);
			F_SHORT CIELab(HSI c);
			F_GETTER string Name() {
				return "CIEL*a*b*";
			};
			F_GETTER Scalar First() {
				return L;
			};
			F_GETTER Scalar Second() {
				return a;
			};
			F_GETTER Scalar Third() {
				return b;
			};
		};

		F_SHORT Grayscale::Grayscale(Scalar i) :
			Intensity(i)
		{
		}

		F_SHORT Grayscale::Grayscale(RGB c)
		{
			Intensity = (c.Red + c.Green + c.Blue) / 3;
		}

		F_SHORT Grayscale::Grayscale(HSI c)
		{
			Intensity = c.Intensity;
		}

		F_SHORT Grayscale::Grayscale(CIELab c)
		{
			throw Exception::NotImplemented("CIELab not supported yet");
		}

		F_SHORT RGB::RGB(Scalar r, Scalar g, Scalar b) :
			Red(r), Green(g), Blue(b)
		{
		}

		F_SHORT RGB::RGB(Grayscale c) :
			Red(c.Intensity), Green(c.Intensity), Blue(c.Intensity)
		{
		}

		F_SHORT RGB::RGB(HSI c)
		{
			Scalar r, g, b;
			Scalar h, s, i;

			h = c.Hue;
			s = c.Saturation;
			i = c.Intensity;

			if (0.0 <= h && h < M_PI * 2 / 3) {
				b = i * (1 - s);
				r = i * (1 + s * cos(h) / cos(M_PI / 3 - h));
				g = 3 * i - (r + b);
			} else if(M_PI * 2 / 3 <= h && h < M_PI * 4 / 3) {
				Scalar H = h - M_PI * 2 / 3;
				r = i * (1 - s);
				g = i * (1 + s * cos(H) / cos(M_PI / 3 - H));
				b = 3 * i - (r + g);
			} else {
				Scalar H = h - M_PI * 4 / 3;
				g = i * (1 - s);
				b = i * (1 + s * cos(H) / cos(M_PI / 3 - H));
				r = 3 * i - (g + b);
			};

			Red = r;
			Green = g;
			Blue = b;
		}

		F_SHORT RGB::RGB(CIELab c)
		{
			throw Exception::NotImplemented("CIELab not supported yet");
		}

		F_SHORT HSI::HSI(Scalar h, Scalar s, Scalar i) :
			Hue(h), Saturation(s), Intensity(i)
		{
		}

		F_SHORT HSI::HSI(Grayscale c) :
			Hue(0), Saturation(0), Intensity(c.Intensity)
		{
		}

		F_SHORT HSI::HSI(RGB c)
		{
			Scalar h, s, i;
			Scalar r, g, b;

			r = c.Red;
			g = c.Green;
			b = c.Blue;

			Scalar theta = acos(
					((r - g) + (r - b)) /
					sqrt((r - g) * (r - g) +
					     (r - b) * (g - b)) / 2);
			if (isnan(theta)) theta = 0.0;
			if (b <= g) {
				h = theta;
			} else {
				h = M_PI * 2 - theta;
			};

			Scalar min = r < g ? r : g;
			if (min > b) min = b;
			s = 1 - 3 * min / (r + g + b);
			if (isnan(s)) s = 0;

			i = (r + g + b) / 3;

			Hue = h;
			Saturation = s;
			Intensity = i;
		}

		F_SHORT HSI::HSI(CIELab c)
		{
			throw Exception::NotImplemented("CIELab not supported yet");
		}

		F_SHORT CIELab::CIELab(Scalar L, Scalar a, Scalar b)
		{
			throw Exception::NotImplemented("CIELab not supported yet");
		}

		F_SHORT CIELab::CIELab(Grayscale c)
		{
			throw Exception::NotImplemented("CIELab not supported yet");
		}

		F_SHORT CIELab::CIELab(RGB c)
		{
			throw Exception::NotImplemented("CIELab not supported yet");
		}

		F_SHORT CIELab::CIELab(HSI c)
		{
			throw Exception::NotImplemented("CIELab not supported yet");
		}
	};
};

#include <DIP/internal/macros_end.hpp>

#endif
