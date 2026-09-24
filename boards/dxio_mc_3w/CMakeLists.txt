cmake_minimum_required(VERSION 3.21)
include($ENV{XMOS_CMAKE_PATH}/xcommon.cmake)
project(dxio_mc_3w)
set(APP_HW_TARGET src/dxio_mc_3w.xn)
include(${CMAKE_CURRENT_LIST_DIR}/../../common.cmake)

set(APP_COMPILER_FLAGS ${EXTRA_BUILD_FLAGS} -O0
                                            -report
                                            -lquadflash
                                            -g
                                            -Wall
                                            -fxscope)
                                            #-DNUM_USB_CHAN_OUT=2)

set(APP_INCLUDES ${FC_COMMON_INCLUDES}
                 ${CMAKE_CURRENT_LIST_DIR}
                 ${CMAKE_CURRENT_LIST_DIR}/src)

FC_XMOS_REGISTER_APP()
