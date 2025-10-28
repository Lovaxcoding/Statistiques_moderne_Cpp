#include <iostream>
#include <cmath>
#include <iomanip>

class Complex {
private:
    double real;
    double imag;

public:
    // Default constructor
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Overload the + operator for addition
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Overload the - operator for subtraction
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Overload the * operator for multiplication
    Complex operator*(const Complex& other) const {
        // (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
        double new_real = (real * other.real) - (imag * other.imag);
        double new_imag = (real * other.imag) + (imag * other.real);
        return Complex(new_real, new_imag);
    }

    // Function to display the number in Cartesian form
    void displayCartesian() const {
        if (imag >= 0) {
            std::cout << real << " + " << imag << "i" << std::endl;
        } else {
            std::cout << real << " - " << -imag << "i" << std::endl;
        }
    }

    // Function to display the number in polar coordinates
    void displayPolar() const {
        // Calculate magnitude (r) and angle (theta)
        double magnitude = sqrt(real * real + imag * imag);
        double angle = atan2(imag, real); // Use atan2 for correct quadrant handling

        // Output with precision for clarity
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Polar: r = " << magnitude << ", theta = " << angle << " radians" << std::endl;
    }
};

int main() {
    // Create complex number objects
    Complex c1(3.0, 4.0);
    Complex c2(2.0, -1.0);

    // Display the numbers
    std::cout << "Complex Number 1: ";
    c1.displayCartesian();
    std::cout << "Complex Number 2: ";
    c2.displayCartesian();

    // Demonstrate addition
    Complex sum = c1 + c2;
    std::cout << "\nSum (c1 + c2): ";
    sum.displayCartesian();
    sum.displayPolar();

    // Demonstrate subtraction
    Complex difference = c1 - c2;
    std::cout << "\nDifference (c1 - c2): ";
    difference.displayCartesian();
    difference.displayPolar();

    // Demonstrate multiplication
    Complex product = c1 * c2;
    std::cout << "\nProduct (c1 * c2): ";
    product.displayCartesian();
    product.displayPolar();

    return 0;
}
