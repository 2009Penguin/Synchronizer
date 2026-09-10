//
// Created by dministrator on 2026/8/30.
//

#ifndef SYNCHRONIZER_ITIMESETTER_H
#define SYNCHRONIZER_ITIMESETTER_H

#include <string>

class ITimeSetter {
public:
    virtual ~ITimeSetter() = default;
    virtual void setTime(const std::string& year, const std::string& month, const std::string& day,
        const std::string& hour, const std::string& minute) = 0;
};



#endif //SYNCHRONIZER_ITIMESETTER_H
