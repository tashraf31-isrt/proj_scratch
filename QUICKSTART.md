## C++ Matrix Calculator - Quick Start Guide

### Compile & Run
```bash
g++ -o main.exe main.cpp Matrix.cpp -std=c++17
./main.exe
```

### Menu Options Quick Reference

| # | Operation | Input Requirements | Example Use Case |
|---|-----------|-------------------|------------------|
| 1 | Addition | Two matrices (same size) | Combine transformations |
| 2 | Subtraction | Two matrices (same size) | Find difference |
| 3 | Multiplication | A(m×n) × B(n×p) | Compose transformations |
| 4 | Determinant | Square matrix | Check invertibility |
| 7 | Rank | Any matrix | Find dimension of span |
| 8 | Linear Independence | Any matrix | Check column independence |
| 9 | Basis | Any matrix | Extract basis vectors |
| 10 | Inverse | Non-singular square | Solve AX = B |
| 11 | Orthogonality | Square matrix | Verify orthogonal basis |
| 12 | Gram-Schmidt | Any matrix | Orthonormalize vectors |
| 13 | SVD | Any matrix | Data compression, PCA |
| 14 | Transpose | Any matrix | Switch rows/columns |
| 15 | Trace | Square matrix | Sum of main diagonal |

### Sample Matrices for Testing

**Identity 2×2:**
```
2 2
1 0
0 1
```

**Simple 2×2 for determinant:**
```
2 2
4 2
3 1
```
Determinant = -2



**Orthogonal matrix:**
```
2 2
0.8 -0.6
0.6 0.8
```

### Tips
- Start with small matrices (2×2 or 3×3) to understand operations
- Option 8 checks if columns form linearly independent set
- Option 13 (Gram-Schmidt) creates orthonormal basis from any set
- Colors may not work in old terminals - use Windows Terminal or modern shell
