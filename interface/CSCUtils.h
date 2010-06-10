#ifndef FIREWORKS_MUONS_CSCUTILS_H
#define FIREWORKS_MUONS_CSCUTILS_H

namespace fireworks
{
  void fillCSCChamberParameters(int station, int ring, double& length, double& thickness);

  void testFill(const int station, const int ring, double* params);

}

#endif
