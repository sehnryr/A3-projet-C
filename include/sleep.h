#ifdef _WIN32
#include <Windows.h>
#else
#define __USE_XOPEN_EXTENDED
#include <unistd.h>
#endif

#ifndef SLEEP_H
#define SLEEP_H

/**
 * @brief Attend un nombre de millisecondes.
 *
 * @param ms Nombre de millisecondes à attendre.
 */
void msleep(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

#endif // SLEEP_H