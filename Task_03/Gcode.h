#pragma once
#include <string>
#include <iostream>
#include <vector>

class Gcode
{
private:
    static int m_x, m_y, m_z;

    static void parse_string(const std::string& st);
public:
    Gcode() {};

    static void parse_string(const std::vector<std::string> &vstring);
    static void print();
    static void reset();
};
