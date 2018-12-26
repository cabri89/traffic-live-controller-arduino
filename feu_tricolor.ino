
int redSwitch = 3;
int orangeSwitch = 4;
int greenSwitch = 2;

int red = 10;
int orange = 9;
int green = 11;

int delayButton = 6;
int modeButton = 7;

int onState = 1;
int offState = 0;

int numMode;
int totalMode = 3;
int lightOn = 1;

int previousMode;
int readingMode;

int previousDelay;
int readingDelay;
int multDelay = 1;
int maxMult = 10;

long mode1Time;
long mode1Delay = 100;

long mode3Time;

void setup()
{
  numMode = 1;
  Serial.begin(9600);
  pinMode(delayButton, OUTPUT);
  pinMode(redSwitch, OUTPUT);
  pinMode(orangeSwitch, OUTPUT);
  pinMode(greenSwitch, OUTPUT);
  pinMode(modeButton, OUTPUT);

  pinMode(red, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(green, OUTPUT);
}

int readModeButton()
{
  readingMode = digitalRead(modeButton);

  if (readingMode != previousMode)
  {
    if (readingMode == offState)
    {
      if (numMode == totalMode)
      {
        numMode = 1;
      }
      else
      {
        numMode++;
      }
    }
    multDelay = 1;
  }

  previousMode = readingMode;
}

int readDelayButton()
{
  readingDelay = digitalRead(delayButton);

  if (readingDelay != previousDelay)
  {
    if (readingDelay == offState)
    {
      if (multDelay == maxMult)
      {
        multDelay = 1;
      }
      else
      {
        multDelay++;
      }
    }
  }
  previousDelay = readingDelay;
}

int switchLight(int greenState, int orangeState, int redState)
{
  digitalWrite(orange, orangeState);
  digitalWrite(red, redState);
  digitalWrite(green, greenState);
}

void loop()
{
  readModeButton();
  readDelayButton();

  if (numMode == 1)
  {
    digitalWrite(orange, digitalRead(orangeSwitch));
    digitalWrite(green, digitalRead(greenSwitch));
    digitalWrite(red, digitalRead(redSwitch));
  }

  if (numMode == 2)
  {
    if (millis() - mode1Time >= (mode1Delay * multDelay))
    {
      if (lightOn == 1)
      {
        switchLight(onState, offState, offState);
      }

      if (lightOn == 2)
      {
        switchLight(offState, offState, onState);
      }

      if (lightOn == 3)
      {
        switchLight(offState, onState, offState);
        lightOn = 0;
      }
      lightOn++;
      mode1Time = millis();
    }
  }

  if (numMode == 3)
  {
    if (millis() - mode1Time >= (mode1Delay * multDelay))
    {
      if (lightOn == 1)
      {
        switchLight(offState, offState, offState);
      }

      if (lightOn == 2)
      {
        switchLight(onState, offState, offState);
      }

      if (lightOn == 3)
      {
        switchLight(onState, onState, offState);
      }

      if (lightOn == 4)
      {
        switchLight(onState, onState, onState);
      }

      if (lightOn == 5)
      {
        switchLight(offState, onState, onState);
      }

      if (lightOn == 6)
      {
        switchLight(offState, offState, onState);
        lightOn = 0;
      }

      lightOn++;
      mode1Time = millis();
    }
  }
}
