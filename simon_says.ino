#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int blueLED = 3;
const int yellowLED = 4;
const int whiteLED = 5; 
const int redLED = 6; 
const int greenLED = 7; 
const int blueButton = 8;
const int yellowButton = 9;
const int whiteButton = 10;
const int redButton = 11;
const int greenButton = 12;
const int buzzer = 13;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int simonScore = 0;
int whackAMoleScore = 0;
int numbers[50];
char game;
unsigned long startGameTime;
unsigned long endGameTime;
const unsigned long GAME_TIME = 100000;
 
void setup() 
{  
  pinMode(blueLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  pinMode(whiteLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(blueButton,INPUT_PULLUP);
  pinMode(yellowButton,INPUT_PULLUP);
  pinMode(whiteButton,INPUT_PULLUP);
  pinMode(redButton,INPUT_PULLUP);
  pinMode(greenButton,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);

  digitalWrite(blueLED,LOW);
  digitalWrite(yellowLED,LOW);
  digitalWrite(whiteLED,LOW);
  digitalWrite(redLED,LOW);
  digitalWrite(greenLED,LOW);

  chooseGame();

  lcd.begin(16,2);
  lcd.backlight();
  lcd.print(0);

  randomSeed(analogRead(0));
}

void loop() 
{
  if(game == 's')
  {
    numbers[simonScore] = random(0,5);
    showPattern();
    if(isCorrect()) 
    {
      simonScore++;
      lcd.clear();
      lcd.print(simonScore);
    }
    else 
    {
      simonScore = 0;
      blinkAll();
      delay(2000);
      lcd.clear();
      lcd.print(0);
    }
  }
  else if(game == 'w')
  {
    startGameTime = millis();
    endGameTime = startGameTime + GAME_TIME;
    
    while(millis() < endGameTime)
    {
      int color = random(0,5);
      onLED(color);
      int button = getButtonPressed();
      if(button != -1 && button != color) 
      {
        button = getButtonPressed();
      }
      if(button != -1)
      {
        offLED(color);
        whackAMoleScore++;
        lcd.clear();
        lcd.print(whackAMoleScore);
      }
    }

    whackAMoleScore = 0;
    blinkAll();
    delay(2000);
    lcd.clear();
    lcd.print(0);
  }
  else if(game == 'p')
  {
    int button = getButtonPressed();
    onLED(button);
    delay(100);
    offLED(button);
  }
}

// la - beep(3520,100)
// si - beep(3951,100)
// do - beep(4186,100)

void onLED(int color)
{
  if(color == 0)
  {
    digitalWrite(blueLED,HIGH);
    beep(2093,100);
  }
  else if(color == 1)
  {
    digitalWrite(yellowLED,HIGH);
    beep(2349,100);
  }
  else if(color == 2)
  {
    digitalWrite(whiteLED,HIGH);
    beep(2637,100);
  }
  else if(color == 3)
  {
    digitalWrite(redLED,HIGH);
    beep(2793,100);
  }
  else if(color == 4)
  {
    digitalWrite(greenLED,HIGH);
    beep(3136,100);
  }
}

void offLED(int color)
{
  if(color == 0)
  {
    digitalWrite(blueLED,LOW);
  }
  else if(color == 1)
  {
    digitalWrite(yellowLED,LOW);
  }
  else if(color == 2)
  {
    digitalWrite(whiteLED,LOW);
  }
  else if(color == 3)
  {
    digitalWrite(redLED,LOW);
  }
  else if(color == 4)
  {
    digitalWrite(greenLED,LOW);
  }
}

void chooseGame()
{
  blinkAll();
  boolean isFinish = false;
  while(!isFinish)
  {
    if(digitalRead(blueButton) == LOW)
    { 
      blinkLED(0);
      game = 's';
      isFinish = true;
    }
    else if(digitalRead(yellowButton) == LOW)
    {
      blinkLED(1);
      game = 'w';
      isFinish = true;
    }
    else if(digitalRead(whiteButton) == LOW)
    {
      blinkLED(2);
      game = 'p';
      isFinish = true;
    }
  }
}

void blinkLED(int color)
{
  if(color == 0)
  {
    digitalWrite(blueLED,HIGH);
    delay(500);
    digitalWrite(blueLED,LOW);
    delay(500);
  }
  else if(color == 1)
  {
    digitalWrite(yellowLED,HIGH);
    delay(500);
    digitalWrite(yellowLED,LOW);
    delay(500);
  }
  else if(color == 2)
  {
    digitalWrite(whiteLED,HIGH);
    delay(500);
    digitalWrite(whiteLED,LOW);
    delay(500);
  }
  else if(color == 3)
  {
    digitalWrite(redLED,HIGH);
    delay(500);
    digitalWrite(redLED,LOW);
    delay(500);
  }
  else if(color == 4)
  {
    digitalWrite(greenLED,HIGH);
    delay(500);
    digitalWrite(greenLED,LOW);
    delay(500);
  }
}

void blinkAll()
{
  for(int i=0; i<3; i++)
  {  
    digitalWrite(blueLED,HIGH);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(whiteLED,HIGH);
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,HIGH);
    delay(500);
    digitalWrite(blueLED,LOW);
    digitalWrite(yellowLED,LOW);
    digitalWrite(whiteLED,LOW);
    digitalWrite(redLED,LOW);
    digitalWrite(greenLED,LOW);
    delay(500);
  }
}

void showPattern()
{
  for(int i=0; i<=simonScore; i++)
  {
    blinkLED(numbers[i]);
  }
}

boolean isCorrect()
{
  int i=0;
  while(i <= simonScore)
  {
    int button = getButtonPressed();
    if(button == numbers[i])
    {
      i++;
    }
    else
    {
      break;
    }
  }
  
  if(i > simonScore)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int getButtonPressed()
{
  while(true)
  {
    if(digitalRead(blueButton) == LOW)
    {
      blinkLED(0);
      return 0;
    }
    else if(digitalRead(yellowButton) == LOW)
    {
      blinkLED(1);
      return 1;
    }
    else if(digitalRead(whiteButton) == LOW)
    {
      blinkLED(2);
      return 2;
    }
    else if(digitalRead(redButton) == LOW)
    {
      blinkLED(3);
      return 3;
    }
    else if(digitalRead(greenButton) == LOW)
    {
      blinkLED(4);
      return 4;
    }

    if(game == 'w' && millis() >= endGameTime)
    {
      return -1;
    }
  }
}

void beep(int frequencyInHertz, long timeInMilliseconds)
{ 
  int x;
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0; x<loopTime; x++)
  {
    digitalWrite(buzzer,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(buzzer,LOW);
    delayMicroseconds(delayAmount);
  }
}

