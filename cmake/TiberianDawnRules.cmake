# Rules code generator, allows keeping game rules in one place
# for a single source of truth.

function(Main)
  message(STATUS "=== TiberianDawnRules.cmake start ===")

  set(RULE_JSON_SOURCES_COMMENTS, "")
  set(RULE_KEYS_DEFINES "")

  file(RELATIVE_PATH RELATIVE_SOURCE_DIR ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
  message(STATUS "Processing rules files in ${RELATIVE_SOURCE_DIR}/rules/*.json")

  file(GLOB_RECURSE RULES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/rules/*.json")

  foreach(RULE_FILE ${RULES_FILES})
    file(RELATIVE_PATH RELATIVE_RULE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/rules ${RULE_FILE})

    message(STATUS "Processing rules file: ${RELATIVE_RULE_FILE}")

    string(APPEND RULE_JSON_SOURCES_COMMENTS " *   - rules/${RELATIVE_RULE_FILE}\n")

    string(REGEX REPLACE "^([A-Z][a-z]+)[.]json$" "\\1" SECTION_NAME ${RELATIVE_RULE_FILE})

    message(STATUS "Rule section: ${SECTION_NAME}")

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
      #string(JSON RULE_TYPE GET ${RULE_OBJECT_JSON} type)
      #string(JSON RULE_DEFAULT GET ${RULE_OBJECT_JSON} default)

      message(STATUS "Generating define for rule: [${SECTION_NAME}] => ${RULE_NAME}")

      string(REGEX REPLACE "([A-Z][a-z]+)" "\\1_" RULE_NAME_SNAKE_CASE ${RULE_NAME})
      string(REGEX REPLACE "_($)" "\\1" RULE_NAME_SNAKE_CASE ${RULE_NAME_SNAKE_CASE})
      string(REGEX REPLACE "([0-9])([A-Z])" "\\1_\\2" RULE_NAME_SNAKE_CASE ${RULE_NAME_SNAKE_CASE})
      string(TOUPPER ${RULE_NAME_SNAKE_CASE} RULE_NAME_SNAKE_CASE)

      string(APPEND RULE_KEYS_DEFINES "\n#define ${RULE_NAME_SNAKE_CASE}_RULE \"${RULE_NAME}\"")
    endforeach()
  endforeach()

  set(RULE_KEYS_HEADER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/rulekeys.h)

  configure_file(${RULE_KEYS_HEADER_PATH}.in ${RULE_KEYS_HEADER_PATH} @ONLY)

  message(STATUS "=== TiberianDawnRules.cmake end ===")
endfunction()

Main()
