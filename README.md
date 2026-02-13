# C++ Linear Algebra Matrix Calculator (Fraction-Based)

A simplified C++ matrix library with **exact fractional arithmetic** and a user-friendly terminal interface. Perfect for educational purposes!

## Key Features

✨ **Exact Fraction Results** - No more 0.3333... See `1/3` instead!  
📏 **5×5 Maximum Size** - Optimized for basic linear algebra learning  
🎨 **Color-Coded Interface** - Beautiful terminal UI  
🔢 **12 Streamlined Operations** - Focused linear algebra tools  

## Operations

### Core Operations
1. **Addition/Subtraction** - Merged for convenience
2. **Matrix Multiplication** - Standard matrix product
3. **RREF (with Linear Independence)** - Gauss-Jordan with independence check
4. **REF (Gaussian)** - Row Echelon Form
5. **Determinant** - Essential matrix property
6. **Rank (Span)** - Dimension of column space

### Advanced Analysis
7. **Inverse** - Matrix inversion (if exists)
8. **Eigenvalues/Eigenvectors** - Spectral analysis
9. **Diagonalization** - Check for similar diagonal matrix
10. **Transpose** - Row-column swap
11. **Trace** - Sum of diagonal elements

## Quick Start

### Build
```bash
g++ -o main_full.exe main.cpp Matrix.cpp -std=c++17
```

### Run
```bash
.\main_full.exe
```

### Example Usage

**Input fractions directly:**
```
Enter number of rows: 2
Enter number of columns: 2

Enter elements row by row (integers or fractions like 1/2):
Row 1: 1/2 1/3
Row 2: 1/4 1/5
```

**Output as clean fractions:**
```
Matrix:
  [      1/2        1/3 ]
  [      1/4        1/5 ]

Determinant: 1/120
```

## Project Structure

```
proj_scratch/
├── Fraction.h          # Fraction class (rational arithmetic)
├── Matrix.h            # Matrix class header
├── Matrix.cpp          # Matrix implementation  
├── main.cpp            # Terminal UI
├── main_fraction.exe   # Compiled executable
└── README.md           # This file
```

## Technical Details

### Fraction Class
- Automatic reduction to lowest terms
- Supports input like `1/2`, `3/4`
- Exact arithmetic (no floating point errors)
- Clean display formatting

### Matrix Class
- Maximum size: 5×5
- Dynamic allocation with validation
- Fraction-based for exact results
- Comprehensive error checking

### Algorithms
- **Gaussian Elimination** - O(n³) for REF/RREF
- **Recursive Determinant** - Expansion by minors
- **Gauss-Jordan** - For matrix inverse
- **Gram-Schmidt** - Orthogonalization

## Example Test Cases

### Test 1: Determinant
```
Input:
2 2
4 2
3 1

Output: Determinant = -2
```

### Test 2: RREF with Fractions
```
Input:
2 3
1/2 1/3 1/4
1/5 1/6 1/7

Output: RREF with exact fractions
```

### Test 3: Matrix Inverse
```
Input (Identity):
2 2
1 0
0 1

Output: Same matrix (its own inverse)
```

## Limitations

- **Max Size**: 5×5 matrices only
- **No Eigenvalues**: Removed for simplicity  
- **Gram-Schmidt**: Uses approximation for normalization

## Why Fractions?

Perfect for education:
- ✅ See exact results: `1/3` not `0.333...`
- ✅ Understand patterns better
- ✅ No rounding errors
- ✅ Cleaner for homework problems

## Color Guide

- **Cyan** - Input prompts
- **Yellow** - Numbers and results
- **Green** - Success and labels
- **Red** - Errors
- **Magenta** - Section headers

---

**Perfect for linear algebra students and educators!** 🎓
