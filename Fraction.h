#ifndef FRACTION_H
#define FRACTION_H

#include <cmath>
#include <iostream>
#include <numeric>
#include <string>


class Fraction {
private:
  long long num; // numerator
  long long den; // denominator

  // Helper to reduce fraction to lowest terms
  void reduce() {
    if (den == 0) {
      throw std::runtime_error("Division by zero");
    }
    if (den < 0) {
      num = -num;
      den = -den;
    }
    long long g = std::gcd(std::abs(num), std::abs(den));
    num /= g;
    den /= g;
  }

public:
  // Constructors
  Fraction(long long n = 0, long long d = 1) : num(n), den(d) { reduce(); }

  // Convert from double (limited precision)
  static Fraction fromDouble(double value, int maxDen = 10000) {
    if (std::abs(value) < 1e-10)
      return Fraction(0, 1);

    bool negative = value < 0;
    value = std::abs(value);

    long long intPart = static_cast<long long>(value);
    double fracPart = value - intPart;

    if (fracPart < 1e-10) {
      return Fraction(negative ? -intPart : intPart, 1);
    }

    // Continued fraction approximation
    long long n = 0, d = 1;
    long long n1 = 1, d1 = 0;
    double x = fracPart;

    for (int i = 0; i < 20 && d < maxDen; i++) {
      long long a = static_cast<long long>(x);
      long long tempN = n;
      long long tempD = d;

      n = a * n + n1;
      d = a * d + d1;
      n1 = tempN;
      d1 = tempD;

      if (d > maxDen) {
        n = n1;
        d = d1;
        break;
      }

      if (std::abs(x - a) < 1e-10)
        break;
      x = 1.0 / (x - a);
    }

    n = intPart * d + n;
    return Fraction(negative ? -n : n, d);
  }

  // Getters
  long long numerator() const { return num; }
  long long denominator() const { return den; }

  // Convert to double
  double toDouble() const {
    return static_cast<double>(num) / static_cast<double>(den);
  }

  // Arithmetic operators
  Fraction operator+(const Fraction &other) const {
    return Fraction(num * other.den + other.num * den, den * other.den);
  }

  Fraction operator-(const Fraction &other) const {
    return Fraction(num * other.den - other.num * den, den * other.den);
  }

  Fraction operator*(const Fraction &other) const {
    return Fraction(num * other.num, den * other.den);
  }

  Fraction operator/(const Fraction &other) const {
    if (other.num == 0) {
      throw std::runtime_error("Division by zero");
    }
    return Fraction(num * other.den, den * other.num);
  }

  Fraction operator-() const { return Fraction(-num, den); }

  // Comparison
  bool operator==(const Fraction &other) const {
    return num * other.den == other.num * den;
  }

  bool operator!=(const Fraction &other) const { return !(*this == other); }

  bool operator<(const Fraction &other) const {
    return num * other.den < other.num * den;
  }

  bool isZero() const { return num == 0; }

  // Display
  std::string toString() const {
    if (den == 1) {
      return std::to_string(num);
    }
    return std::to_string(num) + "/" + std::to_string(den);
  }

  friend std::ostream &operator<<(std::ostream &os, const Fraction &f) {
    os << f.toString();
    return os;
  }
};

#endif
