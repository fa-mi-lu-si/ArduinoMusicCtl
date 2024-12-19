# ArduinoMusicCtl

A music controlling gadget built with arduino
![a picture](image.png)
## How it works

```mermaid
graph TB
    A[Arduino] <--> |Serial Communication| PP[Python Program]
    
    subgraph Arduino
        B[Buttons] --> A
        K[Potentiometer Knob] --> A
        A --> D[LCD Display]
    end
    
    subgraph "Python Program"
        PP --> T1[Thread 1: Fetch Music Info]
        PP --> T2[Thread 2: Receive Commands]
        T1 -->|Query| C[playerctl]
        T2 -->|Control| C
        C <-->|Query/Control| M[Music Player]
    end
    a
    T1 -.->|Send Display Data| A
    A -.->|Send Commands| T2
```

The python program recieves instructions from the arduino via serial and calls a commandline program to perform the action.
It also checks the title and artist of the currently playing song and sends them to the arduino.

It uses playerctl to support all media players that implement the MPRIS D-Bus Interface Specification.

## Hardware Setup

![schematic](./schematic.svg)
![breadboard](./breadboard.png)

## Requirements

[playerctl](https://github.com/altdesktop/playerctl) is used to control the media player. You can edit the main.py to use a different program.

The [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal) and [Button](https://github.com/madleech/Button) libraries for arduino are also required.
