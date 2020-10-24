set(COMPONENT_SRCS
        "main.cpp"
        )

idf_component_register(
        SRCS ${COMPONENT_SRCS}
        INCLUDE_DIRS "."
)
