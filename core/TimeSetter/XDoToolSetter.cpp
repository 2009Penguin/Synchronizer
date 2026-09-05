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

void XDoToolSetter::openControlCenter(const float delay,const int windowInitializeDelay)
{
    info("正在打开控制中心");
    // pressKey("super",delay,1);
    // usleep(delay);
    //
    // system("xdotool key Tab Tab Tab");
    // usleep(delay);
    //
    // system("xdotool key Return");
    pressKey("super",delay,1);
    pressKey("Tab",delay,3);
    pressKey("Return",delay,1);

    info("等待窗口加载");
    sleep(windowInitializeDelay);
}

void XDoToolSetter::enterTimeAdjustmentInterface(const float delay)
{
    // system("xdotool key Tab Tab");
    // usleep(delay);
    //
    // system("xdotool type \"pei\"");
    pressKey("Tab",delay,2);
    info("正在进入时间调整界面");
    typeString("pei",delay);
    // usleep(delay);
    //
    //
    // system("xdotool key Return");
    // usleep(delay);
    pressKey("Return",delay,1);
}

void XDoToolSetter::adjustYear(const string& year, const float delay)
{
    // system(("xdotool type \"" + year + "\"").c_str());
    typeString(year,delay);
    pressKey("Return",delay,1);
    info("正在调整年份");
    usleep(delay);
}

void XDoToolSetter::adjustMonth(const string& month, const float delay)
{
    // system("xdotool key Tab Tab Tab");
    // usleep(delay);
    // system(("xdotool type \"" + month + "\"").c_str());
    pressKey("Tab",delay,3);
    typeString(month,delay);
    info("正在调整月份");
    // usleep(delay);
}

void XDoToolSetter::adjustDay(const string& day, const float delay)
{
    // system("xdotool key Tab Tab Tab");
    // usleep(delay);
    //
    // system(("xdotool type \"" + day + "\"").c_str());
    pressKey("Tab",delay,3);
    typeString(day,delay);
    info("正在调整天数");
    // usleep(delay);
}

void XDoToolSetter::adjustHour(const string& hour, const float delay)
{
    // system("xdotool key Tab Tab Tab Tab Tab Tab Tab");
    // usleep(delay);
    //
    // system(("xdotool type \"" + hour + "\"").c_str());
    pressKey("Tab",delay,7);
    typeString(hour,delay);
    info("正在调整小时");
    // usleep(delay);
}

void XDoToolSetter::adjustMinute(const string& minute, const float delay)
{
    // system("xdotool key Tab Tab Tab");
    // usleep(delay);
    //
    // system(("xdotool type \"" + minute + "\"").c_str());
    pressKey("Tab",delay,3);
    typeString(minute,delay);
    info("正在调整分钟");
    // usleep(delay);
}

void XDoToolSetter::confirmChanges(const float delay)
{
    // system("xdotool key Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab");
    // usleep(delay);
    //
    // system("xdotool key space");
    // usleep(delay);
    pressKey("Tab",delay,23);
    pressKey("space",delay,1);
    info("时间修改完成");
}

void XDoToolSetter::adjustTime(const string& year, const string& month, const string& day, const string& hour, const string& minute, const float delay)
{
    // system("xdotool key Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab");
    // usleep(delay);
    pressKey("Tab",delay,11);
    info("开始调整时间");

    adjustYear(year, delay);
    adjustMonth(month, delay);
    adjustDay(day, delay);
    adjustHour(hour, delay);
    adjustMinute(minute, delay);

    confirmChanges(delay);
}

void XDoToolSetter::closeControlCenter(const float delay)
{
    pressKey("alt+F4",delay,1);
    info("正在关闭控制中心");
}

void XDoToolSetter::pressKey(const string& key, float delay, int times = 1)
{
    string command = "xdotool key " + key + " ";
    for (int i = 0; i < times; i ++)
    {
        system(command.c_str());
        system("xdotool getactivewindow");
        usleep(delay);
    }
}

void XDoToolSetter::typeString(const string& key, float delay)
{
    for (char c : key){
        string s{c};
        pressKey(s,delay,1);
    }
}

void XDoToolSetter::ensureEnglishKeyboard(float settingDelay)
{
    info("正在切换至英文输入法");
    system("fcitx-remote -s fcitx-keyboard-us");
    usleep(settingDelay);

    system("setxkbmap us");
    usleep(settingDelay);
}

void XDoToolSetter::setTime(const string& year, const string& month, const string& day,
                            const string& hour, const string& minute)
{
    using namespace spdlog;
    constexpr float inputDelay = 30000;//30ms
    constexpr int windowInitializeDelay = 6;//5s
    constexpr float settingDelay = 200000;//200ms

    ensureEnglishKeyboard(settingDelay);
    openControlCenter(inputDelay,windowInitializeDelay);
    enterTimeAdjustmentInterface(inputDelay);
    adjustTime(year, month, day, hour, minute, inputDelay);
    closeControlCenter(inputDelay);
}
