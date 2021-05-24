if(WIN32)
  if(DEFINED ENV{DECKLINK_SDK_DIR})
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(DECKLINK_FOUND TRUE)
    set(DECKLINK_DIR $ENV{DECKLINK_SDK_DIR})
    string(REPLACE "\\" "/" DECKLINK_DIR "${DECKLINK_DIR}")
    set(DECKLINK_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR} "${DECKLINK_DIR}/include")
    set(DECKLINK_LIBRARY_DIR ${PROJECT_BINARY_DIR})
    set(DECKLINK_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/DeckLinkAPI_i.c")
    set_source_files_properties(${DECKLINK_SOURCES} PROPERTIES GENERATED TRUE)
    set_source_files_properties(${DECKLINK_SOURCES} PROPERTIES SKIP_AUTOGEN TRUE)
    set(DECKLINK_LIBS DeckLink)
    add_library(DeckLink SHARED ${DECKLINK_SOURCES})
    target_include_directories(DeckLink PRIVATE ${DECKLINK_INCLUDE_DIRS})
    set_target_properties(DeckLink PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
    set(MIDL_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/DeckLinkAPI.h)
    set(MIDL_FILE ${DECKLINK_DIR}/include/DeckLinkAPI.idl)
    set_source_files_properties(${MIDL_OUTPUT} PROPERTIES GENERATED TRUE)
    add_custom_target(DeckLinkMidl DEPENDS ${MIDL_OUTPUT})
    add_custom_command(
        OUTPUT ${MIDL_OUTPUT}
        COMMAND midl /h DeckLinkAPI.h ${MIDL_FILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${MIDL_FILE}
        VERBATIM
    )
    add_dependencies(DeckLink DeckLinkMidl)
  else()
    set(DECKLINK_FOUND FALSE)
  endif()
elseif(APPLE)
  if(DEFINED ENV{DECKLINK_SDK_DIR})
    set(DECKLINK_FOUND TRUE)
    set(DECKLINK_SDK_DIR $ENV{DECKLINK_SDK_DIR})
    set(DECKLINK_INCLUDE_DIRS "${DECKLINK_SDK_DIR}/include")
    set(DECKLINK_SOURCES "${DECKLINK_INCLUDE_DIRS}/DeckLinkAPIDispatch.cpp")
  else()
    set(DECKLINK_FOUND FALSE)
  endif()
elseif(UNIX)
  if(EXISTS "/usr/include/DeckLinkAPI.h")
    set(DECKLINK_FOUND TRUE)
    set(DECKLINK_DIR /usr)
    set(DECKLINK_INCLUDE_DIRS "${DECKLINK_DIR}/include")
    set(DECKLINK_SOURCES "${DECKLINK_INCLUDE_DIRS}/DeckLinkAPIDispatch.cpp")
    set(DECKLINK_LIBS "DeckLink")
    add_library(DeckLink STATIC ${DECKLINK_SOURCES})
    target_include_directories(DeckLink PRIVATE ${DECKLINK_INCLUDE_DIRS})
    target_compile_options(DeckLink PRIVATE -fPIC)
    set_target_properties(DeckLink PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
  else()
    set(DECKLINK_FOUND FALSE)
 endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(DeckLink DEFAULT_MSG DECKLINK_DIR ${DECKLINK_FOUND})
