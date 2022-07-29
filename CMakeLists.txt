cmake_minimum_required(VERSION 3.0.0)
project(argon2_cracker2 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)


include(CTest)
enable_testing()


add_subdirectory(src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# add_subdirectory(dependencies/googletest)
# add_subdirectory(test)


