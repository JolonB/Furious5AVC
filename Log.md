<!-- 
Add things to this log whenever you upload/edit something. It will make our reports easier because we have everything recorded.

I suggest this format:
dd/mm/yy - Statement  
Extended Description  
~~ First Name

(Pro-tip: Use a double space before a line break to go to the next line. Pressing enter twice creates a new paragraph.)
-->

## Log

07/05/2017 - Created and tested `camera_averageBW.cpp` and `colour_test.cpp`.  
`camera_averageBW.cpp` is used to find the average white value in normal lighting.  
`colour_test.cpp` detects the colour of the middle pixel and outputs it to the user.  
Both of these files are for testing purposes.  
~~ Jolon

08/05/2017 - Created `camera_row.cpp`.  
`camera_row.cpp` tests a single row of pixels and finds the colour of the pixel. It utilises code from
`camera_averageBW.cpp` and `colour_test.cpp`. It is ableto adjust itself in low lighting by decreasing
the threshold for which white is detected. In bright it also does the same thing. Testing has proven
successful as the program detects the colours correctly the majority of the time.  
~~ Jolon

17/05/2017 - Created `main.cpp` and tested the robot.  
`main.cpp` contains all of the code for the program. Every function added to it should be before the `int main()`
function. This file will contain *all* of the code for the AVC.  
We also tested the robot during the lab time and it managed to follow the line around small turns. It struggled 
to make it around larger turns as it would often turn earlier than it should. We remedied the situation by 
changing the row the camera scanned and moving the wheels closer to the camera in order to make it respond when
the wheels are closer to the position the camera is detecting. We tested it and had moderate success :tada::tada:. 
We implemented the *P* part of *PID* which has made the robot wiggle a bit which means it sometimes misses corners 
when it overcorrects itself. We next need to implement the *I*<!-- or is it D? --> part in order to make it follow 
the track more accurately and give the robot the ability to open the gate.
~~ Jolon
