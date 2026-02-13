#ifndef STATISTICS_H
#define STATISTICS_H

#include <cmath>
#include <vector>


class Statistics {
public:
  static double calculateMean(const std::vector<double> &data) {
    if (data.empty())
      return 0.0;
    double sum = 0.0;
    for (double val : data) {
      sum += val;
    }
    return sum / static_cast<double>(data.size());
  }

  static double calculateVariance(const std::vector<double> &data) {
    if (data.size() < 2)
      return 0.0;
    double mean = calculateMean(data);
    double sumSqDiff = 0.0;
    for (double val : data) {
      double diff = val - mean;
      sumSqDiff += diff * diff;
    }
    return sumSqDiff / static_cast<double>(data.size() - 1);
  }

  static double calculateStandardDeviation(const std::vector<double> &data) {
    return std::sqrt(calculateVariance(data));
  }
};

#endif
