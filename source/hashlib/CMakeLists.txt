#add by jzf@2021-02-02
#
#设置工程名
set(target "hashlib")
set(OUTPUT_NAME "hashlib")

add_definitions(-D DLL_EXPORT_HASHLIB)

#设置包含头文件路径
include_directories(${OPENSSL_INCLUDE_PATH})
include_directories("${PROJECT_SOURCE_DIR}/include")
#搜索文件，并设置工程目录
file(GLOB PUBLICS  "${PROJECT_SOURCE_DIR}/include/hashlib/*.h")
source_group("public"  FILES  ${PUBLICS})

file(GLOB HEADERS  "*.h")
source_group("include"  FILES  ${HEADERS})


file(GLOB SOURCES  "*.cpp")
source_group("source"  FILES  ${SOURCES})

#汇总文件
set( ALL_LIST
${PUBLICS}
${HEADERS}
${SOURCES}
)

#作为动态库
add_library(${target} SHARED ${ALL_LIST})

#设置项目属性
set_target_properties(${target}  PROPERTIES ARCHIVE_OUTPUT_NAME "${OUTPUT_NAME}")
set_target_properties(${target}  PROPERTIES LIBRARY_OUTPUT_NAME "${OUTPUT_NAME}")
set_target_properties(${target}  PROPERTIES RUNTIME_OUTPUT_NAME "${OUTPUT_NAME}")
set_target_properties(${target}  PROPERTIES FOLDER "hashlib")

#设置链接库
if(WIN32)
target_link_libraries(${target}  "${OPENSSL_LIBRARY_PATH}/libcrypto.lib")
else()
#
endif()