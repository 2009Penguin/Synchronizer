//
// Created by dministrator on 2026/8/30.
//

#ifndef SYNCHRONIZER_TIMEPROVIDER_H
#define SYNCHRONIZER_TIMEPROVIDER_H
#include <memory>

#include "ITimeProvider.h"


class TimeProvider {
public:
    void loadTimeProvider();
    std::string getTime();
private:
    std::unique_ptr<ITimeProvider> mProvider;
    void setimeProvider(std::unique_ptr<ITimeProvider> provider);
};



#endif //SYNCHRONIZER_TIMEPROVIDER_H
