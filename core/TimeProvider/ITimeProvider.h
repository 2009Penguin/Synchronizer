//
// Created by dministrator on 2026/8/30.
//

#ifndef SYNCHRONIZER_ITIMEPROVIDER_H
#define SYNCHRONIZER_ITIMEPROVIDER_H
#include <string>


class ITimeProvider {
public:
    virtual ~ITimeProvider() = default;
    virtual std::string getTime() = 0;
};



#endif //SYNCHRONIZER_ITIMEPROVIDER_H
