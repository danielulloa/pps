#include "MCP3919.h"
#include <SPI.h>

MCP3919 mcp3919;

void setup()
{
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    SPI.begin();
    Serial.begin(9600);
    mcp3919.reset();
}

void loop()
{
    Serial.println(mcp3919.readADC(0) * 20 , 4);
    delay(10);
}
