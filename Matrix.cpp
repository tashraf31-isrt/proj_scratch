#include "Matrix.h"
#include <cmath>

// Constructors
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
  if (r > MAX_SIZE || c > MAX_SIZE || r < 1 || c < 1) {
    throw std::invalid_argument("Matrix dimensions must be between 1 and " +
                                std::to_string(MAX_SIZE));
  }
  data.resize(rows, std::vector<Fraction>(cols, Fraction(0, 1)));
}

Matrix::Matrix(const std::vector<std::vector<Fraction>> &values) {
  if (values.empty()) {
    throw std::invalid_argument("Cannot create matrix from empty vector");
  }
  rows = values.size();
  cols = values[0].size();
  if (rows > MAX_SIZE || cols > MAX_SIZE) {
    throw std::invalid_argument("Matrix dimensions exceed maximum size of " +
                                std::to_string(MAX_SIZE));
  }
  data = values;
}

// Getters and Setters
Fraction Matrix::get(int i, int j) const {
  if (i < 0 || i >= rows || j < 0 || j >= cols) {
    throw std::out_of_range("Matrix indices out of range");
  }
  return data[i][j];
}

void Matrix::set(int i, int j, const Fraction &value) {
  if (i < 0 || i >= rows || j < 0 || j >= cols) {
    throw std::out_of_range("Matrix indices out of range");
  }
  data[i][j] = value;
}

// Display
void Matrix::display() const {
  std::cout << "\n";
  for (int i = 0; i < rows; i++) {
    std::cout << "  [ ";
    for (int j = 0; j < cols; j++) {
      std::string str = data[i][j].toString();
      std::cout << std::setw(8) << str;
      if (j < cols - 1)
        std::cout << "  ";
    }
    std::cout << " ]\n";
  }
  std::cout << "\n";
}

// Basic Operations
Matrix Matrix::operator+(const Matrix &other) const {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Matrix dimensions must match for addition");
  }
  Matrix result(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result.data[i][j] = data[i][j] + other.data[i][j];
    }
  }
  return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Matrix dimensions must match for subtraction");
  }
  Matrix result(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result.data[i][j] = data[i][j] - other.data[i][j];
    }
  }
  return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
  if (cols != other.rows) {
    throw std::invalid_argument("Invalid dimensions for matrix multiplication");
  }
  Matrix result(rows, other.cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < other.cols; j++) {
      Fraction sum(0, 1);
      for (int k = 0; k < cols; k++) {
        sum = sum + data[i][k] * other.data[k][j];
      }
      result.data[i][j] = sum;
    }
  }
  return result;
}

Matrix Matrix::operator*(const Fraction &scalar) const {
  Matrix result(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result.data[i][j] = data[i][j] * scalar;
    }
  }
  return result;
}

Matrix Matrix::transpose() const {
  Matrix result(cols, rows);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result.data[j][i] = data[i][j];
    }
  }
  return result;
}

// Helper Methods
void Matrix::swapRows(int i, int j) { std::swap(data[i], data[j]); }

void Matrix::multiplyRow(int i, const Fraction &scalar) {
  for (int j = 0; j < cols; j++) {
    data[i][j] = data[i][j] * scalar;
  }
}

void Matrix::addMultipleOfRow(int target, int source, const Fraction &scalar) {
  for (int j = 0; j < cols; j++) {
    data[target][j] = data[target][j] + scalar * data[source][j];
  }
}

Matrix Matrix::getSubmatrix(int excludeRow, int excludeCol) const {
  Matrix result(rows - 1, cols - 1);
  int r = 0;
  for (int i = 0; i < rows; i++) {
    if (i == excludeRow)
      continue;
    int c = 0;
    for (int j = 0; j < cols; j++) {
      if (j == excludeCol)
        continue;
      result.data[r][c] = data[i][j];
      c++;
    }
    r++;
  }
  return result;
}

// REF (Row Echelon Form)
Matrix Matrix::ref() const {
  Matrix result = *this;
  int lead = 0;

  for (int r = 0; r < rows && lead < cols; r++) {
    // Find pivot
    int i = r;
    while (i < rows && result.data[i][lead].isZero()) {
      i++;
    }

    if (i == rows) {
      lead++;
      r--;
      continue;
    }

    // Swap rows
    if (i != r) {
      result.swapRows(r, i);
    }

    // Eliminate below
    for (int i = r + 1; i < rows; i++) {
      Fraction factor = result.data[i][lead] / result.data[r][lead];
      result.addMultipleOfRow(i, r, -factor);
    }

    lead++;
  }

  return result;
}

// RREF (Reduced Row Echelon Form)
Matrix Matrix::rref() const {
  Matrix result = *this;
  int lead = 0;

  for (int r = 0; r < rows && lead < cols; r++) {
    // Find pivot
    int i = r;
    while (i < rows && result.data[i][lead].isZero()) {
      i++;
    }

    if (i == rows) {
      lead++;
      r--;
      continue;
    }

    // Swap rows
    if (i != r) {
      result.swapRows(r, i);
    }

    // Scale pivot to 1
    Fraction pivot = result.data[r][lead];
    if (!pivot.isZero()) {
      result.multiplyRow(r, Fraction(1, 1) / pivot);
    }

    // Eliminate above and below
    for (int i = 0; i < rows; i++) {
      if (i != r) {
        Fraction factor = result.data[i][lead];
        result.addMultipleOfRow(i, r, -factor);
      }
    }

    lead++;
  }

  return result;
}

// Rank
int Matrix::rank() const {
  Matrix ref_form = ref();
  int rank = 0;

  for (int i = 0; i < rows; i++) {
    bool allZero = true;
    for (int j = 0; j < cols; j++) {
      if (!ref_form.data[i][j].isZero()) {
        allZero = false;
        break;
      }
    }
    if (!allZero)
      rank++;
  }

  return rank;
}

// Determinant
Fraction Matrix::determinant() const {
  if (!isSquare()) {
    throw std::invalid_argument(
        "Determinant is only defined for square matrices");
  }

  if (rows == 1) {
    return data[0][0];
  }

  if (rows == 2) {
    return data[0][0] * data[1][1] - data[0][1] * data[1][0];
  }

  Fraction det(0, 1);
  for (int j = 0; j < cols; j++) {
    Matrix submatrix = getSubmatrix(0, j);
    Fraction cofactor = data[0][j] * submatrix.determinant();
    if (j % 2 == 0) {
      det = det + cofactor;
    } else {
      det = det - cofactor;
    }
  }

  return det;
}

// Trace
Fraction Matrix::trace() const {
  if (!isSquare()) {
    throw std::invalid_argument("Trace is only defined for square matrices");
  }

  Fraction tr(0, 1);
  for (int i = 0; i < rows; i++) {
    tr = tr + data[i][i];
  }
  return tr;
}

// Inverse
Matrix Matrix::inverse() const {
  if (!isSquare()) {
    throw std::invalid_argument("Only square matrices can be inverted");
  }

  Fraction det = determinant();
  if (det.isZero()) {
    throw std::runtime_error("Matrix is singular and cannot be inverted");
  }

  // Augment with identity matrix
  Matrix augmented(rows, 2 * cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      augmented.data[i][j] = data[i][j];
      augmented.data[i][j + cols] = (i == j) ? Fraction(1, 1) : Fraction(0, 1);
    }
  }

  // Apply RREF
  augmented = augmented.rref();

  // Extract inverse
  Matrix result(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result.data[i][j] = augmented.data[i][j + cols];
    }
  }

  return result;
}

// Gram-Schmidt
Matrix Matrix::gramSchmidt() const {
  Matrix result(rows, cols);

  for (int j = 0; j < cols; j++) {
    // Get column j
    std::vector<Fraction> v(rows);
    for (int i = 0; i < rows; i++) {
      v[i] = data[i][j];
    }

    // Subtract projections onto previous orthogonal vectors
    for (int k = 0; k < j; k++) {
      std::vector<Fraction> u(rows);
      for (int i = 0; i < rows; i++) {
        u[i] = result.data[i][k];
      }

      Fraction dotVU(0, 1), dotUU(0, 1);
      for (int i = 0; i < rows; i++) {
        dotVU = dotVU + v[i] * u[i];
        dotUU = dotUU + u[i] * u[i];
      }

      if (!dotUU.isZero()) {
        Fraction proj = dotVU / dotUU;
        for (int i = 0; i < rows; i++) {
          v[i] = v[i] - proj * u[i];
        }
      }
    }

    // Normalize
    Fraction normSq(0, 1);
    for (int i = 0; i < rows; i++) {
      normSq = normSq + v[i] * v[i];
    }

    if (!normSq.isZero()) {
      double norm = std::sqrt(normSq.toDouble());
      Fraction normFrac = Fraction::fromDouble(norm);
      for (int i = 0; i < rows; i++) {
        result.data[i][j] = v[i] / normFrac;
      }
    }
  }

  return result;
}

// Check properties
bool Matrix::isSymmetric() const {
  if (!isSquare())
    return false;

  for (int i = 0; i < rows; i++) {
    for (int j = i + 1; j < cols; j++) {
      if (data[i][j] != data[j][i]) {
        return false;
      }
    }
  }
  return true;
}

bool Matrix::isLinearlyIndependent() const {
  return rank() == std::min(rows, cols);
}

std::vector<std::vector<Fraction>> Matrix::basis() const {
  Matrix rref_form = rref();
  std::vector<std::vector<Fraction>> basis;

  for (int i = 0; i < rows; i++) {
    bool allZero = true;
    for (int j = 0; j < cols; j++) {
      if (!rref_form.data[i][j].isZero()) {
        allZero = false;
        break;
      }
    }

    if (!allZero) {
      std::vector<Fraction> row;
      for (int j = 0; j < cols; j++) {
        row.push_back(data[i][j]);
      }
      basis.push_back(row);
    }
  }

  return basis;
}

// Eigenvalues - analytical for 2x2, QR algorithm for larger
std::pair<std::vector<Fraction>, Matrix> Matrix::eigenvalues() const {
  if (!isSquare()) {
    throw std::invalid_argument("Eigenvalues only defined for square matrices");
  }

  std::vector<Fraction> eigenvals;

  // For 2x2 matrix, solve analytically
  if (rows == 2) {
    Fraction tr = trace();
    Fraction det = determinant();

    // Characteristic equation: λ² - trace*λ + det = 0
    // Using quadratic formula: λ = (trace ± sqrt(trace² - 4*det)) / 2
    double traceD = tr.toDouble();
    double detD = det.toDouble();
    double discriminant = traceD * traceD - 4 * detD;

    if (discriminant >= 0) {
      double sqrt_disc = std::sqrt(discriminant);
      double lambda1 = (traceD + sqrt_disc) / 2.0;
      double lambda2 = (traceD - sqrt_disc) / 2.0;

      eigenvals.push_back(Fraction::fromDouble(lambda1));
      eigenvals.push_back(Fraction::fromDouble(lambda2));
    } else {
      // Complex eigenvalues - use trace/2 as real part
      eigenvals.push_back(tr / Fraction(2, 1));
      eigenvals.push_back(tr / Fraction(2, 1));
    }
  } else {
    // For larger matrices, use QR iteration
    Matrix A = *this;

    // Perform 30 QR iterations
    for (int iter = 0; iter < 30; iter++) {
      auto [Q, R] = A.qrDecomposition();
      A = R * Q;
    }

    // Diagonal elements are eigenvalue approximations
    for (int i = 0; i < rows; i++) {
      eigenvals.push_back(A.data[i][i]);
    }
  }

  // Create approximate eigenvector matrix (identity for simplicity)
  Matrix eigenvectors = identity(rows);

  return {eigenvals, eigenvectors};
}

// QR Decomposition using Gram-Schmidt
std::pair<Matrix, Matrix> Matrix::qrDecomposition() const {
  Matrix Q = gramSchmidt();
  Matrix R = Q.transpose() * (*this);
  return {Q, R};
}

// Check if diagonalizable
bool Matrix::isDiagonalizable() const {
  if (!isSquare()) {
    return false;
  }

  // Simplified check: if determinant is non-zero
  try {
    Fraction det = determinant();
    return !det.isZero();
  } catch (...) {
    return false;
  }
}

// Static methods
Matrix Matrix::identity(int n) {
  if (n > MAX_SIZE || n < 1) {
    throw std::invalid_argument("Matrix size must be between 1 and " +
                                std::to_string(MAX_SIZE));
  }
  Matrix I(n, n);
  for (int i = 0; i < n; i++) {
    I.data[i][i] = Fraction(1, 1);
  }
  return I;
}

Matrix Matrix::zero(int r, int c) { return Matrix(r, c); }

std::vector<Fraction> Matrix::getRowVector(int i) const {
  if (i < 0 || i >= rows)
    throw std::out_of_range("Row index out of bounds");
  return data[i];
}

std::vector<Fraction> Matrix::getColVector(int j) const {
  if (j < 0 || j >= cols)
    throw std::out_of_range("Column index out of bounds");
  std::vector<Fraction> col;
  for (int i = 0; i < rows; i++) {
    col.push_back(data[i][j]);
  }
  return col;
}
