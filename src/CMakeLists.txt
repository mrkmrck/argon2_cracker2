add_executable(argon2_cracker2 main.cpp benchmark.cpp crack.cpp utils.cpp)


include_directories(../dependencies/cxx_argp)
include_directories(../dependencies/phc-winner-argon2)
target_link_libraries(${PROJECT_NAME} libargon2.a)