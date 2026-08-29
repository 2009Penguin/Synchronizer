//
// Created by dministrator on 2026/8/30.
//

#ifndef SYNCHRONIZER_HTTPPROVIDER_H
#define SYNCHRONIZER_HTTPPROVIDER_H
#include "ITimeProvider.h"


class HttpProvider: public ITimeProvider {
public:
    std::string getTime() override;
private:
    int parseMonth(const std::string& mon);
};



#endif //SYNCHRONIZER_HTTPPROVIDER_H
