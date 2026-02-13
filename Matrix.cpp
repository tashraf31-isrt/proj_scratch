#include "Matrix.h"
#include <cmath>
#include <iomanip>

const double EPSILON = 1e-9;

// Constructors
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
  if (r > MAX_SIZE || c > MAX_SIZE || r < 1 || c < 1) {
    throw std::invalid_argument("Matrix dimensions must be between 1 and " +
                                std::to_string(MAX_SIZE));
  }
  data.resize(rows, std::vector<double>(cols, 0.0));
}

Matrix::Matrix(const std::vector<std::vector<double>> &values) {
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
double Matrix::get(int i, int j) const {
  if (i < 0 || i >= rows || j < 0 || j >= cols) {
    throw std::out_of_range("Matrix indices out of range");
  }
  return data[i][j];
}

void Matrix::set(int i, int j, double value) {
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
      std::cout << std::setw(10) << std::fixed << std::setprecision(4)
                << data[i][j];
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
      double sum = 0.0;
      for (int k = 0; k < cols; k++) {
        sum += data[i][k] * other.data[k][j];
      }
      result.data[i][j] = sum;
    }
  }
  return result;
}

Matrix Matrix::operator*(double scalar) const {
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

void Matrix::multiplyRow(int i, double scalar) {
  for (int j = 0; j < cols; j++) {
    data[i][j] *= scalar;
  }
}

void Matrix::addMultipleOfRow(int target, int source, double scalar) {
  for (int j = 0; j < cols; j++) {
    data[target][j] += scalar * data[source][j];
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
    int i = r;
    while (i < rows && std::abs(result.data[i][lead]) < EPSILON) {
      i++;
    }
    if (i == rows) {
      lead++;
      r--;
      continue;
    }
    if (i != r) {
      result.swapRows(r, i);
    }
    for (int i = r + 1; i < rows; i++) {
      double factor = result.data[i][lead] / result.data[r][lead];
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
    int i = r;
    while (i < rows && std::abs(result.data[i][lead]) < EPSILON) {
      i++;
    }
    if (i == rows) {
      lead++;
      r--;
      continue;
    }
    if (i != r) {
      result.swapRows(r, i);
    }
    double pivot = result.data[r][lead];
    if (std::abs(pivot) > EPSILON) {
      result.multiplyRow(r, 1.0 / pivot);
    }
    for (int i = 0; i < rows; i++) {
      if (i != r) {
        double factor = result.data[i][lead];
        result.addMultipleOfRow(i, r, -factor);
      }
    }
    lead++;
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (std::abs(result.data[i][j]) < EPSILON)
        result.data[i][j] = 0.0;
    }
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
      if (std::abs(ref_form.data[i][j]) > EPSILON) {
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
double Matrix::determinant() const {
  if (!isSquare()) {
    throw std::invalid_argument(
        "Determinant is only defined for square matrices");
  }
  if (rows == 1)
    return data[0][0];
  if (rows == 2)
    return data[0][0] * data[1][1] - data[0][1] * data[1][0];
  double det = 0.0;
  for (int j = 0; j < cols; j++) {
    Matrix submatrix = getSubmatrix(0, j);
    double cofactor = data[0][j] * submatrix.determinant();
    det += (j % 2 == 0) ? cofactor : -cofactor;
  }
  return det;
}

// Trace
double Matrix::trace() const {
  if (!isSquare()) {
    throw std::invalid_argument("Trace is only defined for square matrices");
  }
  double tr = 0.0;
  for (int i = 0; i < rows; i++) {
    tr += data[i][i];
  }
  return tr;
}

// Inverse
Matrix Matrix::inverse() const {
  if (!isSquare()) {
    throw std::invalid_argument("Only square matrices can be inverted");
  }
  double det = determinant();
  if (std::abs(det) < EPSILON) {
    throw std::runtime_error("Matrix is singular and cannot be inverted");
  }
  Matrix augmented(rows, 2 * cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      augmented.data[i][j] = data[i][j];
      augmented.data[i][j + cols] = (i == j) ? 1.0 : 0.0;
    }
  }
  augmented = augmented.rref();
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
    std::vector<double> v(rows);
    for (int i = 0; i < rows; i++)
      v[i] = data[i][j];
    for (int k = 0; k < j; k++) {
      double dotVU = 0.0, dotUU = 0.0;
      for (int i = 0; i < rows; i++) {
        dotVU += v[i] * result.data[i][k];
        dotUU += result.data[i][k] * result.data[i][k];
      }
      if (dotUU > EPSILON) {
        double proj = dotVU / dotUU;
        for (int i = 0; i < rows; i++)
          v[i] -= proj * result.data[i][k];
      }
    }
    double normSq = 0.0;
    for (int i = 0; i < rows; i++)
      normSq += v[i] * v[i];
    if (normSq > EPSILON) {
      double norm = std::sqrt(normSq);
      for (int i = 0; i < rows; i++)
        result.data[i][j] = v[i] / norm;
    }
  }
  return result;
}

bool Matrix::isSymmetric() const {
  if (!isSquare())
    return false;
  for (int i = 0; i < rows; i++) {
    for (int j = i + 1; j < cols; j++) {
      if (std::abs(data[i][j] - data[j][i]) > EPSILON)
        return false;
    }
  }
  return true;
}

bool Matrix::isLinearlyIndependent() const {
  return rank() == std::min(rows, cols);
}

std::vector<std::vector<double>> Matrix::basis() const {
  Matrix rref_form = rref();
  std::vector<std::vector<double>> basis;
  for (int i = 0; i < rows; i++) {
    bool allZero = true;
    for (int j = 0; j < cols; j++) {
      if (std::abs(rref_form.data[i][j]) > EPSILON) {
        allZero = false;
        break;
      }
    }
    if (!allZero) {
      std::vector<double> row;
      for (int j = 0; j < cols; j++)
        row.push_back(data[i][j]);
      basis.push_back(row);
    }
  }
  return basis;
}

std::pair<std::vector<double>, Matrix> Matrix::eigenvalues() const {
  if (!isSquare())
    throw std::invalid_argument("Eigenvalues only defined for square matrices");
  std::vector<double> eigenvals;
  if (rows == 2) {
    double tr = trace();
    double det = determinant();
    double discriminant = tr * tr - 4.0 * det;
    if (discriminant >= 0) {
      double sqrt_disc = std::sqrt(discriminant);
      eigenvals.push_back((tr + sqrt_disc) / 2.0);
      eigenvals.push_back((tr - sqrt_disc) / 2.0);
    } else {
      eigenvals.push_back(tr / 2.0);
      eigenvals.push_back(tr / 2.0);
    }
  } else {
    Matrix A = *this;
    for (int iter = 0; iter < 30; iter++) {
      auto [Q, R] = A.qrDecomposition();
      A = R * Q;
    }
    for (int i = 0; i < rows; i++)
      eigenvals.push_back(A.data[i][i]);
  }
  return {eigenvals, identity(rows)};
}

std::pair<Matrix, Matrix> Matrix::qrDecomposition() const {
  Matrix Q = gramSchmidt();
  Matrix R = Q.transpose() * (*this);
  return {Q, R};
}

bool Matrix::isDiagonalizable() const {
  if (!isSquare())
    return false;
  try {
    return std::abs(determinant()) > EPSILON;
  } catch (...) {
    return false;
  }
}

Matrix Matrix::identity(int n) {
  if (n > MAX_SIZE || n < 1)
    throw std::invalid_argument("Matrix size error");
  Matrix I(n, n);
  for (int i = 0; i < n; i++)
    I.data[i][i] = 1.0;
  return I;
}

Matrix Matrix::zero(int r, int c) { return Matrix(r, c); }

std::vector<double> Matrix::getRowVector(int i) const {
  if (i < 0 || i >= rows)
    throw std::out_of_range("Row index error");
  return data[i];
}

std::vector<double> Matrix::getColVector(int j) const {
  if (j < 0 || j >= cols)
    throw std::out_of_range("Col index error");
  std::vector<double> col;
  for (int i = 0; i < rows; i++)
    col.push_back(data[i][j]);
  return col;
}
