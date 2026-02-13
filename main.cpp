#include "Matrix.h"
#include "Statistics.h"
#include <iostream>
#include <limits>

using namespace std;

// Color codes for terminal
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Forward declarations
void matrixAddSubtract();
void matrixMultiplication();
void calculateRREF();
void calculateREF();
void calculateDeterminant();
void calculateRank();
void calculateInverse();
void transposeMatrix();
void calculateTrace();
void calculateEigenvalues();
void checkDiagonalization();

void printHeader() {
  cout << BOLD << CYAN;
  cout << "\n=============================================\n";
  cout << "   LINEAR ALGEBRA CALCULATOR (MAX 5x5)\n";
  cout << "     Fraction-Based Exact Results\n";
  cout << "=============================================\n" << RESET;
}

void printLinearAlgebraMenu() {
  cout << BOLD << YELLOW << "\n==== Linear Algebra Menu ====\n" << RESET;
  cout << GREEN << "1.  " << RESET << "Addition/Subtraction\n";
  cout << GREEN << "2.  " << RESET << "Matrix Multiplication\n";
  cout << GREEN << "3.  " << RESET << "RREF (with Linear Independence)\n";
  cout << GREEN << "4.  " << RESET << "REF (Gaussian)\n";
  cout << GREEN << "5.  " << RESET << "Determinant\n";
  cout << GREEN << "6.  " << RESET << "Rank (Span)\n";
  cout << GREEN << "7.  " << RESET << "Inverse\n";
  cout << GREEN << "8.  " << RESET << "Eigenvalues/Eigenvectors\n";
  cout << GREEN << "9.  " << RESET << "Diagonalization\n";
  cout << GREEN << "10. " << RESET << "Transpose\n";
  cout << GREEN << "11. " << RESET << "Trace\n";
  cout << GREEN << "0.  " << RESET << "Exit\n";
  cout << BOLD << YELLOW << "============================\n" << RESET;
}

Matrix inputMatrix(const string &name) {
  int rows, cols;
  cout << CYAN << "\nEnter number of rows for " << name << " (max " << MAX_SIZE
       << "): " << RESET;
  cin >> rows;
  cout << CYAN << "Enter number of columns for " << name << " (max " << MAX_SIZE
       << "): " << RESET;
  cin >> cols;

  if (rows < 1 || rows > MAX_SIZE || cols < 1 || cols > MAX_SIZE) {
    throw std::invalid_argument("Matrix dimensions must be between 1 and " +
                                std::to_string(MAX_SIZE));
  }

  Matrix m(rows, cols);
  cout << YELLOW
       << "\nEnter elements row by row (integers or fractions like 1/2):\n"
       << RESET;

  for (int i = 0; i < rows; i++) {
    cout << "Row " << (i + 1) << ": ";
    for (int j = 0; j < cols; j++) {
      string input;
      cin >> input;

      // Parse fraction or integer
      size_t slashPos = input.find('/');
      if (slashPos != string::npos) {
        // It's a fraction
        long long num = stoll(input.substr(0, slashPos));
        long long den = stoll(input.substr(slashPos + 1));
        m.set(i, j, Fraction(num, den));
      } else {
        // It's an integer
        long long num = stoll(input);
        m.set(i, j, Fraction(num, 1));
      }
    }
  }

  return m;
}

void waitForEnter() {
  cout << BLUE << "\nPress Enter to continue..." << RESET;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
}

vector<Fraction> inputVector() {
  int n;
  cout << CYAN << "\nEnter number of elements: " << RESET;
  cin >> n;
  if (n < 1)
    throw std::invalid_argument("Size must be at least 1");

  vector<Fraction> data;
  cout << YELLOW << "\nEnter elements (integers or fractions like 1/2):\n"
       << RESET;
  for (int i = 0; i < n; i++) {
    cout << "Element " << (i + 1) << ": ";
    string input;
    cin >> input;
    size_t slashPos = input.find('/');
    if (slashPos != string::npos) {
      long long num = stoll(input.substr(0, slashPos));
      long long den = stoll(input.substr(slashPos + 1));
      data.push_back(Fraction(num, den));
    } else {
      data.push_back(stoll(input));
    }
  }
  return data;
}

void linearAlgebraMenu() {
  int choice;
  while (true) {
    clearScreen();
    printHeader();
    printLinearAlgebraMenu();

    cout << CYAN << "Select an option: " << RESET;
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << RED << "Invalid input! Please enter a number." << RESET << endl;
      waitForEnter();
      continue;
    }

    if (choice == 0)
      break;

    switch (choice) {
    case 1:
      matrixAddSubtract();
      break;
    case 2:
      matrixMultiplication();
      break;
    case 3:
      calculateRREF();
      break;
    case 4:
      calculateREF();
      break;
    case 5:
      calculateDeterminant();
      break;
    case 6:
      calculateRank();
      break;
    case 7:
      calculateInverse();
      break;
    case 8:
      calculateEigenvalues();
      break;
    case 9:
      checkDiagonalization();
      break;
    case 10:
      transposeMatrix();
      break;
    case 11:
      calculateTrace();
      break;
    default:
      cout << RED << "Invalid option! Please select 0-11." << RESET << endl;
    }

    waitForEnter();
  }
}

void statisticalMenu() {
  int choice;
  while (true) {
    clearScreen();
    printHeader();
    cout << BOLD << YELLOW << "\n==== Statistical Menu ====\n" << RESET;
    cout << GREEN << "1. " << RESET << "Calculate Mean\n";
    cout << GREEN << "2. " << RESET << "Calculate Variance\n";
    cout << GREEN << "3. " << RESET << "Calculate Standard Deviation\n";
    cout << GREEN << "0. " << RESET << "Back to Main Menu\n";
    cout << BOLD << YELLOW << "==========================\n" << RESET;

    cout << CYAN << "Select an option: " << RESET;
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << RED << "Invalid input! Please enter a number." << RESET << endl;
      waitForEnter();
      continue;
    }

    if (choice == 0)
      break;

    if (choice >= 1 && choice <= 3) {
      try {
        Matrix M = inputMatrix("Source Matrix");
        cout << CYAN << "\nChoose extraction:\n";
        cout << "  1. Row (rA, rB, ...)\n";
        cout << "  2. Column (cA, cB, ...)\n";
        cout << "Enter choice: " << RESET;
        int type;
        cin >> type;

        vector<Fraction> data;
        if (type == 1) {
          int r;
          cout << CYAN << "Enter row index (1-" << M.getRows()
               << "): " << RESET;
          cin >> r;
          data = M.getRowVector(r - 1);
        } else if (type == 2) {
          int c;
          cout << CYAN << "Enter column index (1-" << M.getCols()
               << "): " << RESET;
          cin >> c;
          data = M.getColVector(c - 1);
        } else {
          cout << RED << "Invalid choice!" << RESET << endl;
          waitForEnter();
          continue;
        }

        cout << GREEN << "\nSelected Data: " << RESET;
        for (size_t i = 0; i < data.size(); i++) {
          cout << data[i] << (i == data.size() - 1 ? "" : ", ");
        }
        cout << endl;

        if (choice == 1) {
          Fraction mean = Statistics::calculateMean(data);
          cout << GREEN << "Mean:         " << YELLOW << mean << RESET << " ("
               << fixed << setprecision(4) << mean.toDouble() << ")" << endl;
        } else if (choice == 2) {
          Fraction var = Statistics::calculateVariance(data);
          cout << GREEN << "Variance:     " << YELLOW << var << RESET << " ("
               << var.toDouble() << ")" << endl;
        } else if (choice == 3) {
          double stdDev = Statistics::calculateStandardDeviation(data);
          cout << GREEN << "Std Dev:      " << YELLOW << fixed << stdDev
               << RESET << endl;
        }
      } catch (const exception &e) {
        cout << RED << "Error: " << e.what() << RESET << endl;
      }
    } else {
      cout << RED << "Invalid option!" << RESET << endl;
    }
    waitForEnter();
  }
}

void matrixAddSubtract() {
  cout << BOLD << MAGENTA << "\n=== Matrix Addition/Subtraction ===\n" << RESET;
  cout << CYAN << "Choose operation:\n";
  cout << "  1. Addition (A + B)\n";
  cout << "  2. Subtraction (A - B)\n";
  cout << "Enter choice: " << RESET;

  int choice;
  cin >> choice;

  if (choice != 1 && choice != 2) {
    cout << RED << "Invalid choice!" << RESET << endl;
    return;
  }

  Matrix A = inputMatrix("Matrix A");
  Matrix B = inputMatrix("Matrix B");

  try {
    Matrix C = (choice == 1) ? (A + B) : (A - B);
    cout << GREEN << "\nMatrix A:" << RESET;
    A.display();
    cout << GREEN << "Matrix B:" << RESET;
    B.display();
    cout << GREEN << ((choice == 1) ? "Result (A + B):" : "Result (A - B):")
         << RESET;
    C.display();
  } catch (const exception &e) {
    cout << RED << "Error: " << e.what() << RESET << endl;
  }
}

void matrixMultiplication() {
  cout << BOLD << MAGENTA << "\n=== Matrix Multiplication ===\n" << RESET;
  Matrix A = inputMatrix("Matrix A");
  Matrix B = inputMatrix("Matrix B");

  try {
    Matrix C = A * B;
    cout << GREEN << "\nMatrix A:" << RESET;
    A.display();
    cout << GREEN << "Matrix B:" << RESET;
    B.display();
    cout << GREEN << "Result (A × B):" << RESET;
    C.display();
  } catch (const exception &e) {
    cout << RED << "Error: " << e.what() << RESET << endl;
  }
}

void calculateRREF() {
  cout << BOLD << MAGENTA << "\n=== RREF (with Linear Independence) ===\n"
       << RESET;
  Matrix A = inputMatrix("Matrix");

  cout << GREEN << "\nOriginal Matrix:" << RESET;
  A.display();

  Matrix rref = A.rref();
  cout << GREEN << "RREF:" << RESET;
  rref.display();

  bool independent = A.isLinearlyIndependent();
  if (independent) {
    cout << GREEN << "[OK] Result: The columns are LINEARLY INDEPENDENT"
         << RESET << endl;
    cout << CYAN << "(Rank equals number of columns)" << RESET << endl;
  } else {
    cout << RED << "[FAIL] Result: The columns are LINEARLY DEPENDENT" << RESET
         << endl;
    cout << CYAN << "(Rank is less than number of columns)" << RESET << endl;
  }
}

void calculateREF() {
  cout << BOLD << MAGENTA << "\n=== REF (Row Echelon Form) ===\n" << RESET;
  Matrix A = inputMatrix("Matrix");

  cout << GREEN << "\nOriginal Matrix:" << RESET;
  A.display();

  Matrix ref = A.ref();
  cout << GREEN << "REF:" << RESET;
  ref.display();
}

void calculateDeterminant() {
  cout << BOLD << MAGENTA << "\n=== Determinant ===\n" << RESET;
  Matrix A = inputMatrix("Matrix");

  try {
    Fraction det = A.determinant();
    cout << GREEN << "\nMatrix:" << RESET;
    A.display();
    cout << GREEN << "Determinant: " << YELLOW << det << RESET << endl;
  } catch (const exception &e) {
    cout << RED << "Error: " << e.what() << RESET << endl;
  }
}

void calculateRank() {
  cout << BOLD << MAGENTA << "\n=== Rank (Span) ===\n" << RESET;
  Matrix A = inputMatrix("Matrix");

  int r = A.rank();
  cout << GREEN << "\nMatrix:" << RESET;
  A.display();
  cout << GREEN << "Rank: " << YELLOW << r << RESET << endl;
}

void calculateInverse() {
  cout << BOLD << MAGENTA << "\n=== Matrix Inverse ===\n" << RESET;
  Matrix A = inputMatrix("Matrix");

  try {
    Matrix inv = A.inverse();
    cout << GREEN << "\nOriginal Matrix:" << RESET;
    A.display();
    cout << GREEN << "Inverse:" << RESET;
    inv.display();
  } catch (const exception &e) {
    cout << RED << "Error: " << e.what() << RESET << endl;
  }
}

void transposeMatrix() {
  cout << BOLD << MAGENTA << "\n=== Matrix Transpose ===\n" << RESET;
  Matrix A = inputMatrix("Matrix");

  cout << GREEN << "\nOriginal Matrix:" << RESET;
  A.display();

  Matrix T = A.transpose();
  cout << GREEN << "Transpose:" << RESET;
  T.display();
}

void calculateTrace() {
  cout << BOLD << MAGENTA << "\n=== Trace ===\n" << RESET;
  Matrix A = inputMatrix("Matrix");

  try {
    Fraction tr = A.trace();
    cout << GREEN << "\nMatrix:" << RESET;
    A.display();
    cout << GREEN << "Trace: " << YELLOW << tr << RESET << endl;
  } catch (const exception &e) {
    cout << RED << "Error: " << e.what() << RESET << endl;
  }
}

void calculateEigenvalues() {
  cout << BOLD << MAGENTA << "\n=== Eigenvalues/Eigenvectors ===\n" << RESET;
  Matrix A = inputMatrix("Matrix");

  try {
    auto [eigenvals, eigenvecs] = A.eigenvalues();
    cout << GREEN << "\nMatrix:" << RESET;
    A.display();

    cout << GREEN << "\nEigenvalues (approximate, as fractions):" << RESET
         << endl;
    for (size_t i = 0; i < eigenvals.size(); i++) {
      cout << "  Lambda " << (i + 1) << " = " << YELLOW << eigenvals[i] << RESET
           << endl;
    }
  } catch (const exception &e) {
    cout << RED << "Error: " << e.what() << RESET << endl;
  }
}

void checkDiagonalization() {
  cout << BOLD << MAGENTA << "\n=== Diagonalization ===\n" << RESET;
  Matrix A = inputMatrix("Matrix");

  try {
    bool diag = A.isDiagonalizable();
    cout << GREEN << "\nMatrix:" << RESET;
    A.display();

    if (diag) {
      cout << GREEN << "[YES] The matrix is DIAGONALIZABLE" << RESET << endl;
      cout << CYAN << "(Has n linearly independent eigenvectors)" << RESET
           << endl;
    } else {
      cout << RED << "[NO] The matrix is NOT diagonalizable" << RESET << endl;
    }
  } catch (const exception &e) {
    cout << RED << "Error: " << e.what() << RESET << endl;
  }
}

int main() {
  int choice;

  while (true) {
    clearScreen();
    printHeader();
    cout << BOLD << YELLOW << "\n==== Main Menu ====\n" << RESET;
    cout << GREEN << "1. " << RESET << "Linear Algebra Operations\n";
    cout << GREEN << "2. " << RESET << "Statistical Operations\n";
    cout << GREEN << "0. " << RESET << "Exit\n";
    cout << BOLD << YELLOW << "===================\n" << RESET;

    cout << CYAN << "Select an option: " << RESET;
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << RED << "Invalid input! Please enter a number." << RESET << endl;
      waitForEnter();
      continue;
    }

    switch (choice) {
    case 0:
      cout << GREEN << "\nThank you for using Linear Algebra Calculator!\n"
           << RESET;
      return 0;
    case 1:
      linearAlgebraMenu();
      break;
    case 2:
      statisticalMenu();
      break;
    default:
      cout << RED << "Invalid option! Please select 0-2." << RESET << endl;
      waitForEnter();
    }
  }

  return 0;
}
