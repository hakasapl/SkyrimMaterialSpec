cmake_minimum_required (VERSION 3.31)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# For MSVC
add_compile_options("/Zc:__cplusplus")

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

cmake_policy(SET CMP0167 NEW)

add_compile_definitions(NOMINMAX)
add_compile_definitions(WIN32_LEAN_AND_MEAN)
add_compile_definitions(NOSOCKETTYPE)
add_compile_definitions(_DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR)
add_compile_definitions(_WIN32_WINNT=0x0A00)

include_directories("include")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.hpp)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Add the library
set(LIB_NAME SkyrimMaterialSpec)
set(LIB_VERSION 0.1.0)

project(${LIB_NAME} VERSION ${LIB_VERSION} LANGUAGES CXX)
add_library(${LIB_NAME} SHARED ${SOURCES} ${HEADERS})

# Add Packages
add_subdirectory(external/nifly)

find_package(nlohmann_json REQUIRED CONFIG)
find_package(nlohmann_json_schema_validator REQUIRED)

target_link_libraries(${LIB_NAME} PUBLIC
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator::validator
    nifly
)
target_include_directories(${LIB_NAME} PUBLIC include)
