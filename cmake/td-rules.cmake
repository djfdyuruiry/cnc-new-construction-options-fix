# Rules code generator, allows keeping game rules in one place
# for a single source of truth.

function(Main)
  message(STATUS "=== td.rules.cmake start ===")
  message(STATUS "Processing rules files in ${CMAKE_CURRENT_SOURCE_DIR}/rules/*.json")

  file(GLOB_RECURSE RULES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/rules/*.json")

  set(RULE_KEYS_DEFINES "")

  foreach(RULE_FILE ${RULES_FILES})
    file(RELATIVE_PATH RELATIVE_RULE_FILE ${CMAKE_CURRENT_SOURCE_DIR} ${RULE_FILE})

    message(STATUS "Processing rules file: ${RELATIVE_RULE_FILE}")

    string(REGEX REPLACE "rules/([A-Z][a-z]+)[.]json" "\\1" SECTION_NAME ${RELATIVE_RULE_FILE})

    string(TOUPPER ${SECTION_NAME} SECTION_NAME_UPPER)
    string(APPEND RULE_KEYS_DEFINES "// [${SECTION_NAME}]\n")
    string(APPEND RULE_KEYS_DEFINES "#define ${SECTION_NAME_UPPER}_SECTION \"${SECTION_NAME}\"\n")

    file(READ ${RULE_FILE} RULES_JSON)

    # read number of rules
    string(JSON RULE_COUNT LENGTH ${RULES_JSON} rules)
    MATH(EXPR RULE_COUNT "${RULE_COUNT}-1")

    foreach(RULE_INDEX RANGE ${RULE_COUNT})
      # extract rule at index
      string(JSON RULE_OBJECT_JSON GET ${RULES_JSON} rules ${RULE_INDEX})

      string(JSON RULE_NAME GET ${RULE_OBJECT_JSON} name)
      string(JSON RULE_TYPE GET ${RULE_OBJECT_JSON} type)
      string(JSON RULE_DEFAULT GET ${RULE_OBJECT_JSON} default)

      message(STATUS "Rule Name: ${RULE_NAME}")
      message(STATUS "Rule Type: ${RULE_TYPE}")
      message(STATUS "Rule Default: ${RULE_DEFAULT}")

      string(REGEX REPLACE "([A-Z][a-z]+)" "\\1_" RULE_NAME_SNAKE_CASE ${RULE_NAME})
      string(REGEX REPLACE "_($)" "\\1" RULE_NAME_SNAKE_CASE ${RULE_NAME_SNAKE_CASE})
      string(TOUPPER ${RULE_NAME_SNAKE_CASE} RULE_NAME_SNAKE_CASE)

      string(APPEND RULE_KEYS_DEFINES "\n#define ${RULE_NAME_SNAKE_CASE}_RULE \"${RULE_NAME}\"")
    endforeach()
  endforeach()

  message(STATUS ${RULE_KEYS_DEFINES})

  message(STATUS "=== td.rules.cmake end ===")
endfunction()

Main()
