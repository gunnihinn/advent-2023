add_library(advent advent.h advent.cpp)

install(TARGETS advent DESTINATION bin)
install(FILES advent.h DESTINATION include)
