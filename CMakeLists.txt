cmake_minimum_required(VERSION 3.10)
project(upi_fraud_detector)

set(CMAKE_CXX_STANDARD 17)
add_executable(upi_detector
    cpp/src/main.cpp
    cpp/src/csv_reader.cpp
    cpp/src/rules.cpp
    cpp/src/detector.cpp
)

