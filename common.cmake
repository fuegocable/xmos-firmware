#
# Functions
#
function(get_audio_devices OUT_VAR)
    if(DEFINED ${OUT_VAR})
        return()
    endif()

    file(GLOB AUDIO_DEVICE_ENTRIES
        RELATIVE "${FC_AUDIO_DEVICES_DIR}"
        "${FC_AUDIO_DEVICES_DIR}/*"
    )

    set(AUDIO_DEVICES)
    foreach(ENTRY ${AUDIO_DEVICE_ENTRIES})
        if(IS_DIRECTORY "${FC_AUDIO_DEVICES_DIR}/${ENTRY}")
            list(APPEND AUDIO_DEVICES "${ENTRY}")
        endif()
    endforeach()

    set(${OUT_VAR} ${AUDIO_DEVICES} PARENT_SCOPE)
endfunction()

function(create_audio_devices_build_configurations)
    # Build configuration for each audio device
    get_audio_devices(AUDIO_DEVICES)
    foreach(AUDIO_DEVICE ${AUDIO_DEVICES})
        set(APP_COMPILER_FLAGS_${AUDIO_DEVICE} ${APP_COMPILER_FLAGS} -DFC_AUDIO_DEVICE="${AUDIO_DEVICE}" PARENT_SCOPE)
    endforeach()
endfunction()

function(include_additional_sources)
    # Include directories for each audio device
    get_audio_devices(AUDIO_DEVICES)
    foreach(AUDIO_DEVICE ${AUDIO_DEVICES})
        set(BUILD_CONFIG_TARGET "${PROJECT_NAME}_${AUDIO_DEVICE}")

        # We include all common sources but only the build config specific audio_device sources
        glob_srcs("${AUDIO_DEVICE}" "${FC_BASE_DIR}/common/audio_devices" "${AUDIO_DEVICE}")
        set(ALL_SRCS_PATH ${FC_COMMON_SRCS} ${${AUDIO_DEVICE}_XC_SRCS} ${${AUDIO_DEVICE}_ASM_SRCS} ${${AUDIO_DEVICE}_C_SRCS} ${${AUDIO_DEVICE}_CXX_SRCS})
        target_sources(${BUILD_CONFIG_TARGET} PRIVATE ${ALL_SRCS_PATH})
        target_include_directories(${BUILD_CONFIG_TARGET} PRIVATE "${FC_BASE_DIR}/common/audio_devices/${AUDIO_DEVICE}")
    endforeach()
endfunction()

function(FC_XMOS_REGISTER_APP)
    create_audio_devices_build_configurations()
    XMOS_REGISTER_APP()
    include_additional_sources()
endfunction()
#
# END: Functions
#

# Defines
set(FC_BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(FC_AUDIO_DEVICES_DIR "${FC_BASE_DIR}/common/audio_devices")

# Lib dependencies
set(XMOS_SANDBOX_DIR ${CMAKE_CURRENT_LIST_DIR}/sandbox)
set(APP_DEPENDENT_MODULES "lib_xua(develop)"
                          "lib_i2c(6.4.1)"
                          "lib_spi(4.0.0)"
                          "lib_i2s(6.0.1)"
                          "lib_xassert(4.3.2)"
                          "lib_logging(3.4.0)")

# Common includes
set(FC_COMMON_INCLUDES "${CMAKE_CURRENT_LIST_DIR}/common"
                       "${CMAKE_CURRENT_LIST_DIR}/common/drivers")

# Common sources
# We exclude all audio_devices sources because we will add them in each build
glob_srcs("common" "${FC_BASE_DIR}" "common")
set(FC_COMMON_SRCS ${common_XC_SRCS} ${common_ASM_SRCS} ${common_C_SRCS} ${common_CXX_SRCS})
list(FILTER FC_COMMON_SRCS EXCLUDE REGEX "${FC_BASE_DIR}/common/audio_devices")

