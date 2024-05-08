# Include all subdirectories.
file(GLOB subdirectories LIST_DIRECTORIES true *)
foreach(subdir ${subdirectories})
    if(IS_DIRECTORY ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()
