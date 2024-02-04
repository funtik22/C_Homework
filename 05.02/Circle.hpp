#define CIRCLE_HPP
#ifdef CIRCLE_HPP


class Circle{
    private: 
        double radious;
        double ference;
        double area;
    public:
        void set_radious(double radious);
        void set_ference(double ference);
        void set_area(double area);

        double get_radious() const;
        double get_ference() const;
        double get_area() const;
};
#endif