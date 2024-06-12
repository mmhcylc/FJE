aux_source_directory(json_processor JSON_PROCESSOR_SRC)
add_library(json_processor OBJECT ${JSON_PROCESSOR_SRC})

aux_source_directory(json_outputer JSON_OUTPUTER_SRC)
add_library(json_outputer OBJECT ${JSON_OUTPUTER_SRC})

add_executable(main main.cpp)

target_link_libraries(main PUBLIC json_outputer json_processor)