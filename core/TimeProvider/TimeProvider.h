//
// Created by dministrator on 2026/8/30.
//

#ifndef SYNCHRONIZER_TIMEPROVIDER_H
#define SYNCHRONIZER_TIMEPROVIDER_H
#include <memory>

#include "ITimeProvider.h"


class TimeProvider {
public:
    std::string getTime();
private:
    std::unique_ptr<ITimeProvider> mProvider;
    void loadTimeProvider();
    void setTimeProvider(std::unique_ptr<ITimeProvider> provider);
};



#endif //SYNCHRONIZER_TIMEPROVIDER_H
