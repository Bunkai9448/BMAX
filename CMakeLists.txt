cmake_minimum_required(VERSION 3.16)

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
set(VITA_VERSION  "02.01")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
  ../samples/common 
)

add_executable(${PROJECT_NAME}
  ../samples/common/debugScreen.c
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
  FILE bmax_files/goodbye.bmp bmax_files/goodbye.bmp
  FILE btn_dash/btn_dash_rulesENG.bmp btn_dash/btn_dash_rulesENG.bmp
  FILE btn_dash/btn_dash_rulesSPA.bmp btn_dash/btn_dash_rulesSPA.bmp
  FILE btn_dash/btn_dash_rulesJPN.bmp btn_dash/btn_dash_rulesJPN.bmp
  FILE btn_dash/b_L.bmp btn_dash/b_L.bmp
  FILE btn_dash/b_L2.bmp btn_dash/b_L2.bmp
  FILE btn_dash/b_R.bmp btn_dash/b_R.bmp
  FILE btn_dash/b_R2.bmp btn_dash/b_R2.bmp
  FILE btn_dash/b_triangle.bmp btn_dash/b_triangle.bmp
  FILE btn_dash/b_triangle2.bmp btn_dash/b_triangle2.bmp
  FILE btn_dash/b_square.bmp btn_dash/b_square.bmp
  FILE btn_dash/b_square2.bmp btn_dash/b_square2.bmp
  FILE btn_dash/b_X.bmp btn_dash/b_X.bmp
  FILE btn_dash/b_X2.bmp btn_dash/b_X2.bmp
  FILE btn_dash/b_circle.bmp btn_dash/b_circle.bmp
  FILE btn_dash/b_circle2.bmp btn_dash/b_circle2.bmp
  FILE btn_dash/b_up.bmp btn_dash/b_up.bmp
  FILE btn_dash/b_up2.bmp btn_dash/b_up2.bmp
  FILE btn_dash/b_left.bmp btn_dash/b_left.bmp
  FILE btn_dash/b_left2.bmp btn_dash/b_left2.bmp
  FILE btn_dash/b_down.bmp btn_dash/b_down.bmp
  FILE btn_dash/b_down2.bmp btn_dash/b_down2.bmp
  FILE btn_dash/b_right.bmp btn_dash/b_right.bmp
  FILE btn_dash/b_right2.bmp btn_dash/b_right2.bmp
)
