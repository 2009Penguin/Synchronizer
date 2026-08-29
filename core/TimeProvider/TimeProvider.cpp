//
// Created by dministrator on 2026/8/30.
//

#include "TimeProvider.h"
#include "../config/ConfigManager.h"
#include  <spdlog/spdlog.h>

#include "SmbProvider.h"
#include "HttpProvider.h"

using namespace std;
using namespace spdlog;

string TimeProvider::getTime()
{
    loadTimeProvider();
    return mProvider->getTime();;
}

void TimeProvider::loadTimeProvider()
{
    ConfigManager& configManager = ConfigManager::instance();
    SmbConfig smbConfig = configManager.getSmbConfig();
    HttpConfig httpConfig = configManager.getHttpConfig();
    if (!(smbConfig.enabled && httpConfig.enabled))
    {
        error("请启用Smb选项或者Http选项");
        return;
    }
    if (smbConfig.enabled)
    {
        info("启用Smb选项");
        setimeProvider(make_unique<SmbProvider>());
    }
    if (httpConfig.enabled)
    {
        info("启用Http选项");
        setimeProvider(make_unique<HttpProvider>());
    }
}

void TimeProvider::setimeProvider(std::unique_ptr<ITimeProvider> provider)
{
    mProvider = move(provider);
}
