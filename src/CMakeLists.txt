add_executable(rime_table_bin_decompiler
    main.cpp
    rime/dict/table.cc
    rime/dict/mapped_file.cc
    rime/dict/string_table.cc
    rime/dict/vocabulary.cc
)
link_directories(rime_table_bin_decompiler ${Boost_LIBRARY_DIRS})
target_link_libraries(rime_table_bin_decompiler ${Boost_LIBRARIES}  ${Marisa_LIBRARY})
install(TARGETS rime_table_bin_decompiler DESTINATION ${CMAKE_INSTALL_BINDIR})
