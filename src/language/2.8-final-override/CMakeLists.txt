set(APP_NAME "28-final-override")

set(LIBRARY_DEPENDENCIES "")

if (${PLATFORM_IS_MACOS})
    list(APPEND LIBRARY_DEPENDENCIES -lc++)
endif()

add_executable(${APP_NAME})
target_sources(${APP_NAME}
    PRIVATE
        main.cpp
)
target_link_libraries(${APP_NAME} PRIVATE ${LIBRARY_DEPENDENCIES})
