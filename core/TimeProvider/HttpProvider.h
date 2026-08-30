//
// Created by dministrator on 2026/8/30.
//

#ifndef SYNCHRONIZER_HTTPPROVIDER_H
#define SYNCHRONIZER_HTTPPROVIDER_H
#include "ITimeProvider.h"
#include <iomanip>


class HttpProvider: public ITimeProvider {
public:

    std::string getTime() override;
private:
    int parseMonth(const std::string& mon);
    std::string fetchCurlHead(const std::string& url);
    std::string dateExtraction(const std::string& rawText);
    std::string tmToString(const std::tm& tm, const std::string& fmt = "%Y-%m-%d %H:%M:%S");
    std::string convertTimeZone(std::string time, int mon, int day, int year);
    std::string adjustTime(std::string httpDate, std::string weekday, std::string day, std::string month, std::string year,
                           std::string time, std::string tz);
};



#endif //SYNCHRONIZER_HTTPPROVIDER_H
