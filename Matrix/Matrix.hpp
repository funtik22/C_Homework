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
        Matrix transpose() const;
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
            private:
                double* row;
                int m;
            public:
                RowView(double *row_, int m_):row(row_), m(m_){};
                class Iterator{
                    public:
                        using iterator_category = std::forward_iterator_tag;
                        using difference_type   = std::ptrdiff_t;
                        using value_type        = double;
                        using pointer           = value_type*;  
                        using reference         = value_type&;
                        Iterator(pointer ptr_):ptr(ptr_){};
                        reference operator*() const{return *ptr;};
                        pointer operator->() const{return ptr;};
                        Iterator& operator++(){ptr++; return *this;};
                        Iterator operator++(int){
                            Iterator tmp = *this;
                            ++(*this);
                            return tmp;
                        };
                        bool operator== (const Iterator& b) const {return ptr == b.ptr;};
                        bool operator!= (const Iterator& b) const {return ptr != b.ptr;};
                    private:
                        pointer ptr;               
                };
            Iterator begin() const {return Matrix::RowView::Iterator(row);};
            Iterator end() const {return Matrix::RowView::Iterator(row+m);};
        };


        class Rows{
            private:
                double* rows;
                int n;
                int m;
            public:
                Rows(double *rows_, int n_, int m_):rows(rows_), n(n_), m(m_){};
                class Iterator{
                    public:
                        using iterator_category = std::forward_iterator_tag;
                        using difference_type   = std::ptrdiff_t;
                        using value_type        = double;
                        using pointer           = value_type*;  
                        using reference         = value_type&;
                        Iterator(pointer ptr_, int m_):ptr(ptr_), m(m_){};
                        RowView operator*() const {return RowView(ptr, m);};
                        pointer operator->() const {return ptr;};
                        Iterator& operator++() {ptr+=m; return *this;};
                        Iterator operator++(int) {
                            Iterator tmp = *this;
                            ++(*this);
                            return tmp;
                        };
                        bool operator== (const Iterator& b) const { return ptr == b.ptr; };
                        bool operator!= (const Iterator& b) const { return ptr != b.ptr; };
                    private:
                        pointer ptr;
                        int n; 
                        int m;     
                };
            Iterator begin() const {return Matrix::Rows::Iterator(rows, m);};
            Iterator end() const {return Matrix::Rows::Iterator(rows+n*m, m);};
        };


        class ColumnView{
            private:
                double* column;
                int m;
                int n;
            public:
                ColumnView(double *column_, int m_, int n_):column(column_), n(n_), m(m_){};
                class Iterator{
                    public:
                        using iterator_category = std::forward_iterator_tag;
                        using difference_type   = std::ptrdiff_t;
                        using value_type        = double;
                        using pointer           = value_type*;  
                        using reference         = value_type&;
                        Iterator(pointer ptr_, int m_):ptr(ptr_), m(m_){};
                        reference operator*() const {return *ptr;};
                        pointer operator->() const {return ptr;};
                        Iterator& operator++() {ptr+=m; return *this;};
                        Iterator operator++(int){
                            Iterator tmp = *this;
                            ++(*this);
                            return tmp;
                        };
                        bool operator== (const Iterator& b) const { return ptr == b.ptr; };
                        bool operator!= (const Iterator& b) const { return ptr != b.ptr; };
                    private:
                        pointer ptr; 
                        int m;              
                };
            Iterator begin() const {return Matrix::ColumnView::Iterator(column, m);};
            Iterator end() const {return Matrix::ColumnView::Iterator(column+n*m, m);};
        };


        class Columns{
            private:
                double* columns;
                int n;
                int m;
            public:
                Columns(double *columns_, int n_, int m_):columns(columns_), n(n_), m(m_){};
                
                class Iterator{
                    public:
                        using iterator_category = std::forward_iterator_tag;
                        using difference_type   = std::ptrdiff_t;
                        using value_type        = double;
                        using pointer           = value_type*;  
                        using reference         = value_type&;
                        Iterator(pointer ptr_, int n_, int m_):ptr(ptr_), n(n_), m(m_){};
                        ColumnView operator*() const {return ColumnView(ptr, n, m);};
                        pointer operator->() const {return ptr;};
                        Iterator& operator++() {ptr++; return *this;};;
                        Iterator operator++(int){
                            Iterator tmp = *this;
                            ++(*this);
                            return tmp;
                        };
                        bool operator== (const Iterator& b) const { return ptr == b.ptr; };
                        bool operator!= (const Iterator& b) const { return ptr != b.ptr; };
                    private:
                        pointer ptr;
                        int n; 
                        int m;     
                };
            Iterator begin() const {return Matrix::Columns::Iterator(columns, n, m);};
            Iterator end() const {return Matrix::Columns::Iterator(columns+m, n, m);};
        };
        Rows iter_rows() const {return Rows(array2D, n, m);};
        Columns iter_columns() const {return Columns(array2D, n, m);};
};


std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
Matrix operator*(double d, const Matrix &matrix);