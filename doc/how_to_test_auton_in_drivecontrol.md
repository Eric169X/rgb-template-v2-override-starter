# Build-in Test Auton System

## Overview

The test auton system allows you to test autonomous routines during driver control. 

## Complete Flow of Actions

###  Entering Test Mode
**Button: A** (hold within first 5 seconds of program startup)

```cpp
    controller1.rumble("-");
    printControllerScreen("Test mode: ON");
    waitUntil(!controller1.ButtonA.pressing());
    showAutonMenu();
    autonTestMode = true;
```

**What happens:**
- ✅ Controller rumbles with "-" pattern
- ✅ Displays "Test Mode: ON" on controller screen
- ✅ Shows auton menu
- ✅ Sets `autonTestMode = true`

---

###  Navigating the Auton Menu
**Button: Right** (when already in test mode)

```cpp
if (autonTestMode) {
  controller1.rumble(".");
  // if in test mode, scroll through the auton menu
  currentAutonSelection = (currentAutonSelection + 1) % autonNum;
  showAutonMenu();
}
```

**What happens:**
- ✅ Increments `currentAutonSelection` (cycles through available autons)
- ✅ Calls `showAutonMenu()` which displays menu on brain and controller screens
- ✅ Shows current selection (e.g., "auton1", "auton2", "auton_skill")

**Navigation Options:**
- **Right Button**: Move forward in menu (auton1 → auton2 → auton_skill → auton1...)

---


###  Running the Selected Auton/Step
**Button: A** (when in test mode)

**What happens:**
- ✅ Checks if in test mode
- ✅ Records start time
- ✅ Calls `runAutonItem()` which executes the selected auton
- ✅ Calculates and displays run time
- ✅ Stops chassis with coast
- ✅ Controller rumbles to confirm execution

---

###  Abort auto driving
- ✅ At any time, move joystick to abort the auto driving.

---

###  Quick test code
- ✅ When not in auton test mode, press the 'A' button to execute the quick test code at the end of 'robot-config.cpp'
```cpp
void quickTestCode()
{
   // disable button if in auton test mode, config mode, or in compeitition mode
  if (autonTestMode  || endGameTimerEnabled) return; 
  wait(300, msec);
  if (controller1.ButtonA.pressing()) return; //only trigger single press

  double t1 = Brain.Timer.time(sec);
  printControllerScreen("Running test...");
  //write code here:

  double t2 = Brain.Timer.time(sec);
  char timeMsg[30];
  sprintf(timeMsg, "run time: %.1f", t2-t1);
  printControllerScreen(timeMsg);
  chassis.stop(hold);
  wait(500, msec);
  chassis.stop(coast); 
}

```
---
