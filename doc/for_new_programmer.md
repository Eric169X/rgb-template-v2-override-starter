# Prerequsite
## Knowldge of basic c++ syntax
* variable and statement
* arithmetic
* if
* while
* function
* object dot notation

## VEX API
* motor operations
* Button press states and events
* wait statement

## Software configuration
* install VS Code and necessary extensions
* Github Account management
* Github Repository operations



# RGB template
## robot-config.h
In the `include/` folder, find the `robot-config.h` file. Define a robot with the correct port configuration and parameters.

## robot-config.cpp
In the `src/` folder, find the `robot-config.cpp` file. Edit the `Button controls` section to write the control functions for the buttons. (optional) Edit test code in the `Quick Test Code` section.

## auton.cpp
In the `src/` folder, find the `auton.cpp` file. Edit the `Auton Functions` and write your auton functions. Then, map auton functions to auton menu items in the `runAutonItem()` function. Finally, add the names of your autonomous functions to the `autonMenuText` array.

## Programming Interfaces of the library

### `driveWithVoltage(float leftVoltage, float rightVoltage)`
This is the most basic drive function. It sets the voltage (max is 12V) for the left and right sides of the drivetrain directly. 

**Example:**

```cpp
// Drive forward at half speed for 1 second
chassis.driveWithVoltage(6, 6);
wait(1000, msec);
chassis.stop();

// rotate slowly for 1 second
chassis.driveWithVoltage(-4, 4);
wait(1000, msec);
chassis.stop();
```

### `turn(...)`

This API turns the robot to a specific heading using a PID controller.

**Variations:**

1.  `turn(float heading)`: Turns to the specified heading with default parameters.
2.  `turn(float heading, float turnMaxVoltage)`: Limits the maximum voltage for a slower, more accurate turn.

**Examples:**

```cpp
// Simple turn to 90 degrees
chassis.turn(90);

// Slower, more accurate turn
chassis.turn(-90, 6);
```

### `drive(...)`

This API drives the robot a specific distance using a PID controller, with options for turning to a heading.

**Variations:**

1.  `drive(float distance)`: Drives the specified distance with default parameters.
2.  `drive(float distance, float driveMaxVoltage)`: Limits the maximum voltage for slow driving.


**Examples:**

```cpp
// Drive backward 24 inches
chassis.drive(-24);

// Drive forward 24 inches with a slow speed, e.g. when intaking field game elements
chassis.drive(24, 4);

```

### `setHeading(...)`

This API set the robot to a specific heading, e.g. when the auton routine starts.

**Examples:**

```cpp
// set robot intial heading to 90 degrees
chassis.setHeading(90);

```
### Advanced Driving Features
- motion chaining using early exit, e.g. no stopping
- distance sensing using distance sensors
- swing turn
- curve drive

**Examples:**

```cpp

// turn to heading 90 with maxium speed, and move on to the next drive command when the robot is within 10 degree of the target heading
chassis.turn(90, 12, 10);

// Drive forward 40 inches while maintaining heading 90, and move on to the next drive command when the robot is within 5 inches of target 
chassis.drive(40, 90, 5);

// Drive towards the side wall, stopping at 12 inches away from the wall (need to install front distance sensor)
chassis.drive(12, 10, 90, 6, 1, true);  

// Hold the right side drivetrain and swing turn to heading 0. Complete stop when reaching the heading.
chassis.turn(0, 10, 1, 1); 

// Drive forward 30 inches while turning to heading 45. Complete stop when reaching the target
chassis.drive(30, 10, 45, 6, 1);

```

### Complete Set of Drive API

```cpp


  // Sets the current heading of the robot.
  void setHeading(float orientationDeg);
  // Drives the robot with a specific voltage for each side of the drivetrain.
  void driveWithVoltage(float leftVoltage, float rightVoltage);

  // Turns the robot to a specific heading.
  void turn(float heading);
  // turn slower with lower max voltage
  void turn(float heading, float turnMaxVoltage); 
  // earlyExitFactor for motion chaining: nonstopping if greater than 1. Maxium is 10.
  void turn(float heading, float turnMaxVoltage, float earlyExitFactor); 
  // only one side moves. swing = 1: right side swings, swing = -1: left side swings.
  void turn(float heading, float turnMaxVoltage, float earlyExitFactor, int swing);

  // Drives the robot a specific distance.
  void drive(float distance);
  // Drives the robot a specific distance with a maximum voltage.
  void drive(float distance, float driveMaxVoltage);
  // earlyExitFactor for motion chaining: nonstopping if greater than 1. Maxium is 10.
  void drive(float distance, float heading, float earlyExitFactor);
  // distance > 0: front sensor, distance < 0: back sensor
  void drive(float distance, float heading, float earlyExitFactor, bool distanceSensing); 
  // Curve drive with max voltage and heading correction
  void drive(float distance, float driveMaxVoltage, float heading, float headingMaxVoltage,  float earlyExitFactor);
  void drive(float distance, float driveMaxVoltage, float heading, float headingMaxVoltage,  float earlyExitFactor, bool distanceSensing);

    // Stops the drivetrain.
  void stop(vex::brakeType mode);

  // Gets the current heading of the robot.
  float getHeading();

```

## Complete Set of VEX API
Additional VEX API can be found at https://api.vex.com/v5/home/cpp/index.html


