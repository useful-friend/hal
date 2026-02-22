cmake_minimum_required(VERSION 3.16)
project(hal LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

# Interface-only library (headers)
add_library(hal INTERFACE)
target_include_directories(hal INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(hal INTERFACE cxx_std_20)

# FT4222 implementation (stub; link libft4222 when available)
add_library(hal_ft4222 STATIC
  src/ft4222_spi.cpp
  src/ft4222_i2c.cpp
)
target_include_directories(hal_ft4222 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(hal_ft4222 PUBLIC hal)
# target_link_libraries(hal_ft4222 PRIVATE ft4222)  # Uncomment when libft4222 installed
