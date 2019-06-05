#include "OpenInterfaceConfig.h"

///Serial Communication function implementations\

///Sends driveDirect command to roomba (Velocities in mm/sec) for driving straight
std::vector<uint8_t> driveDirect(int16_t rightVelocity, int16_t leftVelocity)
{
   return {DRIVE_DIRECT_4, static_cast<uint8_t>(rightVelocity >> 8),
           static_cast<uint8_t>(rightVelocity & 0x00ff),
           static_cast<uint8_t>(leftVelocity >> 8),
           static_cast<uint8_t>(leftVelocity & 0x00ff)};
}

///Sends driveCommand to roomba for turning left and right around the z coordinate
std::vector<uint8_t> drive(int16_t Velocity, int16_t radius)
{
   return {DRIVE, static_cast<uint8_t>(Velocity >> 8),
           static_cast<uint8_t>(Velocity & 0x00ff),
           static_cast<uint8_t>(radius >> 8),
           static_cast<uint8_t>(radius & 0x00ff)};
}

///Puts the Roomba into safe-Mode from which other modes can be executed
std::vector<uint8_t> startSafe()
{
   return {START, MODE_SAFE};
}
///Command to activate clean mode
std::vector<uint8_t> clean()
{
  return {MODE_CLEAN};
}

///Command to activate dock mode
std::vector<uint8_t>dock()
{
  return {MODE_DOCK};
}
///Sends a Song to the Roomba and stores it 
std::vector<uint8_t>addSong(int sel)
{
  //final Countdown
  /*if (sel == 0)
    {
      ///Mode, song nr, nr of notes, note, duration 1/64...
      return {MODE_SONG, 0, 15, 73, 10, 71, 10, 73, 20, 66, 50, 0, 20, 74, 10, 73, 10, 74, 17, 73, 17, 71, 50, 0, 20, 74, 10, 73, 10, 74, 20, 66, 50};
    }
  else if(sel == 1)
    {
      return{MODE_SONG, 1, 12, 71, 10, 69, 10, 71, 17, 69, 17, 68, 17, 71, 17, 69, 45, 68, 10, 69, 10, 71, 20, 69, 10, 71, 10};
    }
  else if(sel == 2)
    {
      return {MODE_SONG, 2, 12, 73, 17, 71, 17, 69, 17, 68, 17, 66, 20, 74, 20, 73, 50, 74, 10, 73, 10, 71, 10, 73, 14, 73, 64};
      }*/
  //GOT Theme song
  if (sel == 0)
    {
      ///Mode, song nr, nr of notes, note, duration 1/64...
      return {MODE_SONG, 0, 13, 67, 20, 60, 20, 63, 15, 65, 15, 67, 20, 60, 20, 63, 15, 65, 15, 67, 20, 60, 20, 63, 15, 65, 15, 67, 20};
    }
  
  else if(sel == 1)
    {
      return{MODE_SONG, 1, 12, 60, 20, 63, 15, 65, 15, 67, 20, 60, 20, 64, 15, 65, 15, 67, 20, 60, 20, 64, 15, 65, 15, 67, 20};
    }
  
  else if(sel == 2)
    {
      return {MODE_SONG, 2, 12, 60, 20, 64, 15, 65, 15, 55, 30, 48, 30, 51, 15, 53, 15, 55, 15, 48, 30, 51, 10, 50, 10, 48, 30};
    }
}
///executes/playes stored song on the Roomba
std::vector<uint8_t>playSong(int nr)
{
  return {MODE_PLAY, nr};
}
