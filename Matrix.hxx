#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF
#include "Vector.hxx"

class Matrix
{
private:
    double** mData; // entries of matrix
    int mNumRows, mNumCols; // dimensions
public:
    Matrix(const Matrix& otherMatrix);
    Matrix(int numRows, int numCols);
    ~Matrix();
    int GetNumberOfRows() const;
    int GetNumberOfColumns() const;
    void Print();
    double& operator()(int i, int j);
    //overloaded assignment operator
    Matrix& operator=(const Matrix& otherMatrix);
    Matrix operator+(double constant) const; // unary +
    Matrix operator-(double constant) const; // unary -
    Matrix operator+(const Matrix& m1) const; // binary +
    Matrix operator-(const Matrix& m1) const; // binary -
    // scalar multiplication
    Matrix operator*(double a) const;
    // Matrix multiplication
    Matrix operator*(const Matrix& otherMatrix);
    Matrix CalculateInverse() const;
    Matrix Transpose() const;
    // declare vector multiplication friendship
    friend Vector operator*(const Matrix& m, const Vector& v);
    friend Vector operator*(const Vector& v, const Matrix& m);
};
// prototype signatures for friend operators
Vector operator*(const Matrix& m, const Vector& v);
Vector operator*(const Vector& v, const Matrix& m);

#endif