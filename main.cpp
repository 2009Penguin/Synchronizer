//
// Created by dministrator on 2026/8/27.
//

#include <cstdlib>
#include <string>
#include <unistd.h>

void setTimeViaXdotool(const std::string& year, const std::string& month, const std::string& day) {
    // 1. 按下 Windows 键
    system("xdotool key super");
    usleep(200000); // 等待菜单弹出

    // 2. 三下 Tab
    system("xdotool key Tab Tab Tab");
    usleep(200000);

    // 3. 一下回车
    system("xdotool key Return");

    // 4. 休眠 5 秒（你要求的）
    sleep(5);

    // 5. 两下 Tab
    system("xdotool key Tab Tab");
    usleep(200000);

    // 6. 输入“时间和格式/时间设置/自动同步配置”
    system("xdotool type \"时间和格式/时间设置/自动同步配置\"");
    usleep(200000);

    // 7. 一下回车
    system("xdotool key Return");
    usleep(500000); // 等待搜索/加载

    // 8. 十下 Tab
    system("xdotool key Tab Tab Tab Tab Tab Tab Tab Tab Tab Tab");
    usleep(200000);

    // 9. 输入年份
    system(("xdotool type \"" + year + "\"").c_str());
    usleep(200000);

    // 10. 三下 Tab
    system("xdotool key Tab Tab Tab");
    usleep(200000);

    // 11. 输入月份
    system(("xdotool type \"" + month + "\"").c_str());
    usleep(200000);

    // 12. 三下 Tab
    system("xdotool key Tab Tab Tab");
    usleep(200000);

    // 13. 输入日期
    system(("xdotool type \"" + day + "\"").c_str());
    usleep(200000);

    // 14. 三下 Tab
    system("xdotool key Tab Tab Tab");
    usleep(200000);

    // 15. 按下空格
    system("xdotool key space");
    usleep(200000);

    // 16. 按下 alt+f4
    system("xdotool key alt+F4");
}

int main() {
    setTimeViaXdotool("2026", "08", "27");
    return 0;

    return 0;
}