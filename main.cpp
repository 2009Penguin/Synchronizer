//
// Created by dministrator on 2026/8/27.
//

#include <cstdlib>
#include <string>
#include <unistd.h>
#include <spdlog/spdlog.h>

#include "core/config/ConfigManager.h"
#include "core/TimeProvider/TimeProvider.h"
#include "core/TimeSetter/SystemTimeSetter.h"
#include "core/TimeSetter/TimeSetter.h"
#include "core/TimeSetter/XDoToolSetter.h"

using namespace std;
using namespace spdlog;

struct Time
{
    string year, month, day, hour, minute;
};

Time parseTime(const string time)
{
    tm t = {};
    istringstream ss(time);
    ss >> get_time(&t, "%Y-%m-%d %H:%M:%S");

    int year = t.tm_year + 1900;
    int month = t.tm_mon + 1;
    int day = t.tm_mday;
    int hour = t.tm_hour;
    int minute = t.tm_min;

    return Time{to_string(year), to_string(month), to_string(day),
        to_string(hour), to_string(minute)};
}

void rollback(TimeSetter& ts,const RollbackConfig& rollbackConfig)
{

    if (rollbackConfig.enabled)
    {
        info("回滚已启用，正在回滚至" + rollbackConfig.time);
        Time t = parseTime(rollbackConfig.time);
        ts.setTime(t.year,t.month,t.day,t.hour,t.minute);
    }
    info("回滚成功");
}

int main() {
    TimeProvider tm;
    TimeSetter ts;

    // ts.setSetter(make_unique<XDoToolSetter>());
    ts.setSetter(make_unique<SystemTimeSetter>());
    string time = tm.getTime();

    ConfigManager& configManager = ConfigManager::instance();
    RollbackConfig rollbackConfig = configManager.getRollbackConfig();

    if (time.empty()){
        error("时间获取异常");
        rollback(ts, rollbackConfig);
        return -1;
    }
    info("获取时间成功");

    if (rollbackConfig.enabled)
    {
        info("自动更行回滚时间已开启，正在更新回滚时间");
        configManager.setRollbackConfigTime(time);
    }

    Time t = parseTime(time);
    ts.setTime(t.year,t.month,t.day,t.hour,t.minute);
    return 0;
}
