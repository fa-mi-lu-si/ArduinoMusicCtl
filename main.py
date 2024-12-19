import serial
import time
import threading
from subprocess import call, check_output

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)

def send_song_info():
    while True:
        try:
            title = check_output(["playerctl", "metadata", "title"]).decode().strip()
            artist = check_output(["playerctl", "metadata", "artist"]).decode().strip()
            arduino.write(f"T{title}\nA{artist}\n".encode())
        except:
            arduino.write("T \nA \n".encode())
        time.sleep(1)  # Send song info every second

# Start the song info sending thread
threading.Thread(target=send_song_info, daemon=True).start()

while True:
    time.sleep(0.01)

    value = arduino.readline().decode().strip()

    if value == 't':
        call(["playerctl", "play-pause"])
    elif value == 'p':
        call(["playerctl", "previous"])
    elif value == 'n':
        call(["playerctl", "next"])
    elif value.startswith('V'):
        try:
            volume = int((int(value[1:])/1024)*100)
            call(["pactl", "set-sink-volume", "0", f"{volume}%"])
        except:
            pass

    print(value)
