#include <ctime>
#include <string>

#define DATETIME_CPP
#ifdef DATETIME_CPP

class DateTime{
    private:
        struct tm* timeInfo;
        const char *weekday[7] = { "Sunday", "Monday",
                             "Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"};
        const char *months[12] = { "January", "February", "March", 
                            "April", "May", "June", "July", "August",  
                            "September",  "October","November",
                            "December"};
        std::string toLower(std::string s);
        void setDay(int day);      
    public:
        DateTime(int day, int month, int year);
        DateTime(std::string date);
        DateTime(const DateTime &other);
        DateTime();
        ~DateTime();
        std::string get_today() const;
        std::string get_yesterday() const;
        std::string get_tommorow() const;
        std::string get_future(unsigned int N) const;
        std::string get_past(unsigned int N) const;
        int get_difference(DateTime& other) const;
};

#endif