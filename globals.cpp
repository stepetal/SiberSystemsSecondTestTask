#include "globals.h"


int GLB::number_of_digits(int number)
{
    int digits = 0;
    if (number < 0)
    {
        return 0;
    }
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

int GLB::round_to_decade(int value)
{
    int ceil_value{0};
    int digits = number_of_digits(value);
    if(digits != 0)
    {
        if(digits == 1)
        {
            ceil_value = 10;
            return ceil_value;
        }
        int division_factor = 10 * (digits - 1);
        ceil_value = (int)(std::ceil((double)value / double(division_factor)) * (double)division_factor);
    }
    else
    {
        return 0;
    }
    return ceil_value;
}

double GLB::get_row_height_in_vh_units(int max_coord_y)
{
    double row_height_in_vh;
    row_height_in_vh = (double)10 / (double)(max_coord_y / 10);
    return row_height_in_vh;
}

double GLB::get_column_width_in_percentage(int max_coord_x)
{
    return std::floor((double)100 / max_coord_x);
}
