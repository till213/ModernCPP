set(APP_NAME "23-typed-enum")

set(LIBRARY_DEPENDENCIES "")

if (${PLATFORM_IS_MACOS})
    list(APPEND LIBRARY_DEPENDENCIES -lc++)
endif()

add_executable(${APP_NAME})
target_sources(${APP_NAME}
    PRIVATE
        main.cpp
        README.md
)
target_link_libraries(${APP_NAME} PRIVATE ${LIBRARY_DEPENDENCIES})
