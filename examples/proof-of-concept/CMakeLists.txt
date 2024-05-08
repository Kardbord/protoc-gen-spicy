find_package(Protobuf REQUIRED)

add_executable(sender sender.cpp SimpleMessage.proto)
add_executable(receiver receiver.cpp SimpleMessage.proto)

target_include_directories(sender PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(receiver PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(sender PRIVATE protobuf::libprotobuf)
target_link_libraries(receiver PRIVATE protobuf::libprotobuf)

protobuf_generate(TARGET sender LANGUAGE cpp)
protobuf_generate(TARGET receiver LANGUAGE cpp)
