/**
 * @file    set_pixel.c
 * @brief   set single pixel value
 *
 *
 */


#include "CommandLineInterface/CLIcore.h"
#include "COREMOD_memory/COREMOD_memory.h"

imageID arith_set_pixel(
    const char *ID_name,
    double      value,
    long        x,
    long        y
)
{
    imageID  ID;
    uint32_t naxes[2];
    uint8_t  datatype;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxes[0] = data.image[ID].md[0].size[0];
    naxes[1] = data.image[ID].md[0].size[1];

    //  printf("Setting pixel %ld %ld of image %s [%ld] to %f\n", x, y, ID_name, ID, (float) value);

    data.image[ID].md[0].write = 1;
    if(datatype == _DATATYPE_FLOAT)
    {
        data.image[ID].array.F[y * naxes[0] + x] = (float) value;
        //    printf("float -> %f\n", data.image[ID].array.F[y*naxes[0]+x]);
    }
    else if(datatype == _DATATYPE_DOUBLE)
    {
        data.image[ID].array.D[y * naxes[0] + x] = value;
    }
    else if(datatype == _DATATYPE_UINT8)
    {
        data.image[ID].array.UI8[y * naxes[0] + x] = (uint8_t) value;
    }
    else if(datatype == _DATATYPE_UINT16)
    {
        data.image[ID].array.UI16[y * naxes[0] + x] = (uint16_t) value;
    }
    else if(datatype == _DATATYPE_UINT32)
    {
        data.image[ID].array.UI32[y * naxes[0] + x] = (uint32_t) value;
    }
    else if(datatype == _DATATYPE_UINT64)
    {
        data.image[ID].array.UI64[y * naxes[0] + x] = (uint64_t) value;
    }
    else if(datatype == _DATATYPE_INT8)
    {
        data.image[ID].array.SI8[y * naxes[0] + x] = (int8_t) value;
    }
    else if(datatype == _DATATYPE_INT16)
    {
        data.image[ID].array.SI16[y * naxes[0] + x] = (int16_t) value;
    }
    else if(datatype == _DATATYPE_INT32)
    {
        data.image[ID].array.SI32[y * naxes[0] + x] = (int32_t) value;
    }
    else if(datatype == _DATATYPE_INT64)
    {
        data.image[ID].array.SI64[y * naxes[0] + x] = (int64_t) value;
    }
    else
    {
        PRINT_ERROR("Wrong image type(s)\n");
        exit(EXIT_FAILURE);
    }
    data.image[ID].md[0].write = 0;
    data.image[ID].md[0].cnt0++;
    COREMOD_MEMORY_image_set_sempost(ID_name, -1);

    return ID;
}



imageID arith_set_pixel_1Drange(
    const char *ID_name,
    double      value,
    long        x,
    long        y
)
{
    imageID ID;
    uint32_t naxes[2];
    uint8_t datatype;
    long ii, iistart, iiend;


    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxes[0] = data.image[ID].md[0].size[0];
    naxes[1] = data.image[ID].md[0].size[1];
    iistart = x;
    iiend = y + 1;

    if(iistart < 0)
    {
        iistart = 0;
    }
    if(iistart >= naxes[0]*naxes[1])
    {
        iistart = naxes[0] * naxes[1];
    }

    if(iiend < 0)
    {
        iiend = 0;
    }
    if(iiend >= naxes[0]*naxes[1])
    {
        iiend = naxes[0] * naxes[1];
    }

    list_image_ID();
    printf("%ld -> %ld\n", iistart, iiend);
    fflush(stdout);

    data.image[ID].md[0].write = 1;
    if(datatype == _DATATYPE_FLOAT)
    {
        for(ii = iistart; ii < iiend; ii++)
        {
            data.image[ID].array.F[ii] = (float) value;
        }
    }
    else if(datatype == _DATATYPE_DOUBLE)
    {
        for(ii = iistart; ii < iiend; ii++)
        {
            data.image[ID].array.D[ii] = value;
        }
    }
    else
    {
        PRINT_ERROR("Wrong image type(s)\n");
        exit(0);
    }
    data.image[ID].md[0].write = 0;
    data.image[ID].md[0].cnt0++;
    COREMOD_MEMORY_image_set_sempost(ID_name, -1);

    return ID;
}




imageID arith_set_row(
    const char *ID_name,
    double      value,
    long        y
)
{
    imageID   ID;
    uint32_t  naxes[2];
    long      ii;
    uint8_t   datatype;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxes[0] = data.image[ID].md[0].size[0];
    naxes[1] = data.image[ID].md[0].size[1];

    data.image[ID].md[0].write = 1;
    if(datatype == _DATATYPE_FLOAT)
    {
        for(ii = 0; ii < naxes[0]; ii++)
        {
            data.image[ID].array.F[y * naxes[0] + ii] = value;
        }
    }
    else if(datatype == _DATATYPE_DOUBLE)
    {
        for(ii = 0; ii < naxes[0]; ii++)
        {
            data.image[ID].array.D[y * naxes[0] + ii] = value;
        }
    }
    else
    {
        PRINT_ERROR("Wrong image type(s)\n");
        exit(0);
    }

    data.image[ID].md[0].write = 0;
    data.image[ID].md[0].cnt0++;
    COREMOD_MEMORY_image_set_sempost(ID_name, -1);

    return ID;
}




imageID arith_set_col(
    const char *ID_name,
    double      value,
    long        x
)
{
    imageID  ID;
    uint32_t naxes[2];
    long     y;
    uint8_t  datatype;

    ID = image_ID(ID_name);
    naxes[0] = data.image[ID].md[0].size[0];
    naxes[1] = data.image[ID].md[0].size[1];
    datatype = data.image[ID].md[0].datatype;


    data.image[ID].md[0].write = 1;
    if(datatype == _DATATYPE_FLOAT)
    {
        for(y = 0; y < naxes[1]; y++)
        {
            data.image[ID].array.F[y * naxes[0] + x] = value;
        }
    }
    else if(datatype == _DATATYPE_DOUBLE)
    {
        for(y = 0; y < naxes[1]; y++)
        {
            data.image[ID].array.D[y * naxes[0] + x] = value;
        }
    }
    else
    {
        PRINT_ERROR("Wrong image type(s)\n");
        exit(0);
    }

    data.image[ID].md[0].write = 0;
    data.image[ID].md[0].cnt0++;
    COREMOD_MEMORY_image_set_sempost(ID_name, -1);


    return ID;
}




imageID arith_image_zero(
    const char *ID_name
)
{
    imageID ID;
    long nelem;

    ID = image_ID(ID_name);

    if(ID != -1)
    {
        nelem = data.image[ID].md[0].nelement;

        data.image[ID].md[0].write = 0;

        if(data.image[ID].md[0].datatype == _DATATYPE_FLOAT)
        {
            memset(data.image[ID].array.F, 0, SIZEOF_DATATYPE_FLOAT * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_DOUBLE)
        {
            memset(data.image[ID].array.D, 0, SIZEOF_DATATYPE_DOUBLE * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_INT8)
        {
            memset(data.image[ID].array.SI8, 0, SIZEOF_DATATYPE_INT8 * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_INT16)
        {
            memset(data.image[ID].array.SI16, 0, SIZEOF_DATATYPE_INT16 * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_INT32)
        {
            memset(data.image[ID].array.SI32, 0, SIZEOF_DATATYPE_INT32 * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_INT64)
        {
            memset(data.image[ID].array.SI64, 0, SIZEOF_DATATYPE_INT64 * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_UINT8)
        {
            memset(data.image[ID].array.UI8, 0, SIZEOF_DATATYPE_UINT8 * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_UINT16)
        {
            memset(data.image[ID].array.UI16, 0, SIZEOF_DATATYPE_UINT16 * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_UINT32)
        {
            memset(data.image[ID].array.UI32, 0, SIZEOF_DATATYPE_UINT32 * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_UINT64)
        {
            memset(data.image[ID].array.UI64, 0, SIZEOF_DATATYPE_UINT64 * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_COMPLEX_FLOAT)
        {
            memset(data.image[ID].array.CF, 0, SIZEOF_DATATYPE_COMPLEX_FLOAT * nelem);
        }
        else if(data.image[ID].md[0].datatype == _DATATYPE_COMPLEX_DOUBLE)
        {
            memset(data.image[ID].array.CD, 0, SIZEOF_DATATYPE_COMPLEX_DOUBLE * nelem);
        }
        else
        {
            PRINT_ERROR("cannot detect image type for image %s",
                         ID_name);
            exit(0);
        }
        data.image[ID].md[0].write = 0;
        data.image[ID].md[0].cnt0++;
        COREMOD_MEMORY_image_set_sempost(ID_name, -1);
    }

    return(ID);
}

