set(CATCH_VERSION 1.7.0)
set(CATCH_DIR ${CMAKE_BINARY_DIR}/catch/${CATCH_VERSION})
set(CATCH_FILE ${CATCH_DIR}/catch.hpp)
if(NOT EXISTS ${CATCH_FILE})
	file(DOWNLOAD "https://github.com/philsquared/Catch/releases/download/v${CATCH_VERSION}/catch.hpp" ${CATCH_FILE})
endif()

add_library(Catch UNKNOWN IMPORTED)
set_target_properties(Catch PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES ${CATCH_DIR}
)
