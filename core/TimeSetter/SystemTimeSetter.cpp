//
// Created by dministrator on 2026/9/10.
//

#include "SystemTimeSetter.h"
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <spdlog/spdlog.h>

using namespace spdlog;

void SystemTimeSetter::setTime(const std::string& year, const std::string& month,
                               const std::string& day, const std::string& hour,
                               const std::string& minute) {
    std::string datetime = year + "-" + month + "-" + day + " " + hour + ":" + minute + ":00";
    info("正在设置系统时间至：" + datetime);
    std::string cmd = "date -s \"" + datetime + "\"";
    int ret = system(cmd.c_str());
    if (ret != 0) {
        error("date -s 执行失败，返回码：" + std::to_string(ret));
    } else {
        info("系统时间设置成功");
    }
}