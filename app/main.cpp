// #include <smartfloorheading/mini.hpp>

#include "../include/smartfloorheading/mini.hpp"

#include <fstream>
#include <filesystem>
#include <iostream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main() {
  std::cout << "Hello cross build!\n";

  auto ifs = std::ifstream{ "test.json" };
    if (!ifs.is_open())
    {
      std::cout << "error\n";
        return 1;
    }
    
  const auto parsed_data = json::parse(ifs);
  const auto name = parsed_data["name"];

  std::cout << "json: "  << name.dump();
  return 0;
}
