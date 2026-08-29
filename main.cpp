//
// Created by dministrator on 2026/8/27.
// 使用 smbclient 获取服务器时间（无需挂载）
//

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <regex>

using namespace std;

// 读取配置文件，获取共享路径（如 //192.168.1.100/年段资源）
void loadConfiguration(ifstream& config, string& sharePath) {
    getline(config, sharePath);
}

// 将 smbclient 输出的时间字符串（如 "Wed Aug 27 14:30:00 2026"）转换为 tm 结构
bool parseSmbTime(const string& timeStr, struct tm& tmOut) {
    // 月份缩写映射
    const string months[] = {"Jan","Feb","Mar","Apr","May","Jun",
                             "Jul","Aug","Sep","Oct","Nov","Dec"};
    // 用正则提取：星期 月份 日 时:分:秒 年
    regex pattern(R"((\w{3})\s+(\w{3})\s+(\d{1,2})\s+(\d{2}):(\d{2}):(\d{2})\s+(\d{4}))");
    smatch match;
    if (!regex_search(timeStr, match, pattern)) {
        cerr << "无法解析时间字符串: " << timeStr << endl;
        return false;
    }
    // match[1]=星期, match[2]=月份, match[3]=日, match[4]=时, match[5]=分, match[6]=秒, match[7]=年
    tmOut.tm_sec = stoi(match[6]);
    tmOut.tm_min = stoi(match[5]);
    tmOut.tm_hour = stoi(match[4]);
    tmOut.tm_mday = stoi(match[3]);
    tmOut.tm_year = stoi(match[7]) - 1900;  // tm_year 从 1900 开始
    // 查找月份
    for (int i = 0; i < 12; ++i) {
        if (months[i] == match[2]) {
            tmOut.tm_mon = i;
            break;
        }
    }
    return true;
}

// 通过 smbclient 获取服务器时间，返回格式化的时间字符串 "YYYY-MM-DD HH:MM:SS"
string getServerTimeViaSmbclient(const string& sharePath) {
    // 检查 smbclient 是否可用
    if (system("which smbclient > /dev/null 2>&1") != 0) {
        cerr << "错误：smbclient 命令未找到，请安装 smbclient" << endl;
        return "";
    }

    // 生成临时文件名（使用进程ID避免冲突）
    string tempFile = "temp_time_" + to_string(getpid()) + ".txt";
    string localTemp = "/tmp/" + tempFile;

    // 创建一个本地临时文件（内容无所谓）
    ofstream tmp(localTemp);
    if (!tmp.is_open()) {
        cerr << "无法创建本地临时文件" << endl;
        return "";
    }
    tmp << "sync" << endl;
    tmp.close();

    // 1. 上传文件到共享（匿名访问）
    string putCmd = "smbclient " + sharePath + " -N -c 'put " + localTemp + " " + tempFile + "' 2>/dev/null";
    int ret = system(putCmd.c_str());
    if (ret != 0) {
        cerr << "上传文件失败，请检查共享路径是否正确、是否可写" << endl;
        // 可以尝试改用只读方式？但我们需要创建文件来获取时间，如果不可写则无解。
        // 也许服务器已有其他文件，我们可以用 ls 获取任意文件的修改时间，但为了准确，还是尝试创建。
        // 这里返回空。
        return "";
    }

    // 2. 列出该文件，获取修改时间（输出重定向到临时文件）
    string listCmd = "smbclient " + sharePath + " -N -c 'ls " + tempFile + "' 2>/dev/null > /tmp/smb_ls_output.txt";
    system(listCmd.c_str());

    // 3. 读取输出，解析时间
    ifstream output("/tmp/smb_ls_output.txt");
    if (!output.is_open()) {
        cerr << "无法读取 smbclient 输出文件" << endl;
        return "";
    }

    string line;
    string timeStr;
    bool found = false;
    while (getline(output, line)) {
        // 查找包含文件名和日期时间的行（典型格式： temp_time_xxx.txt  N  0  Wed Aug 27 14:30:00 2026）
        if (line.find(tempFile) != string::npos) {
            // 提取从星期开始的子串（假设格式固定）
            size_t pos = line.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ"); // 找星期首字母
            if (pos != string::npos) {
                timeStr = line.substr(pos);
                found = true;
                break;
            }
        }
    }
    output.close();
    // 清理远程临时文件（可选）
    system(("smbclient " + sharePath + " -N -c 'rm " + tempFile + "' 2>/dev/null").c_str());
    // 清理本地临时文件
    remove(localTemp.c_str());
    remove("/tmp/smb_ls_output.txt");

    if (!found || timeStr.empty()) {
        cerr << "未能从 smbclient 输出中提取时间" << endl;
        return "";
    }

    // 解析时间
    struct tm tmResult{};
    if (!parseSmbTime(timeStr, tmResult)) {
        return "";
    }

    // 格式化为 "YYYY-MM-DD HH:MM:SS"
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tmResult);
    return string(buffer);
}

// 校准系统时间
void timeCalibration(const string& timeStr) {
    string cmd = "date -s \"" + timeStr + "\"";
    int ret = system(cmd.c_str());
    if (ret == 0) {
        cout << "时间同步成功：" << timeStr << endl;
    } else {
        cerr << "时间设置失败，请检查权限（需要 root）" << endl;
    }
}

int main() {
    // 读取配置文件
    ifstream config("config.txt");
    if (!config.is_open()) {
        cerr << "读取配置文件失败，请确保 config.txt 存在并包含共享路径" << endl;
        return -1;
    }
    string sharePath;
    loadConfiguration(config, sharePath);
    if (sharePath.empty()) {
        cerr << "配置文件中的共享路径为空！" << endl;
        return -1;
    }

    // 重试机制：最多尝试 5 次，每次等待 3 秒
    string serverTime;
    for (int attempt = 1; attempt <= 5; ++attempt) {
        cout << "尝试获取服务器时间（第 " << attempt << " 次）..." << endl;
        serverTime = getServerTimeViaSmbclient(sharePath);
        if (!serverTime.empty()) {
            break;
        }
        if (attempt < 5) {
            sleep(3);
        }
    }

    if (serverTime.empty()) {
        cerr << "多次尝试后仍无法获取服务器时间，程序退出" << endl;
        return -1;
    }

    cout << "获取到的服务器时间: " << serverTime << endl;

    // 校准系统时间
    timeCalibration(serverTime);

    return 0;
}