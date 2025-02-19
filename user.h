#pragma once
extern int timeStep;
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

// #define SMALL
// #define BIG
#define MIDDLE

#define USE_DBUS 1

#define PI 3.14159
// #define LEFT 0
// #define RIGHT 1
#define RAD_PER_DEG 0.017453293f
#define WHEEL_RADIAN 210
#define INWHEEL_RADIAN 75
#define CAR_WHITE 310
#define RATIO 0.2
#define FI_OFFSET 0

//  #define START_FROM_UP
 #define START_FROM_DOWN


#define RAD_TO_DEGREE 57.295779513082320876798154814105
#define DEGREE_TO_RAD 0.0174532925199432957692369076849


#define LIMIT(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define ABS(x) ((x) > 0 ? (x) : (-(x)))
extern double titaClock;
// 重置控制台格式
#define ANSI_RESET "\x1b[0m"
// 控制台格式定义
#define ANSI_BOLD "\x1b[1m"      // 加粗
#define ANSI_UNDERLINE "\x1b[4m" // 下划线
// 背景颜色
#define ANSI_BLACK_BACKGROUND "\x1b[40m"
#define ANSI_RED_BACKGROUND "\x1b[41m"
#define ANSI_GREEN_BACKGROUND "\x1b[42m"
#define ANSI_YELLOW_BACKGROUND "\x1b[43m"
#define ANSI_BLUE_BACKGROUND "\x1b[44m"
#define ANSI_MAGENTA_BACKGROUND "\x1b[45m"
#define ANSI_CYAN_BACKGROUND "\x1b[46m"
#define ANSI_WHITE_BACKGROUND "\x1b[47m"
// 前景颜色
#define ANSI_BLACK_FOREGROUND "\x1b[30m"
#define ANSI_RED_FOREGROUND "\x1b[31m"
#define ANSI_GREEN_FOREGROUND "\x1b[32m"
#define ANSI_YELLOW_FOREGROUND "\x1b[33m"
#define ANSI_BLUE_FOREGROUND "\x1b[34m"
#define ANSI_MAGENTA_FOREGROUND "\x1b[35m"
#define ANSI_CYAN_FOREGROUND "\x1b[36m"
#define ANSI_WHITE_FOREGROUND "\x1b[37m"

#define ANSI_CLEAR_SCREEN "\x1b[2J"    // 清屏

// 调试输出
//报错
#define ldg_err(y, x) std::cout << ANSI_BOLD << ANSI_RED_FOREGROUND << "[err] " << y << ANSI_RESET << "  [" << x << "]" << ANSI_WHITE_FOREGROUND << "\tFun:" << __FUNCTION__ << "\tLine:" << __LINE__ << ANSI_RESET << std::endl
//警告
#define ldg_warn(y) std::cout << ANSI_BOLD << ANSI_YELLOW_FOREGROUND << "[wrn] " << y << ANSI_RESET << ANSI_WHITE_FOREGROUND << "\tFun:" << __FUNCTION__ << "\tLine:" << __LINE__ << ANSI_RESET << std::endl
//成功
#define ldg_ok(y, x) std::cout << ANSI_BOLD << ANSI_GREEN_FOREGROUND << "[o.k] " << y << ANSI_RESET << "  [" << x << "]" << ANSI_WHITE_FOREGROUND << "\tFun:" << __FUNCTION__ << "\tLine:" << __LINE__ << ANSI_RESET << std::endl
//一般信息
#define ldg(y, x) std::cout << ANSI_BOLD << ANSI_MAGENTA_FOREGROUND << "[...] " << y << ANSI_RESET << "  [" << x << "]" << ANSI_WHITE_FOREGROUND << "\tFun:" << __FUNCTION__ << "\tLine:" << __LINE__ << ANSI_RESET << std::endl
//输出矩阵
#define ldg_mat(x) std::cout << ANSI_BOLD << ANSI_CYAN_FOREGROUND << "----[" << #x << "]----\n" \
                             << ANSI_RESET << x << std::endl

#define data1(y, x) std::cout << "[" << y << ":1" \
                              << "] " << x << std::endl
#define data2(y, x1, x2) std::cout << "[" << y << ":2" \
                                   << "] " << x1 << "\t" << x2 << "\t" << std::endl
#define data3(y, x1, x2, x3) std::cout << "[" << y << ":3" \
                                       << "] " << x1 << "\t" << x2 << "\t" << x3 << "\t" << std::endl
#define data4(y, x1, x2, x3, x4) std::cout << "[" << y << ":4" \
                                           << "] " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << "\t" << std::endl
