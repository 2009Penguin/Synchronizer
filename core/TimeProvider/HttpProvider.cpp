//
// Created by dministrator on 2026/8/30.
//

#include "HttpProvider.h"

#include "../config/ConfigManager.h"
#include "spdlog/spdlog.h"

#include <memory>
#include <sstream>
#include <iomanip>
#include <unistd.h>

using namespace std;
using namespace spdlog;

string HttpProvider::convertTimeZone(string time, int mon, int day, int year)
{
    int hour, min, sec;
    char colon1, colon2;
    stringstream time_ss(time);
    time_ss >> hour >> colon1 >> min >> colon2 >> sec;

    tm utc_tm = {};
    utc_tm.tm_year = year - 1900;
    utc_tm.tm_mon  = mon - 1;
    utc_tm.tm_mday = day;
    utc_tm.tm_hour = hour;
    utc_tm.tm_min  = min;
    utc_tm.tm_sec  = sec;

    time_t utc_seconds = timegm(&utc_tm);
    time_t beijing_seconds = utc_seconds + (8 * 3600);

    string newTime = tmToString(*gmtime(&beijing_seconds));
    info("调整时区之后的日期：" + newTime);
    return newTime;
}

string HttpProvider::adjustTime(string httpDate, string weekday, string day, string month, string year, string time, string tz)
{
    stringstream ss(httpDate);
    ss >> weekday >> day >> month >> year >> time >> tz;

    if (weekday.back() == ',') weekday.pop_back();

    int mon = parseMonth(month);
    if (mon == -1) {
        error("月份解析失败");
        return "";
    }
    return convertTimeZone(time, mon, stoi(day), stoi(year));;
}

string HttpProvider::getTime()
{
    ConfigManager& configManager = ConfigManager::instance();
    string httpDate = dateExtraction(fetchCurlHead(configManager.getHttpConfig().link));
    string weekday, day, month, year, time, tz;
    return adjustTime(httpDate, weekday, day, month, year, time, tz);
}

int HttpProvider::parseMonth(const string& mon)
{
    static const string months[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    for (int i = 0; i < 12; ++i) {
        if (months[i] == mon) return i + 1;
    }
    return -1;
}

string HttpProvider::fetchCurlHead(const string& url)
{
    const int MAX_RETRIES = 3;
    const int RETRY_DELAY_SEC = 1;

    auto isBlank = [](const std::string& s) {
        return std::all_of(s.begin(), s.end(), [](unsigned char c) {
            return std::isspace(c);
        });
    };

    for (int attempt = 1; attempt <= MAX_RETRIES; ++attempt) {
        std::string cmd = "curl -I -s " + url;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);

        if (!pipe) {
            error("popen函数调用失败，尝试 " + std::to_string(attempt) + "/" + std::to_string(MAX_RETRIES));
            if (attempt < MAX_RETRIES) {
                sleep(RETRY_DELAY_SEC);
                continue;
            }
            return "";
        }

        char buffer[128];
        std::string result;
        while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
            result += buffer;
        }

        info("服务器返回原始数据：" + result);

        if (!result.empty() && !isBlank(result)) {
            return result;
        }

        error("获取到的响应为空，尝试 " + std::to_string(attempt) + "/" + std::to_string(MAX_RETRIES));
        if (attempt < MAX_RETRIES) {
            sleep(RETRY_DELAY_SEC);
        }
    }

    return "";
}

string HttpProvider::dateExtraction(const string& rawText)
{
    istringstream iss(rawText);
    string line;
    string date;
    while (getline(iss, line))
    {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.find("Date: ") == 0) {
            string rawDate = line.substr(6);
            size_t pos = rawDate.find_last_of(' ');
            date = rawDate.substr(0, pos);
            break;
        }
    }
    info("解析得到日期字符串："  + date);
    return date;
}

string HttpProvider::tmToString(const tm& tm, const string& fmt)
{
    stringstream ss;
    ss << put_time(&tm, fmt.c_str());
    return ss.str();
}
