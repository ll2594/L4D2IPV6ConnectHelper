file(GLOB header_list *.h)

target_sources( ${PROJECT_NAME}
        PUBLIC
        ${header_list}
)
