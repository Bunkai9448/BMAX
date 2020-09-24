cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()


project(BMAX)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "BMAX")
set(VITA_TITLEID  "BUNKAI001")
set(VITA_VERSION  "02.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
  ../common
)

add_executable(${PROJECT_NAME}
  ../common/debugScreen.c
  src/main.c
  src/common.c
  src/screen.c
  src/btnDash.c
)

target_link_libraries(${PROJECT_NAME}
  SceAppUtil_stub
  SceCommonDialog_stub
  SceSysmodule_stub
  SDL2
  vita2d
  SceDisplay_stub
  SceCtrl_stub
  SceAudio_stub
  SceSysmodule_stub
  SceGxm_stub
  SceCommonDialog_stub
  SceAppMgr_stub
  SceTouch_stub
  SceHid_stub
  m
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/pic0.png sce_sys/pic0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/logo0.png sce_sys/livearea/contents/logo0.png
  FILE sce_sys/livearea/contents/logo1.png sce_sys/livearea/contents/logo1.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE bmax_files/help_ENG.txt bmax_files/help_ENG.txt
  FILE bmax_files/help_SPA.txt bmax_files/help_SPA.txt
  FILE bmax_files/help_JPN.txt bmax_files/help_JPN.txt
  FILE bmax_files/goodbye.png bmax_files/goodbye.png
  FILE btn_dash/ps_vita_buttons.bmp btn_dash/ps_vita_buttons.bmp  
)
