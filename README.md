# ptimer

ptimer is a CLI timer to track productivity using the Pomodoro Technique.
Helps to organize time effectively during studying or working.

## Build

To compile it run make.

```
make ptimer
```

## Usage

To start ptimer just launch the file. By default there will be 2 sessions (50 min) and 1 break (10 min). 
```
./ptimer
```

You can use special flags to change default values
```
-s    session duration
-b    break duration
-n    number of sessions
```

Example:
```
./ptimer -s 25 -b 5 -n 5
```
