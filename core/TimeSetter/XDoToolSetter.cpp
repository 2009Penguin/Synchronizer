//
// Created by dministrator on 2026/8/30.
//

#include "XDoToolSetter.h"
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <spdlog/spdlog.h>

using namespace std;
using namespace spdlog;

void XDoToolSetter::openControlCenter(const float delay)
{
    info("正在打开控制中心");
    system("xdotool key super");
    usleep(delay);

    system("xdotool key Tab Tab Tab");
    usleep(delay);

    system("xdotool key Return");
    info("等待窗口加载");
    sleep(6);
}

void XDoToolSetter::enterTimeAdjustmentInterface(const float delay)
{
    system("xdotool key Tab Tab");
    usleep(delay);

    system("xdotool type \"pei\"");
    info("正在进入时间调整界面");
    usleep(delay);


    system("xdotool key Return");
    usleep(delay);
}

void XDoToolSetter::adjustYear(const string& year, const float delay)
{
    system(("xdotool type \"" + year + "\"").c_str());
    info("正在调整年份");
    usleep(delay);
}

void XDoToolSetter::adjustMonth(const string& month, const float delay)
{
    system("xdotool key Tab Tab Tab");
    usleep(delay);
    system(("xdotool type \"" + month + "\"").c_str());
    info("正在调整月份");
    usleep(delay);
}

void XDoToolSetter::adjustDay(const string& day, const float delay)
{
    system("xdotool key Tab Tab Tab");
    usleep(delay);

    system(("xdotool type \"" + day + "\"").c_str());
    info("正在调整天数");
    usleep(delay);
}

void XDoToolSetter::adjustHour(const string& hour, const float delay)
{
    system("xdotool key Tab Tab Tab Tab Tab Tab Tab");
    usleep(delay);

    system(("xdotool type \"" + hour + "\"").c_str());
    info("正在调整小时");
    usleep(delay);
}

void XDoToolSetter::adjustMinute(const string& minute, const float delay)
{
    system("xdotool key Tab Tab Tab");
    usleep(delay);

    system(("xdotool type \"" + minute + "\"").c_str());
    info("正在调整分钟");
    usleep(delay);
}

void XDoToolSetter::confirmChanges(const float delay)
{
    system("xdotool key Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab");
    usleep(delay);

    system("xdotool key space");
    usleep(delay);
    info("时间修改完成");
}

void XDoToolSetter::adjustTime(const string& year, const string& month, const string& day, const string& hour, const string& minute, const float delay)
{
    system("xdotool key Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab");
    usleep(delay);
    info("开始调整时间");

    adjustYear(year, delay);
    adjustMonth(month, delay);
    adjustDay(day, delay);
    adjustHour(hour, delay);
    adjustMinute(minute, delay);

    confirmChanges(delay);
}

void XDoToolSetter::closeControlCenter()
{
    system("xdotool key alt+F4");
    info("正在关闭控制中心");
}

void XDoToolSetter::setTime(const string& year, const string& month, const string& day,
                            const string& hour, const string& minute)
{
    using namespace spdlog;
    const float delay = 400000;//0.4秒

    openControlCenter(delay);
    enterTimeAdjustmentInterface(delay);
    adjustTime(year, month, day, hour, minute, delay);
    closeControlCenter();
}