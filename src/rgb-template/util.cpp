#include "vex.h"

float normalize180(float angle) {
    float result = fmod(angle + 180.0f, 360.0f);
    if (result < 0)
        result += 360.0f;
    return result - 180.0f;
}

float normalize360(float angle) {
  float result = fmod(angle, 360.0f);
  if (result < 0){
      result += 360.0f;
  }
  return result;
}

float threshold(float input, float min, float max){
  if(input > max) return max;
  if(input < min) return min;
  return input;
}

float percentToVolt(float percent){
  return percent*12.0/100.0;
}

int numberToPort(int number){
  return abs(number)-1; 
}

float deadband(float input, float width){
  if (fabs(input)<width){
    return 0;
  }
  return input;
}

bool port_reverse(int port_number){
  if(port_number>0) return(false);
  return(true);
}

double curveFunction(double x, double curveScale) {
  return (powf(2.718, -(curveScale / 10)) + powf(2.718, (fabs(x) - 100) / 10) * (1 - powf(2.718, -(curveScale / 10)))) * x;
}


/**
 * @brief Trim leading and trailing whitespace from a string.
 * @param str The string to trim.
 * @return A pointer to the trimmed string.
 */
static inline bool my_isspace(unsigned char ch) {
    return (ch == ' '  || ch == '\t' || ch == '\n' || 
            ch == '\v' || ch == '\f' || ch == '\r');
}

char* trim_whitespace(char* str) {
    char* end;
    // Trim leading whitespace
    while (my_isspace((unsigned char)*str)) {
        str++;
    }
    if (*str == 0) {
        return str; // All whitespace
    }
    // Trim trailing whitespace
    end = str + strlen(str) - 1;
    while (end > str && my_isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = 0;
    return str;
}

bool checkMotors(int motorCount, int temperatureLimit) {
  int count = 0;
  int t = 0;
  for (int i = 0; i < 20; i++) {
    motor m = motor(i);
    if (m.installed()) {
      count++;
      t = m.temperature(celsius);
      if (t > temperatureLimit) {
        controller(primary).Screen.print("motor %d is %dC           ", i + 1, t);
        controller(primary).rumble("---");
        return false;
      }
    }
  }
  if (count < motorCount) {
    controller(primary).Screen.print("%d motor is disconnected      ", motorCount - count);
    controller(primary).rumble("---");
    return false;
  }
  return true;
}


void showMotorTemperature()
{
    Brain.Screen.clearScreen();
    int row = 1;

    for (int i=0; i < 20; i++)
    {
        motor m = motor(i);
        if(m.installed())
        {
            Brain.Screen.setCursor(row, 1);
            int t = m.temperature(celsius);
            Brain.Screen.print("port%d: %dC", i+1, t);
            row ++;
        }
    }
}

void printControllerScreen(const char* message, bool vibrate) {
  char padded[25];
  snprintf(padded, sizeof(padded), "%-24s", message);
  controller(primary).Screen.print("%s", padded);
  if (vibrate)
  {
    controller(primary).rumble("---");
    wait(3, seconds);
  }
}


