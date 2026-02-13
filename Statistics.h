#ifndef STATISTICS_H
#define STATISTICS_H

#include "Fraction.h"
#include <cmath>
#include <vector>


class Statistics {
public:
  static Fraction calculateMean(const std::vector<Fraction> &data) {
    if (data.empty())
      return Fraction(0, 1);
    Fraction sum(0, 1);
    for (const auto &f : data) {
      sum = sum + f;
    }
    return sum / Fraction(data.size(), 1);
  }

  static Fraction calculateVariance(const std::vector<Fraction> &data) {
    if (data.size() < 2)
      return Fraction(0, 1);
    Fraction mean = calculateMean(data);
    Fraction sumSqDiff(0, 1);
    for (const auto &f : data) {
      Fraction diff = f - mean;
      sumSqDiff = sumSqDiff + (diff * diff);
    }
    // Using Sample Variance (n-1) as it is more common in statistics
    return sumSqDiff / Fraction(data.size() - 1, 1);
  }

  static double calculateStandardDeviation(const std::vector<Fraction> &data) {
    Fraction variance = calculateVariance(data);
    return std::sqrt(variance.toDouble());
  }
};

#endif
