#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

// Sample values
bool barometerDataAvailable = true;
float oldAltitude = 400.0; // m
float newAltitude = 385.0; // m
float elapsedTime = 1.2; // s


int errorCode1 = 0;
int errorCode2 = 0;
int errorCode3 = 0;

void recordTime() {
    time_t now = time(NULL);
    printf("Time recorded: %s", asctime(localtime(&now)));
}

float readBarometer() {
    if (!barometerDataAvailable) {
        errorCode3 = 1;
        printf("Barometer connection failed! Error Code 3 = 1\n");
        return -1;
    }

    errorCode3 = 0;
    recordTime();

    // Converts from barometer to altitude
    float newValue = newAltitude;  
    printf("Data received from barometer. Altitude: %.2f m\n", newValue);
    return newValue;
}

float calculateAverageSpeed(float alt1, float alt2, float time) {
    return fabs(alt1 - alt2) / time;
}

void checkErrorCode(float speed, int *errorCode, float lowerLimit, float upperLimit) {
    if (speed >= lowerLimit && speed <= upperLimit) {
        *errorCode = 0;
    } else {
        *errorCode = 1;
    }
}

int main() {
    float alt1 = oldAltitude;
    float alt2 = readBarometer();

    if (errorCode3 == 1) {
        return 1; // Exit due to connection error
    }

    float avgSpeed = calculateAverageSpeed(alt1, alt2, elapsedTime);
    printf("Average Speed: %.2f m/s\n", avgSpeed);

    // Speed control (12-14 m/s)
    checkErrorCode(avgSpeed, &errorCode1, 12.0, 14.0);
    printf("Error Code 1: %d\n", errorCode1);

    // Payload: speed control (6-8 m/s)
    checkErrorCode(avgSpeed, &errorCode2, 6.0, 8.0);
    printf("Error Code 2: %d\n", errorCode2);

    return 0;
}
