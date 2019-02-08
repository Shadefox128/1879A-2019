#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

//built in
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

//using namespace pros;

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

//---CUSTOM---
#include "api.h"
#include "display/lvgl.h"

#include <string>

#define AUTON_MAX 3
#endif  // _PROS_MAIN_H_
