#ifndef TIMER_H
#define TIMER_H

#include <QMainWindow>
#include <QTimer>
#include <chrono>
#include <iostream>
#include <string>
#include <algorithm>
#include <thread>

using namespace std;
using namespace std::chrono;

class Timer_Convolution
{
private:
    // 原型：template <class Timer, class Duration = typename Timer::duration>
    // class time_point;
    time_point<high_resolution_clock>_startTimer;
    time_point<high_resolution_clock>_endTimer;
    // high_resolution_clock 高精度时钟
    string _labelName;

public:
    Timer_Convolution():_labelName("Time Elapsed: ")
    {
        Refresh();
    }

    explicit Timer_Convolution(const string & userName):_labelName(userName + ": ")
    {
        Refresh();
    }

    ~Timer_Convolution() {}

    void Refresh()
    {
        // 初始化，获取当前时间，通过差值计算运行时间
        _startTimer = high_resolution_clock::now();
    }

    long double Duration(bool again = false)
    {
        _endTimer = high_resolution_clock::now();
        duration<long double> timeMinus = _endTimer-_startTimer; // 计算经过时间
        if(again)
            this->Refresh();
            // this 指向当前对象
        return timeMinus.count()*1000;
    }

    string timerAnswerOutput(const string &tip)
    {
        return output(true,tip,true,false);
    }

    // tip 为引用
    string output(bool reset = false, const string &tip = "", bool unit_ms = true, bool kill = false) // 输出时间的字符串
    {
        string res = "";
        // 如果单位为毫秒
        if (unit_ms)
        {
            if (tip.length() > 0) // tip 为默认参数
                res.append(tip + ": " + to_string(Duration()) + "ms");
            else
                res.append(_labelName + to_string(Duration()) + "ms");
        }
        else // 单位为秒
        {
            if (tip.length() > 0)
                res.append(tip + ": " + to_string(Duration()/1000.0) + "s");
            else
                res.append(_labelName + to_string(Duration()/1000.0) + "s");
        }
        if (reset) // 重新计时
            this->Refresh();
        if (kill) // 停止计时
            exit(0);
        return res;
    }
};

#endif // TIMER_H
