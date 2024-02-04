#include "DateTime.hpp"
#include <ctime>
#include <string>
#include <vector>
#include <iostream>

#define SECOND_IN_DAY 86400

std::string DateTime::toLower(std::string s){
    std::string out = "";
    for(int i = 0; i<s.size(); i++){
        out+=tolower(s[i]);
    }
    return out;
}



DateTime::DateTime(int day, int month, int year){
    timeInfo = (tm*)malloc(sizeof(tm));
    timeInfo->tm_mday = day;
    timeInfo->tm_mon = month-1;
    timeInfo->tm_year = year - 1900;
    timeInfo->tm_hour = 0;
    timeInfo->tm_min = 0;
    timeInfo->tm_sec = 0;
    mktime(timeInfo);
}

DateTime::DateTime(std::string date){
    timeInfo = (tm*)malloc(sizeof(tm));
    int i = 0, day = 1, month = 0, year = 2024;
    std::string partDate = "";
    std::vector<std::string> partsDate;
    while(i<date.size()){
        if(date[i] == ','){
            i++;
            continue;
        }
        if(date[i] == ' '){
            partsDate.push_back(partDate);
            partDate = "";
            i++;
            continue;
        }
        partDate += date[i];
    
        i++;
    }
    day = stoi(partsDate[0]);
    for(int i = 0; i<12; i++){
        if(toLower(months[i]) == toLower(partsDate[1])){
            month = i;
            break;
        }
    }
    year = stoi(partsDate[2]);
    timeInfo->tm_mday = day;
    timeInfo->tm_mon = month;
    timeInfo->tm_year = year-1900;
    timeInfo->tm_hour = 0;
    timeInfo->tm_min = 0;
    timeInfo->tm_sec = 0;
    mktime(timeInfo);
}

DateTime::DateTime(){
    time_t seconds = time(NULL);
    timeInfo = localtime(&seconds);
    mktime(timeInfo);
}

DateTime::DateTime(const DateTime &other){
    this->timeInfo = (tm*)malloc(sizeof(tm));
    this->timeInfo->tm_mday = other.timeInfo->tm_mday;
    this->timeInfo->tm_mon = other.timeInfo->tm_mon;
    this->timeInfo->tm_year = other.timeInfo->tm_year;
    this->timeInfo->tm_hour = other.timeInfo->tm_hour;
    this->timeInfo->tm_min = other.timeInfo->tm_min;
    this->timeInfo->tm_sec = other.timeInfo->tm_sec;
    mktime(this->timeInfo);
}

DateTime::~DateTime(){
    delete timeInfo;
}

void DateTime::setDay(int day){
    timeInfo->tm_mday = day;
    mktime(this->timeInfo);
}

 std::string DateTime::get_today() const{
     std::string out =  std::to_string(timeInfo->tm_mday) + " ";
     out = out + months[timeInfo->tm_mon] + " ";
     out = out + std::to_string(timeInfo->tm_year+1900) + " ";
     out += weekday[timeInfo->tm_wday];
     return out;
 }

std::string DateTime::get_yesterday() const{
    DateTime *yesterday = new DateTime(*this);
    yesterday->setDay(this->timeInfo->tm_mday-1);
    std::string out = yesterday->get_today();
    delete yesterday;
    return out;
}

std::string DateTime::get_tommorow() const{
    DateTime *tommorow = new DateTime(*this);
    tommorow->setDay(this->timeInfo->tm_mday+1);
    std::string out = tommorow->get_today();
    delete tommorow;
    return out;
}

std::string DateTime::get_future(unsigned int N) const{
   DateTime *future = new DateTime(*this);
   future->setDay(this->timeInfo->tm_mday+N);
   std::string out = future->get_today();
   delete future;
   return out;
}

std::string DateTime::get_past(unsigned int N) const{
   DateTime *past = new DateTime(*this);
   past->setDay(this->timeInfo->tm_mday-N);
   std::string out = past->get_today();
   delete past;
   return out;
}

int DateTime:: get_difference(DateTime& other) const{
    return abs(difftime(mktime(this->timeInfo), mktime(other.timeInfo))/SECOND_IN_DAY);
}