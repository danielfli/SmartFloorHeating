#pragma once
#include <vector>

namespace sfh
{

class Output
{
  private:
    bool InitSuccess;
    std::vector<unsigned int> _output;

  public:
    Output(const unsigned int num);
    ~Output();

    operator bool()
    {
        return InitSuccess;
    }

    void SwitchAllOn();

    void SwitchAllOff();

    void TurnOn(const int unsigned id);
    void TurnOff(const int unsigned id);

    std::vector<unsigned int> GetSwitches() const;
};

} // namespace sfh