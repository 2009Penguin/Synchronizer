//
// Created by dministrator on 2026/8/30.
//

#ifndef SYNCHRONIZER_TIMESETTER_H
#define SYNCHRONIZER_TIMESETTER_H

#include <memory>
#include <string>

#include "ITimeSetter.h"

class TimeSetter {
public:
    void setTime(const std::string& year, const std::string& month, const std::string& day,
        const std::string& hour, const std::string& minute);
    void setSetter(std::unique_ptr<ITimeSetter> setter);
private:
    std::unique_ptr<ITimeSetter> mSetter;
};



#endif //SYNCHRONIZER_TIMESETTER_H
