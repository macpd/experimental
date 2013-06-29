// Calculates BMI from height in feet and inches, and mass in pounds
// BMI = (height in meters)^2 / (mass in kilograms)
#include <iostream>

const int INCHES_PER_FOOT = 12;
const double METERS_PER_INCH = 0.0254;
const double POUNDS_PER_KILOGRAM = 2.2;

double CalculateBmi(double mass, double height);

int main() {

  using std::cin;
  using std::cerr;
  using std::cout;
  using std::endl;

  cout << "Enter you height and mass." << endl;
  cout << "Feet: ";
  int height_feet;
  cin >> height_feet;
  cout << "Inches: ";
  int height_inches;
  cin >> height_inches;
  cout << "Mass in pounds: ";
  float mass_pounds;
  cin >> mass_pounds; 

  int total_height_inches = height_inches + (INCHES_PER_FOOT * height_feet);
  cerr << "Height in inches: " << total_height_inches << endl;

  double total_height_meters = total_height_inches * METERS_PER_INCH;
  cerr << "Height in meters: " << total_height_meters << endl;

  double mass_kilograms = static_cast<double> (mass_pounds) / POUNDS_PER_KILOGRAM;
  cerr << "Mass in kilograms: " << mass_kilograms << endl;

  cout << "BMI: " << CalculateBmi(mass_kilograms, total_height_meters) << endl;

  return 0;
 }

double CalculateBmi(double kilograms, double meters) {
  return kilograms/(meters * meters);
}
