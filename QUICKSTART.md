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
| 4 | RREF | Any matrix | Solve linear systems |
| 5 | REF | Any matrix | Find pivot positions |
| 6 | Determinant | Square matrix | Check invertibility |
| 7 | Rank | Any matrix | Find dimension of span |
| 8 | Linear Independence | Any matrix | Check column independence |
| 9 | Basis | Any matrix | Extract basis vectors |
| 10 | Eigenvalues | Square matrix | Find principal components |
| 11 | Inverse | Non-singular square | Solve AX = B |
| 12 | Orthogonality | Square matrix | Verify orthogonal basis |
| 13 | Gram-Schmidt | Any matrix | Orthonormalize vectors |
| 14 | Diagonalization | Square matrix | Simplify matrix powers |
| 15 | SVD | Any matrix | Data compression, PCA |
| 16 | Transpose | Any matrix | Switch rows/columns |
| 17 | Trace | Square matrix | Sum of eigenvalues |

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

**For RREF:**
```
3 4
1 2 -1 3
2 4 1 -2
-3 -6 3 4
```

**Orthogonal matrix:**
```
2 2
0.8 -0.6
0.6 0.8
```

### Tips
- Start with small matrices (2×2 or 3×3) to understand operations
- Use option 4 (RREF) to solve systems of linear equations
- Option 8 checks if columns form linearly independent set
- Option 13 (Gram-Schmidt) creates orthonormal basis from any set
- Colors may not work in old terminals - use Windows Terminal or modern shell
