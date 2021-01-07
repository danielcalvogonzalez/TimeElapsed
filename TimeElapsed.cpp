/**
 * @file timeElapsed.cpp
 * 
 * @section description Description
 * Lleva la gestión del tiempo medido en días, horas, minutos y segundos
 * desde un momento dado que es inicializada.
 * 
 * Se debe llamar regularmente la función **loopTimeElapsed()** para que actualice el tiempo
 * transcurrido y llamar a la función **getTimeElapsed()** cuando se quiera obtener una
 * cadena de tiempo con el citado tiempo.
 * 
 * @author Daniel Calvo Gonzalez
 *
 */
#include <Arduino.h>
#include "TimeElapsed.h"

/**
  * Constructor de la clase TimeElapsed
  * 
  * @param days		Número de días
  * @param hours	Número de horas
  * @param minutes	Número de minutos
  * @param seconds	Número de segundos
  */
TimeElapsed::TimeElapsed(byte days, byte hours, byte minutes, byte seconds) {
  _days = days;
  _hours = hours;
  _minutes = minutes;
  _seconds = seconds;
}

/**
  * Devuelve el número de segundos transcurridos.
  *
  * @return el número de segundos transcurridos
  */
byte TimeElapsed::getSeconds() {
  loopTimeElapsed();
  return _seconds;
}

/**
  * Devuelve el número de minutos transcurridos.
  *
  * @return el número de minutos transcurridos
  */
byte TimeElapsed::getMinutes() {
  loopTimeElapsed();
  return _minutes;
}

/**
  * Devuelve el número de horas transcurridas.
  *
  * @return el número de horas transcurridas
  */
byte TimeElapsed::getHours() {
  loopTimeElapsed();
  return _hours;
}

/**
  * Devuelve el número de dias transcurridos.
  *
  * @return el número de dias transcurridos
  */
byte TimeElapsed::getDays() {
  loopTimeElapsed();
  return _days;
}

/**
  * Función **interna** para actualizar los contadores internos de tiempo
  * transcurrido.
  *
  * @param nTicks	Contiene el número de segundos a incrementar
  */
void TimeElapsed::update(unsigned int nTicks) {
  unsigned int carrier;

  carrier = 0;
  _seconds += nTicks;
  if (_seconds >= 60) {
    carrier = _seconds / 60;
    _seconds %= 60;

    _minutes += carrier;
    if (_minutes >= 60) {
      carrier = _minutes / 60;
      _minutes %= 60;

      _hours += carrier;
      if (_hours >= 24) {
        carrier = _hours / 24;
        _hours %= 24;

        _days += carrier;
      }
    }
  }
}

/**
  * Reinicializa los contadores de tiempo transcurrido a 0.
  *
  */
void TimeElapsed::reset() {
  _seconds = _minutes = _hours = _days = 0;
}

/**
  * Devuelve una cadena de texto con el tiempo transcurrido en el formato
  * DD:HH:MM:SS.
  *
  * @param buffer	Puntero al buffer donde se grabará la cadena de texto.
  * @param nSizeBuffer	Longitud en bytes del buffer.
  */
void TimeElapsed::getTimeElapsed(char *buffer, int nSizeBuffer) {

  loopTimeElapsed();
  if (nSizeBuffer < MAX_LEN_TIMEELAPSED) {
    buffer[0] = '\0';
    return;
  }
  snprintf(buffer, nSizeBuffer, "%02d:%02d:%02d:%02d", _days, _hours, _minutes, _seconds);
}

/**
  * Función para actualizar los contadores internos de tiempo transcurrido.
  */
void TimeElapsed::loopTimeElapsed() {
  unsigned long now;
  unsigned int incremento;
  unsigned int resto;

  now = millis();
  if (now - lastUpdate > 1000) {
    incremento = (now - lastUpdate) / 1000;
    resto = (now - lastUpdate) % 1000;
    lastUpdate = now - resto;
    update(incremento);
  }
}
