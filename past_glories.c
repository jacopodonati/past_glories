/*
 * past_glories
 * Copyright (C) 2024 Jacopo Donati
 *
 * Questo programma è software libero: è possibile ridistribuirlo e/o modificarlo
 * secondo i termini della GNU General Public License come pubblicata dalla
 * Free Software Foundation, sia la versione 3 della Licenza, sia (a vostra scelta)
 * qualsiasi versione successiva.
 *
 * Questo programma è distribuito nella speranza che possa essere utile,
 * ma SENZA ALCUNA GARANZIA; senza neppure la garanzia implicita di
 * COMMERCIABILITÀ o IDONEITÀ PER UN PARTICOLARE SCOPO. Vedere la
 * GNU General Public License per maggiori dettagli.
 *
 * Dovreste aver ricevuto una copia della GNU General Public License
 * insieme a questo programma. In caso contrario, vedere <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int get_day_of_week(int year, int month, int day) {
    if (month < 3) {
        month += 12;
        year--;
    }
    return (day + 13*(month+1)/5 + year + year/4 - year/100 + year/400) % 7;
}

bool same_calendar(int year1, int year2) {
    if (is_leap_year(year1) != is_leap_year(year2)) {
        return false;
    }

    for (int month = 1; month <= 12; month++) {
        if (get_day_of_week(year1, month, 1) != get_day_of_week(year2, month, 1)) {
            return false;
        }
    }

    return true;
}

bool is_valid_integer(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2 || !is_valid_integer(argv[1])) {
        return 1;
    }

    int target_year = atoi(argv[1]);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900;

    for (int year = 1900; year < current_year; year++) {
        if (same_calendar(year, target_year)) {
            printf("%d\n", year);
        }
    }

    return 0;
}
