#include <iostream>

const int HOURS_IN_DAY = 24;
const int MINUTES_IN_HOUR = 60;
const int SECONDS_IN_MINUTE = 60;

int main() {
  using std::cin;
  using std::cout;
  using std::endl;

  cout << "Enter the number of seconds: ";
  long long total_seconds;
  cin >> total_seconds;
  int seconds = total_seconds % SECONDS_IN_MINUTE;
  long long total_minutes = total_seconds / SECONDS_IN_MINUTE;
  int minutes = total_minutes % MINUTES_IN_HOUR;
  long long total_hours = total_minutes / MINUTES_IN_HOUR;
  int hours = total_hours % HOURS_IN_DAY;
  long long total_days = total_hours / HOURS_IN_DAY;

  cout << total_seconds << " seconds: " << total_days << " days, "
    << hours << " hours, "
    << minutes << " minutes, "
    << seconds << " seconds"
    << endl;

  return 0;
}
