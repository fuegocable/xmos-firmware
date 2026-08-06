cmake_minimum_required(VERSION 3.21)
include($ENV{XMOS_CMAKE_PATH}/xcommon.cmake)
project(app_dxio_mc_3w)
set(APP_HW_TARGET dxio_mc_3w.xn)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

set(APP_COMPILER_FLAGS ${EXTRA_BUILD_FLAGS} -O0
                                            -report
                                            -lquadflash
                                            -g
                                            -Wall
                                            -fxscope)
                                            #-DNUM_USB_CHAN_OUT=2)

set(APP_INCLUDES ${FC_COMMON_INCLUDES}
                 src
                 src/board
                 src/core
                 src/extensions)

FC_XMOS_REGISTER_APP()
