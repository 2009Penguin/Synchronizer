//
// Created by dministrator on 2026/8/30.
//

#include "SmbProvider.h"

#include "../config/ConfigManager.h"
#include "spdlog/spdlog.h"

#include <sys/stat.h>
#include <time.h>

using namespace std;
using namespace spdlog;

string SmbProvider::getTime()
{
    string shareDir,subDir;
    loadConfiguration(shareDir,subDir);
    string anchorFile = createTimeAnchor(shareDir,subDir);
    return getFileModTime(anchorFile);
}

void SmbProvider::loadConfiguration(string& sharePath,string& subDir)
{
    ConfigManager& configManager = ConfigManager::instance();
    string link = configManager.getSmbConfig().link;
    string dir = configManager.getSmbConfig().subDir;

    if (link.empty()) {
        error("link内容为空");
        return;
    }
    sharePath = link;
    info("link加载成功，值：" + sharePath);

    if (dir.empty()) {
        error("subDir内容为空");
        return;
    }
    subDir = dir;
    info("subDir加载成功，值：" + subDir);
}

string SmbProvider::createTimeAnchor(const string& shareDir, const string& subDir)
{
    string anchorFile = shareDir + subDir + "/timeAnchor.txt";
    info("临时文件创建地址：" + anchorFile);
    ofstream ofs(anchorFile);
    if (!ofs.is_open()) {
        error("无法在共享目录创建文件，请检查路径和权限：" + anchorFile);
        return "";
    }

    ofs << "sync" << endl;
    ofs.close();

    if (anchorFile.empty()) {
        error("文件无法写入，请检查路径和权限：" + anchorFile);
        return "";
    }
    info("临时文件创建成功：" + anchorFile);
    return anchorFile;
}

string SmbProvider::getFileModTime(const string& filePath)
{
    struct stat fileStat{};
    if (stat(filePath.c_str(), &fileStat) != 0) {
        error( "读取文件属性失败：" + filePath);
        return "";
    }
    struct tm *timeinfo = localtime(&fileStat.st_mtime);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    string time = string(buffer);
    info("服务器时间" + time);
    return time;
}