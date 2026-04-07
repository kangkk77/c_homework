#include <iostream>
#include <string>
using namespace std;

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }
    
    int subtract(int a, int b) {
        return a - b;
    }
};

int main() {
    Calculator calc;
    int a = 10, b = 5;
    
    cout << a << " + " << b << " = " << calc.add(a, b) << endl;
    cout << a << " - " << b << " = " << calc.subtract(a, b) << endl;
    
    return 0;
}
