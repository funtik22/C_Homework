#include <iostream>
#include <string>
#include "Matrix.cpp"

int main(){
  std::string stringMatrix;
  std::cout<<"Enter the Matrix in format [[1, 2, 3], [4, 5, 6], [7, 8, 9] ...]"<<std::endl;
  std::getline(std::cin, stringMatrix);
  
  Matrix A = Matrix::FromString(stringMatrix);
  Matrix B = Matrix::RandomInt(A.get_n(), A.get_m());
  
  A.print();
  std::cout<<std::endl;
  
  B.print();
  std::cout<<std::endl;
  
  Matrix C = ((A * B) - (B / A.T() * A.sumElements()) + (B.T() * A / B.sumElements()));
  std::cout<<C;
}