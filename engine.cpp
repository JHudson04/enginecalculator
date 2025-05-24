#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <limits>

using namespace std;

// Function declarations
double getInput(const string& prompt);
double calculateDisplacement(double bore, double stroke, int cylinders);
double calculateCFM(double displacement, double rpm, double ve);
double calculateHorsepower(double cfm);
double calculateTorque(double hp, double trpm);
string determineGeometry(double bore, double stroke);
double calculatePistonSpeed(double stroke, double rpm);

int main()
{
    cout << "** C++ Engine Calculator **" << endl << endl;

    double bore = getInput("Enter bore (inches): ");
    double stroke = getInput("Enter stroke (inches): ");
    int numCylinders = static_cast<int>(getInput("Enter number of cylinders: "));
    double prpm = getInput("Enter peak power RPM: ");
    double trpm = getInput("Enter peak torque RPM: ");
    double ve = getInput("Enter volumetric efficiency (decimal): ");
    double displacement = calculateDisplacement(bore, stroke, numCylinders);
    double cfm = calculateCFM(displacement, prpm, ve);
    double hp = calculateHorsepower(cfm);
    double torque = calculateTorque(hp, trpm);
    string geo = determineGeometry(bore, stroke);
    double pistonSpeed = calculatePistonSpeed(stroke, prpm);

    cout << "\n--- Results ---\n";
    double displacementLiters = displacement * 0.0163871;

    cout << fixed << setprecision(3);
    cout << "Displacement: " << displacement << " cubic inches (" << displacementLiters << "L)" << endl;
    cout << "Power-optimized airflow volume: " << cfm << " cfm" << endl;
    cout << "Approximated power: " << hp << " hp" << endl;
    cout << "Approximated torque: " << torque << " lb-ft" << endl;
    cout << "Engine geometry: " << geo << endl;
    cout << "Mean piston speed: " << pistonSpeed << " ft/min" << endl;
    if (pistonSpeed > 4000)
    {
        cout << "Warning: High piston speed may exceed typical reliability limits." << endl;
    }
    return 0;
}

// Function definitions
double getInput(const string& prompt)
{
    double value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards bad input
            cout << "Invalid input. Please enter a numeric value.\n";
        }
        
        if (value <= 0)
        {
            cout << "Value must be positive. Try again." << endl;
            continue;
        }

        if (prompt.find("volumetric efficiency") != string::npos && (value <= 0.0 || value > 1.5))
        {
            cout << "Volumetric efficiency should be between 0.0 and 1.5.\n";
            continue;
        }

        else
        {
            cout << endl;
            return value;
        }

    }
}

double calculateDisplacement(double bore, double stroke, int cylinders)
{
    return M_PI * pow(bore, 2) * 0.25 * stroke * cylinders;
}

double calculateCFM(double displacement, double rpm, double ve)
{
    return (displacement * rpm * ve) / 3456;
}

double calculateHorsepower(double cfm)
{
    return (cfm / 1.5);
}

double calculateTorque(double hp, double trpm)
{
    return (5252 * hp) / trpm;
}

string determineGeometry(double bore, double stroke)
{
    if (bore > stroke)
        return "Oversquare";
    else if (bore < stroke)
        return "Undersquare";
    else
        return "Square";
}

double calculatePistonSpeed(double stroke, double rpm)
{
    return 2 * stroke * rpm / 12; // feet per minute
}
