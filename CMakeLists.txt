cmake_minimum_required(VERSION 4.3)

project(Parallel_Puasson CXX)

add_subdirectory(matplotplusplus)
add_subdirectory(matrix)

find_package(OpenMP REQUIRED)

add_executable(puasson)
target_sources(puasson PRIVATE
    main.cpp
)

target_include_directories(puasson PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# target_compile_definitions(puasson PUBLIC OMP_VERSION NUM_THREADS=6)
target_link_libraries(puasson PRIVATE 
    matplot
    fraction
    matrix
)
# target_link_libraries(puasson PUBLIC OpenMP::OpenMP_CXX)

# target_compile_definitions(matrix PUBLIC OMP_VERSION NUM_THREADS=6)
# target_link_libraries(matrix PUBLIC OpenMP::OpenMP_CXX)


# add_executable(puasson_2)
# target_sources(puasson_2 PRIVATE
#     main2.cpp
# )

# target_include_directories(puasson_2 PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )

# target_compile_definitions(puasson_2 PUBLIC PUASSON_2)
# target_link_libraries(puasson_2 PRIVATE 
#     matplot
#     fraction
#     matrix
# )