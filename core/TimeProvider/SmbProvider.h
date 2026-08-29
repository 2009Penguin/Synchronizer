//
// Created by dministrator on 2026/8/30.
//

#ifndef SYNCHRONIZER_SMBPROVIDER_H
#define SYNCHRONIZER_SMBPROVIDER_H
#include "ITimeProvider.h"


class SmbProvider: public ITimeProvider {
public:
    std::string getTime() override;
private:
    void loadConfiguration(std::string& sharePath,std::string& subDir);
    std::string createTimeAnchor(const std::string& shareDir, const std::string& subDir);
    std::string getFileModTime(const std::string& filePath);

};



#endif //SYNCHRONIZER_SMBPROVIDER_H
