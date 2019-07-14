#pragma once

struct Time
{
  Time(unsigned int hours, unsigned int minutes, unsigned int seconds) 
  : hours(hours)
  , minutes(minutes)
  , seconds(seconds) {}

  Time() {}

  unsigned int hours;
  unsigned int minutes;
  unsigned int seconds;
  unsigned int millis;

  void addMillis(unsigned int millis) {
    this->millis += millis;

    seconds += this->millis / 1000;
    this->millis = this->millis % 1000;
    minutes += seconds / 60;
    seconds = seconds % 60;
    hours += minutes / 60;
    minutes = minutes % 60;    
    hours = hours % 24;
  }

  String toString() {
    return String() + hours + ":" + minutes + ":" + seconds;
  }
};