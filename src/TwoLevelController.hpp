#pragma once
#include <iostream>
#include <vector>

namespace sfh
{

/**
 * @brief hysteresis between to points 
 * 
 */

class TwoLevelController
{
  private:
    double _setvalue_w;
    double _actualvalue_x;
    double _e;
    double _w_upperLimit;
    double _w_lowerLimit;
    double _hysteresis;
    int _y_output;
    int _state;

  public:
    TwoLevelController(unsigned int hysteresisPercent);
    ~TwoLevelController();

    void SetsetPoint_W(double SetValue, double ActualValue);

    int GetControllerOutput_Y();
};

} // namespace sfh