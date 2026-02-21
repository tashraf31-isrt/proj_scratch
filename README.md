# C++ Linear Algebra & Statistics Calculator (Decimal-Based)

A professional C++ library for **Linear Algebra** and **Statistical Analysis** with high-precision decimal output and a user-friendly terminal interface.

## Key Features

✨ **High Precision** - Uses `double` arithmetic with 4-decimal-place output.
📏 **5×5 Maximum Size** - Optimized for linear algebra learning and matrix analysis.
🎨 **Color-Coded Interface** - Premium terminal UI with intuitive navigation.
📊 **Matrix-Based Stats** - Extract rows or columns from matrices for statistical calculations.
🔢 **9 Operations** - Comprehensive suite across Algebra and Statistics.

## Operations

### Linear Algebra
1.  **Addition/Subtraction**
2.  **Matrix Multiplication**
3.  **Determinant** - Using triangular reduction for stability.
4.  **Inverse** - Full matrix inversion.
5.  **Transpose** - Row-column swap.
6.  **Trace** - Sum of main diagonal.

### Statistical Analysis
1.  **Mean** - Calculate the average of a selected row or column.
2.  **Variance** - Sample variance with Bessel's correction (n-1).
3.  **Standard Deviation** - Square root of variance.

## Quick Start

### Build
```bash
g++ -o main_full.exe main.cpp Matrix.cpp -std=c++17
```

### Run
```bash
.\main_full.exe
```

## Project Structure

```
proj_scratch/
├── Matrix.h            # Matrix class header
├── Matrix.cpp          # Matrix implementation  
├── Statistics.h        # Statistical utilities
├── main.cpp            # Terminal UI
├── .gitignore          # Repository cleanup (ignores binaries)
└── README.md           # This file
```

## Technical Details

### Numerical Stability
The project uses an `EPSILON` threshold (1e-9) for all zero-checks to ensure that floating-point inaccuracies do not interfere with calculations.

## Example Test Case: Statistics
1. Enter a 1x3 Matrix: `[1.0, 2.0, 3.0]`
2. Go to **Statistical Menu** -> **Calculate Mean**
3. Select **Row 1**
4. Output: `Mean: 2.0000`

---
**Designed for students, educators, and developers interested in numerical methods!** 🎓
