cmake_minimum_required(VERSION 3.1)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(primes main.cpp prime.cpp settings.cpp starter.cpp)
target_link_libraries(primes Threads::Threads)

