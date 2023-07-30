#include "_HCSR04.h"

float defaultDistanceIn, defaultDistanceOut;
int peoples = 0;

extern bool busIsStarted;

enum Previous_Way{
  NONE,
  IN,
  OUT
};

void initHCSR04(){
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);

  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
}

float getDistance(int trigPin, int echoPin)
{
  long duration = 0;
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH); // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  return (duration * SOUND_SPEED/2);
}

void measureDefaultDistance(){
  defaultDistanceIn = getDistance(TRIG_PIN_1, ECHO_PIN_1);
  for(int i = 0; i < NO_TIMES_GET_DEFAULT_DISTANCE; i++){
    defaultDistanceIn = (defaultDistanceIn + getDistance(TRIG_PIN_1, ECHO_PIN_1)) / 2;
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }

  defaultDistanceOut = getDistance(TRIG_PIN_2, ECHO_PIN_2);
  for(int i = 0; i < NO_TIMES_GET_DEFAULT_DISTANCE; i++){
    defaultDistanceOut = (defaultDistanceOut + getDistance(TRIG_PIN_2, ECHO_PIN_2)) / 2;
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void HCSR04RunTask(void *parameter){
  int counterIn = 0, counterOut = 0, peopleIn = 0, peopleOut = 0;
  float distanceIn, distanceOut;
  while(true){
    distanceIn = getDistance(TRIG_PIN_1, ECHO_PIN_1);
    distanceOut = getDistance(TRIG_PIN_2, ECHO_PIN_2);

    if(distanceIn < DISTANCE_THRESHOLD){
      counterIn++;
      if(counterIn == NO_OF_DISTANCE_DEBOUNCING){
        peopleIn++;
      }
      else if (counterIn > NO_OF_DISTANCE_DEBOUNCING){
        counterIn = NO_OF_DISTANCE_DEBOUNCING + 5;
      }
    }
    else{
      counterIn = 0;
    }

    if(distanceOut < DISTANCE_THRESHOLD){
      counterOut++;
      if(counterOut == NO_OF_DISTANCE_DEBOUNCING){
        peopleOut++;
      }
      else if (counterOut > NO_OF_DISTANCE_DEBOUNCING){
        counterOut = NO_OF_DISTANCE_DEBOUNCING + 5;
      }
    }
    else{
      counterOut = 0;
    }

    peoples = (peopleIn - peopleOut);

    if(peoples > MAX_PEOPLES_IN_BUS){
      digitalWrite(LED_OVERLOAD_PIN, HIGH);
    }
    else{
      digitalWrite(LED_OVERLOAD_PIN, LOW);
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void HCSR04RunTask_v2(void *parameter){
  int counterIn = 0, counterOut = 0;
  int counterIn1 = 0, counterOut1 = 0;
  int peopleIn = 0, peopleOut = 0;
  unsigned long timeChangeIn = 0, timeChangeOut = 0, diff = 0;
  float distanceIn, distanceOut;
  int previousWayChange = NONE;
  
  measureDefaultDistance();

  peoples = 0;
  
  while(true){
    if(!busIsStarted) {
      vTaskDelete(NULL);
    }
    
    distanceIn = getDistance(TRIG_PIN_1, ECHO_PIN_1);
    distanceOut = getDistance(TRIG_PIN_2, ECHO_PIN_2);

    if(distanceIn < defaultDistanceIn * DISTANCE_THRESHOLD_RATE){
      counterIn++;
      if(counterIn == NO_OF_DISTANCE_DEBOUNCING){
        timeChangeIn = millis();
        Serial.print("In change");
        Serial.print("---- DIFF: ");
        diff = timeChangeIn - timeChangeOut;
        Serial.println(diff);

        if(previousWayChange != IN && diff <= THRESHOLD_DETERMINE_PEOPLE_MS){
          Serial.print("Deteced people OUT. peopleOut = ");
          peopleOut++;
          Serial.println(peopleOut);
        }

        previousWayChange = IN;
        counterIn1 = 0;
      }
      else if (counterIn > NO_OF_DISTANCE_DEBOUNCING){
        counterIn = NO_OF_DISTANCE_DEBOUNCING + 5;
      }
    }
    else{
      counterIn1++;
      if(counterIn1 == NO_OF_DISTANCE_DEBOUNCING){
        counterIn = 0;
      }
      else if (counterIn1 > NO_OF_DISTANCE_DEBOUNCING){
        counterIn1 = NO_OF_DISTANCE_DEBOUNCING + 5;
      }
    }

    if(distanceOut < defaultDistanceOut * DISTANCE_THRESHOLD_RATE){
      counterOut++;
      if(counterOut == NO_OF_DISTANCE_DEBOUNCING){
        timeChangeOut = millis();
        Serial.print("Out change");
        Serial.print("---- DIFF: ");
        diff = timeChangeOut - timeChangeIn;
        Serial.println(diff);

        if(previousWayChange != OUT && diff <= THRESHOLD_DETERMINE_PEOPLE_MS){
          Serial.print("Deteced people IN. peopleIn = ");
          peopleIn++;
          Serial.println(peopleIn);
        }

        previousWayChange = OUT;
        counterOut1 = 0;
      }
      else if (counterOut > NO_OF_DISTANCE_DEBOUNCING){
        counterOut = NO_OF_DISTANCE_DEBOUNCING + 5;
      }
    }
    else{
        counterOut1++;
        if(counterOut1 == NO_OF_DISTANCE_DEBOUNCING){
            counterOut = 0;
        }
        else if (counterOut1 > NO_OF_DISTANCE_DEBOUNCING){
            counterOut1 = NO_OF_DISTANCE_DEBOUNCING + 5;
        }
    }

    peoples = (peopleIn - peopleOut);

//    Serial.print("==============Peoples: ");
//    Serial.println(peoples);

    if(peoples > MAX_PEOPLES_IN_BUS){
      digitalWrite(LED_OVERLOAD_PIN, HIGH);
    }
    else{
      digitalWrite(LED_OVERLOAD_PIN, LOW);
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
