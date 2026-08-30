//
// Created by dministrator on 2026/8/30.
//

#include "TimeSetter.h"
#include <spdlog/spdlog.h>

using namespace std;
using namespace spdlog;


void TimeSetter::setTime(const string& year, const string& month, const string& day,
    const string& hour, const string& minute)
{
    mSetter->setTime(year, month, day, hour, minute);
}

void TimeSetter::setSetter(unique_ptr<ITimeSetter> setter)
{
    mSetter = move(setter);
}
