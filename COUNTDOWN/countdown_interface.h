#ifndef COUNTDOWN_INTERFACE_H
#define COUNTDOWN_INTERFACE_H

#include "STD_TYPES.h"

/**
 * @brief Initializes the countdown timer module.
 *        Configures the LCD, buttons, and initializes TWI for RTC if used.
 */
void countdown_init(void);

/**
 * @brief Starts a countdown timer with the specified initial time.
 * @param initial_hours Initial hours for the countdown timer.
 * @param initial_minutes Initial minutes for the countdown timer.
 * @param initial_seconds Initial seconds for the countdown timer.
 */
void countdown(u8 initial_hours, u8 initial_minutes, u8 initial_seconds);

/**
 * @brief Updates the LCD display with the current countdown time.
 *        Displays hours, minutes, and seconds in HH:MM:SS format.
 * @param hours Current hour value to display.
 * @param minutes Current minute value to display.
 * @param seconds Current second value to display.
 */
void update_display(u8 hours, u8 minutes, u8 seconds);

#endif // COUNTDOWN_INTERFACE_H
