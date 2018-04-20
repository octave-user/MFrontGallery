function(add_mfront_behaviour_sources lib mat interface file)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${file}.mfront.in")
    set(mfront_file   "${CMAKE_CURRENT_BINARY_DIR}/${file}.mfront")
    configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/${file}.mfront.in"
      "${CMAKE_CURRENT_BINARY_DIR}/${file}.mfront"
      @ONLY)
  else(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${file}.mfront.in")
    set(mfront_file   "${CMAKE_CURRENT_SOURCE_DIR}/${file}.mfront")
  endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${file}.mfront.in")
  set(file_OK ON)
  if(${interface} STREQUAL "ansys")
    check_ansys_compatibility(${mat} ${mfront_file})
  endif(${interface} STREQUAL "ansys")
  if(${interface} STREQUAL "epx")
    check_europlexus_compatibility(${mat} ${mfront_file})
  endif(${interface} STREQUAL "epx")
  if(${interface} STREQUAL "abaqusexplicit")
    check_abaqus_explicit_compatibility(${mat} ${mfront_file})
  endif(${interface} STREQUAL "abaqusexplicit")
  if(${interface} STREQUAL "calculix")
    check_calculix_compatibility(${mat} ${mfront_file})
  endif(${interface} STREQUAL "calculix")
  if(${interface} STREQUAL "cyrano")
    check_cyrano_compatibility(${mat} ${mfront_file})
  endif(${interface} STREQUAL "cyrano")
  if(file_OK)
    set(mfront_output1 "${interface}/src/${file}.cxx")
    if(interface STREQUAL "zmat")
      set(mfront_output2 "${interface}/src/ZMAT${file}.cxx")
    elseif(interface STREQUAL "castem")
      set(mfront_output2 "${interface}/src/umat${file}.cxx")
    else(interface STREQUAL "zmat")
      set(mfront_output2 "${interface}/src/${interface}${file}.cxx")
    endif(interface STREQUAL "zmat")
    add_custom_command(
      OUTPUT  "${mfront_output1}"
      OUTPUT  "${mfront_output2}"
      COMMAND "${MFRONT}"
      ARGS    "--interface=${interface}"
      ARGS    "--search-path=${CMAKE_SOURCE_DIR}/materials/${mat}/properties"
      ARGS    "--search-path=${CMAKE_SOURCE_DIR}/materials/${mat}/behaviours"
      ARGS     "${mfront_file}"
      DEPENDS "${mfront_file}"
      WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${interface}"
      COMMENT "mfront source ${mfront_file} for interface ${interface}")
    set(${lib}_SOURCES ${mfront_output1} ${mfront_output2}
      ${${lib}_SOURCES} PARENT_SCOPE)
    install_mfront("${mfront_file}" ${mat} behaviours)
  else(file_OK)
    message(STATUS "${file} has been discarded for interface ${interface}")
  endif(file_OK)
endfunction(add_mfront_behaviour_sources)

function(mfront_behaviours_library mat)
  set ( _CMD SOURCES )
  set ( _SOURCES )
  set ( _DEPENDENCIES )
  if((TFEL_CXX_STANDARD GREATER 17) OR (TFEL_CXX_STANDARD EQUAL 17))
    set(TFEL_MFRONT_LIBRARIES
      "${TFELException};${TFELMath};${TFELMaterial}")
  else((TFEL_CXX_STANDARD GREATER 17) OR (TFEL_CXX_STANDARD EQUAL 17))
    set(TFEL_MFRONT_LIBRARIES
      "${TFELException};${TFELMath};${TFELMaterial};${TFELPhysicalConstants}")
  endif((TFEL_CXX_STANDARD GREATER 17) OR (TFEL_CXX_STANDARD EQUAL 17))
  foreach ( _ARG ${ARGN})
    if ( ${_ARG} MATCHES SOURCES )
      set ( _CMD SOURCES )
    elseif ( ${_ARG} MATCHES DEPENDENCIES )
      set ( _CMD DEPENDENCIES )
    else ()
      if ( ${_CMD} MATCHES SOURCES )
        list ( APPEND _SOURCES "${_ARG}" )
      elseif ( ${_CMD} MATCHES DEPENDENCIES )
        list ( APPEND _DEPENDENCIES "${_ARG}" )
      endif ()
    endif ()
  endforeach ()
  list(LENGTH _SOURCES _SOURCES_LENGTH )
  if(${_SOURCES_LENGTH} LESS 1)
    message(FATAL_ERROR "mfront_behaviours_library : no source specified")
  endif(${_SOURCES_LENGTH} LESS 1)
  # treating dependencies
  foreach(dep ${_DEPENDENCIES})
    foreach(interface ${mfront-behaviours-interfaces})
      add_mfront_dependency(${mat}_mfront_behaviours_dependencies ${mat} ${interface} ${dep})
    endforeach(interface ${mfront-behaviours-interfaces})
  endforeach(dep ${_DEPENDENCIES})
  include_directories("${TFEL_INCLUDE_PATH}")
  foreach(interface ${mfront-behaviours-interfaces})
    if(${interface} STREQUAL "castem")
      getCastemBehaviourName(${mat})
    elseif(${interface} STREQUAL "ansys")
      getAnsysBehaviourName(${mat})
    elseif(${interface} STREQUAL "abaqus")
      getAbaqusBehaviourName(${mat})
    elseif(${interface} STREQUAL "abaqusexplicit")
      getAbaqusExplicitBehaviourName(${mat})
    elseif(${interface} STREQUAL "calculix")
      getCalculixBehaviourName(${mat})
    else((${interface} STREQUAL "castem"))
      set(lib "${mat}Behaviours-${interface}")
    endif(${interface} STREQUAL "castem")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${interface}")
    foreach(source ${_SOURCES})
      if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
	set(${lib}_SOURCES ${source} ${${lib}_SOURCES})
      else(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
	add_mfront_behaviour_sources(${lib} ${mat} ${interface} ${source})
      endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
    endforeach(source ${_SOURCES})
    if(${mat}_mfront_behaviours_dependencies_${interface}_SOURCES)
      message("dependencies : ${${mat}_mfront_behaviours_dependencies_${interface}_SOURCES}")
    endif(${mat}_mfront_behaviours_dependencies_${interface}_SOURCES)
    foreach(deps ${${mat}_mfront_behaviours_dependencies_${interface}_SOURCES})
      set(${lib}_SOURCES ${deps} ${${lib}_SOURCES})
    endforeach(deps ${${mat}_mfront_behaviours_dependencies_${interface}_SOURCES})
    list(LENGTH ${lib}_SOURCES nb_sources)
    if(nb_sources GREATER 0)
      message(STATUS "Adding library : ${lib} (${${lib}_SOURCES})")
      add_library(${lib} SHARED ${${lib}_SOURCES})
      target_include_directories(${lib}
	PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/${interface}/include"
	PRIVATE "${TFEL_INCLUDE_PATH}")
      if(${interface} STREQUAL "castem")
	if(CASTEMHOME)
	  if(enable-castem-pleiades)
	    target_include_directories(${lib}
	      PRIVATE "${CASTEMHOME}/include")
	  else(enable-castem-pleiades)
	    target_include_directories(${lib}
	      PRIVATE "${CASTEMHOME}/include/c")
	  endif(enable-castem-pleiades)
	endif(CASTEMHOME)
      endif(${interface} STREQUAL "castem")
      if(WIN32)
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	  set_target_properties(${lib}
	    PROPERTIES LINK_FLAGS "-Wl,--kill-at -Wl,--no-undefined")
	endif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	install(TARGETS ${lib} DESTINATION bin)
      else(WIN32)
	install(TARGETS ${lib} DESTINATION lib${LIB_SUFFIX})
      endif(WIN32)
      if(${interface} STREQUAL "castem")
	if(CASTEMHOME)
	  target_include_directories(${lib}
	    PRIVATE "${CASTEMHOME}/include")
	endif(CASTEMHOME)
	if(CASTEM_CPPFLAGS)
	  set_target_properties(${lib} PROPERTIES
	    COMPILE_FLAGS "${CASTEM_CPPFLAGS}")
	endif(CASTEM_CPPFLAGS)
	target_link_libraries(${lib} ${TFEL_MFRONT_LIBRARIES}
	  ${CastemInterface})
      elseif(${interface} STREQUAL "aster")
	if(ASTER_CPPFLAGS)
	  set_target_properties(${lib} PROPERTIES
	    COMPILE_FLAGS "${ASTER_CPPFLAGS}")
	endif(ASTER_CPPFLAGS)
	target_link_libraries(${lib} ${TFEL_MFRONT_LIBRARIES}
	  ${AsterInterface})
      elseif(${interface} STREQUAL "epx")
	if(EUROPLEXUS_CPPFLAGS)
	  set_target_properties(${lib} PROPERTIES
	    COMPILE_FLAGS "${EUROPLEXUS_CPPFLAGS}")
	endif(EUROPLEXUS_CPPFLAGS)
	target_link_libraries(${lib} ${TFEL_MFRONT_LIBRARIES}
	  ${EuroplexusInterface})
      elseif(${interface} STREQUAL "abaqus")
	if(ABAQUS_CPPFLAGS)
	  set_target_properties(${lib} PROPERTIES
	    COMPILE_FLAGS "${ABAQUS_CPPFLAGS}")
	endif(ABAQUS_CPPFLAGS)
	target_link_libraries(${lib} ${TFEL_MFRONT_LIBRARIES}
	  ${AbaqusInterface})
      elseif(${interface} STREQUAL "abaqusexplicit")
	if(ABAQUS_EXPLICIT_CPPFLAGS)
	  set_target_properties(${lib} PROPERTIES
	    COMPILE_FLAGS "${ABAQUS_EXPLICIT_CPPFLAGS}")
	endif(ABAQUS_EXPLICIT_CPPFLAGS)
	target_link_libraries(${lib} ${TFEL_MFRONT_LIBRARIES}
	  ${AbaqusInterface})
      elseif(${interface} STREQUAL "ansys")
	if(ANSYS_CPPFLAGS)
	  set_target_properties(${lib} PROPERTIES
	    COMPILE_FLAGS "${ANSYS_CPPFLAGS}")
	endif(ANSYS_CPPFLAGS)
	target_link_libraries(${lib} ${TFEL_MFRONT_LIBRARIES}
	  ${AnsysInterface})
      elseif(${interface} STREQUAL "calculix")
	if(CALCULIX_CPPFLAGS)
	  set_target_properties(${lib} PROPERTIES
	    COMPILE_FLAGS "${CALCULIX_CPPFLAGS}")
	endif(CALCULIX_CPPFLAGS)
	target_link_libraries(${lib} ${TFEL_MFRONT_LIBRARIES}
	  ${CalculiXInterface})
      elseif(${interface} STREQUAL "cyrano")
	if(CYRANO_CPPFLAGS)
	  set_target_properties(${lib} PROPERTIES
	    COMPILE_FLAGS "${CYRANO_CPPFLAGS}")
	endif(CYRANO_CPPFLAGS)
	target_link_libraries(${lib} ${TFEL_MFRONT_LIBRARIES}
	  ${CyranoInterface})
      elseif(${interface} STREQUAL "zmat")
	set_target_properties(${lib} PROPERTIES
	  COMPILE_FLAGS "${ZSET_CPPFLAGS}")
	target_include_directories(${lib}
	  SYSTEM PRIVATE "${ZSET_INCLUDE_DIR}")
	target_link_libraries(${lib} ${TFEL_MFRONT_LIBRARIES})
      else(${interface} STREQUAL "castem")
	message(FATAL_ERROR "mfront_behaviours_library : "
	  "unsupported interface ${interface}")
      endif(${interface} STREQUAL "castem")
    else(nb_sources GREATER 0)
      message(STATUS "No sources selected for "
	"library ${lib} for interface ${interface}")
    endif(nb_sources GREATER 0)
  endforeach(interface)
endfunction(mfront_behaviours_library)

macro(add_mtest interface lib)
  set ( _CMD TESTS )
  set ( _TESTS )
  set ( _MATERIAL_PROPERTIES_LIBRARIES )
  foreach ( _ARG ${ARGN})
    if ( ${_ARG} MATCHES TESTS )
      set ( _CMD TESTS )
    elseif ( ${_ARG} MATCHES MATERIAL_PROPERTIES_LIBRARIES )
      set ( _CMD MATERIAL_PROPERTIES_LIBRARIES )
    else ()
      if ( ${_CMD} MATCHES TESTS )
        list ( APPEND _TESTS "${_ARG}" )
      elseif ( ${_CMD} MATCHES MATERIAL_PROPERTIES_LIBRARIES )
        list ( APPEND _MATERIAL_PROPERTIES_LIBRARIES "${_ARG}" )
      endif ()
    endif ()
  endforeach ()
  list(LENGTH _TESTS _TESTS_LENGTH )
  if(${_TESTS_LENGTH} LESS 1)
    message(FATAL_ERROR "add_mtest : no test specified")
  endif(${_TESTS_LENGTH} LESS 1)
  foreach(test ${_TESTS})
    if(CMAKE_CONFIGURATION_TYPES)
      foreach(conf ${CMAKE_CONFIGURATION_TYPES})
	set(file "${test}-${conf}.mtest")
	get_property(${lib}BuildPath TARGET ${lib} PROPERTY LOCATION_${conf})
	foreach(mplib ${_MATERIAL_PROPERTIES_LIBRARIES})
	  get_property(${mplib}BuildPath TARGET ${mplib} PROPERTY LOCATION_${conf})
	endforeach(mplib ${_MATERIAL_PROPERTIES_LIBRARIES})
	configure_file(${test}.mtest.in ${test}-${conf}.mtest @ONLY)
	foreach(rm ${IEEE754_ROUNDING_MODES})
	  add_test(NAME ${test}_${conf}_${rm}_mtest
	    COMMAND mtest --rounding-direction-mode=${rm} --verbose=level0 --xml-output=true --result-file-output=false ${test}-${conf}.mtest
	    CONFIGURATIONS ${conf})
          set_property(TEST ${test}_${conf}_${rm}_mtest
            PROPERTY DEPENDS ${lib} ${_MATERIAL_PROPERTIES_LIBRARIES})
	endforeach(rm ${IEEE754_ROUNDING_MODES})
      endforeach(conf ${CMAKE_CONFIGURATION_TYPES})      
    else(CMAKE_CONFIGURATION_TYPES)
      get_property(${lib}BuildPath TARGET ${lib} PROPERTY LOCATION)
      foreach(mplib ${_MATERIAL_PROPERTIES_LIBRARIES})
	get_property(${mplib}BuildPath TARGET ${mplib} PROPERTY LOCATION)
      endforeach(mplib ${_MATERIAL_PROPERTIES_LIBRARIES})
      configure_file(${test}.mtest.in	${test}.mtest @ONLY)
      foreach(rm ${IEEE754_ROUNDING_MODES})
	add_test(NAME ${test}_${rm}_mtest
	  COMMAND mtest --rounding-direction-mode=${rm} --verbose=level0 --xml-output=true --result-file-output=false ${test}.mtest)
	set_property(TEST ${test}_${rm}_mtest
	  PROPERTY DEPENDS ${lib} ${_MATERIAL_PROPERTIES_LIBRARIES})
      endforeach(rm ${IEEE754_ROUNDING_MODES})
    endif(CMAKE_CONFIGURATION_TYPES)
  endforeach(test ${_TESTS})
endmacro(add_mtest interface lib file)
    
macro(castemmtest mat)
  if(MFM_CASTEM_BEHAVIOUR_INTERFACE)
    set(lib "${mat}Behaviours")
    add_mtest("castem" ${lib} ${ARGN})
  endif(MFM_CASTEM_BEHAVIOUR_INTERFACE)
endmacro(castemmtest)

macro(astermtest mat)
  if(MFM_ASTER_INTERFACE)
    set(lib "${mat}Behaviours-aster")
    add_mtest("aster" ${lib} ${ARGN})
  endif(MFM_ASTER_INTERFACE)
endmacro(astermtest)

macro(europlexusmtest mat)
  if(MFM_EUROPLEXUS_INTERFACE)
    set(lib "${mat}Behaviours-epx")
    add_mtest("europlexus" ${lib} ${ARGN})
  endif(MFM_EUROPLEXUS_INTERFACE)
endmacro(europlexusmtest)

macro(abaqusmtest mat)
  if(MFM_ABAQUS_INTERFACE)
    set(lib "${mat}Behaviours-abaqus")
    add_mtest("abaqus" ${lib} ${ARGN})
  endif(MFM_ABAQUS_INTERFACE)
endmacro(abaqusmtest)

macro(abaqusexplicitmtest mat)
  if(MFM_ABAQUS_EXPLICIT_INTERFACE)
    set(lib "${mat}Behaviours-abaqusexplicit")
    add_mtest("abaqusexplicit" ${lib} ${ARGN})
  endif(MFM_ABAQUS_EXPLICIT_INTERFACE)
endmacro(abaqusexplicitmtest)

macro(ansysmtest mat)
  if(MFM_ANSYS_INTERFACE)
    set(lib "${mat}Behaviours-ansys")
    add_mtest("ansys" ${lib} ${ARGN})
  endif(MFM_ANSYS_INTERFACE)
endmacro(ansysmtest)

macro(calculixmtest mat)
  if(MFM_CALCULIX_INTERFACE)
    set(lib "${mat}Behaviours-calculix")
    add_mtest("calculix" ${lib} ${ARGN})
  endif(MFM_CALCULIX_INTERFACE)
endmacro(calculixmtest)

macro(add_python_test interface lib)
  if(TFEL_PYTHON_BINDINGS)
    set ( _CMD TESTS )
    set ( _TESTS )
    set ( _MATERIAL_PROPERTIES_LIBRARIES )
    foreach ( _ARG ${ARGN})
      if ( ${_ARG} MATCHES TESTS )
	set ( _CMD TESTS )
      elseif ( ${_ARG} MATCHES MATERIAL_PROPERTIES_LIBRARIES )
	set ( _CMD MATERIAL_PROPERTIES_LIBRARIES )
      else ()
	if ( ${_CMD} MATCHES TESTS )
          list ( APPEND _TESTS "${_ARG}" )
	elseif ( ${_CMD} MATCHES MATERIAL_PROPERTIES_LIBRARIES )
          list ( APPEND _MATERIAL_PROPERTIES_LIBRARIES "${_ARG}" )
	endif ()
      endif ()
    endforeach ()
    list(LENGTH _TESTS _TESTS_LENGTH )
    if(${_TESTS_LENGTH} LESS 1)
      message(FATAL_ERROR "add_python_test : no test specified")
    endif(${_TESTS_LENGTH} LESS 1)
    foreach(test ${_TESTS})
      get_property(${lib}BuildPath TARGET ${lib} PROPERTY LOCATION_${conf})
      foreach(mplib ${_MATERIAL_PROPERTIES_LIBRARIES})
	get_property(${mplib}BuildPath TARGET ${mplib} PROPERTY LOCATION_${conf})
      endforeach(mplib ${_MATERIAL_PROPERTIES_LIBRARIES})
      configure_file(${test}.py.in ${test}.py @ONLY)
      add_test(NAME ${test}_py
	COMMAND ${PYTHON_EXECUTABLE} ${test}.py)
      set_tests_properties(${test}_py
	PROPERTIES DEPENDS ${lib})
    endforeach(test ${_TESTS})
  endif(TFEL_PYTHON_BINDINGS)
endmacro(add_python_test interface lib)

macro(castempythontest mat)
  if(MFM_CASTEM_BEHAVIOUR_INTERFACE)
    set(lib "${mat}Behaviours")
    add_python_test("castem" ${lib} ${ARGN})
  endif(MFM_CASTEM_BEHAVIOUR_INTERFACE)
endmacro(castempythontest mat)

macro(asterpythontest mat)
  if(MFM_ASTER_INTERFACE)
    set(lib "${mat}Behaviours-aster")
    add_python_test("aster" ${lib} ${ARGN})
  endif(MFM_ASTER_INTERFACE)
endmacro(asterpythontest mat)
