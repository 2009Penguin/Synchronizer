//
// Created by dministrator on 2026/8/30.
//

#ifndef SYNCHRONIZER_XDOTOOLSETTER_H
#define SYNCHRONIZER_XDOTOOLSETTER_H
#include <string>

#include "ITimeSetter.h"


class XDoToolSetter:public ITimeSetter {
public:
    void openControlCenter(float delay);
    void enterTimeAdjustmentInterface(float delay);
    void adjustYear(const std::string& year, float delay);
    void adjustMonth(const std::string& month, float delay);
    void adjustDay(const std::string& day, float delay);
    void adjustHour(const std::string& hour, float delay);
    void adjustMinute(const std::string& minute, float delay);
    void confirmChanges(float delay);
    void adjustTime(const std::string& year, const std::string& month, const std::string& day, const std::string& hour,
                    const std::string& minute, float delay);
    void closeControlCenter();
    void setTime(const std::string& year, const std::string& month, const std::string& day,
                 const std::string& hour, const std::string& minute) override;
};



#endif //SYNCHRONIZER_XDOTOOLSETTER_H
