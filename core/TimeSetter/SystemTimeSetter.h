//
// Created by dministrator on 2026/9/10.
//

#ifndef SYNCHRONIZER_SYSTEMTIMESETTER_H
#define SYNCHRONIZER_SYSTEMTIMESETTER_H

#include "ITimeSetter.h"
#include <string>

class SystemTimeSetter : public ITimeSetter {
public:
    void setTime(const std::string& year, const std::string& month, const std::string& day,
                 const std::string& hour, const std::string& minute);
};



#endif //SYNCHRONIZER_SYSTEMTIMESETTER_H
