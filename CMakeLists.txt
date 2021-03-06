######################################################################
#@auther:  jzfamily
#@date: 2020-05-22
#@version：
#        v1.5.22.22 create by jzf
#@description:
#        加密解密操作
#
#######################################################################
cmake_minimum_required(VERSION 3.8.1)
project(show_ts)

#打印信息
message("CMAKE_SYSTEM: ${CMAKE_SYSTEM}")
message("CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message("CMAKE_VS_PLATFORM_TOOLSET: ${CMAKE_VS_PLATFORM_TOOLSET}")


set(THIRD_LIB_PATH "${PROJECT_SOURCE_DIR}/thirdlib")
set(CURL_INCLUDE_PATH "${THIRD_LIB_PATH}/curl-7.70.0/include")
set(BOOST_INCLUDE_PATH "${THIRD_LIB_PATH}/boost_1_74_0/include")
set(NLOHMANN_INCLUDE_PATH "${THIRD_LIB_PATH}/nlohmann/include")
set(SQLITECPP_INCLUDE_PATH "${THIRD_LIB_PATH}/SQLiteCpp3.x/include")
set(SQLITE_INCLUDE_PATH "${THIRD_LIB_PATH}/sqlite-3.33.0/include")
set(OPENSSL_INCLUDE_PATH "${THIRD_LIB_PATH}/openssl-1.1.1g/include")
if(WIN32)
#此时默认win64 
#启用自定义工程文件夹
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#配置编译文件输出目录
set(CMAKE_PDB_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/pdb/win64")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/win64")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/win64")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/win64")


#配置第三方库目录
set(CURL_LIBRARY_PATH "${THIRD_LIB_PATH}/curl-7.70.0/lib/win64")
set(BOOST_LIBRARY_PATH "${THIRD_LIB_PATH}/boost_1_74_0/lib/win64")
set(SQLITECPP_LIBRARY_PATH "${THIRD_LIB_PATH}/SQLiteCpp3.x/lib/win64")
set(SQLITE_LIBRARY_PATH "${THIRD_LIB_PATH}/sqlite-3.33.0/lib/win64")
set(OPENSSL_LIBRARY_PATH "${THIRD_LIB_PATH}/openssl-1.1.1g/lib/win64")
else()
#linux
endif()

add_subdirectory(source)