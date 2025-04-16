cmake_minimum_required(VERSION 3.10)
project(Lizon)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(Lizon
    src/mframe.cpp
    src/main.cpp
)

target_link_libraries(Lizon ${wxWidgets_LIBRARIES})

if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    add_custom_command(TARGET Lizon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:Lizon>/assets
        COMMENT "Copying assets directory"
    )

    install(DIRECTORY "${CMAKE_SOURCE_DIR}/assets/"
            DESTINATION "share/${PROJECT_NAME}"
            PATTERN ".gitignore" EXCLUDE 
    )
else()
    message(WARNING "Assets directory not found at ${CMAKE_SOURCE_DIR}/assets")
endif()

if(WIN32)
    set_target_properties(Lizon PROPERTIES
        WIN32_EXECUTABLE_ICON "${CMAKE_SOURCE_DIR}/assets/icon.ico"
    )
endif()

install(TARGETS Lizon DESTINATION "bin")