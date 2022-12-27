#include "TwoLevelController.hpp"

namespace sfh
{

TwoLevelController::TwoLevelController(unsigned int hysteresisPercent)
    : _setvalue_w(0), _actualvalue_x(10.0), _e(0), _w_upperLimit(0), _w_lowerLimit(0),
      _hysteresis(static_cast<double>(hysteresisPercent)), _y_output(-1), _state(10)
{
    if (hysteresisPercent > 100)
        _hysteresis = 100;
}

TwoLevelController::~TwoLevelController()
{
}

int TwoLevelController::GetControllerOutput_Y()
{
    return _y_output;
}

void TwoLevelController::SetsetPoint_W(double SetValue, double ActualValue)
{
    _actualvalue_x = ActualValue;

    if (SetValue < 0)
    {
        std::cerr << "Error - negativ SetValue not permitted..\n";
        // take old value
    }
    else
    {
        _setvalue_w = SetValue;
    }

    // calculation
    double delta = (_hysteresis / 100.0);

    _w_lowerLimit = _setvalue_w - (_setvalue_w * delta);
    _w_upperLimit = _setvalue_w + (_setvalue_w * delta);

    // differenz set output
    _e = _setvalue_w - _actualvalue_x;

    switch (_state)
    {
    case 10:
        // to point A - upper limit
        _y_output = 1;

        if (_actualvalue_x >= _w_upperLimit)
        {
            _y_output = -1; // off
            _state = 20;
        }

        break;

    case 20:
        //to point B - lower limit
        _y_output = -1; // off
        if (_actualvalue_x <= _w_lowerLimit)
        {
            _y_output = 1; // on
            _state = 10;
        }
        break;

    default:
        break;
    }
    std::cout << "Controller value:\n";
    std::cout << "Set: " << _setvalue_w << " upLimit: " << _w_upperLimit << " lowLimit: " << _w_lowerLimit
              << "  Actual: " << _actualvalue_x << "\n";
    std::cout << "Delta: " << delta << "\n";
    std::cout << "Controller e: " << _e << "\n";
    std::cout << "Output set: " << _y_output << "\n";
}
} // namespace sfh