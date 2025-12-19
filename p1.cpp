#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string center(const string& input, int width) {
    // Calculate the number of spaces for the left padding
    int padding_left = (width - input.length()) / 2;
    
    // If the input is longer than the width, return the original string
    if (padding_left < 0) {
        return input;
    }
    
    // Create the centered string
    return string(padding_left, ' ') + input + string(width - input.length() - padding_left, ' ');
}

int main() {
    int console_width = 80; 
    string text_to_center = "Hello, World!";

    cout << center(text_to_center, console_width) << endl;

    return 0;
}
