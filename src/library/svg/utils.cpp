#include "svg/utils.h"

#include <math.h>

bool Ganash::Svg::Utils::ParseNumber(const xmlChar*& ptr, const xmlChar *end, float& number, bool skip)
{
    int   len      = 0;
    int   sign     = 1;
    float integer  = 0;
    float decimal  = 0;
    float frac     = 1.0;
    float exponent = 0;
    int   expsign  = 1;
    const xmlChar *string = ptr;

    if (!string) {
        return false;
    }

    // read the sign
    if (*ptr == '+')
    {
        ptr++;
    }
    else if (*ptr == '-')
    {
        ptr++;
        sign = -1;
    }

    if(ptr == end)
    {
        return false;
    }

    // First charactere must be a digit or a dot
    if((*ptr < '0' || '9' < *ptr) && *ptr!='.')
    {
        return false;
    }

    // read the integer part, build right-to-left
    const xmlChar *ptrStartIntPart = ptr;
    while (ptr < end && '0' <= *ptr && *ptr <= '9')
    {
        ++ptr; // Advance to first non-digit.
    }

    if (ptr != ptrStartIntPart)
    {
        const xmlChar* ptrScanIntPart = ptr - 1;
        float multiplier = 1;
        while (ptrScanIntPart >= ptrStartIntPart) {
            integer += multiplier * static_cast<float>(*(ptrScanIntPart--) - '0');
            multiplier *= 10;
        }
        // TODO
        // Bail out early if this overflows.
        //if (!isValidRange(integer))
        //    return false;
    }

    // read the decimals
    if (ptr < end && *ptr == '.')
    {
        ptr++;

        // There must be a least one digit following the .
        if (ptr >= end || *ptr < '0' || '9' < *ptr )
        {
            return false;
        }

        while (ptr < end && *ptr >= '0' && *ptr <= '9')
        {
            decimal += (*(ptr++) - '0') * (frac *= static_cast<float>(0.1));
        }
    }


    // read the exponent part
    if (ptr != string && ptr + 1 < end && (*ptr == 'e' || *ptr == 'E')
        && (ptr[1] != 'x' && ptr[1] != 'm'))
    {
        ptr++;

        // read the sign of the exponent
        if (*ptr == '+')
        {
            ptr++;
        }
        else if (*ptr == '-')
        {
            ptr++;
            expsign = -1;
        }

        // There must be an exponent
        if (ptr >= end || *ptr < '0' || *ptr > '9')
        {
            return false;
        }

        while (ptr < end && *ptr >= '0' && *ptr <= '9')
        {
            exponent *= static_cast<float>(10);
            exponent += *ptr - '0';
            ptr++;
        }
        // TODO
        // Make sure exponent is valid.
        //if (!isValidRange(exponent) || exponent > std::numeric_limits<FloatType>::max_exponent)
        //    return false;
    }

    // TODO use this->number || this->value But
    number = integer + decimal;
    number *= sign;

    if (exponent)
        number *= static_cast<float>(pow(10.0, expsign * static_cast<int>(exponent)));

    // TODO
    // Don't return Infinity() or NaN().
    //if (!isValidRange(number))
    //    return false;

    if (string == ptr)
        return false;

    // TODO
    //if (skip)
    //    skipOptionalSVGSpacesOrDelimiter(ptr, end);

    return true;
}
