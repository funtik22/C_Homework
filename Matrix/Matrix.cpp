#include "Matrix.hpp"
#include <ctime>
#include <random>
#include <stack>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>



Matrix Matrix::Identity(int _n, int _m){
    Matrix matrix(_n, _m);
    for(int i = 0; i<std::min(_n, _m); i++){
        matrix.array2D[i*matrix.m+i]= 1;
    }
    return matrix;
}


Matrix Matrix::Zero(int _n, int _m){
    Matrix matrix(_n, _m);
    return matrix;
}


Matrix Matrix::RandomDouble(int _n, int _m){
    Matrix matrix(_n, _m);
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<double> urd(0, 5);
    for(int i = 0; i<_n; i++){
       for(int j = 0; j<_m; j++){
            matrix.array2D[i*matrix.m+j] = urd(gen);
       }
    }
    return matrix;
}


Matrix Matrix::RandomInt(int _n, int _m){
    Matrix matrix(_n, _m);
    std::srand(time(NULL));
    for(int i = 0; i<_n; i++){
       for(int j = 0; j<_m; j++){
            matrix.array2D[i*matrix.m+j] = std::rand()%5;
       }
    }
    return matrix;
}


Matrix Matrix::FromString(std::string str){
    std::stack<char> staples;
    std::vector<double> numbers;
    std::vector<std::vector<double>> matrix;
    std::string number = "";
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end()); // delete spaces
    for(int i = 0; i<str.size(); i++){
        if(!(str[i]==',' || str[i]=='[' || str[i]==']' || str[i]=='.' || isdigit(str[i]))){
            throw std::runtime_error{"You enter invalid characters"};
        }
        if(str[i] == '['){
            staples.push('[');
        }
        if(str[i] == ','){ 
            if(number!=""){
                numbers.push_back(stod(number));
                number = "";
            }
        }
        if(str[i] == ']'){
            if(number!=""){
                numbers.push_back(stod(number));
                number = "";
            }
            if(matrix.size()!=0 && numbers.size()!=matrix[0].size() && str[i-1]!=']'){
                throw std::runtime_error{"Numbers elements in line doesn't match"};
            }
            if(staples.empty()){
                throw std::runtime_error("The sequence of parentneses is incorrect");
            }
            
            staples.pop();
            if(numbers.size()!=0){
                matrix.push_back(numbers);
                numbers.clear();
            }
        }
        if((int(str[i])>=48 && int(str[i])<=57) || str[i]=='.'){
            number+=str[i];
        }     
    }
    if(!staples.empty()){
        throw std::runtime_error("The sequence of parentneses is incorrect");
    }
    return Matrix(matrix);
 }


Matrix::Matrix(): n(), m(), array2D(){}


Matrix::Matrix(const Matrix &other){
    array2D = new double [n*m];
    for(int i = 0; i<other.n; i++){
        for(int j = 0; j<other.m; j++){
            array2D[i*other.m+j] = other.array2D[i*other.m+j];
        }
    }
    n = other.n;
    m = other.m;
}


Matrix::Matrix(Matrix&& other) {
    array2D = other.array2D;
    n = other.n;
    m = other.m;

    other.array2D = nullptr;
    other.n = 0;
    other.m = 0;
}


Matrix::Matrix(int _n, int _m): n(_n), m(_m){
    array2D = new double [n*m];
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            array2D[i*m+j] = 0;
        }
    }
}


Matrix::Matrix(int _n, int _m, double val): n(_n), m(_m){
    array2D = new double [n*m];
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            array2D[i*m+j] = val;
        }
    }
}


Matrix::Matrix(std::vector<std::vector<double>> matrix){
    n = matrix.size();
    m = matrix[0].size();
    array2D = new double [n*m];
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            array2D[i*m+j] = matrix[i][j];
        }
    }
}


Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list){
    n = list.size();
    m = list.begin()->size();
    array2D = new double [n*m];
    int i = 0, j = 0; 
    for(std::initializer_list<double> line: list){
        if(line.size()!=m){
            throw std::runtime_error("error in list");
        }
        j = 0;
        for(double element: line){
            array2D[i*m+j] = element;
            j++;
        }
        i++;
    }
}


Matrix::~Matrix() {
    delete [] array2D;
}


Matrix Matrix::sum(const Matrix& other) const{
    Matrix matrix(n, m);
        if(n!=other.n || m!=other.m){
            throw std::runtime_error("Error: Matrix have different sizes");
        }
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                matrix.array2D[i*m+j] = array2D[i*m+j] + other.array2D[i*m+j];
            }
        }
    return matrix;
}


Matrix Matrix::sub(const Matrix& other) const{
    Matrix matrix(n, m);
        if(n!=other.n || m!=other.m){
            throw std::runtime_error("Error: Matrix have different sizes");
        }
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                matrix.array2D[i*m+j] = array2D[i*m+j] - other.array2D[i*m+j];
            }
        }
    return matrix;
}


Matrix Matrix::mul(const Matrix& other) const{
    Matrix matrix(n, other.m);
    if(m!=other.n){
        throw std::runtime_error("Error: Matrix have the wrong sizes");
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<other.m; j++){
            for(int x = 0; x<m; x++){
                matrix.array2D[i*m+j] = matrix.array2D[i*m+j] + array2D[i*m+x] * other.array2D[x*m+j];
            }

        }
    }
    return matrix;
}


Matrix Matrix::mul(double d) const{
    Matrix matrix(n, m);
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            matrix.array2D[i*m+j] = d * array2D[i*m+j];  
        }
    }
    return matrix;
}


//  A/B = A*inv(B)
Matrix Matrix::div(const Matrix& other) const{
    if(m!=other.n){
        throw std::runtime_error("Error: Matrix have the wrong sizes");
    }
    return this->mul(other.inverse());
}


Matrix Matrix::div(double d) const{
    Matrix matrix(n, m);
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            matrix.array2D[i*m+j] = array2D[i*m+j]/d;
        }
    }
    return matrix;
} 


Matrix Matrix::T() const{
    Matrix trans(m, n);
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            trans.array2D[j*n+i] = array2D[i*m+j];
        }
    }
    return trans;
}


Matrix Matrix::operator+ (const Matrix &other) const{
    return this->sum(other);
}


Matrix Matrix::operator- (const Matrix &other) const{
    return this->sub(other);
}


Matrix Matrix::operator* (const Matrix &other) const{
    return this->mul(other);
}


Matrix Matrix::operator* (double d) const{
    return this->mul(d);
}


Matrix operator*(double d, const Matrix &matrix){
    return matrix.mul(d);
}


Matrix Matrix::operator/ (const Matrix &other) const{
    return this->div(other);
}


Matrix Matrix::operator/ (double d) const{
    return this->div(d);
}


//use finding attached Matrix
Matrix Matrix::inverse() const{
    if(this->det() == 0){
        throw std::runtime_error("Inverse matrix isn't exist because det=0");
    }
    Matrix attached(n, m);
    if(n!=m){
        throw std::runtime_error("The matrix isn't square");
    }
    Matrix inv = this->T();
    for(int i  = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            attached.array2D[i*m+j] = inv.minor(i, j).det() *  pow(-1, i+j);
        }
    }
    return attached.div(this->det());
}

// this algorithm use "decomposition by the first line"
 double Matrix::det() const{
     if(n!=m){
         throw std::runtime_error("The matrix isn't square");
     }
     if(n == 1) return array2D[0];
     if (n == 2) return array2D[0]*array2D[m+1] - array2D[m]*array2D[1];
     double det = 0; 
     for(int j = 0; j<n; j++){
        det += array2D[j] * this->minor(0, j).det() * pow(-1, j);
     }
     return det;
 }


Matrix Matrix::minor(int x, int y) const{
    Matrix matrix(n-1, n-1);
    int _i = 0, _j = 0;
    for(int i = 0; i<n; i++){
        if(i == x){
            continue;
        }
        _j = 0;
        for(int j = 0; j<n; j++){
            if(j == y){
                continue;
            }
            matrix.array2D[_i*(n-1)+_j] = array2D[i*m+j];
            _j++;
        }
        _i++;
    }
    return matrix;
}


double Matrix::sumElements() const{
    double sum = 0;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            sum+=array2D[i*m+j];
        }
    }
    return sum;
}


void Matrix::print() const{
    if(n == 0 || m == 0 || array2D==nullptr){
        std::cout<<"Empty matrix"<<std::endl;
        return;
    }
    std::cout.precision(4);
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            std::cout<<std::setw(6)<<array2D[i*m+j]<<" ";
        }
        std::cout<<std::endl;
    }
}


std::string Matrix::to_string() const{
    std::string out = ""; 
    if(n == 0 || m == 0 || array2D==nullptr){
        out = "Empty matrix";
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            out=out + std::to_string(array2D[i*m+j]) + " ";
        }
        out+='\n';
    }
    return out;
}


std::ostream& operator<<(std::ostream &os, const Matrix &matrix){
    os.precision(4);
    for(int i = 0; i<matrix.get_n(); i++){
        for(int j = 0; j<matrix.get_m(); j++){
            os<<std::setw(6)<<matrix.get_element(i, j)<<" ";
        }
        os<<std::endl;
    }
    return os;
}


bool Matrix::operator==(const Matrix &other) const{
    bool out = true;
    if(n!=other.n || m!=other.m){
        out = false;        
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(array2D[i*m+j] != other.array2D[i*m+j]){
                out = false;
            }
        }
    }
    return out;
}


bool Matrix::operator!=(const Matrix &other) const{
    return !((*this)==other);
}


double Matrix::operator()(int i, int j) const{
    if(i>=n || j>=m){
        throw std::out_of_range("out of range of matrix");
    }
    return array2D[i*m+j];
}


int Matrix::get_n() const{
    return n;
}


int Matrix::get_m() const{
    return m;
}


double Matrix::get_element(int i, int j) const{
    return array2D[i*m+j]; 
}