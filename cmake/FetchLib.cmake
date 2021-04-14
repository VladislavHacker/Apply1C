function(FetchLib GIT_REPOSITORY LIB_NAME)
    execute_process(
            COMMAND git clone ${GIT_REPOSITORY} ${LIB_NAME}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/library
    )
    include_directories(${PROJECT_SOURCE_DIR}/library)
endfunction()
