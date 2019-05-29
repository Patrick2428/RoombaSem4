#include "OpenInterfaceConfig.h"


/// Velocities in mm/sec
std::vector<uint8_t> driveDirect(int16_t rightVelocity, int16_t leftVelocity)
{
   return {DRIVE_DIRECT_4, static_cast<uint8_t>(rightVelocity >> 8),
           static_cast<uint8_t>(rightVelocity & 0x00ff),
           static_cast<uint8_t>(leftVelocity >> 8),
           static_cast<uint8_t>(leftVelocity & 0x00ff)};
}

std::vector<uint8_t> drive(int16_t Velocity, int16_t radius)
{
   return {DRIVE, static_cast<uint8_t>(Velocity >> 8),
           static_cast<uint8_t>(Velocity & 0x00ff),
           static_cast<uint8_t>(radius >> 8),
           static_cast<uint8_t>(radius & 0x00ff)};
}

// Command data
std::vector<uint8_t> startSafe()
{
   return {START, MODE_SAFE};
}

std::vector<uint8_t> clean()
{
  return {MODE_CLEAN};
}

std::vector<uint8_t>dock()
{
  return {MODE_DOCK};
}

std::vector<uint8_t>addSong(int sel)
{
  if (sel == 0)
    {
      //Mode, song nr, nr of notes, note, duration 1/64...
      return {MODE_SONG, 0, 15, 73, 10, 71, 16, 73, 20, 66, 45, 0, 20, 74, 10, 73, 16, 74, 16, 73, 16, 71, 45, 0, 20, 74, 16, 73, 16, 74, 20, 66, 45 };
    }
  else if(sel == 1)
    {
      return{MODE_SONG, 1, 7, 71, 16, 69, 16, 71, 16, 69, 16, 68, 10, 71, 16, 69, 45};
    }
  else if(sel = 2)
    {
      return {MODE_SONG, 2, 4, 50, 32, 55, 16, 57, 10, 55, 10};
    }
}

std::vector<uint8_t>playSong(int nr)
{
  return {MODE_PLAY, nr};
}
