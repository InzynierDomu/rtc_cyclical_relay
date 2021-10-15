/**
 * @file main.cpp
 * @brief time relay
 * @author by Szymon Markiewicz
 * @details http://www.inzynierdomu.pl/
 * @date 06-2021
 */

#include "RTClib.h"

#include <Arduino.h>
#include <Wire.h>

RTC_DS1307 m_rtc; ///< DS1307 RTC

const uint16_t m_period_time = 15; ///< period when relay is turning on
const uint16_t m_active_time = 2; ///< how long relay is turned on

const byte m_output_pin = 2; ///< pin connected to relay

const uint8_t m_min_in_h = 60; ///< minutes in an hour
const unsigned long m_refresh_time_ms = 15000; ///< time of repeting check time is in range and sending message

/**
 * @brief calculate hours and minutes to only minutes
 * @param time hours and minutes to calculate
 * @return minutes
 */
uint16_t min_calculate(const DateTime& time)
{
  uint16_t time_minute = time.hour() * m_min_in_h;
  time_minute += time.minute();
  return time_minute;
}

/**
 * @brief check if current time is in range from start to end time
 * @param current current time
 * @param start start time
 * @param stop stop time
 * @return true if is in range, false if is not in range
 */
bool is_in_range(const DateTime& current, const DateTime& start, const DateTime& end)
{
  auto current_minute = min_calculate(current);
  auto start_minute = min_calculate(start);
  auto end_minute = min_calculate(end);

  return ((current_minute >= start_minute) && (current_minute < end_minute));
}

/**
 * @brief setup
 */
void setup()
{
  Serial.begin(9600);

  pinMode(m_output_pin, OUTPUT);

  if (!m_rtc.begin())
  {
    Serial.println("Couldn't find RTC");
  }

  if (!m_rtc.isrunning())
  {
    Serial.println("RTC is NOT running, let's set the time!");
  }

  m_rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (m_period_time < m_active_time)
  {
    Serial.println("Active time must be shorter than period time");
    while (true)
    {}
  }
}

/**
 * @brief main loop
 */
void loop()
{
  static unsigned long last_loop_time = 0;
  unsigned long loop_time = millis();
  if (loop_time - last_loop_time > m_refresh_time_ms)
  {
    DateTime now = m_rtc.now();
    Serial.print(now.hour(), DEC);
    Serial.print(":");
    Serial.print(now.minute(), DEC);
    Serial.print(":");
    Serial.println(now.second(), DEC);
    last_loop_time = millis();

    static uint16_t last_active = min_calculate(now);
    static bool is_turn_on = false;

    if ((!is_turn_on) && ((min_calculate(now) - last_active) >= m_period_time))
    {
      Serial.println("Start");
      digitalWrite(m_output_pin, HIGH);
      last_active = min_calculate(now);
      is_turn_on = true;
    }

    if (is_turn_on && ((min_calculate(now) - last_active) >= m_active_time))
    {
      Serial.println("Stop");
      digitalWrite(m_output_pin, LOW);
      is_turn_on = false;
    }
  }
}