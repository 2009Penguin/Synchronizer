//
// Created by dministrator on 2026/8/29.
//

#ifndef SYNCHRONIZER_CONFIGMANAGER_H
#define SYNCHRONIZER_CONFIGMANAGER_H
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

struct SmbConfig {
    std::string link;
    std::string subDir;
    bool enabled;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SmbConfig, link, subDir, enabled)
};

struct HttpConfig {
    std::string link;
    bool enabled;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(HttpConfig, link, enabled)
};

struct RollbackConfig {
    std::string time;
    bool enabled;
    bool autoUpdate;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RollbackConfig, time, enabled, autoUpdate)
};

class ConfigManager {
public:
    static ConfigManager& instance();

    ConfigManager(const ConfigManager&) = delete;
    ConfigManager(ConfigManager&&) = delete;

    SmbConfig getSmbConfig();
    HttpConfig getHttpConfig();
    RollbackConfig getRollbackConfig();

    void setRollbackConfigTime(std::string time);

    ConfigManager& operator=(const ConfigManager&) = delete;
    ConfigManager& operator=(ConfigManager&&) = delete;
private:
    ConfigManager();
    ~ConfigManager();

    std::string mJsonText;

    std::ifstream mJsonFile{"config.json"};
};



#endif //SYNCHRONIZER_CONFIGMANAGER_H
