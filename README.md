# rtc_cyclical_relay

Simple time relay based on Arduino and RTC

- [About](#About)
- [Scheme](#Scheme)
- [IDE](#IDE)

## About

To config project for own needs You should change (in src/main.cpp):

```cpp
const uint16_t m_period_time = 15; ///< period when relay is turning on
const uint16_t m_active_time = 2; ///< how long relay is turned on
```

From start, it's turning on relay after 15 minutes, next after 2 minutes turn off, and after next 15 minutes turn on in the loop
<br><br>
Setting the time is executing when the project is built and uploaded to the board with the connected RTC
<br><br>
If you want additional information delete ; in
paltformio.ini

```cpp
;build_flags = -D DEBUG
```

It isn't work for RTC_DS3231

## Scheme

You can use ready RTC module
![alt text](https://github.com/InzynierDomu/rtc_relay/blob/main/schem_2.PNG)
<br>
or use chip with other elements.
![alt text](https://github.com/InzynierDomu/rtc_relay/blob/main/schem_1.PNG)

## IDE

The project is prepared for the Platform IO environment. A video on how to install such an environment can be watched on this [video](https://youtu.be/Em9NuebT2Kc).
<br><br>
Formatting is executed using clang-format. The description of the tool configuration is in the [video](https://youtu.be/xxuaOG0WjIE).
<br><br>
The code contains a comment prepared for doxygen, their use is described in the [video](https://youtu.be/1YKJtrCsPD4).
