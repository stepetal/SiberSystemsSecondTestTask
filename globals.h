#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>
#include <type_traits>

namespace GLB
{
    int number_of_digits(int number);
    /*
     *
     * Round integer value to the closest decade (i.e. 19 -> 20, 26 -> 30)
     *
     */
    int round_to_decade(int value);

    /*
     *
     * Calculates height of the row in vh units of font size (https://www.w3schools.com/cssref/css_units.asp)
     *
     */
    double get_row_height_in_vh_units(int max_coord_y);

    /*
     *
     * Calculates column width in percentage
     *
     */
     double get_column_width_in_percentage(int max_coord_x);
}

#endif // GLOBALS_H
