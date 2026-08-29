//
// Created by dministrator on 2026/8/30.
//

#include "HttpProvider.h"

#include "../config/ConfigManager.h"
#include "spdlog/spdlog.h"
#include <curl/curl.h>

using namespace std;
using namespace spdlog;

string HttpProvider::getTime()
{

}

int HttpProvider::parseMonth(const std::string& mon)
{
    static const std::string months[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    for (int i = 0; i < 12; ++i) {
        if (months[i] == mon) return i + 1;
    }
    return -1;
}
