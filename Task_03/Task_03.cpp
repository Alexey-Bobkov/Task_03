#include"Gcode.h"
    
using namespace std;

int main()
{
    vector<string> test1 = { "10 20 0",
    "X10;Y20;Z30;","X40;Y-20;Z20;","X-10;Y-20;Z-10;" };
    vector<string > test2 = { "10 20 0",
    "X10;Y20;Z30;","X40;Y-20;<Z20;","X-10;Y-20;Z-10;"};
    vector<string > test3 = { "10 20 0",
    "X10;Y20;Z30;","X4-0;Y-2w0;<Z2/0;","X-10;Y-20;Z-10;" };
    vector<string > test4 = { "100 200 100",
"100 2-20 Z320;","X4-0;Y-2w0;<Z2/0;","X-10;Y-20;Z-10;" };

    Gcode::parse_string(test1);
    Gcode::reset();
    Gcode::parse_string(test2);
    Gcode::reset();
    Gcode::parse_string(test3);
    Gcode::parse_string(test4);

    return 0;
}
