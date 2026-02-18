#include "Matrix.h"
#include "Statistics.h"
#include <iostream>
#include <limits>
#include <vector>

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
void calculateDeterminant();
void calculateInverse();
void transposeMatrix();
void calculateTrace();

void printHeader() {
  cout << BOLD << CYAN;
  cout << "\n=============================================\n";
  cout << "   LINEAR ALGEBRA CALCULATOR (MAX 5x5)\n";
  cout << "       High Precision Decimal Results\n";
  cout << "=============================================\n" << RESET;
}

void printLinearAlgebraMenu() {
  cout << BOLD << YELLOW << "\n==== Linear Algebra Menu ====\n" << RESET;
  cout << GREEN << "1.  " << RESET << "Addition/Subtraction\n";
  cout << GREEN << "2.  " << RESET << "Matrix Multiplication\n";
  cout << GREEN << "3.  " << RESET << "RREF (with Linear Independence)\n";
  cout << GREEN << "4.  " << RESET << "Determinant\n";
  cout << GREEN << "5.  " << RESET << "Inverse\n";
  cout << GREEN << "6.  " << RESET << "Transpose\n";
  cout << GREEN << "7.  " << RESET << "Trace\n";
  cout << GREEN << "0.  " << RESET << "Back to Main Menu\n";
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
  cout << YELLOW << "\nEnter elements row by row (e.g., 1.5, -4, 0.33):\n"
       << RESET;

  for (int i = 0; i < rows; i++) {
    cout << "Row " << (i + 1) << ": ";
    for (int j = 0; j < cols; j++) {
      double val;
      cin >> val;
      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid numeric input");
      }
      m.set(i, j, val);
    }
  }

  return m;
}

void waitForEnter() {
  cout << BLUE << "\nPress Enter to continue..." << RESET;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
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
      calculateDeterminant();
      break;
    case 5:
      calculateInverse();
      break;
    case 6:
      transposeMatrix();
      break;
    case 7:
      calculateTrace();
      break;
    default:
      cout << RED << "Invalid option! Please select 0-7." << RESET << endl;
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

        vector<double> data;
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
          cout << fixed << setprecision(4) << data[i]
               << (i == data.size() - 1 ? "" : ", ");
        }
        cout << endl;

        if (choice == 1) {
          double mean = Statistics::calculateMean(data);
          cout << GREEN << "Mean:         " << YELLOW << fixed
               << setprecision(4) << mean << RESET << endl;
        } else if (choice == 2) {
          double var = Statistics::calculateVariance(data);
          cout << GREEN << "Variance:     " << YELLOW << fixed
               << setprecision(4) << var << RESET << endl;
        } else if (choice == 3) {
          double stdDev = Statistics::calculateStandardDeviation(data);
          cout << GREEN << "Std Dev:      " << YELLOW << fixed
               << setprecision(4) << stdDev << RESET << endl;
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

  try {
    Matrix A = inputMatrix("Matrix A");
    Matrix B = inputMatrix("Matrix B");
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
  try {
    Matrix A = inputMatrix("Matrix A");
    Matrix B = inputMatrix("Matrix B");
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
  try {
    Matrix A = inputMatrix("Matrix");
    cout << GREEN << "\nOriginal Matrix:" << RESET;
    A.display();
    Matrix rref = A.rref();
    cout << GREEN << "RREF:" << RESET;
    rref.display();
    if (A.isLinearlyIndependent()) {
      cout << GREEN << "[OK] Result: The columns are LINEARLY INDEPENDENT"
           << RESET << endl;
    } else {
      cout << RED << "[FAIL] Result: The columns are LINEARLY DEPENDENT"
           << RESET << endl;
    }
  } catch (const exception &e) {
    cout << RED << "Error: " << e.what() << RESET << endl;
  }
}

void calculateDeterminant() {
  cout << BOLD << MAGENTA << "\n=== Determinant ===\n" << RESET;
  try {
    Matrix A = inputMatrix("Matrix");
    double det = A.determinant();
    cout << GREEN << "\nMatrix:" << RESET;
    A.display();
    cout << GREEN << "Determinant: " << YELLOW << fixed << setprecision(4)
         << det << RESET << endl;
  } catch (const exception &e) {
    cout << RED << "Error: " << e.what() << RESET << endl;
  }
}

void calculateInverse() {
  cout << BOLD << MAGENTA << "\n=== Matrix Inverse ===\n" << RESET;
  try {
    Matrix A = inputMatrix("Matrix");
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
  try {
    Matrix A = inputMatrix("Matrix");
    cout << GREEN << "\nOriginal Matrix:" << RESET;
    A.display();
    Matrix T = A.transpose();
    cout << GREEN << "Transpose:" << RESET;
    T.display();
  } catch (const exception &e) {
    cout << RED << "Error: " << e.what() << RESET << endl;
  }
}

void calculateTrace() {
  cout << BOLD << MAGENTA << "\n=== Trace ===\n" << RESET;
  try {
    Matrix A = inputMatrix("Matrix");
    double tr = A.trace();
    cout << GREEN << "\nMatrix:" << RESET;
    A.display();
    cout << GREEN << "Trace: " << YELLOW << fixed << setprecision(4) << tr
         << RESET << endl;
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
