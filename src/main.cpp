#include <iostream>
#include <exception>
#include "../include/calculator.h"
using namespace std;

int main() {
    int choice;
    double num1, num2;

    do {
        cout << "\n===== Scientific Calculator =====\n";
        cout << "1. Square Root\n";
        cout << "2. Factorial\n";
        cout << "3. Natural Log (ln)\n";
        cout << "4. Power (x^b)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            switch(choice) {
                case 1:
                    cout << "Enter number: ";
                    cin >> num1;
                    cout << "Result: " << squareRoot(num1) << endl;
                    break;

                case 2:
                    cout << "Enter integer: ";
                    cin >> num1;
                    cout << "Result: " << factorial((int)num1) << endl;
                    break;

                case 3:
                    cout << "Enter number: ";
                    cin >> num1;
                    cout << "Result: " << naturalLog(num1) << endl;
                    break;

                case 4:
                    cout << "Enter base: ";
                    cin >> num1;
                    cout << "Enter exponent: ";
                    cin >> num2;
                    cout << "Result: " << power(num1, num2) << endl;
                    break;

                case 5:
                    cout << "Exiting...\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
            }
        } catch (exception &e) {
            cout << "Error: " << e.what() << endl;
        }

    } while(choice != 5);

    return 0;
}
