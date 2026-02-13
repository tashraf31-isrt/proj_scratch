#ifndef MATRIX_H
#define MATRIX_H

#include "Fraction.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

const int MAX_SIZE = 5;

class Matrix {
private:
  std::vector<std::vector<Fraction>> data;
  int rows;
  int cols;

public:
  // Constructors
  Matrix(int r, int c);
  Matrix(const std::vector<std::vector<Fraction>> &values);

  // Getters
  int getRows() const { return rows; }
  int getCols() const { return cols; }
  Fraction get(int i, int j) const;
  void set(int i, int j, const Fraction &value);

  // Display
  void display() const;

  // Basic Operations
  Matrix operator+(const Matrix &other) const;
  Matrix operator-(const Matrix &other) const;
  Matrix operator*(const Matrix &other) const;
  Matrix operator*(const Fraction &scalar) const;
  Matrix transpose() const;

  // Advanced Operations
  Fraction determinant() const;
  Matrix inverse() const;
  Matrix rref() const;
  Matrix ref() const;
  int rank() const;
  Fraction trace() const;

  // Decompositions
  std::pair<std::vector<Fraction>, Matrix> eigenvalues() const;
  Matrix gramSchmidt() const;

  std::pair<Matrix, Matrix> qrDecomposition() const;
  bool isDiagonalizable() const;

  // Properties
  bool isSquare() const { return rows == cols; }
  bool isSymmetric() const;
  bool isLinearlyIndependent() const;
  std::vector<std::vector<Fraction>> basis() const;

  // Helper methods
  void swapRows(int i, int j);
  void multiplyRow(int i, const Fraction &scalar);
  void addMultipleOfRow(int target, int source, const Fraction &scalar);
  Matrix getSubmatrix(int excludeRow, int excludeCol) const;

  // Static methods
  static Matrix identity(int n);
  static Matrix zero(int r, int c);
};

#endif
