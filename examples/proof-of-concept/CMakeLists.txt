include(FindProtobuf)

include_directories("./")
add_executable(sender sender.cpp)
add_executable(receiver receiver.cpp)
