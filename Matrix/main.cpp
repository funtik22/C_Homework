#include <iostream>
#include <string>
#include "Matrix.cpp"

//#define MATRIX
#define ITERATORS

int main(){
  #ifdef MATRIX
  std::string stringMatrix;
  std::cout<<"Enter the Matrix in format [[1, 2, 3], [4, 5, 6], [7, 8, 9] ...]"<<std::endl;
  std::getline(std::cin, stringMatrix);
  
  Matrix A = Matrix::FromString(stringMatrix);
  Matrix B = Matrix::RandomInt(A.get_n(), A.get_m());
  
  A.print();
  std::cout<<std::endl;
  
  B.print();
  std::cout<<std::endl;
  
  Matrix C = ((A * B) - (B / A.transpose() * A.sumElements()) + (B.transpose() * A / B.sumElements()));
  std::cout<<C;
  #endif
  
  std::cout<<std::endl<<"------------------"<<std::endl;
  
  #ifdef ITERATORS
  Matrix m {
      {0, 1, 2},
      {3, 4, 5},
      {6, 7, 8}
  };

  for (auto&& row : m.iter_rows()) {
    for (auto&& elem : row) {
      std::cout << elem << ' ';
    }
  }

  std::cout<<std::endl<<"------------------"<<std::endl;
  
  for (auto&& col : m.iter_columns()) {
    for (auto&& elem : col) {
      std::cout << elem << ' ';
    }
  }
  #endif
}