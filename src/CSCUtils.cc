#include "Fireworks/Muons/interface/CSCUtils.h"
#include <iostream>
#include <cassert>

namespace fireworks
{
  void fillCSCChamberParameters(int station, int ring, 
                                double& length, double& thickness)
  {
    thickness = 18.0;

    if ( ring == 3 )
    {
      assert(station == 1); // Only station 1 has a 3rd ring
      length = 179.3;
      return;
    }

    else if ( ring == 4 )
    {
      assert(station == 1); // Only station 1 has a 4th ring
      length = 162.0;
      thickness = 14.7; // ME1/4 (a.k.a. ME1a)
      return;
    }
    
    else if ( ring == 1 )
    {
      if ( station == 1 )
      {
        length = 162.0;
        thickness = 14.7; // ME1/1 (a.k.a. ME1b)
        return;
      }
      else if ( station == 2 )
      {
        length = 204.6;
        return;
      }
      else if ( station == 3 )
      {
        length = 184.6; 
        return;
      }
      else if ( station == 4 )
      {
        length = 166.7;
        return;
      }
      else
        return;
    }
  
    else if ( ring == 2 )
    {
      if ( station == 2 || station == 3 || station == 4 )
      {
        length = 338.0;
        return;
      }
      else if ( station == 1 )
      {
        length = 189.4;
        return;
      }
      else 
        return;
    }
    
    else
      return;
  }


  void testFill(const int station, const int ring, double* params)
  {
    // params = { length, thickness, bottomWidth, topWidth } in cm

    if ( station == 1 )
    {
      if ( ring == 1 )
      {
        params[0] = 162.0;
        params[1] = 15.0;
        params[2] = 20.13;
        params[3] = 48.71;
          
        return;
      }
      
      if ( ring == 2 )
      { 
        params[0] = 189.4;
        params[1] = 15.875;
        params[2] = 51.0;
        params[3] = 83.7;
        
        return;
      }
      
      if ( ring == 3 )
      {
        params[0] = 179.3;
        params[1] = 15.875;
        params[2] = 63.4;
        params[3] = 92.1;
      }
      
      if ( ring == 4 )
      {
        params[0] = 162.0;
        params[1] = 15.0;
        params[2] = 20.13;
        params[3] = 48.71;
      }
      
      else 
        return;
    }
    
    if ( station == 2 )
    {
      if ( ring == 1 )
      {
        params[0] = 204.6;
        params[1] = 15.875;
        params[2] = 54.0;
        params[3] = 125.71;
      }
      
      if ( ring == 2 )
      {
        params[0] = 338.0;
        params[1] = 15.875;
        params[2] = 66.46;
        params[3] = 127.15;
      }
      
      else 
        return;
    }
    
    if ( station == 3 )
    {
      if ( ring == 1 )
      {
        params[0] = 184.6;
        params[1] = 15.875;
        params[2] = 61.4;
        params[3] = 125.71;
      }
      
      if ( ring == 2 )
      {
        params[0] = 338.0;
        params[1] = 15.875;
        params[2] = 66.46;
        params[3] = 127.15;
      }
      
      else 
        return;
    }
    
    if ( station == 4 )
    {
      if ( ring == 1 )
      {
        params[0] = 166.7;
        params[1] = 15.875;
        params[2] = 69.01;
        params[3] = 125.65;
      }
      
      if ( ring == 2 )
      {
        params[0] = 338.0;
        params[1] = 15.875;
        params[2] = 66.46;
        params[3] = 127.15;
      }
      
      else 
        return;
    }
    
    else
      return;
  }
}       

