#include <string>
#include <algorithm>
#include <cmath>

namespace Number
{

	class Rational
	{
	public:
		using Type = int;
		Rational(Type num, Type den) {
			initialize(num, den);
		};
		Rational() :numerator{ 1 }, denominator{ 1 } {};
		Rational(Type num) :numerator{ num }, denominator{ 1 } {};

		void initialize(Type num, Type den) {
			Type g = gcd(num, den);
			numerator = num / g;
			denominator = den / g;
			adjust(numerator, denominator);
		}

		static void adjust(Type &num, Type &den) {
			bool _isnegative = false;
			if (num < 0) {
				num = -num;
				_isnegative = !_isnegative;
			}
			if (den < 0) {
				den = -den;
				_isnegative = !_isnegative;
			}

			if (_isnegative) {
				num = -num;
			}
		}

		Rational& operator=(const Rational &r) { 
			this->numerator = r.numerator;
			this->denominator = r.denominator;
			return *this;
		}

		Rational& operator+=(const Rational &r) {
			initialize(numerator * r.denominator + r.numerator * denominator, denominator * r.denominator);
			return *this;
		}

		Rational& operator-=(const Rational &r) {
			initialize(numerator * r.denominator - r.numerator * denominator, denominator * r.denominator);
			return *this;
		}

		Rational& operator*=(const Rational &r) {
			initialize(numerator * r.numerator, denominator * r.denominator);
			return *this;
		}

		Rational& operator/=(const Rational &r) {
			initialize(numerator * r.denominator, denominator * r.numerator);
			return *this;
		}

		bool isNaN() const {
			return (denominator == 0 && numerator == 0) || (denominator < 0);
		}
		bool isInf() const {
			return (denominator == 0 && numerator != 0);
		}
		bool isInt() const {
			return denominator == 1;
		}

	private:
		Type numerator;
		Type denominator;
		static Type gcd(Type a, Type b) {
			using std::max;  //will be improved to GMP... next time...
			for (Type divisor = max(a, b); divisor >= 1; divisor--) {
				if (a % divisor == 0 && b % divisor == 0)
					return divisor;
			}
			return 1;
		}
	public:
		const Type& getnum() const { // Good.
			return numerator;
		}
		const Type& getden() const {
			return denominator;
		}
	};
	const Rational operator+(const Rational &a, const Rational &b) {
		return Rational(a.getnum() * b.getden() + b.getnum() * a.getden(), a.getden() * b.getden());
	}

	const Rational operator-(const Rational &a, const Rational &b) {
		return Rational(a.getnum() * b.getden() - b.getnum() * a.getden(), a.getden() * b.getden());
	}

	const Rational operator*(const Rational &a, const Rational &b) {
		return Rational(a.getnum() * b.getnum(), a.getden() * b.getden());
	}

	const Rational operator/(const Rational &a, const Rational &b) {
		return Rational(a.getnum() * b.getden(), a.getden() * b.getnum());
	}

	const Rational operator-(const Rational &a) {
		return Rational(-a.getnum(), a.getden());
	}

	const Rational operator~(const Rational &a) {
		return Rational(a.getden(), a.getnum());
	}

	bool operator>(const Rational &a, const Rational &b) {
		return a.getnum() * b.getden() - b.getnum() * a.getnum() > 0;
	}

	bool operator>=(const Rational &a, const Rational &b) {
		return a.getnum() * b.getden() - b.getnum() * a.getnum() >= 0;
	}

	bool operator==(const Rational &a, const Rational &b) {
		return a.getnum() * b.getden() == b.getnum() * a.getnum();
	}

	bool operator!=(const Rational &a, const Rational &b) {
		return a.getnum() * b.getden() != b.getnum() * a.getnum();
	}

	bool operator<(const Rational &a, const Rational &b) {
		return a.getnum() * b.getden() - b.getnum() * a.getnum() < 0;
	}

	bool operator<=(const Rational &a, const Rational &b) {
		return a.getnum() * b.getden() - b.getnum() * a.getnum() <= 0;
	}

	const Rational abs(const Rational &a) {
		return Rational(std::abs(a.getnum()), std::abs(a.getden()));
	}


	Rational::Type floor(const Rational &a) {
		if (a.isInf())
			return std::numeric_limits<Rational::Type>::max();
		if (a.isNaN())
			return 0;
		else
			return (Rational::Type)std::floor((long double) a.getnum() / a.getden());
	}
	Rational::Type ceil(const Rational &a) {
		if (a.isInf())
			return std::numeric_limits<Rational::Type>::max();
		if (a.isNaN())
			return 0;
		else
			return (Rational::Type)std::ceil((long double) a.getnum() / a.getden());
	}
	Rational::Type fix(const Rational &a) {
		if (a.getnum() > 0)
			return floor(a);
		else
			return ceil(a);
	}

	const Rational mod(const Rational &a, const Rational &b) {
		return a - (b * floor(a / b));
	}
	const Rational rem(const Rational &a, const Rational &b) {
		return  a - (b * fix(a / b));
	}
	std::string to_string(const Rational &a) {
		using std::to_string;

		if (a.isInt())
			return to_string(a.getnum());
		else if (a.isInf())
			return "Inf";
		else if (a.isNaN())
			return "NaN";
		else
			return to_string(a.getnum()) + "/" + to_string(a.getden());
	}

}

