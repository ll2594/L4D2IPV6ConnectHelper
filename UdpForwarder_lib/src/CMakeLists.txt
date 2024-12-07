file(GLOB src_list *.cpp)

target_sources( ${PROJECT_NAME}
        PUBLIC
        ${src_list}
)
