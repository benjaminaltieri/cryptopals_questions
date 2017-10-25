#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class MyClass {
   public:
    MyClass();
    ~MyClass();

    std::string str_repr() const;
    static std::vector<std::string> mesh_path(std::unordered_map<std::string, std::vector<std::string> >& mesh, std::pair<std::string, std::string> connection);

   private:
    std::string str_repr_ = "My repr!";
};
