# add_executable(
#   crack_gtest
#   crack_gtest.cpp
# )
# target_link_libraries(
#   crack_gtest
#   GTest::gtest_main
#   libargon2.a)

# include(GoogleTest)
# gtest_discover_tests(crack_gtest)
set(TESTS crack_ctest.cpp)
foreach(test ${TESTS})
    set(test_name ${test})
    add_executable(${test_name} ${test})
    target_link_libraries(${test_name} libargon2.a)
    add_test(${test_name} ${test_name})
endforeach()
# include(GoogleTest)
# gtest_discover_tests(crack_gtest)

file(COPY hashfile.txt words.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})