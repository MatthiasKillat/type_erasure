cmake_minimum_required(VERSION 3.10)
project(type_erasure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories( include )

add_executable(polymorphic_pushpop
  src/main_polymorphic.cpp
)

add_executable(any_pushpop_simple
  src/main_any_simple.cpp
)

add_executable(any_pushpop
  src/main_any.cpp
)

add_executable(any_pushpop_client
  src/main_any_client.cpp
)

add_executable(stringref
  src/main_stringref.cpp
)


