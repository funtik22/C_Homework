#include <string>
#include <vector>


class Matrix{
    private:
        double** array2D;
        int n;
        int m;
    public:
        // Static methods
        static Matrix Identity(int _n, int _m);
        static Matrix Zero(int _n, int _m);
        static Matrix RandomDouble(int _n, int _m);
        static Matrix RandomInt(int _n, int _m);
        static Matrix FromString(std::string str);

        // Constructors and destructor
        Matrix();
        Matrix(const Matrix& other);
        Matrix(Matrix&& other);
        Matrix(int _n, int _m);
        Matrix(int _n, int _m, double val);
        Matrix(std::vector<std::vector<double>> matrix);
        Matrix(std::initializer_list<std::initializer_list<double>> list);
        ~Matrix();

        // Operators
        Matrix operator+ (const Matrix& other) const;
        Matrix operator- (const Matrix& other) const;
        Matrix operator* (const Matrix& other) const;
        Matrix operator*(double d) const;
        Matrix operator/ (const Matrix& other) const;
        Matrix operator/ (double d) const;
        Matrix operator- () const;
        bool operator== (const Matrix& other) const;
        bool operator!= (const Matrix& other) const;
        double operator() (int n, int m) const;

        // Methods
        Matrix sum(const Matrix& other) const;
        Matrix mul(const Matrix& other) const;
        Matrix mul(double d) const;
        Matrix sub(const Matrix& other) const;
        Matrix div(const Matrix& other) const;
        Matrix div(double d) const;
        Matrix T() const;
        Matrix inverse() const;
        double det() const;
        Matrix minor(int i, int j) const;
        double sumElements() const;
        void print() const;
        std::string to_string() const;

        //getter and setter
        int get_n() const;
        int get_m() const;
        double get_element(int i, int j) const;
};


std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
Matrix operator*(double d, const Matrix &matrix);