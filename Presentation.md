# CSE130 Project Presentation: Matrix & Statistics Calculator

---

## Page 1: Title & Team
# CSE130 Project
## Matrix & Statistics Calculator

### Group Members
| Member Name | Photo Section |
| :--- | :--- |
| **Member 1** | ![Photo 1](placeholder_image_path) |
| **Member 2** | ![Photo 2](placeholder_image_path) |
| **Member 3** | ![Photo 3](placeholder_image_path) |
| **Member 4** | ![Photo 4](placeholder_image_path) |

---

## Page 2: Project Overview
### Introduction
A professional-grade terminal application for high-precision numerical analysis, handling complex Linear Algebra and Descriptive Statistics.

### Project Objective
To provide an efficient and accurate C++ tool for students and educators to solve mathematical problems without relying on heavy graphical software.

### Language & Structure
- **Language:** C++ (C++17)
- **Structure:**
    - `Matrix.h/cpp`: Core Matrix logic and algorithms.
    - `Statistics.h`: Statistical utility functions.
    - `main.cpp`: Interactive color-coded UI.

### Key Features
- Floating point stability with `EPSILON` threshold.
- Color-coded terminal UI for better UX.
- Support for matrices up to 5x5.

---

## Page 3: Operations
### Linear Algebra Operations
- Matrix Addition, Subtraction, & Multiplication
- Determinant & Trace
- Inverse & Transpose

### Statistical Operations
- Data Extraction (Rows/Columns)
- Mean Calculation
- Variance Analysis
- Standard Deviation

---

## Page 4: Technical Deep Dive
# Code Logic and Functions Explanation

---

## Page 5: Addition & Subtraction
### Code Snippet
```cpp
Matrix Matrix::operator+(const Matrix &other) const {
  Matrix result(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result.data[i][j] = data[i][j] + other.data[i][j];
    }
  }
  return result;
}
```

### Explanation
The function iterates through each element $(i, j)$ of two matrices and performs element-wise addition. Subtraction follows the same logic using the `-` operator.

### Example
Input $A = \begin{bmatrix} 1 & 2 \\ 3 & 4 \end{bmatrix}, B = \begin{bmatrix} 5 & 6 \\ 7 & 8 \end{bmatrix} \implies A+B = \begin{bmatrix} 6 & 8 \\ 10 & 12 \end{bmatrix}$

---

---

## Page 7: Determinant
### Code Snippet
```cpp
double Matrix::determinant() const {
  if (rows == 1) return data[0][0];
  if (rows == 2) return data[0][0] * data[1][1] - data[0][1] * data[1][0];
  double det = 0.0;
  for (int j = 0; j < cols; j++) {
    Matrix submatrix = getSubmatrix(0, j);
    double cofactor = data[0][j] * submatrix.determinant();
    det += (j % 2 == 0) ? cofactor : -cofactor;
  }
  return det;
}
```

### Explanation
Implements Laplace expansion (expansion by minors). For larger matrices, it recursively breaks down the matrix into submatrices until it reaches the base case (2x2).

---


---

## Page 9: Matrix Inverse
### Code Snippet
```cpp
Matrix Matrix::inverse() const {
  Matrix augmented(rows, 2 * cols);
  // ... augment matrix with Identity Matrix [A|I] ...
  augmented = augmented.rref();
  // ... extract the right side [I|A^-1] ...
  return result;
}
```

### Explanation
Uses the Augmented Matrix method. We attach an identity matrix to the right of $A$, apply Gauss-Jordan elimination to turn the left side into Identity, which results in $A^{-1}$ on the right.

---

## Page 10: Transpose
### Code Snippet
```cpp
Matrix Matrix::transpose() const {
  Matrix result(cols, rows);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result.data[j][i] = data[i][j];
    }
  }
  return result;
}
```

### Explanation
A simple operation where the row index and column index are swapped: $A_{ij}$ becomes $A_{ji}$.

---

## Page 11: Multiplication
### Code Snippet
```cpp
Matrix Matrix::operator*(const Matrix &other) const {
  Matrix result(rows, other.cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < other.cols; j++) {
      for (int k = 0; k < cols; k++) {
        result.data[i][j] += data[i][k] * other.data[k][j];
      }
    }
  }
  return result;
}
```

### Explanation
Implements standard dot-product multiplication. The number of columns in the first matrix must match the number of rows in the second.

---

## Page 12: Trace (Diagonal Sum)
### Code Snippet
```cpp
double Matrix::trace() const {
  double tr = 0.0;
  for (int i = 0; i < rows; i++) {
    tr += data[i][i];
  }
  return tr;
}
```

### Explanation
Computes the sum of elements on the main diagonal. This is a key property used in matrix characterization.

---

## Page 13: User Interface
### UI Design
| Terminal View | Description |
| :--- | :--- |
| ![UI Menu](placeholder_ui_image) | **Main Menu:** Color-coded options for easy navigation. |
| ![Operation View](placeholder_op_image) | **Data Input:** Clean prompts with error handling for non-numeric input. |
| ![Result View](placeholder_result_image) | **Output:** High-precision results (4 decimal places). |

---

## Page 14: Summary & Conclusion
### Summary
The project successfully delivers a robust, high-precision C++ tool for Linear Algebra and Statistics. Its modular structure allows for easy expansion (e.g., adding more statistical tests or 3D transformations).

### Conclusion
Building this calculator deepened our understanding of numerical stability, C++ optimization, and the practical implementation of abstract mathematical concepts.

**Thank You! Any Questions?**
