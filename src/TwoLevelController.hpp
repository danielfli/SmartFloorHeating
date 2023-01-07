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
    double _delta;

  public:
    TwoLevelController(const u_int hysteresisPercent);
    ~TwoLevelController();

    void SetSetpoint_W(double SetValue, double ActualValue);

    /**
     * @brief 
     * 
     * @return int (1): controller on; (-1) controller off  
     */
    int GetControllerOutput_Y();
};

} // namespace sfh