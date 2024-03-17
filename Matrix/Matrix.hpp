#include <string>
#include <vector>


class Matrix{
    private:
        double* array2D;
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

        //iterators
        class RowView{
             // я не придумал, как не передавать в RowView значения)
            private:
                double* row;
                int m;
            public:
                RowView(double *row_, int m_);
                class Iterator{
                    public:
                        using iterator_category = std::forward_iterator_tag;
                        using difference_type   = std::ptrdiff_t;
                        using value_type        = double;
                        using pointer           = value_type*;  
                        using reference         = value_type&;
                        Iterator(pointer ptr_);
                        reference operator*() const;
                        pointer operator->() const;
                        Iterator& operator++();
                        Iterator operator++(int);
                        bool operator== (const Iterator& b) const;
                        bool operator!= (const Iterator& b) const;
                    private:
                        pointer ptr;               
                };
            Iterator begin() const;
            Iterator end() const;
        };


        class Rows{
            private:
                double* rows;
                int n;
                int m;
            public:
                Rows(double *rows_, int n_, int m_);
                class Iterator{
                    public:
                        using iterator_category = std::forward_iterator_tag;
                        using difference_type   = std::ptrdiff_t;
                        using value_type        = double;
                        using pointer           = value_type*;  
                        using reference         = value_type&;
                        Iterator(pointer ptr_, int m_);
                        RowView operator*() const;
                        pointer operator->() const;
                        Iterator& operator++();
                        Iterator operator++(int);
                        bool operator== (const Iterator& b) const;
                        bool operator!= (const Iterator& b) const;
                    private:
                        pointer ptr;
                        int n; 
                        int m;     
                };
            Iterator begin() const;
            Iterator end() const;
        };


        class ColumnView{
            private:
                double* column;
                int m;
                int n;
            public:
                ColumnView(double *column_, int m_, int n_);
                class Iterator{
                    public:
                        using iterator_category = std::forward_iterator_tag;
                        using difference_type   = std::ptrdiff_t;
                        using value_type        = double;
                        using pointer           = value_type*;  
                        using reference         = value_type&;
                        Iterator(pointer ptr_, int m_);
                        reference operator*() const;
                        pointer operator->() const;
                        Iterator& operator++();
                        Iterator operator++(int);
                        bool operator== (const Iterator& b) const;
                        bool operator!= (const Iterator& b) const;
                    private:
                        pointer ptr; 
                        int m;              
                };
            Iterator begin() const;
            Iterator end() const;
        };


        class Columns{
            private:
                double* columns;
                int n;
                int m;
            public:
                Columns(double *columns_, int n_, int m_);
                
                class Iterator{
                    public:
                        using iterator_category = std::forward_iterator_tag;
                        using difference_type   = std::ptrdiff_t;
                        using value_type        = double;
                        using pointer           = value_type*;  
                        using reference         = value_type&;
                        Iterator(pointer ptr_, int n_, int m_);
                        ColumnView operator*() const;
                        pointer operator->() const;
                        Iterator& operator++();
                        Iterator operator++(int);
                        bool operator== (const Iterator& b) const;
                        bool operator!= (const Iterator& b) const;
                    private:
                        pointer ptr;
                        int n; 
                        int m;     
                };
            Iterator begin() const;
            Iterator end() const;
        };
        Rows iter_rows() const;
        Columns iter_columns() const;
};


std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
Matrix operator*(double d, const Matrix &matrix);