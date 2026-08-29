//
// Created by dministrator on 2026/8/27.
//

#include <cstdlib>
#include <string>
#include <unistd.h>
#include <spdlog/spdlog.h>

void setTimeViaXdotool(const std::string& year, const std::string& month, const std::string& day,const std::string& hour, const std::string& minute) {
    using namespace spdlog;
    const float delay = 500000;
    // system("xdotool windowminimize $(xdotool getactivewindow)");
    // info("xdotool windowminimize $(xdotool getactivewindow)");
    // sleep(1);

    // 1. 按下 Windows 键
    system("xdotool key super");
    info("xdotool key super");
    usleep(delay);

    // 2. 三下 Tab
    system("xdotool key Tab Tab Tab");
    info("xdotool key Tab Tab Tab");
    usleep(delay);

    // 3. 一下回车
    system("xdotool key Return");
    info("xdotool key Return");
    sleep(5);

    // 5. 两下 Tab
    system("xdotool key Tab Tab");
    info("xdotool key Tab Tab");
    usleep(delay);

    system("xdotool type \"pei\"");
    info("xdotool type \"pei\"");
    usleep(delay);


    // 7. 一下回车
    system("xdotool key Return");
    info("xdotool key Return");
    sleep(1);

    // 8. 十下 Tab
    system("xdotool key Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab");
    info("xdotool key Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab");
    usleep(delay);

    // 9. 输入年份
    system(("xdotool type \"" + year + "\"").c_str());
    info(("xdotool type \"" + year + "\"").c_str());
    usleep(delay);

    // 10. 三下 Tab
    system("xdotool key Tab Tab Tab");
    info("xdotool key Tab Tab Tab");
    usleep(delay);

    // 11. 输入月份
    system(("xdotool type \"" + month + "\"").c_str());
    info(("xdotool type \"" + month + "\"").c_str());
    usleep(delay);

    // 12. 三下 Tab
    system("xdotool key Tab Tab Tab");
    info("xdotool key Tab Tab Tab");
    usleep(delay);

    // 13. 输入日期
    system(("xdotool type \"" + day + "\"").c_str());
    info(("xdotool type \"" + day + "\"").c_str());
    usleep(delay);

    system("xdotool key Tab Tab Tab Tab Tab Tab Tab");
    usleep(delay); // 操作后间隔1秒

    // 2. 输入小时
    system(("xdotool type \"" + hour + "\"").c_str());
    usleep(delay);

    // 3. 3次tab
    system("xdotool key Tab Tab Tab");
    usleep(delay);

    // 4. 输入分钟
    system(("xdotool type \"" + minute + "\"").c_str());
    usleep(delay);

    // 5. 23次tab（连续按下）
    system("xdotool key Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab");
    usleep(delay);

    // 15. 按下空格
    system("xdotool key space");
    info("xdotool key space");
    sleep(1);

    // 16. 按下 alt+f4
    system("xdotool key alt+F4");
    info("xdotool key alt+F4");
}

int main() {
    setTimeViaXdotool("2026", "08", "27","08","30");
    return 0;
}