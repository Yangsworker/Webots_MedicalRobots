cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_FLAGS "-std=c++14")  #使用C++14标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g -Wno-unused-parameter -Wno-unused-variable -Wno-overloaded-virtual -pthread") #开启所有警告 -O3优化 -g调试信息 -pthread多线程 
#禁止警告未使用的参数 禁止警告未使用的变量 禁止警告重载虚函数


# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
aux_source_directory(./Alg/src DIR_SRCS)
aux_source_directory(./Device/src DIR_SRCS)
aux_source_directory(./Mode/src DIR_SRCS)
aux_source_directory(./USER_Task/src DIR_SRCS)

set(WEBOTS_HOME "/home/tdt/webots")   #设置webots路径

set (LIBRARIES m ${CMAKE_SHARED_LIBRARY_PREFIX}Controller${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_PREFIX}CppController${CMAKE_SHARED_LIBRARY_SUFFIX})

# 查找当前目录下的所有库文件
include_directories("./")
include_directories("./Alg/inc")
include_directories("./Device/inc")
include_directories("./Mode/inc")
include_directories("./Eigen/inc")
include_directories("./USER_Task/inc")
include_directories("${WEBOTS_HOME}/include/controller/cpp")
include_directories("${WEBOTS_HOME}/include/controller/c")

link_directories(${WEBOTS_HOME}/lib/controller)




# 指定生成目标
add_executable(${PROJECT_NAME} ${DIR_SRCS})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# 复制可执行文件到上级目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
${CMAKE_BINARY_DIR}/${PROJECT_NAME} ../Webots_MedicalRobots
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME}) #设置项目名称
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})#设置项目版本
include(CPack)#包装项目
