//
// Created by dministrator on 2026/8/29.
//

#include "ConfigManager.h"

#include "spdlog/logger.h"
#include "spdlog/spdlog.h"

using json = nlohmann::json;
using namespace spdlog;
using namespace std;

ConfigManager& ConfigManager::instance()
{
    static ConfigManager instance;
    return instance;
}

SmbConfig ConfigManager::getSmbConfig()
{
    return json::parse(mJsonText)["smb"].get<SmbConfig>();
}

HttpConfig ConfigManager::getHttpConfig()
{
    return json::parse(mJsonText)["http"].get<HttpConfig>();
}

RollbackConfig ConfigManager::getRollbackConfig()
{
    return json::parse(mJsonText)["rollback"].get<RollbackConfig>();
}

void ConfigManager::setRollbackConfigTime(string time)
{
    json j = json::parse(mJsonText);
    j["rollback"]["time"] = time;
    std::ofstream out("config.json");
    out << std::setw(4) << j << std::endl;
    info("回滚时间更新成功");
    mJsonText = j.dump();
}

ConfigManager::ConfigManager()
{
    if(!mJsonFile.is_open())
    {
        error("未找到文件config.json");
        return;
    }
    info("开始解析配置文件");
    stringstream buffer;
    buffer << mJsonFile.rdbuf();
    mJsonText = buffer.str();
    info("解析完成");
}

ConfigManager::~ConfigManager()
{
    mJsonFile.close();
}
