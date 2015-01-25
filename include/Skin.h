#pragma once

#include <string>

class Skin
{
 public:
 Skin(): name("NOT_SET"), description("NOT_SET"), cost(0) {}

  void setName(const std::string& name) { this->name = name; }
  std::string getName() { return this->name; }

  void setDescription(const std::string& description) { this->description = description; }
  std::string getDescription() { return this->description; } 

  void setCost(int cost) { this->cost = cost; }
  int getCost() { return this->cost; }

 protected:
  std::string name;
  std::string description;
  int cost;
};
