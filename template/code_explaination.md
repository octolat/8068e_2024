# autonHelper();

**Use case**  
To help with figuring out degrees or heading you should input when coding auton  
Basically, it will print the degrees the drive train is moving, and the current heading of the bot onto your controller, so that you can read it and write it down, and use that information in moveForDegrees or turnToHeading

It will run forever once you call it in main()

**Operation**:

1. Once running, you will see the turns moved of the left front and right front motors of the drive train on your controller. You can move your bot and this number will update  
2. Press the Up button on your controller to reset the turn count   
3. Hold down the Right button on your controller to see the heading it is facing. This will also update as you move the bot

# moveForTurns(float destination, int timeout)

**Use case**  
Move the bot forward for given amount of turns

Destination   
	How many turns to move forward by.  
	If you want to move backwards, set this number to a negative number  
Timeout  
	How long to wait for the robot to reach the destination before giving up and moving on, in   
seconds   
	This is **optional**, you can leave it blank to wait forever  
	Useful in situations where you might hit a wall and get stuck

**examples**:  
moveForTurns(0.55); // move forwards by 0.55 turns, will keep trying to turn 0.55 turns forever  
moveForTurns(\-3, 4); // move backwards by 3 turns, if it has not turned 3 turns in 4 seconds, it will give up and move on

**Tuning**  
This function uses a modified PID controller. The tuned values are stored in the global variables:   
moveP and moveConst  
Simplified Controller idea: moveP \* (destination \- currentPosition) \+ moveConst  
moveP → the normal P value in a PID controller, multiplied by the error to increase or decrease the speed of the drivetrain  
moveConst → no matter the error, the drive train will move by this speed minimally  
		Set your moveConst so that even if moveP is 0, the drive train can still move abit slowly

# turnToDegrees(float destination, int pivotSetting, int timeout)

**Use case**  
Turn the bot until it faces the heading given

Destination  
	The heading you want the bot to face  
pivotSetting  
	Either Both, Left, or Right  
	If Both, the robot will turn in a spot turn manner  
	If Left, only the left side of the drivetrain will move, and the right side will remain stationary,   
resulting in a pivot turn   
If right, the same but the right side moves  
This is **Optional**, default is Both  
Timeout  
	How long to wait for the robot to reach the heading before giving up and moving on, in   
seconds   
	This is **optional**, you can leave it blank to wait forever  
	Useful in situations where you might hit a wall and get stuck

**Examples**  
turnToDegree(39); // turn and face the heading 39, spot turns, will try forever  
turnToDegree(320, Left);  // turn and face heading 320, pivot turn with left side moving, will try forever  
turnToDegree(75, Both, 3); // turn and face heading 75, spot turn, will try for 3 seconds before giving up

**Tuning**  
This function uses a modified PID controller. The tuned values are stored in the global variables:   
turnP and turnConst  
Simplified Controller idea: turnP \* (destination \- currentPosition) \+ turnConst  
turnP → the normal P value in a PID controller, multiplied by the error to increase or decrease the speed of the drivetrain  
turnConst → no matter the error, the drivetrain will move by this speed minimally  
		Set your turnConst so that even if moveP is 0, the drive train can still move abit slowly

# driveMacro(int action, float argument1, float argument2)

**Use case**  
Basically a short cut so you dont have to repeat 6 lines just to make the 6 motors in your drivetrain do smth

| action | argument1 | argument2 | description |
| :---- | :---- | :---- | :---- |
| Spin | nil | nil | Tells the drivetrain to start moving |
| Stop | nil | nil | Tells the drivetrain to stop |
| SetSpeed | Speed for the left side | Speed for the right side | Sets the target velocity to the given speeds (wont start moving until you call Spin) |
| SetBreaking | Brake, Hold, or Coast | nil | Set the breaking mode for the whole drivetrain |
| SetTimeout | Timeout length | nil | Runs motor.setTimeout() For all 6 motors (dont need to touch) |
| SpinFor | Turns for left side to move for | Turns for right side to move for | Runs motor.spinFor() For all 6 motors (very jank, dont use) |
| SpinTo | Encoder position for left side to move to | Encoder position for right side to move to | Runs motor.spinTo() For all 6 motors (very jank, dont use) |

**Examples:**  
//Make the bot turn in a clockwise manner for 3 seconds, and set breaking to coast   
driveMacro(SetBraking, Coast);  
driveMacro(SetSpeed, 100, \-100);  
driveMacro(Spin);  
wait(3, seconds);  
driveMacro(Stop);

# TODOs

Search up the TODO\[i\] in the editor

TODO\[1\] \--\> edit the ports, gear ratio, and rotation of your drivetrain motors  
TODO\[2\] \--\> edit the port of your gyro sensor  
TODO\[3\] \--\> define the other stuff your using eg.  
  motor intake\_motor \= motor(PORT1, ratio18\_1, false); // for a motor  
  rotation Rotation2 \= rotation(PORT2, false); // for a v5 rotation sensor  
  digital\_out hang\_piston \= digital\_out(Brain.ThreeWirePort.A); // for a solonoid at port A  
  digital\_in intake\_limitSwitch \= digital\_out(Brain.ThreeWirePort.b); // for a limit switch at port B  
  see https://api.vex.com/v5/home/cpp/  
TODO\[4\] \--\> choose whether you are running a 'Match' or a 'Skills' run before uploading  
TODO\[5\] \--\> these are the pid variables for turnToDegree() and moveForTurns(). you have to tune them   
        like you tune a line tracking bot. the values below were from 8068e worlds bot  
TODO\[6\] \--\> uncomment the code that you want to run before uploading  
TODO\[7\] \--\> choose Brake, Coast or Hold for your drive train during driver control  
TODO\[8\] \--\> code stuff other than the drivetrain for your driver control mode  
    	         github has the over under code for you to refer to  
TODO\[9\] \--\> your auton\_one/auton\_two/auton\_skills code  
TODO\[10\] \--\> do wtv you want to set up before each auton