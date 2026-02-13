#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

const int MAX_SIZE = 5;

class Matrix {
private:
  std::vector<std::vector<double>> data;
  int rows;
  int cols;

public:
  // Constructors
  Matrix();
  Matrix(int r, int c);
  Matrix(const std::vector<std::vector<double>> &values);

  // Getters
  int getRows() const { return rows; }
  int getCols() const { return cols; }
  double get(int i, int j) const;
  void set(int i, int j, double value);

  // Display
  void display() const;

  // Basic Operations
  Matrix operator+(const Matrix &other) const;
  Matrix operator-(const Matrix &other) const;
  Matrix operator*(const Matrix &other) const;
  Matrix operator*(double scalar) const;
  Matrix transpose() const;

  // Advanced Operations
  double determinant() const;
  Matrix inverse() const;
  Matrix rref() const;
  Matrix ref() const;
  int rank() const;
  double trace() const;

  // Eigen-stuff
  std::pair<std::vector<double>, Matrix> eigenvalues() const;
  std::vector<Matrix> findEigenvectors(double lambda) const;
  bool diagonalize(Matrix &P, Matrix &D, Matrix &Pinv) const;

  // Decompositions
  Matrix gramSchmidt() const;

  std::pair<Matrix, Matrix> qrDecomposition() const;
  bool isDiagonalizable() const;

  // Properties
  bool isSquare() const { return rows == cols; }
  bool isSymmetric() const;
  bool isLinearlyIndependent() const;
  std::vector<std::vector<double>> basis() const;
  std::vector<double> getRowVector(int i) const;
  std::vector<double> getColVector(int j) const;

  // Helper methods
  void swapRows(int i, int j);
  void multiplyRow(int i, double scalar);
  void addMultipleOfRow(int target, int source, double scalar);
  Matrix getSubmatrix(int excludeRow, int excludeCol) const;

  // Static methods
  static Matrix identity(int n);
  static Matrix zero(int r, int c);
};

#endif
