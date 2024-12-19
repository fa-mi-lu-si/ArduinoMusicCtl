#include <LiquidCrystal.h>
#include <Button.h>

const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int knob_pin = A0;
int knob_value;
int last_knob_value = -1;

unsigned long last_vol_time;
unsigned long vol_delay = 200;

Button button_1(12);
Button button_2(11);
Button button_3(10);

String artist_str;
String title_str;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    button_1.begin();
    button_2.begin();
    button_3.begin();

    pinMode(knob_pin, INPUT);
    lcd.begin(16, 2);
}

void loop()
{
    //  Recieve input
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        if (input.startsWith("T")) {
            title_str = input.substring(1);
        } else if (input.startsWith("A")) {
            artist_str = input.substring(1);
            updateLCD();
        }
    }

    knob_value = analogRead(knob_pin);

    //  check for button press and send appropriate command
    if (button_1.pressed())
    {
        Serial.println("p");
    }
    else if (button_2.pressed())
    {
        Serial.println("t");
    }
    else if (button_3.pressed())
    {
        Serial.println("n");
    }
    
    unsigned long current_time = millis();
    //  if the value of the knob has changed
    if (abs(knob_value - last_knob_value) > 5 && (current_time - last_vol_time) > vol_delay)
    {
        Serial.print("V");
        Serial.println(knob_value);
        last_vol_time = current_time;
        last_knob_value = knob_value;
    }

    delay(50);
}

void updateLCD()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(title_str);
    lcd.setCursor(0, 1);
    lcd.print(artist_str);
}
