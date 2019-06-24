/** @file */
///\header for serial communication with roomba

#ifndef OPENINTERFACECONFIG_H
#define OPENINTERFACECONFIG_H

#include <cstdint>
#include <vector>
///Serial Interface functions and mode definitions for roomba control
enum class Baud : unsigned int { ROOMBA_SLOW = 19200, ROOMBA_DEFAULT = 115200 };

/// Get started
const uint8_t START{128};
const uint8_t BAUD_1{129};

/// Mode commands
const uint8_t MODE_SAFE{131};
const uint8_t MODE_FULL{132};
const uint8_t MODE_CLEAN{135};
const uint8_t MODE_DOCK{143};
const uint8_t MODE_SONG{140};
const uint8_t MODE_PLAY{141};

///Drive  Commands
const uint8_t DRIVE_DIRECT_4{145};
const uint8_t DRIVE{137};

///function definitions
std::vector<uint8_t> driveDirect(int16_t rightVelocity, int16_t leftVelocity); ///Control drive direction and velocity
std::vector<uint8_t> drive(int16_t Velocity, int16_t radius); ///Control the turning direction and velocity of the roomba
std::vector<uint8_t> startSafe();///Puts Roomba into safe mode 
std::vector<uint8_t> clean(); ///sends clean command
std::vector<uint8_t> dock(); ///sends dock command 
std::vector<uint8_t> addSong(int sel); ///adds a song to the roomba buffer
std::vector<uint8_t> playSong(int nr); ///executes the added song



#endif
