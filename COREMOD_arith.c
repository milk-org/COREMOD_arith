/**
 * @file    COREMOD_arith.c
 * @brief   Arithmeric operations on images
 *
 * Addition, multiplication and much more
 *
 *
 */


/* ================================================================== */
/* ================================================================== */
/*            MODULE INFO                                             */
/* ================================================================== */
/* ================================================================== */

// module default short name
// all CLI calls to this module functions will be <shortname>.<funcname>
// if set to "", then calls use <funcname>
#define MODULE_SHORTNAME_DEFAULT ""

// Module short description
#define MODULE_DESCRIPTION       "Image arithmetic operations"

// Application to which module belongs
#define MODULE_APPLICATION       "milk"






#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

#include <fitsio.h>


#ifdef _OPENMP
#include <omp.h>
#define OMP_NELEMENT_LIMIT 1000000
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "CommandLineInterface/CLIcore.h"
#include "COREMOD_memory/COREMOD_memory.h"
#include "COREMOD_tools/COREMOD_tools.h"

#include "COREMOD_arith/COREMOD_arith.h"

#define SBUFFERSIZE 1000

//extern DATA data;

static char errmsg_arith[SBUFFERSIZE];







/* ================================================================== */
/* ================================================================== */
/*            INITIALIZE LIBRARY                                      */
/* ================================================================== */
/* ================================================================== */

// Module initialization macro in CLIcore.h
// macro argument defines module name for bindings
//
INIT_MODULE_LIB(COREMOD_arith)



/* ================================================================== */
/* ================================================================== */
/*            COMMAND LINE INTERFACE (CLI) FUNCTIONS                  */
/* ================================================================== */
/* ================================================================== */


// CLI commands
//
// function CLI_checkarg used to check arguments
// 1: float
// 2: long
// 3: string
// 4: existing image
//


errno_t arith_image_extract2D_cli()
{
    if(0
            + CLI_checkarg(1, CLIARG_IMG)
            + CLI_checkarg(2, CLIARG_STR_NOT_IMG)
            + CLI_checkarg(3, CLIARG_LONG)
            + CLI_checkarg(4, CLIARG_LONG)
            + CLI_checkarg(5, CLIARG_LONG)
            + CLI_checkarg(6, CLIARG_LONG)
            == 0)
    {
        arith_image_extract2D(
            data.cmdargtoken[1].val.string,
            data.cmdargtoken[2].val.string,
            data.cmdargtoken[3].val.numl,
            data.cmdargtoken[4].val.numl,
            data.cmdargtoken[5].val.numl,
            data.cmdargtoken[6].val.numl);

        return CLICMD_SUCCESS;
    }
    else
    {
        return CLICMD_INVALID_ARG;
    }
}


errno_t arith_image_extract3D_cli()
{
    if(0
            + CLI_checkarg(1, CLIARG_IMG)
            + CLI_checkarg(2, CLIARG_STR_NOT_IMG)
            + CLI_checkarg(3, CLIARG_LONG)
            + CLI_checkarg(4, CLIARG_LONG)
            + CLI_checkarg(5, CLIARG_LONG)
            + CLI_checkarg(6, CLIARG_LONG)
            + CLI_checkarg(7, CLIARG_LONG)
            + CLI_checkarg(8, CLIARG_LONG)
            == 0)
    {
        arith_image_extract3D(
            data.cmdargtoken[1].val.string,
            data.cmdargtoken[2].val.string,
            data.cmdargtoken[3].val.numl,
            data.cmdargtoken[4].val.numl,
            data.cmdargtoken[5].val.numl,
            data.cmdargtoken[6].val.numl,
            data.cmdargtoken[7].val.numl,
            data.cmdargtoken[8].val.numl);

        return CLICMD_SUCCESS;
    }
    else
    {
        return 1;
    }
}


errno_t arith_set_pixel_cli()
{
    if(0
            + CLI_checkarg(1, CLIARG_IMG)
            + CLI_checkarg(2, CLIARG_FLOAT)
            + CLI_checkarg(3, CLIARG_LONG)
            + CLI_checkarg(4, CLIARG_LONG)
            == 0)
    {
        arith_set_pixel(
            data.cmdargtoken[1].val.string,
            data.cmdargtoken[2].val.numf,
            data.cmdargtoken[3].val.numl,
            data.cmdargtoken[4].val.numl);

        return CLICMD_SUCCESS;
    }
    else
    {
        return 1;
    }
}


errno_t arith_set_pixel_1Drange_cli()
{
    if(0
            + CLI_checkarg(1, CLIARG_IMG)
            + CLI_checkarg(2, CLIARG_FLOAT)
            + CLI_checkarg(3, CLIARG_LONG)
            + CLI_checkarg(4, CLIARG_LONG)
            == 0)
    {
        arith_set_pixel_1Drange(
            data.cmdargtoken[1].val.string,
            data.cmdargtoken[2].val.numf,
            data.cmdargtoken[3].val.numl,
            data.cmdargtoken[4].val.numl);

        return CLICMD_SUCCESS;
    }
    else
    {
        return 1;
    }
}


errno_t arith_set_row_cli()
{
    if(0
            + CLI_checkarg(1, CLIARG_IMG)
            + CLI_checkarg(2, CLIARG_FLOAT)
            + CLI_checkarg(3, CLIARG_LONG)
            == 0)
    {
        arith_set_row(
            data.cmdargtoken[1].val.string,
            data.cmdargtoken[2].val.numf,
            data.cmdargtoken[3].val.numl);

        return CLICMD_SUCCESS;
    }
    else
    {
        return 1;
    }
}


errno_t arith_set_col_cli()
{
    if(0
            + CLI_checkarg(1, CLIARG_IMG)
            + CLI_checkarg(2, CLIARG_FLOAT)
            + CLI_checkarg(3, CLIARG_LONG)
            == 0)
    {
        arith_set_col(
            data.cmdargtoken[1].val.string,
            data.cmdargtoken[2].val.numf,
            data.cmdargtoken[3].val.numl);

        return CLICMD_SUCCESS;
    }
    else
    {
        return 1;
    }
}


errno_t arith_image_zero_cli()
{
    if(0
            + CLI_checkarg(1, CLIARG_IMG)
            == 0)
    {
        arith_image_zero(data.cmdargtoken[1].val.string);

        return CLICMD_SUCCESS;
    }
    else
    {
        return 1;
    }
}


errno_t arith_image_trunc_cli()
{
    if(0
            + CLI_checkarg(1, CLIARG_IMG)
            + CLI_checkarg(2, CLIARG_FLOAT)
            + CLI_checkarg(3, CLIARG_FLOAT)
            + CLI_checkarg(4, CLIARG_STR_NOT_IMG)
            == 0)
    {
        arith_image_trunc(
            data.cmdargtoken[1].val.string,
            data.cmdargtoken[2].val.numf,
            data.cmdargtoken[3].val.numf,
            data.cmdargtoken[4].val.string);

        return CLICMD_SUCCESS;
    }
    else
    {
        return 1;
    }
}


errno_t arith_image_merge3D_cli()
{
    if(0
            + CLI_checkarg(1, CLIARG_IMG)
            + CLI_checkarg(2, CLIARG_IMG)
            + CLI_checkarg(3, CLIARG_STR_NOT_IMG)
            == 0)
    {
        arith_image_merge3D(
            data.cmdargtoken[1].val.string,
            data.cmdargtoken[2].val.string,
            data.cmdargtoken[3].val.string);

        return CLICMD_SUCCESS;
    }
    else
    {
        return 1;
    }
}






static errno_t init_module_CLI()
{

    RegisterCLIcommand(
        "cmemtestf",
        __FILE__,
        COREMOD_MEMORY_testfunc,
        "testfunc",
        "no arg",
        "cmemtestf",
        "COREMOD_MEMORY_testfunc()");

    RegisterCLIcommand(
        "extractim",
        __FILE__,
        arith_image_extract2D_cli,
        "crop 2D image",
        "<input image> <output image> <sizex> <sizey> <xstart> <ystart>",
        "extractim im ime 256 256 100 100",
        "int arith_image_extract2D(const char *in_name, const char *out_name, long size_x, long size_y, long xstart, long ystart)");



    RegisterCLIcommand(
        "extract3Dim",
        __FILE__,
        arith_image_extract3D_cli,
        "crop 3D image",
        "<input image> <output image> <sizex> <sizey> <sizez> <xstart> <ystart> <zstart>",
        "extractim im ime 256 256 5 100 100 0",
        "int arith_image_extract3D(const char *in_name, const char *out_name, long size_x, long size_y, long size_z, long xstart, long ystart, long zstart)");


    RegisterCLIcommand(
        "setpix",
        __FILE__,
        arith_set_pixel_cli,
        "set pixel value",
        "<input image> <value> <x> <y>",
        "setpix im 1.24 100 100",
        "int arith_set_pixel(const char *ID_name, double value, long x, long y)");


    RegisterCLIcommand(
        "setpix1Drange",
        __FILE__,
        arith_set_pixel_1Drange_cli,
        "set pixel value for 1D area",
        "<input image> <value> <first pix> <last pix>",
        "setpix im 1.24 10 200",
        "int arith_set_pixel_1Drange(const char *ID_name, double value, long x, long y)");


    RegisterCLIcommand(
        "setrow",
        __FILE__,
        arith_set_row_cli,
        "set pixel row value",
        "<input image> <value> <row>",
        "setrow im 1.24 100",
        "int arith_set_row(const char *ID_name, double value, long y)");


    RegisterCLIcommand(
        "setcol",
        __FILE__,
        arith_set_col_cli,
        "set pixel column value",
        "<input image> <value> <col>",
        "setcol im 1.24 100",
        "int arith_set_col(const char *ID_name, double value, long x)");


    RegisterCLIcommand(
        "imzero",
        __FILE__,
        arith_image_zero_cli,
        "set pixels to zero",
        "<input image>",
        "imzero im",
        "int arith_image_zero(const char *ID_name)");


    RegisterCLIcommand(
        "imtrunc",
        __FILE__,
        arith_image_trunc_cli,
        "trucate pixel values",
        "<input image> <min> <max> <output image>",
        "imtrunc im 0.0 1.0 out",
        "arith_image_trunc(const char *ID_name, double f1, double f2, const char *ID_out)");


    RegisterCLIcommand(
        "merge3d",
        __FILE__,
        arith_image_merge3D_cli,
        "merge two 3D cubes into one",
        "<input cube 1> <input cube 2> <output cube>",
        "merge3d imc1 imc2 imcout",
        "long arith_image_merge3D(const char *ID_name1, const char *ID_name2, const char *IDout_name)");



    // add atexit functions here

    return RETURN_SUCCESS;
}






errno_t init_COREMOD_arith()
{
    init_module_CLI();

    return RETURN_SUCCESS;
}






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
    int      nbchar;

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
    int n;
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
    int n;

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





imageID arith_image_crop(
    const char *ID_name,
    const char *ID_out,
    long       *start,
    long       *end,
    long        cropdim
)
{
    long naxis;
    imageID IDin;
    imageID IDout;
    long i;
    uint32_t *naxes = NULL;
    uint32_t *naxesout = NULL;
    uint8_t datatype;
    int n;

    long start_c[3];
    long end_c[3];

    for(i = 0; i < 3; i++)
    {
        start_c[i] = 0;
        end_c[i] = 0;
    }

    IDin = image_ID(ID_name);
    if(IDin == -1)
    {
        PRINT_ERROR("Missing input image = %s", ID_name);
        list_image_ID();
        exit(0);
    }

    naxis = data.image[IDin].md[0].naxis;
    if(naxis < 1)
    {
        PRINT_ERROR("naxis < 1");
        exit(0);
    }
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
        PRINT_ERROR("malloc() error, naxis = %ld", naxis);
        exit(0);
    }

    naxesout  = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxesout == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }

    datatype = data.image[IDin].md[0].datatype;

    naxes[0] = 0;
    naxesout[0] = 0;
    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[IDin].md[0].size[i];
        naxesout[i] = end[i] - start[i];
    }
    IDout = create_image_ID(ID_out, naxis, naxesout, datatype, data.SHARED_DFT,
                            data.NBKEWORD_DFT);

    start_c[0] = start[0];
    if(start_c[0] < 0)
    {
        start_c[0] = 0;
    }
    end_c[0] = end[0];
    if(end_c[0] > naxes[0])
    {
        end_c[0] = naxes[0];
    }
    if(naxis > 1)
    {
        start_c[1] = start[1];
        if(start_c[1] < 0)
        {
            start_c[1] = 0;
        }
        end_c[1] = end[1];
        if(end_c[1] > naxes[1])
        {
            end_c[1] = naxes[1];
        }
    }
    if(naxis > 2)
    {
        start_c[2] = start[2];
        if(start_c[2] < 0)
        {
            start_c[2] = 0;
        }
        end_c[2] = end[2];
        if(end_c[2] > naxes[2])
        {
            end_c[2] = naxes[2];
        }
    }


    printf("CROP: \n");
    for(i = 0; i < 3; i++)
    {
        printf("axis %ld: %ld -> %ld\n", i, start_c[i], end_c[i]);
    }


    if(cropdim != naxis)
    {
        printf("Error (arith_image_crop): cropdim [%ld] and naxis [%ld] are different\n",
               cropdim, naxis);
    }


    if(naxis == 1)
    {
        if(datatype == _DATATYPE_FLOAT)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.F[ii - start[0]] = data.image[IDin].array.F[ii];
            }
        }
        else if(datatype == _DATATYPE_DOUBLE)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.D[ii - start[0]] = data.image[IDin].array.D[ii];
            }
        }
        else if(datatype == _DATATYPE_COMPLEX_FLOAT)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.CF[ii - start[0]].re = data.image[IDin].array.CF[ii].re;
                data.image[IDout].array.CF[ii - start[0]].im = data.image[IDin].array.CF[ii].im;
            }
        }
        else if(datatype == _DATATYPE_COMPLEX_DOUBLE)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.CD[ii - start[0]].re = data.image[IDin].array.CD[ii].re;
                data.image[IDout].array.CD[ii - start[0]].im = data.image[IDin].array.CD[ii].im;
            }
        }
        else if(datatype == _DATATYPE_UINT8)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.UI8[ii - start[0]] = data.image[IDin].array.UI8[ii];
            }
        }
        else if(datatype == _DATATYPE_UINT16)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.UI16[ii - start[0]] = data.image[IDin].array.UI16[ii];
            }
        }
        else if(datatype == _DATATYPE_UINT32)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.UI32[ii - start[0]] = data.image[IDin].array.UI32[ii];
            }
        }
        else if(datatype == _DATATYPE_UINT64)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.UI64[ii - start[0]] = data.image[IDin].array.UI64[ii];
            }
        }
        else if(datatype == _DATATYPE_INT8)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.SI8[ii - start[0]] = data.image[IDin].array.SI8[ii];
            }
        }
        else if(datatype == _DATATYPE_INT16)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.SI16[ii - start[0]] = data.image[IDin].array.SI16[ii];
            }
        }
        else if(datatype == _DATATYPE_INT32)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.SI32[ii - start[0]] = data.image[IDin].array.SI32[ii];
            }
        }
        else if(datatype == _DATATYPE_INT64)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
            {
                data.image[IDout].array.SI64[ii - start[0]] = data.image[IDin].array.SI64[ii];
            }
        }
        else
        {
            PRINT_ERROR("invalid data type");
            exit(0);
        }
    }
    if(naxis == 2)
    {
        if(datatype == _DATATYPE_FLOAT)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    data.image[IDout].array.F[(jj - start[1])*naxesout[0] + (ii - start[0])]
                        = data.image[IDin].array.F[jj * naxes[0] + ii];
        }
        else if(datatype == _DATATYPE_DOUBLE)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    data.image[IDout].array.D[(jj - start[1])*naxesout[0] + (ii - start[0])]
                        = data.image[IDin].array.D[jj * naxes[0] + ii];
        }
        else if(datatype == _DATATYPE_COMPLEX_FLOAT)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                {
                    data.image[IDout].array.CF[(jj - start[1])*naxesout[0] + (ii - start[0])].re
                        = data.image[IDin].array.CF[jj * naxes[0] + ii].re;
                    data.image[IDout].array.CF[(jj - start[1])*naxesout[0] + (ii - start[0])].im
                        = data.image[IDin].array.CF[jj * naxes[0] + ii].im;
                }
        }
        else if(datatype == _DATATYPE_COMPLEX_DOUBLE)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                {
                    data.image[IDout].array.CD[(jj - start[1])*naxesout[0] + (ii - start[0])].re
                        = data.image[IDin].array.CD[jj * naxes[0] + ii].re;
                    data.image[IDout].array.CD[(jj - start[1])*naxesout[0] + (ii - start[0])].im
                        = data.image[IDin].array.CD[jj * naxes[0] + ii].im;
                }
        }
        else if(datatype == _DATATYPE_UINT8)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    data.image[IDout].array.UI8[(jj - start[1])*naxesout[0] + (ii - start[0])]
                        = data.image[IDin].array.UI8[jj * naxes[0] + ii];
        }
        else if(datatype == _DATATYPE_UINT16)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    data.image[IDout].array.UI16[(jj - start[1])*naxesout[0] + (ii - start[0])]
                        = data.image[IDin].array.UI16[jj * naxes[0] + ii];
        }
        else if(datatype == _DATATYPE_UINT32)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    data.image[IDout].array.UI32[(jj - start[1])*naxesout[0] + (ii - start[0])]
                        = data.image[IDin].array.UI32[jj * naxes[0] + ii];
        }
        else if(datatype == _DATATYPE_UINT64)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    data.image[IDout].array.UI64[(jj - start[1])*naxesout[0] + (ii - start[0])]
                        = data.image[IDin].array.UI64[jj * naxes[0] + ii];
        }
        else if(datatype == _DATATYPE_INT8)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    data.image[IDout].array.SI8[(jj - start[1])*naxesout[0] + (ii - start[0])]
                        = data.image[IDin].array.SI8[jj * naxes[0] + ii];
        }
        else if(datatype == _DATATYPE_INT16)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    data.image[IDout].array.SI16[(jj - start[1])*naxesout[0] + (ii - start[0])]
                        = data.image[IDin].array.SI16[jj * naxes[0] + ii];
        }
        else if(datatype == _DATATYPE_INT32)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    data.image[IDout].array.SI32[(jj - start[1])*naxesout[0] + (ii - start[0])]
                        = data.image[IDin].array.SI32[jj * naxes[0] + ii];
        }
        else if(datatype == _DATATYPE_INT64)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    data.image[IDout].array.SI64[(jj - start[1])*naxesout[0] + (ii - start[0])]
                        = data.image[IDin].array.SI64[jj * naxes[0] + ii];
        }
        else
        {
            PRINT_ERROR("invalid data type");
            exit(0);
        }
    }
    if(naxis == 3)
    {
        //	printf("naxis = 3\n");
        if(datatype == _DATATYPE_FLOAT)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.F[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                  (jj - start[1])*naxesout[0] + (ii - start[0])]
                            = data.image[IDin].array.F[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii];
                    }
        }
        else if(datatype == _DATATYPE_DOUBLE)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.D[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                  (jj - start[1])*naxesout[0] + (ii - start[0])]
                            = data.image[IDin].array.D[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii];
                    }
        }
        else if(datatype == _DATATYPE_COMPLEX_FLOAT)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.CF[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                   (jj - start[1])*naxesout[0] + (ii - start[0])].re
                            = data.image[IDin].array.CF[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii].re;
                        data.image[IDout].array.CF[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                   (jj - start[1])*naxesout[0] + (ii - start[0])].im
                            = data.image[IDin].array.CF[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii].im;
                    }
        }
        else if(datatype == _DATATYPE_COMPLEX_DOUBLE)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.CD[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                   (jj - start[1])*naxesout[0] + (ii - start[0])].re
                            = data.image[IDin].array.CD[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii].re;
                        data.image[IDout].array.CD[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                   (jj - start[1])*naxesout[0] + (ii - start[0])].im
                            = data.image[IDin].array.CD[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii].im;
                    }
        }
        else if(datatype == _DATATYPE_UINT8)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.UI8[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                    (jj - start[1])*naxesout[0] + (ii - start[0])]
                            = data.image[IDin].array.UI8[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii];
                    }
        }
        else if(datatype == _DATATYPE_UINT16)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.UI16[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                     (jj - start[1])*naxesout[0] + (ii - start[0])]
                            = data.image[IDin].array.UI16[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii];
                    }
        }
        else if(datatype == _DATATYPE_UINT32)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.UI32[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                     (jj - start[1])*naxesout[0] + (ii - start[0])]
                            = data.image[IDin].array.UI32[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii];
                    }
        }
        else if(datatype == _DATATYPE_UINT64)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.UI64[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                     (jj - start[1])*naxesout[0] + (ii - start[0])]
                            = data.image[IDin].array.UI64[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii];
                    }
        }
        else if(datatype == _DATATYPE_INT8)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.SI8[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                    (jj - start[1])*naxesout[0] + (ii - start[0])]
                            = data.image[IDin].array.SI8[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii];
                    }
        }
        else if(datatype == _DATATYPE_INT16)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.SI16[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                     (jj - start[1])*naxesout[0] + (ii - start[0])]
                            = data.image[IDin].array.SI16[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii];
                    }
        }
        else if(datatype == _DATATYPE_INT32)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.SI32[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                     (jj - start[1])*naxesout[0] + (ii - start[0])]
                            = data.image[IDin].array.SI32[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii];
                    }
        }
        else if(datatype == _DATATYPE_INT64)
        {
            for(uint32_t ii = start_c[0]; ii < end_c[0]; ii++)
                for(uint32_t jj = start_c[1]; jj < end_c[1]; jj++)
                    for(uint32_t kk = start_c[2]; kk < end_c[2]; kk++)
                    {
                        data.image[IDout].array.SI64[(kk - start[2])*naxesout[0]*naxesout[1] +
                                                     (jj - start[1])*naxesout[0] + (ii - start[0])]
                            = data.image[IDin].array.SI64[kk * naxes[0] * naxes[1] + jj * naxes[0] + ii];
                    }
        }
        else
        {
            PRINT_ERROR("invalid data type");
            exit(0);
        }
    }

    free(naxesout);
    free(naxes);

    return IDout;
}





imageID arith_image_extract2D(
    const char *in_name,
    const char *out_name,
    long        size_x,
    long        size_y,
    long        xstart,
    long        ystart
)
{
    long    *start = NULL;
    long    *end = NULL;
    int      naxis;
    imageID  ID;
    imageID  IDout;
    uint_fast8_t k;

    ID = image_ID(in_name);
    naxis = data.image[ID].md[0].naxis;


    start = (long *) malloc(sizeof(long) * naxis);
    if(start == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }

    end = (long *) malloc(sizeof(long) * naxis);
    if(end == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }

    for(k = 0; k < naxis; k++)
    {
        start[k] = 0;
        end[k] = data.image[ID].md[0].size[k];
    }

    start[0] = xstart;
    start[1] = ystart;
    end[0] = xstart + size_x;
    end[1] = ystart + size_y;
    IDout = arith_image_crop(in_name, out_name, start, end, naxis);

    free(start);
    free(end);

    return IDout;
}






imageID arith_image_extract3D(
    const char *in_name,
    const char *out_name,
    long        size_x,
    long        size_y,
    long        size_z,
    long        xstart,
    long        ystart,
    long        zstart
)
{
    imageID   IDout;
    long     *start = NULL;
    long     *end = NULL;

    start = (long *) malloc(sizeof(long) * 3);
    if(start == NULL)
    {
        PRINT_ERROR("malloc() error");
        printf("params: %s %s %ld %ld %ld %ld %ld %ld \n", in_name, out_name, size_x,
               size_y, size_z, xstart, ystart, zstart);
        exit(0);
    }

    end = (long *) malloc(sizeof(long) * 3);
    if(end == NULL)
    {
        PRINT_ERROR("malloc() error");
        printf("params: %s %s %ld %ld %ld %ld %ld %ld \n", in_name, out_name, size_x,
               size_y, size_z, xstart, ystart, zstart);
        exit(0);
    }

    start[0] = xstart;
    start[1] = ystart;
    start[2] = zstart;
    end[0] = xstart + size_x;
    end[1] = ystart + size_y;
    end[2] = zstart + size_z;
    IDout = arith_image_crop(in_name, out_name, start, end, 3);

    free(start);
    free(end);

    return IDout;
}



// join two cubes
imageID arith_image_merge3D(
    const char *ID_name1,
    const char *ID_name2,
    const char *IDout_name
)
{
    imageID ID1;
    imageID ID2;
    imageID IDout;
    long xsize, ysize, zsize1, zsize2;
    void *mapv;

    ID1 = image_ID(ID_name1);
    ID2 = image_ID(ID_name2);

    xsize = data.image[ID1].md[0].size[0];
    ysize = data.image[ID1].md[0].size[1];

    if(data.image[ID1].md[0].naxis == 2)
    {
        zsize1 = 1;
    }
    else
    {
        zsize1 = data.image[ID1].md[0].size[2];
    }

    if(data.image[ID2].md[0].naxis == 2)
    {
        zsize2 = 1;
    }
    else
    {
        zsize2 = data.image[ID2].md[0].size[2];
    }



    if((xsize != data.image[ID2].md[0].size[0])
            || (ysize != data.image[ID2].md[0].size[1]))
    {
        printf("ERROR: input images must have same x y sizes\n");
        printf("%s :  %ld %ld\n", ID_name1, xsize, ysize);
        printf("%s :  %ld %ld\n", ID_name2, (long) data.image[ID2].md[0].size[0],
               (long) data.image[ID2].md[0].size[1]);
        exit(0);
    }

    IDout = create_3Dimage_ID(IDout_name, xsize, ysize, zsize1 + zsize2);

    mapv = (void *) data.image[IDout].array.F;

    memcpy(mapv, (void *) data.image[ID1].array.F,
           sizeof(float)*xsize * ysize * zsize1);

    mapv += sizeof(float) * xsize * ysize * zsize1;
    memcpy(mapv, data.image[ID2].array.F, sizeof(float)*xsize * ysize * zsize2);

    return IDout;
}






double arith_image_total(
    const char *ID_name
)
{
    long double lvalue; // uses long double internally
    imageID ID;
    long ii;
    long nelement;
    uint8_t datatype;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;

    nelement = data.image[ID].md[0].nelement;

    lvalue = 0.0;

    if(datatype == _DATATYPE_UINT8)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.UI8[ii];
        }
    }
    else if(datatype == _DATATYPE_INT32)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.SI32[ii];
        }
    }
    else if(datatype == _DATATYPE_FLOAT)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.F[ii];
        }
    }
    else if(datatype == _DATATYPE_DOUBLE)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.D[ii];
        }
    }
    else if(datatype == _DATATYPE_UINT8)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.UI8[ii];
        }
    }
    else if(datatype == _DATATYPE_UINT16)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.UI16[ii];
        }
    }
    else if(datatype == _DATATYPE_UINT32)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.UI32[ii];
        }
    }
    else if(datatype == _DATATYPE_UINT64)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.UI64[ii];
        }
    }
    else if(datatype == _DATATYPE_INT8)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.SI8[ii];
        }
    }
    else if(datatype == _DATATYPE_INT16)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.SI16[ii];
        }
    }
    else if(datatype == _DATATYPE_INT32)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.SI32[ii];
        }
    }
    else if(datatype == _DATATYPE_INT64)
    {
        for(ii = 0; ii < nelement; ii++)
        {
            lvalue += (long double) data.image[ID].array.SI64[ii];
        }
    }
    else
    {
        PRINT_ERROR("invalid data type");
        exit(0);
    }

    double value;
    value = (double) lvalue;

    return(value);
}




double arith_image_mean(
    const char *ID_name
)
{
    double value;
    imageID ID;

    ID = image_ID(ID_name);

    value = (double)(arith_image_total(ID_name) / data.image[ID].md[0].nelement);

    return(value);
}


double arith_image_min(
    const char *ID_name
)
{
    imageID ID;
    long ii;
    long nelement;
    uint8_t datatype;
    int OK = 0;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;

    nelement = data.image[ID].md[0].nelement;


    if(datatype == _DATATYPE_FLOAT)
    {
        float value, value1;

        value = data.image[ID].array.F[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.F[ii];
            if(value1 < value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_DOUBLE)
    {
        double value, value1;

        value = data.image[ID].array.D[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.D[ii];
            if(value1 < value)
            {
                value = value1;
            }
        }
        OK = 1;
        return (value);
    }

    if(datatype == _DATATYPE_UINT8)
    {
        uint8_t value, value1;

        value = data.image[ID].array.UI8[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.UI8[ii];
            if(value1 < value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_UINT16)
    {
        uint16_t value, value1;

        value = data.image[ID].array.UI16[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.UI16[ii];
            if(value1 < value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_UINT32)
    {
        uint32_t value, value1;

        value = data.image[ID].array.UI32[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.UI32[ii];
            if(value1 < value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_UINT64)
    {
        uint64_t value, value1;

        value = data.image[ID].array.UI64[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.UI64[ii];
            if(value1 < value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_INT8)
    {
        int8_t value, value1;

        value = data.image[ID].array.SI8[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.SI8[ii];
            if(value1 < value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_INT16)
    {
        int16_t value, value1;

        value = (double) data.image[ID].array.SI16[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.SI16[ii];
            if(value1 < value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_INT32)
    {
        int32_t value, value1;

        value = data.image[ID].array.SI32[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.SI32[ii];
            if(value1 < value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_INT64)
    {
        int64_t value, value1;

        value = data.image[ID].array.SI64[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.SI64[ii];
            if(value1 < value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(OK == 0)
    {
        printf("Error : Invalid data format for arith_image_min\n");
    }

    return(0);
}



double arith_image_max(
    const char *ID_name
)
{
    imageID ID;
    long    ii;
    long    nelement;
    uint8_t datatype;
    int     OK = 0;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;

    nelement = data.image[ID].md[0].nelement;

    if(datatype == _DATATYPE_FLOAT)
    {
        float value, value1;

        value = data.image[ID].array.F[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.F[ii];
            if(value1 > value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_DOUBLE)
    {
        double value, value1;

        value = data.image[ID].array.D[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.D[ii];
            if(value1 > value)
            {
                value = value1;
            }
        }
        OK = 1;
        return (value);
    }

    if(datatype == _DATATYPE_UINT8)
    {
        uint8_t value, value1;

        value = data.image[ID].array.UI8[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.UI8[ii];
            if(value1 > value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_UINT16)
    {
        uint16_t value, value1;

        value = data.image[ID].array.UI16[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.UI16[ii];
            if(value1 > value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_UINT32)
    {
        uint32_t value, value1;

        value = data.image[ID].array.UI32[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.UI32[ii];
            if(value1 > value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_UINT64)
    {
        uint64_t value, value1;

        value = data.image[ID].array.UI64[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.UI64[ii];
            if(value1 > value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_INT8)
    {
        int8_t value, value1;

        value = data.image[ID].array.SI8[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.SI8[ii];
            if(value1 > value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_INT16)
    {
        int16_t value, value1;

        value = (double) data.image[ID].array.SI16[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.SI16[ii];
            if(value1 > value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_INT32)
    {
        int32_t value, value1;

        value = data.image[ID].array.SI32[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.SI32[ii];
            if(value1 > value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }

    if(datatype == _DATATYPE_INT64)
    {
        int64_t value, value1;

        value = data.image[ID].array.SI64[0];
        for(ii = 0; ii < nelement; ii++)
        {
            value1 = data.image[ID].array.SI64[ii];
            if(value1 > value)
            {
                value = value1;
            }
        }
        OK = 1;
        return ((double) value);
    }
    if(OK == 0)
    {
        printf("Error : Invalid data format for arith_image_max\n");
    }

    return(0);
}





double arith_image_percentile(
    const char *ID_name,
    double      fraction
)
{
    imageID  ID;
    long     ii;
    double   value = 0;
    long    *arrayL = NULL;
    float   *arrayF = NULL;
    double  *arrayD = NULL;
    unsigned short *arrayU = NULL;
    long     nelement;
    uint8_t  datatype;
    int      atypeOK = 1;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;

    nelement = data.image[ID].md[0].nelement;


    switch(datatype)
    {

        case _DATATYPE_FLOAT :
            arrayF = (float *) malloc(sizeof(float) * nelement);
            if(arrayF == NULL)
            {
                PRINT_ERROR("malloc() error");
                exit(EXIT_FAILURE);
            }
            memcpy(arrayF, data.image[ID].array.F, sizeof(float)*nelement);
            quick_sort_float(arrayF, nelement);
            value = (double) arrayF[(long)(fraction * nelement)];
            free(arrayF);
            break;

        case _DATATYPE_DOUBLE :
            arrayD = (double *) malloc(sizeof(double) * nelement);
            if(arrayD == NULL)
            {
                PRINT_ERROR("malloc() error");
                exit(EXIT_FAILURE);
            }
            memcpy(arrayD, data.image[ID].array.D, sizeof(double)*nelement);
            quick_sort_double(arrayD, nelement);
            value = arrayD[(long)(fraction * nelement)];
            free(arrayD);
            break;



        case _DATATYPE_UINT8 :
            arrayU = (unsigned short *) malloc(sizeof(unsigned short) * nelement);
            if(arrayU == NULL)
            {
                PRINT_ERROR("malloc() error");
                exit(EXIT_FAILURE);
            }
            for(ii = 0; ii < nelement; ii++)
            {
                arrayU[ii] = data.image[ID].array.UI8[ii];
            }
            quick_sort_ushort(arrayU, nelement);
            value = arrayU[(long)(fraction * nelement)];
            free(arrayU);
            break;

        case _DATATYPE_UINT16 :
            arrayU = (unsigned short *) malloc(sizeof(unsigned short) * nelement);
            if(arrayU == NULL)
            {
                PRINT_ERROR("malloc() error");
                exit(EXIT_FAILURE);
            }
            for(ii = 0; ii < nelement; ii++)
            {
                arrayU[ii] = data.image[ID].array.UI16[ii];
            }
            quick_sort_ushort(arrayU, nelement);
            value = arrayU[(long)(fraction * nelement)];
            free(arrayU);
            break;

        case _DATATYPE_UINT32 :
            arrayL = (long *) malloc(sizeof(long) * nelement);
            if(arrayU == NULL)
            {
                PRINT_ERROR("malloc() error");
                exit(EXIT_FAILURE);
            }
            for(ii = 0; ii < nelement; ii++)
            {
                arrayL[ii] = data.image[ID].array.UI32[ii];
            }
            quick_sort_long(arrayL, nelement);
            value = arrayL[(long)(fraction * nelement)];
            free(arrayL);
            break;

        case _DATATYPE_UINT64 :
            arrayL = (long *) malloc(sizeof(long) * nelement);
            if(arrayU == NULL)
            {
                PRINT_ERROR("malloc() error");
                exit(EXIT_FAILURE);
            }
            for(ii = 0; ii < nelement; ii++)
            {
                arrayL[ii] = data.image[ID].array.UI64[ii];
            }
            quick_sort_long(arrayL, nelement);
            value = arrayL[(long)(fraction * nelement)];
            free(arrayL);
            break;


        case _DATATYPE_INT8 :
            arrayL = (long *) malloc(sizeof(long) * nelement);
            if(arrayL == NULL)
            {
                PRINT_ERROR("malloc() error");
                exit(EXIT_FAILURE);
            }
            for(ii = 0; ii < nelement; ii++)
            {
                arrayL[ii] = (long) data.image[ID].array.SI8[ii];
            }
            quick_sort_long(arrayL, nelement);
            value = (double) arrayL[(long)(fraction * nelement)];
            free(arrayL);
            break;

        case _DATATYPE_INT16 :
            arrayL = (long *) malloc(sizeof(long) * nelement);
            if(arrayL == NULL)
            {
                PRINT_ERROR("malloc() error");
                exit(EXIT_FAILURE);
            }
            for(ii = 0; ii < nelement; ii++)
            {
                arrayL[ii] = (long) data.image[ID].array.SI16[ii];
            }
            quick_sort_long(arrayL, nelement);
            value = (double) arrayL[(long)(fraction * nelement)];
            free(arrayL);
            break;

        case _DATATYPE_INT32 :
            arrayL = (long *) malloc(sizeof(long) * nelement);
            if(arrayL == NULL)
            {
                PRINT_ERROR("malloc() error");
                exit(EXIT_FAILURE);
            }
            for(ii = 0; ii < nelement; ii++)
            {
                arrayL[ii] = (long) data.image[ID].array.SI32[ii];
            }
            quick_sort_long(arrayL, nelement);
            value = (double) arrayL[(long)(fraction * nelement)];
            free(arrayL);
            break;

        case _DATATYPE_INT64 :
            arrayL = (long *) malloc(sizeof(long) * nelement);
            if(arrayL == NULL)
            {
                PRINT_ERROR("malloc() error");
                exit(EXIT_FAILURE);
            }
            for(ii = 0; ii < nelement; ii++)
            {
                arrayL[ii] = (long) data.image[ID].array.SI64[ii];
            }
            quick_sort_long(arrayL, nelement);
            value = (double) arrayL[(long)(fraction * nelement)];
            free(arrayL);
            break;

        default:
            PRINT_ERROR("Image type not supported");
            atypeOK = 0;
            break;
    }

    if(atypeOK == 0)
    {
        exit(EXIT_FAILURE);
    }

    return(value);
}


double arith_image_median(
    const char *ID_name
)
{
    double value = 0.0;

    value = arith_image_percentile(ID_name, 0.5);

    return(value);
}



long arith_image_dx(
    const char *ID_name,
    const char *IDout_name
)
{
    imageID ID;
    imageID IDout;
    uint32_t *naxes = NULL;
    long naxis;
    long ii, jj;
    uint8_t datatype;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxis = data.image[ID].md[0].naxis;
    if(naxis != 2)
    {
        PRINT_ERROR("Function only supports 2-D images\n");
        exit(0);
    }
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    naxes[0] = data.image[ID].md[0].size[0];
    naxes[1] = data.image[ID].md[0].size[1];

    IDout = create_image_ID(IDout_name, naxis, naxes, datatype, data.SHARED_DFT,
                            data.NBKEWORD_DFT);
    for(jj = 0; jj < naxes[1]; jj++)
    {
        for(ii = 1; ii < naxes[0] - 1; ii++)
            data.image[IDout].array.F[jj * naxes[0] + ii] =
                (data.image[ID].array.F[jj * naxes[0] + ii + 1] - data.image[ID].array.F[jj *
                        naxes[0] + ii - 1]) / 2.0;
        data.image[IDout].array.F[jj * naxes[0]] =
            data.image[ID].array.F[jj * naxes[0] + 1] - data.image[ID].array.F[jj *
                    naxes[0]];
        data.image[IDout].array.F[jj * naxes[0] + naxes[0] - 1] =
            data.image[ID].array.F[jj * naxes[0] + naxes[0] - 1] - data.image[ID].array.F[jj
                    * naxes[0] + naxes[0] - 2];
    }

    free(naxes);

    return(IDout);
}


long arith_image_dy(
    const char *ID_name,
    const char *IDout_name
)
{
    imageID ID;
    imageID IDout;
    uint32_t *naxes = NULL;
    long naxis;
    long ii, jj;
    uint8_t datatype;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxis = data.image[ID].md[0].naxis;
    if(naxis != 2)
    {
        PRINT_ERROR("Function only supports 2-D images\n");
        exit(0);
    }
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    naxes[0] = data.image[ID].md[0].size[0];
    naxes[1] = data.image[ID].md[0].size[1];

    IDout = create_image_ID(IDout_name, naxis, naxes, datatype, data.SHARED_DFT,
                            data.NBKEWORD_DFT);
    for(ii = 0; ii < naxes[0]; ii++)
    {
        for(jj = 1; jj < naxes[1] - 1; jj++)
        {
            data.image[IDout].array.F[jj * naxes[0] + ii] = (data.image[ID].array.F[(jj + 1)
                    * naxes[0] + ii] - data.image[ID].array.F[(jj - 1) * naxes[0] + ii]) / 2.0;
        }

        data.image[IDout].array.F[ii] = data.image[ID].array.F[1 * naxes[0] + ii] -
                                        data.image[ID].array.F[ii];

        data.image[IDout].array.F[(naxes[1] - 1)*naxes[0] + ii] =
            data.image[ID].array.F[(naxes[1] - 1) * naxes[0] + ii] -
            data.image[ID].array.F[(naxes[1] - 2) * naxes[0] + ii];

    }

    free(naxes);

    return(IDout);
}






/* ------------------------------------------------------------------------- */
/* Functions for bison / flex                                                */
/* im : image
  d : double

  function_<inputformat>_<outputformat>__<math function input>_<math function output>

  examples:
  function_imim__dd_d  : input is (image, image), applies double,double -> double function

  ------------------------------------------------------------------------- */


errno_t arith_image_function_im_im__d_d(
    const char *ID_name,
    const char *ID_out,
    double (*pt2function)(double)
)
{
    imageID ID;
    imageID IDout;
    uint32_t *naxes = NULL;
    long naxis;
    long ii;
    long nelement;
    uint8_t datatype, datatypeout;
    long i;


    if(data.Debug > 0)
    {
        printf("arith_image_function_d_d  %s %s\n", ID_name, ID_out);
        fflush(stdout);
    }

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxis = data.image[ID].md[0].naxis;
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }


    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[ID].md[0].size[i];
    }


    datatypeout = _DATATYPE_FLOAT;
    if(datatype == _DATATYPE_DOUBLE)
    {
        datatypeout = _DATATYPE_DOUBLE;
    }

    IDout = create_image_ID(ID_out, naxis, naxes, datatypeout, data.SHARED_DFT,
                            data.NBKEWORD_DFT);
    free(naxes);

    nelement = data.image[ID].md[0].nelement;


# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif


        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI8[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI16[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI32[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI64[ii]));
            }
        }

        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI8[ii]));
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI16[ii]));
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI32[ii]));
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI64[ii]));
            }
        }

        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.F[ii]));
            }
        }
        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.D[ii] = pt2function(data.image[ID].array.D[ii]);
            }
        }
# ifdef _OPENMP
    }
# endif


    if(data.Debug > 0)
    {
        printf("arith_image_function_d_d  DONE\n");
        fflush(stdout);
    }


    return RETURN_SUCCESS;
}





errno_t arith_image_function_imd_im__dd_d(
    const char *ID_name,
    double      v0,
    const char *ID_out,
    double (*pt2function)(double, double)
)
{
    imageID ID;
    imageID IDout;
    uint32_t *naxes = NULL;
    long naxis;
    long ii;
    long nelement;
    uint8_t datatype, datatypeout;
    long i;



    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxis = data.image[ID].md[0].naxis;
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
       PRINT_ERROR("malloc() error");
        exit(0);
    }


    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[ID].md[0].size[i];
    }


    datatypeout = _DATATYPE_FLOAT;
    if(datatype == _DATATYPE_DOUBLE)
    {
        datatypeout = _DATATYPE_DOUBLE;
    }

    IDout = create_image_ID(ID_out, naxis, naxes, datatypeout, data.SHARED_DFT,
                            data.NBKEWORD_DFT);
    free(naxes);

    nelement = data.image[ID].md[0].nelement;


# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif


        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI8[ii]), v0);
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI16[ii]), v0);
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI32[ii]), v0);
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI64[ii]), v0);
            }
        }


        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI8[ii]), v0);
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI16[ii]), v0);
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI32[ii]), v0);
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI64[ii]), v0);
            }
        }


        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.F[ii]), v0);
            }
        }
        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.D[ii] = pt2function(data.image[ID].array.D[ii], v0);
            }
        }
# ifdef _OPENMP
    }
# endif


    if(data.Debug > 0)
    {
        printf("arith_image_function_d_d  DONE\n");
        fflush(stdout);
    }


    return RETURN_SUCCESS;
}




errno_t arith_image_function_imdd_im__ddd_d(
    const char *ID_name,
    double      v0,
    double      v1,
    const char *ID_out,
    double (*pt2function)(double, double, double)
)
{
    imageID ID;
    imageID IDout;
    uint32_t *naxes = NULL;
    long naxis;
    long ii;
    long nelement;
    uint8_t datatype, datatypeout;
    long i;



    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxis = data.image[ID].md[0].naxis;
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }


    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[ID].md[0].size[i];
    }


    datatypeout = _DATATYPE_FLOAT;
    if(datatype == _DATATYPE_DOUBLE)
    {
        datatypeout = _DATATYPE_DOUBLE;
    }

    IDout = create_image_ID(ID_out, naxis, naxes, datatypeout, data.SHARED_DFT,
                            data.NBKEWORD_DFT);
    free(naxes);

    nelement = data.image[ID].md[0].nelement;


# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif


        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI8[ii]), v0, v1);
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI16[ii]), v0, v1);
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI32[ii]), v0, v1);
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.UI64[ii]), v0, v1);
            }
        }


        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI8[ii]), v0, v1);
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI16[ii]), v0, v1);
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI32[ii]), v0, v1);
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.SI64[ii]), v0, v1);
            }
        }


        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = (float) pt2function((double)(
                                                    data.image[ID].array.F[ii]), v0, v1);
            }
        }
        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.D[ii] = pt2function(data.image[ID].array.D[ii], v0,
                                                v1);
            }
        }
# ifdef _OPENMP
    }
# endif


    if(data.Debug > 0)
    {
        printf("arith_image_function_d_d  DONE\n");
        fflush(stdout);
    }


    return RETURN_SUCCESS;
}










/* ------------------------------------------------------------------------- */
/* image  -> image                                                           */
/* ------------------------------------------------------------------------- */




errno_t arith_image_function_1_1_byID(
    imageID ID,
    imageID IDout,
    double (*pt2function)(double)
)
{
    uint32_t *naxes = NULL;
    long naxis;
    long ii;
    long nelement;
    uint8_t datatype;
    //, datatypeout;
    long i;

    //  printf("arith_image_function_1_1\n");

    datatype = data.image[ID].md[0].datatype;
    naxis = data.image[ID].md[0].naxis;
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }


    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[ID].md[0].size[i];
    }


//    datatypeout = _DATATYPE_FLOAT;
//    if(datatype == _DATATYPE_DOUBLE)
//        datatypeout = _DATATYPE_DOUBLE;

    free(naxes);

    nelement = data.image[ID].md[0].nelement;


# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif


        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI8[ii]));
            }
        }

        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI16[ii]));
            }
        }

        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI32[ii]));
            }
        }

        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI64[ii]));
            }
        }



        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI8[ii]));
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI16[ii]));
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI32[ii]));
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI64[ii]));
            }
        }


        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.F[ii]));
            }
        }
        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.D[ii] = (double) pt2function((double)(
                                                    data.image[ID].array.D[ii]));
            }
        }
# ifdef _OPENMP
    }
# endif

    return RETURN_SUCCESS;
}






errno_t arith_image_function_1_1(
    const char *ID_name,
    const char *ID_out,
    double (*pt2function)(double)
)
{
    imageID ID;
    imageID IDout;
    uint32_t *naxes = NULL;
    long naxis;
    long ii;
    long nelement;
    uint8_t datatype, datatypeout;
    long i;

    //  printf("arith_image_function_1_1\n");

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxis = data.image[ID].md[0].naxis;
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }


    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[ID].md[0].size[i];
    }


    datatypeout = _DATATYPE_FLOAT;
    if(datatype == _DATATYPE_DOUBLE)
    {
        datatypeout = _DATATYPE_DOUBLE;
    }

    IDout = create_image_ID(ID_out, naxis, naxes, datatypeout, data.SHARED_DFT,
                            data.NBKEWORD_DFT);
    free(naxes);

    nelement = data.image[ID].md[0].nelement;


# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif


        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI8[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI16[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI32[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI64[ii]));
            }
        }

        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI8[ii]));
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI16[ii]));
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI32[ii]));
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI64[ii]));
            }
        }

        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.F[ii]));
            }
        }


        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.D[ii] = (double) pt2function((double)(
                                                    data.image[ID].array.D[ii]));
            }
        }
# ifdef _OPENMP
    }
# endif

    return RETURN_SUCCESS;
}







// imagein -> imagein (in place)
errno_t arith_image_function_1_1_inplace_byID(
    imageID ID,
    double (*pt2function)(double)
)
{
    long ii;
    long nelement;
    uint8_t datatype;
    //, datatypeout;

    // printf("arith_image_function_1_1_inplace\n");

    datatype = data.image[ID].md[0].datatype;

    //datatypeout = _DATATYPE_FLOAT;
    //if(datatype == _DATATYPE_DOUBLE)
    //   datatypeout = _DATATYPE_DOUBLE;

    nelement = data.image[ID].md[0].nelement;

    data.image[ID].md[0].write = 0;
# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
#endif

        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI8[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI16[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI32[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI64[ii]));
            }
        }


        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI8[ii]));
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI16[ii]));
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI32[ii]));
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI64[ii]));
            }
        }


        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(data.image[ID].array.F[ii]));
            }
        }

        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.D[ii] = (double) pt2function((double)(
                                                 data.image[ID].array.D[ii]));
            }
        }

# ifdef _OPENMP
    }
# endif

    data.image[ID].md[0].write = 0;
    data.image[ID].md[0].cnt0++;

    return RETURN_SUCCESS;
}




// imagein -> imagein (in place)
errno_t arith_image_function_1_1_inplace(
    const char *ID_name,
    double (*pt2function)(double)
)
{
    imageID ID;
    long ii;
    long nelement;
    uint8_t datatype;
    //, datatypeout;

    // printf("arith_image_function_1_1_inplace\n");

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;

//    datatypeout = _DATATYPE_FLOAT;
//    if(datatype == _DATATYPE_DOUBLE)
//        datatypeout = _DATATYPE_DOUBLE;

    nelement = data.image[ID].md[0].nelement;

    data.image[ID].md[0].write = 0;
# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
#endif

        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI8[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI16[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI32[ii]));
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI64[ii]));
            }
        }


        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI8[ii]));
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI16[ii]));
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI32[ii]));
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI64[ii]));
            }
        }


        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(data.image[ID].array.F[ii]));
            }
        }
        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.D[ii] = (double) pt2function((double)(
                                                 data.image[ID].array.D[ii]));
            }
        }

# ifdef _OPENMP
    }
# endif

    data.image[ID].md[0].write = 0;
    data.image[ID].md[0].cnt0++;

    return RETURN_SUCCESS;
}








double Pacos(double a)
{
    return((double) acos(a));
}
double Pasin(double a)
{
    return((double) asin(a));
}
double Patan(double a)
{
    return((double) atan(a));
}
double Pceil(double a)
{
    return((double) ceil(a));
}
double Pcos(double a)
{
    return((double) cos(a));
}
double Pcosh(double a)
{
    return((double) cosh(a));
}
double Pexp(double a)
{
    return((double) exp(a));
}
double Pfabs(double a)
{
    return((double) fabs(a));
}
double Pfloor(double a)
{
    return((double) floor(a));
}
double Pln(double a)
{
    return((double) log(a));
}
double Plog(double a)
{
    return((double) log10(a));
}
double Psqrt(double a)
{
    return((double) sqrt(a));
}
double Psin(double a)
{
    return((double) sin(a));
}
double Psinh(double a)
{
    return((double) sinh(a));
}
double Ptan(double a)
{
    return((double) tan(a));
}
double Ptanh(double a)
{
    return((double) tanh(a));
}

double Ppositive(double a)
{
    double value = 0.0;
    if(a > 0.0)
    {
        value = (double) 1.0;
    }
    return(value);
}


int arith_image_acos_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Pacos);
    return(0);
}
int arith_image_asin_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Pasin);
    return(0);
}
int arith_image_atan_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Patan);
    return(0);
}
int arith_image_ceil_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Pceil);
    return(0);
}
int arith_image_cos_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Pcos);
    return(0);
}
int arith_image_cosh_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Pcosh);
    return(0);
}
int arith_image_exp_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Pexp);
    return(0);
}
int arith_image_fabs_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Pfabs);
    return(0);
}
int arith_image_floor_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Pfloor);
    return(0);
}
int arith_image_ln_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Pln);
    return(0);
}
int arith_image_log_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Plog);
    return(0);
}
int arith_image_sqrt_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Psqrt);
    return(0);
}
int arith_image_sin_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Psin);
    return(0);
}
int arith_image_sinh_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Psinh);
    return(0);
}
int arith_image_tan_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Ptan);
    return(0);
}
int arith_image_tanh_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Ptanh);
    return(0);
}
int arith_image_positive_byID(long ID, long IDout)
{
    arith_image_function_1_1_byID(ID, IDout, &Ppositive);
    return(0);
}

int arith_image_acos(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Pacos);
    return(0);
}
int arith_image_asin(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Pasin);
    return(0);
}
int arith_image_atan(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Patan);
    return(0);
}
int arith_image_ceil(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Pceil);
    return(0);
}
int arith_image_cos(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Pcos);
    return(0);
}
int arith_image_cosh(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Pcosh);
    return(0);
}
int arith_image_exp(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Pexp);
    return(0);
}
int arith_image_fabs(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Pfabs);
    return(0);
}
int arith_image_floor(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Pfloor);
    return(0);
}
int arith_image_ln(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Pln);
    return(0);
}
int arith_image_log(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Plog);
    return(0);
}
int arith_image_sqrt(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Psqrt);
    return(0);
}
int arith_image_sin(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Psin);
    return(0);
}
int arith_image_sinh(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Psinh);
    return(0);
}
int arith_image_tan(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Ptan);
    return(0);
}
int arith_image_tanh(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Ptanh);
    return(0);
}
int arith_image_positive(const char *ID_name, const char *ID_out)
{
    arith_image_function_1_1(ID_name, ID_out, &Ppositive);
    return(0);
}








int arith_image_acos_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Pacos);
    return(0);
}
int arith_image_asin_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Pasin);
    return(0);
}
int arith_image_atan_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Patan);
    return(0);
}
int arith_image_ceil_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Pceil);
    return(0);
}
int arith_image_cos_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Pcos);
    return(0);
}
int arith_image_cosh_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Pcosh);
    return(0);
}
int arith_image_exp_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Pexp);
    return(0);
}
int arith_image_fabs_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Pfabs);
    return(0);
}
int arith_image_floor_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Pfloor);
    return(0);
}
int arith_image_ln_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Pln);
    return(0);
}
int arith_image_log_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Plog);
    return(0);
}
int arith_image_sqrt_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Psqrt);
    return(0);
}
int arith_image_sin_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Psin);
    return(0);
}
int arith_image_sinh_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Psinh);
    return(0);
}
int arith_image_tan_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Ptan);
    return(0);
}
int arith_image_tanh_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Ptanh);
    return(0);
}
int arith_image_positive_inplace_byID(long ID)
{
    arith_image_function_1_1_inplace_byID(ID, &Ppositive);
    return(0);
}

int arith_image_acos_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Pacos);
    return(0);
}
int arith_image_asin_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Pasin);
    return(0);
}
int arith_image_atan_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Patan);
    return(0);
}
int arith_image_ceil_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Pceil);
    return(0);
}
int arith_image_cos_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Pcos);
    return(0);
}
int arith_image_cosh_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Pcosh);
    return(0);
}
int arith_image_exp_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Pexp);
    return(0);
}
int arith_image_fabs_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Pfabs);
    return(0);
}
int arith_image_floor_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Pfloor);
    return(0);
}
int arith_image_ln_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Pln);
    return(0);
}
int arith_image_log_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Plog);
    return(0);
}
int arith_image_sqrt_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Psqrt);
    return(0);
}
int arith_image_sin_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Psin);
    return(0);
}
int arith_image_sinh_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Psinh);
    return(0);
}
int arith_image_tan_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Ptan);
    return(0);
}
int arith_image_tanh_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Ptanh);
    return(0);
}
int arith_image_positive_inplace(const char *ID_name)
{
    arith_image_function_1_1_inplace(ID_name, &Ppositive);
    return(0);
}








/* ------------------------------------------------------------------------- */
/* image, image  -> image                                                    */
/* ------------------------------------------------------------------------- */


errno_t arith_image_function_2_1(
    const char *ID_name1,
    const char *ID_name2,
    const char *ID_out,
    double (*pt2function)(double, double)
)
{
    imageID ID1;
    imageID ID2;
    imageID IDout;
    long ii, kk;
    uint32_t *naxes = NULL; // input, output
    uint32_t *naxes2 = NULL;
    long nelement1, nelement2, nelement;
    long naxis, naxis2;
    uint8_t datatype1, datatype2, datatypeout;
    long i;
    int n;
    int op3D2Dto3D = 0; // 3D image, 2D image -> 3D image
    long xysize;
    char errmsg[SBUFFERSIZE];



    ID1 = image_ID(ID_name1);
    ID2 = image_ID(ID_name2);

    //list_image_ID(); //TEST
    printf("%s  IDs : %ld %ld\n", __FUNCTION__, ID1, ID2);

    if(ID1 == -1)
    {
        PRINT_WARNING("Image %s does not exist: cannot proceed\n", ID_name1);
        return 1;
    }

    if(ID2 == -1)
    {
        PRINT_WARNING("Image %s does not exist: cannot proceed\n", ID_name2);
        return 1;
    }

    datatype1 = data.image[ID1].md[0].datatype;
    datatype2 = data.image[ID2].md[0].datatype;
    naxis = data.image[ID1].md[0].naxis;
    naxis2 = data.image[ID2].md[0].naxis;
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    naxes2 = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }

    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[ID1].md[0].size[i];
    }
    for(i = 0; i < naxis2; i++)
    {
        naxes2[i] = data.image[ID2].md[0].size[i];
    }


    datatypeout = _DATATYPE_FLOAT; // default

    // other cases

    // DOUBLE * -> DOUBLE
    if(datatype1 == _DATATYPE_DOUBLE)
    {
        datatypeout = _DATATYPE_DOUBLE;
    }

    // * DOUBLE -> DOUBLE
    if(datatype2 == _DATATYPE_DOUBLE)
    {
        datatypeout = _DATATYPE_DOUBLE;
    }



    IDout = create_image_ID(ID_out, naxis, naxes, datatypeout, data.SHARED_DFT,
                            data.NBKEWORD_DFT);



    nelement1 = data.image[ID1].md[0].nelement;
    nelement2 = data.image[ID2].md[0].nelement;

    //list_image_ID();

    // test if 3D 2D -> 3D operation
    //printf("naxis   %ld (%d)   %ld (%d)\n", naxis, atype1, naxis2, atype2);
    //fflush(stdout);

    op3D2Dto3D = 0;
    xysize = 0;
    if((naxis == 3) && (naxis2 == 2))
    {
        printf("naxes:  %ld %ld     %ld %ld\n", (long) naxes[0], (long) naxes2[0],
               (long) naxes[1], (long) naxes2[1]);
        fflush(stdout);
        if((naxes[0] == naxes2[0]) && (naxes[1] == naxes2[1]))
        {
            op3D2Dto3D = 1;
            xysize = naxes[0] * naxes[1];
            printf("input : 3D im, 2D im -> output : 3D im\n");
            fflush(stdout);
            //list_image_ID();
        }
    }


    nelement = nelement1;
    if(op3D2Dto3D == 0)
        if(nelement1 != nelement2)
        {
            PRINT_ERROR(
                         "images %s and %s have different number of elements ( %ld %ld )\n", ID_name1,
                         ID_name2, nelement1, nelement2);
            exit(0);
        }

    //list_image_ID();



//# ifdef _OPENMP
//    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
//    {
//# endif


// ID1 datatype  UINT8
    if(datatype1 == _DATATYPE_UINT8)
    {
        if(datatype2 == _DATATYPE_UINT8) // UINT8 UINT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI8[ii]), (double)(data.image[ID2].array.UI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT16) // UINT8 UINT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI8[ii]), (double)(data.image[ID2].array.UI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT32) // UINT8 UINT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI8[ii]), (double)(data.image[ID2].array.UI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT64) // UINT8 UINT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI8[ii]), (double)(data.image[ID2].array.UI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT8) // UINT8 INT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI8[ii]), (double)(data.image[ID2].array.SI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT16) // UINT8 INT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI8[ii]), (double)(data.image[ID2].array.SI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT32) // UINT8 INT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI8[ii]), (double)(data.image[ID2].array.SI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT64) // UINT8 INT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI8[ii]), (double)(data.image[ID2].array.SI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_FLOAT) // UINT8 FLOAT -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI8[ii]), (double)(data.image[ID2].array.F[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.F[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_DOUBLE) // UINT8 DOUBLE -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.D[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI8[ii]), data.image[ID2].array.D[ii]);
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.D[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI8[kk * xysize + ii]), data.image[ID2].array.D[ii]);
                    }
        }
    }



// ID1 datatype  UINT16

    if(datatype1 == _DATATYPE_UINT16)
    {
        if(datatype2 == _DATATYPE_UINT8) // UINT16 UINT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI16[ii]), (double)(data.image[ID2].array.UI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT16) // UINT16 UINT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI16[ii]), (double)(data.image[ID2].array.UI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT32) // UINT16 UINT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI16[ii]), (double)(data.image[ID2].array.UI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT64) // UINT16 UINT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI16[ii]), (double)(data.image[ID2].array.UI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT8) // UINT16 INT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI16[ii]), (double)(data.image[ID2].array.SI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT16) // UINT16 INT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI16[ii]), (double)(data.image[ID2].array.SI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT32) // UINT16 INT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI16[ii]), (double)(data.image[ID2].array.SI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT64) // UINT16 INT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI16[ii]), (double)(data.image[ID2].array.SI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_FLOAT) // UINT16 FLOAT -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI16[ii]), (double)(data.image[ID2].array.F[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.F[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_DOUBLE) // UINT16 DOUBLE -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.D[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI16[ii]), data.image[ID2].array.D[ii]);
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.D[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI16[kk * xysize + ii]), data.image[ID2].array.D[ii]);
                    }
        }
    }


// ID1 datatype  UINT32
    if(datatype1 == _DATATYPE_UINT32)
    {

        if(datatype2 == _DATATYPE_UINT8) // UINT32 UINT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI32[ii]), (double)(data.image[ID2].array.UI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT16) // UINT32 UINT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI32[ii]), (double)(data.image[ID2].array.UI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT32) // UINT32 UINT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI32[ii]), (double)(data.image[ID2].array.UI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT64) // UINT32 UINT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI32[ii]), (double)(data.image[ID2].array.UI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT8) // UINT32 INT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI32[ii]), (double)(data.image[ID2].array.SI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT16) // UINT32 INT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI32[ii]), (double)(data.image[ID2].array.SI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT32) // UINT32 INT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI32[ii]), (double)(data.image[ID2].array.SI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT64) // UINT32 INT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI32[ii]), (double)(data.image[ID2].array.SI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_FLOAT) // UINT32 FLOAT -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI32[ii]), (double)(data.image[ID2].array.F[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.F[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_DOUBLE) // UINT32 DOUBLE -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.D[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI32[ii]), data.image[ID2].array.D[ii]);
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.D[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI32[kk * xysize + ii]), data.image[ID2].array.D[ii]);
                    }
        }
    }



// ID1 datatype  UINT64
    if(datatype1 == _DATATYPE_UINT64)
    {
        if(datatype2 == _DATATYPE_UINT8) // UINT64 UINT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI64[ii]), (double)(data.image[ID2].array.UI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT16) // UINT64 UINT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI64[ii]), (double)(data.image[ID2].array.UI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT32) // UINT64 UINT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI64[ii]), (double)(data.image[ID2].array.UI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT64) // UINT64 UINT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI64[ii]), (double)(data.image[ID2].array.UI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT8) // UINT64 INT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI64[ii]), (double)(data.image[ID2].array.SI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT16) // UINT64 INT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI64[ii]), (double)(data.image[ID2].array.SI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT32) // UINT64 INT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI64[ii]), (double)(data.image[ID2].array.SI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT64) // UINT64 INT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI64[ii]), (double)(data.image[ID2].array.SI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_FLOAT) // UINT64 FLOAT -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI64[ii]), (double)(data.image[ID2].array.F[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.F[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_DOUBLE) // UINT64 DOUBLE -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.D[ii] = pt2function((double)(
                                                        data.image[ID1].array.UI64[ii]), data.image[ID2].array.D[ii]);
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.D[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.UI64[kk * xysize + ii]), data.image[ID2].array.D[ii]);
                    }
        }
    }



// ID1 datatype  INT8

    if(datatype1 == _DATATYPE_INT8)
    {
        if(datatype2 == _DATATYPE_UINT8) // INT8 UINT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI8[ii]), (double)(data.image[ID2].array.UI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT16) // INT8 UINT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI8[ii]), (double)(data.image[ID2].array.UI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT32) // INT8 UINT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI8[ii]), (double)(data.image[ID2].array.UI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT64) // INT8 UINT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI8[ii]), (double)(data.image[ID2].array.UI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT8) // INT8 INT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI8[ii]), (double)(data.image[ID2].array.SI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT16) // INT8 INT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI8[ii]), (double)(data.image[ID2].array.SI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT32) // INT8 INT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI8[ii]), (double)(data.image[ID2].array.SI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT64) // INT8 INT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI8[ii]), (double)(data.image[ID2].array.SI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_FLOAT) // INT8 FLOAT -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI8[ii]), (double)(data.image[ID2].array.F[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI8[kk * xysize + ii]),
                                (double)(data.image[ID2].array.F[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_DOUBLE) // INT8 DOUBLE -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.D[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI8[ii]), data.image[ID2].array.D[ii]);
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.D[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI8[kk * xysize + ii]), data.image[ID2].array.D[ii]);
                    }
        }
    }



// ID1 datatype  INT16

    if(datatype1 == _DATATYPE_INT16)
    {
        if(datatype2 == _DATATYPE_UINT8) // INT16 UINT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI16[ii]), (double)(data.image[ID2].array.UI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT16) // INT16 UINT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI16[ii]), (double)(data.image[ID2].array.UI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT32) // INT16 UINT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI16[ii]), (double)(data.image[ID2].array.UI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT64) // INT16 UINT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI16[ii]), (double)(data.image[ID2].array.UI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT8) // INT16 INT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI16[ii]), (double)(data.image[ID2].array.SI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT16) // INT16 INT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI16[ii]), (double)(data.image[ID2].array.SI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT32) // INT16 INT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI16[ii]), (double)(data.image[ID2].array.SI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT64) // INT16 INT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI16[ii]), (double)(data.image[ID2].array.SI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_FLOAT) // INT16 FLOAT -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI16[ii]), (double)(data.image[ID2].array.F[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI16[kk * xysize + ii]),
                                (double)(data.image[ID2].array.F[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_DOUBLE) // INT16 DOUBLE -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.D[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI16[ii]), data.image[ID2].array.D[ii]);
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.D[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI16[kk * xysize + ii]), data.image[ID2].array.D[ii]);
                    }
        }
    }



// ID1 datatype  INT32

    if(datatype1 == _DATATYPE_INT32)
    {
        if(datatype2 == _DATATYPE_UINT8) // INT32 UINT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI32[ii]), (double)(data.image[ID2].array.UI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT16) // INT32 UINT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI32[ii]), (double)(data.image[ID2].array.UI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT32) // INT32 UINT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI32[ii]), (double)(data.image[ID2].array.UI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT64) // INT32 UINT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI32[ii]), (double)(data.image[ID2].array.UI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT8) // INT32 INT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI32[ii]), (double)(data.image[ID2].array.SI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT16) // INT32 INT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI32[ii]), (double)(data.image[ID2].array.SI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT32) // INT32 INT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI32[ii]), (double)(data.image[ID2].array.SI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT64) // INT32 INT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI32[ii]), (double)(data.image[ID2].array.SI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_FLOAT) // INT32 FLOAT -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI32[ii]), (double)(data.image[ID2].array.F[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI32[kk * xysize + ii]),
                                (double)(data.image[ID2].array.F[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_DOUBLE) // INT32 DOUBLE -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.D[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI32[ii]), data.image[ID2].array.D[ii]);
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.D[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI32[kk * xysize + ii]), data.image[ID2].array.D[ii]);
                    }
        }
    }



// ID1 datatype  INT64
    if(datatype1 == _DATATYPE_INT64)
    {
        if(datatype2 == _DATATYPE_UINT8) // INT64 UINT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI64[ii]), (double)(data.image[ID2].array.UI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT16) // INT64 UINT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI64[ii]), (double)(data.image[ID2].array.UI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT32) // INT64 UINT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI64[ii]), (double)(data.image[ID2].array.UI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT64) // INT64 UINT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI64[ii]), (double)(data.image[ID2].array.UI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT8) // INT64 INT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI64[ii]), (double)(data.image[ID2].array.SI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT16) // INT64 INT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI64[ii]), (double)(data.image[ID2].array.SI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT32) // INT64 INT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI64[ii]), (double)(data.image[ID2].array.SI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT64) // INT64 INT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI64[ii]), (double)(data.image[ID2].array.SI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_FLOAT) // INT64 FLOAT -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI64[ii]), (double)(data.image[ID2].array.F[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI64[kk * xysize + ii]),
                                (double)(data.image[ID2].array.F[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_DOUBLE) // INT64 DOUBLE -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.D[ii] = pt2function((double)(
                                                        data.image[ID1].array.SI64[ii]), data.image[ID2].array.D[ii]);
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.D[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.SI64[kk * xysize + ii]), data.image[ID2].array.D[ii]);
                    }
        }
    }



// ID1 datatype  FLOAT
    if(datatype1 == _DATATYPE_FLOAT)
    {
        if(datatype2 == _DATATYPE_UINT8) // FLOAT UINT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.F[ii]), (double)(data.image[ID2].array.UI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.F[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT16) // FLOAT UINT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.F[ii]), (double)(data.image[ID2].array.UI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.F[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT32) // FLOAT UINT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.F[ii]), (double)(data.image[ID2].array.UI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.F[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT64) // FLOAT UINT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.F[ii]), (double)(data.image[ID2].array.UI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.F[kk * xysize + ii]),
                                (double)(data.image[ID2].array.UI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT8) // FLOAT INT8 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.F[ii]), (double)(data.image[ID2].array.SI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.F[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT16) // FLOAT INT16 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.F[ii]), (double)(data.image[ID2].array.SI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.F[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT32) // FLOAT INT32 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.F[ii]), (double)(data.image[ID2].array.SI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.F[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT64) // FLOAT INT64 -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.F[ii]), (double)(data.image[ID2].array.SI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.F[kk * xysize + ii]),
                                (double)(data.image[ID2].array.SI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_FLOAT) // FLOAT FLOAT -> FLOAT
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function((double)(
                                                        data.image[ID1].array.F[ii]), (double)(data.image[ID2].array.F[ii]));
                }

            if(op3D2Dto3D == 1)
            {
//# ifdef _OPENMP
//                #pragma omp for
//# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.F[kk * xysize + ii]),
                                (double)(data.image[ID2].array.F[ii]));
                    }
            }
        }

        if(datatype2 == _DATATYPE_DOUBLE) // FLOAT DOUBLE -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.D[ii] = pt2function((double)(
                                                        data.image[ID1].array.F[ii]), data.image[ID2].array.D[ii]);
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.D[kk * xysize + ii] = pt2function((double)(
                                    data.image[ID1].array.F[kk * xysize + ii]), data.image[ID2].array.D[ii]);
                    }
        }
    }




// ID1 datatype  DOUBLE

    if(datatype1 == _DATATYPE_DOUBLE)
    {
        if(datatype2 == _DATATYPE_UINT8) // DOUBLE UINT8 -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function(data.image[ID1].array.D[ii],
                                                    (double)(data.image[ID2].array.UI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function(
                                    data.image[ID1].array.D[kk * xysize + ii],
                                    (double)(data.image[ID2].array.UI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT16) // DOUBLE UINT16 -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function(data.image[ID1].array.D[ii],
                                                    (double)(data.image[ID2].array.UI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function(
                                    data.image[ID1].array.D[kk * xysize + ii],
                                    (double)(data.image[ID2].array.UI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT32) // DOUBLE UINT32 -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function(data.image[ID1].array.D[ii],
                                                    (double)(data.image[ID2].array.UI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function(
                                    data.image[ID1].array.D[kk * xysize + ii],
                                    (double)(data.image[ID2].array.UI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_UINT64) // DOUBLE UINT64 -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function(data.image[ID1].array.D[ii],
                                                    (double)(data.image[ID2].array.UI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function(
                                    data.image[ID1].array.D[kk * xysize + ii],
                                    (double)(data.image[ID2].array.UI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT8) // DOUBLE INT8 -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function(data.image[ID1].array.D[ii],
                                                    (double)(data.image[ID2].array.SI8[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function(
                                    data.image[ID1].array.D[kk * xysize + ii],
                                    (double)(data.image[ID2].array.SI8[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT16) // DOUBLE INT16 -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function(data.image[ID1].array.D[ii],
                                                    (double)(data.image[ID2].array.SI16[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function(
                                    data.image[ID1].array.D[kk * xysize + ii],
                                    (double)(data.image[ID2].array.SI16[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT32) // DOUBLE INT32 -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function(data.image[ID1].array.D[ii],
                                                    (double)(data.image[ID2].array.SI32[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function(
                                    data.image[ID1].array.D[kk * xysize + ii],
                                    (double)(data.image[ID2].array.SI32[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_INT64) // DOUBLE INT64 -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function(data.image[ID1].array.D[ii],
                                                    (double)(data.image[ID2].array.SI64[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function(
                                    data.image[ID1].array.D[kk * xysize + ii],
                                    (double)(data.image[ID2].array.SI64[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_FLOAT) // DOUBLE FLOAT -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.F[ii] = pt2function(data.image[ID1].array.D[ii],
                                                    (double)(data.image[ID2].array.F[ii]));
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.F[kk * xysize + ii] = pt2function(
                                    data.image[ID1].array.D[kk * xysize + ii],
                                    (double)(data.image[ID2].array.F[ii]));
                    }
        }

        if(datatype2 == _DATATYPE_DOUBLE) // DOUBLE DOUBLE -> DOUBLE
        {
            if(op3D2Dto3D == 0)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[IDout].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                    data.image[ID2].array.D[ii]);
                }

            if(op3D2Dto3D == 1)
# ifdef _OPENMP
                #pragma omp for
# endif
                for(kk = 0; kk < naxes[2]; kk++)
                    for(ii = 0; ii < xysize; ii++)
                    {
                        data.image[IDout].array.D[kk * xysize + ii] = pt2function(
                                    data.image[ID1].array.D[kk * xysize + ii], data.image[ID2].array.D[ii]);
                    }
        }
    }





//# ifdef _OPENMP
//    }
//# endif

    free(naxes);
    free(naxes2);

    return RETURN_SUCCESS;
}






errno_t arith_image_function_2_1_inplace_byID(
    imageID ID1,
    imageID ID2,
    double (*pt2function)(double, double)
)
{
    long ii;
    long nelement1, nelement2, nelement;
    uint8_t datatype1, datatype2;
    int n;

    datatype1 = data.image[ID1].md[0].datatype;
    datatype2 = data.image[ID2].md[0].datatype;
    nelement1 = data.image[ID1].md[0].nelement;
    nelement2 = data.image[ID2].md[0].nelement;

    nelement = nelement1;
    if(nelement1 != nelement2)
    {
        PRINT_ERROR(
                     "images %ld and %ld have different number of elements\n", ID1, ID2);
        exit(0);
    }

    data.image[ID1].md[0].write = 1;

# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif

        // FLOAT
        if(datatype1 == _DATATYPE_FLOAT)
        {
            if(datatype2 == _DATATYPE_UINT8) // FLOAT <- UINT8
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.F[ii] = pt2function((double)(data.image[ID1].array.F[ii]),
                                                  (double)(data.image[ID2].array.UI8[ii]));
                }
            }

            if(datatype2 == _DATATYPE_UINT16) // FLOAT <- UINT16
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.F[ii] = pt2function((double)(data.image[ID1].array.F[ii]),
                                                  (double)(data.image[ID2].array.UI16[ii]));
                }
            }

            if(datatype2 == _DATATYPE_UINT32) // FLOAT <- UINT32
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.F[ii] = pt2function((double)(data.image[ID1].array.F[ii]),
                                                  (double)(data.image[ID2].array.UI32[ii]));
                }
            }

            if(datatype2 == _DATATYPE_UINT64) // FLOAT <- UINT64
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.F[ii] = pt2function((double)(data.image[ID1].array.F[ii]),
                                                  (double)(data.image[ID2].array.UI64[ii]));
                }
            }

            if(datatype2 == _DATATYPE_INT8) // FLOAT <- INT8
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.F[ii] = pt2function((double)(data.image[ID1].array.F[ii]),
                                                  (double)(data.image[ID2].array.SI8[ii]));
                }
            }

            if(datatype2 == _DATATYPE_INT16) // FLOAT <- INT16
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.F[ii] = pt2function((double)(data.image[ID1].array.F[ii]),
                                                  (double)(data.image[ID2].array.SI16[ii]));
                }
            }

            if(datatype2 == _DATATYPE_INT32) // FLOAT <- INT32
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.F[ii] = pt2function((double)(data.image[ID1].array.F[ii]),
                                                  (double)(data.image[ID2].array.SI32[ii]));
                }
            }

            if(datatype2 == _DATATYPE_INT64) // FLOAT <- INT64
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.F[ii] = pt2function((double)(data.image[ID1].array.F[ii]),
                                                  (double)(data.image[ID2].array.SI64[ii]));
                }
            }


            if(datatype2 == _DATATYPE_FLOAT) // FLOAT <- FLOAT
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.F[ii] = pt2function((double)(data.image[ID1].array.F[ii]),
                                                  (double)(data.image[ID2].array.F[ii]));
                }
            }

            if(datatype2 == _DATATYPE_DOUBLE) // FLOAT <- DOUBLE
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.F[ii] = pt2function((double)(data.image[ID1].array.F[ii]),
                                                  data.image[ID2].array.D[ii]);
                }
            }

        }



        // DOUBLE
        if(datatype1 == _DATATYPE_DOUBLE)
        {
            if(datatype2 == _DATATYPE_UINT8) // DOUBLE <- UINT8
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                  (double)(data.image[ID2].array.UI8[ii]));
                }
            }

            if(datatype2 == _DATATYPE_UINT16) // DOUBLE <- UINT16
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                  (double)(data.image[ID2].array.UI16[ii]));
                }
            }

            if(datatype2 == _DATATYPE_UINT32) // DOUBLE <- UINT32
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                  (double)(data.image[ID2].array.UI32[ii]));
                }
            }

            if(datatype2 == _DATATYPE_UINT64) // DOUBLE <- UINT64
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                  (double)(data.image[ID2].array.UI64[ii]));
                }
            }

            if(datatype2 == _DATATYPE_INT8) // DOUBLE <- INT8
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                  (double)(data.image[ID2].array.SI8[ii]));
                }
            }

            if(datatype2 == _DATATYPE_INT16) // DOUBLE <- INT16
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                  (double)(data.image[ID2].array.SI16[ii]));
                }
            }

            if(datatype2 == _DATATYPE_INT32) // DOUBLE <- INT32
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                  (double)(data.image[ID2].array.SI32[ii]));
                }
            }

            if(datatype2 == _DATATYPE_INT64) // DOUBLE <- INT64
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                  (double)(data.image[ID2].array.SI64[ii]));
                }
            }


            if(datatype2 == _DATATYPE_FLOAT) // DOUBLE <- FLOAT
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                  (double)(data.image[ID2].array.F[ii]));
                }
            }


            if(datatype2 == _DATATYPE_DOUBLE) // DOUBLE <- DOUBLE
            {
# ifdef _OPENMP
                #pragma omp for
# endif
                for(ii = 0; ii < nelement; ii++)
                {
                    data.image[ID1].array.D[ii] = pt2function(data.image[ID1].array.D[ii],
                                                  data.image[ID2].array.D[ii]);
                }
            }
        }







        if((datatype1 == _DATATYPE_COMPLEX_FLOAT)
                && (datatype2 == _DATATYPE_COMPLEX_FLOAT))
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID1].array.CF[ii].re = pt2function((double)(
                                                      data.image[ID1].array.CF[ii].re), (double)(data.image[ID2].array.CF[ii].re));
                data.image[ID1].array.CF[ii].im = pt2function((double)(
                                                      data.image[ID1].array.CF[ii].im), (double)(data.image[ID2].array.CF[ii].im));
            }
        }

        if((datatype1 == _DATATYPE_COMPLEX_DOUBLE)
                && (datatype2 == _DATATYPE_COMPLEX_DOUBLE))
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID1].array.CD[ii].re = pt2function((double)(
                                                      data.image[ID1].array.CD[ii].re), (double)(data.image[ID2].array.CD[ii].re));
                data.image[ID1].array.CD[ii].im = pt2function((double)(
                                                      data.image[ID1].array.CD[ii].im), (double)(data.image[ID2].array.CD[ii].im));
            }
        }

# ifdef _OPENMP
    }
# endif

    data.image[ID1].md[0].write = 0;
    data.image[ID1].md[0].cnt0++;

    return EXIT_SUCCESS;
}






errno_t arith_image_function_2_1_inplace(
    const char *ID_name1,
    const char *ID_name2,
    double (*pt2function)(double, double)
)
{
    imageID ID1;
    imageID ID2;

    ID1 = image_ID(ID_name1);
    ID2 = image_ID(ID_name2);

    arith_image_function_2_1_inplace_byID(ID1, ID2, pt2function);

    return EXIT_SUCCESS;
}



















double Pfmod(double a, double b)
{
    return((double) fmod(a, b));
}
double Ppow(double a, double b)
{
    if(b > 0)
    {
        return((double) pow(a, b));
    }
    else
    {
        return((double) pow(a, -b));
    }
}
double Padd(double a, double b)
{
    return((double) a + b);
}
double Psubm(double a, double b)
{
    return((double) b - a);
}
double Psub(double a, double b)
{
    return((double) a - b);
}
double Pmult(double a, double b)
{
    return((double) a * b);
}
double Pdiv(double a, double b)
{
    return((double) a / b);
}
double Pdiv1(double a, double b)
{
    return((double) b / a);
}
double Pminv(double a, double b)
{
    if(a < b)
    {
        return(a);
    }
    else
    {
        return(b);
    }
}
double Pmaxv(double a, double b)
{
    if(a > b)
    {
        return(a);
    }
    else
    {
        return(b);
    }
}
double Ptestlt(double a, double b)
{
    if(a < b)
    {
        return((double) 1.0);
    }
    else
    {
        return((double) 0.0);
    }
}
double Ptestmt(double a, double b)
{
    if(a < b)
    {
        return((double) 0.0);
    }
    else
    {
        return((double) 1.0);
    }
}



int arith_image_fmod(const char *ID1_name, const char *ID2_name,
                     const char *ID_out)
{
    arith_image_function_2_1(ID1_name, ID2_name, ID_out, &Pfmod);
    return(0);
}
int arith_image_pow(const char *ID1_name, const char *ID2_name,
                    const char *ID_out)
{
    arith_image_function_2_1(ID1_name, ID2_name, ID_out, &Ppow);
    return(0);
}
int arith_image_add(const char *ID1_name, const char *ID2_name,
                    const char *ID_out)
{
    arith_image_function_2_1(ID1_name, ID2_name, ID_out, &Padd);
    return(0);
}
int arith_image_sub(const char *ID1_name, const char *ID2_name,
                    const char *ID_out)
{
    arith_image_function_2_1(ID1_name, ID2_name, ID_out, &Psub);
    return(0);
}
int arith_image_mult(const char *ID1_name, const char *ID2_name,
                     const char *ID_out)
{
    arith_image_function_2_1(ID1_name, ID2_name, ID_out, &Pmult);
    return(0);
}
int arith_image_div(const char *ID1_name, const char *ID2_name,
                    const char *ID_out)
{
    arith_image_function_2_1(ID1_name, ID2_name, ID_out, &Pdiv);
    return(0);
}
int arith_image_minv(const char *ID1_name, const char *ID2_name,
                     const char *ID_out)
{
    arith_image_function_2_1(ID1_name, ID2_name, ID_out, &Pminv);
    return(0);
}
int arith_image_maxv(const char *ID1_name, const char *ID2_name,
                     const char *ID_out)
{
    arith_image_function_2_1(ID1_name, ID2_name, ID_out, &Pmaxv);
    return(0);
}
int arith_image_testlt(const char *ID1_name, const char *ID2_name,
                       const char *ID_out)
{
    arith_image_function_2_1(ID1_name, ID2_name, ID_out, &Ptestlt);
    return(0);
}
int arith_image_testmt(const char *ID1_name, const char *ID2_name,
                       const char *ID_out)
{
    arith_image_function_2_1(ID1_name, ID2_name, ID_out, &Ptestmt);
    return(0);
}


int arith_image_fmod_inplace(const char *ID1_name, const char *ID2_name)
{
    arith_image_function_2_1_inplace(ID1_name, ID2_name, &Pfmod);
    return(0);
}
int arith_image_pow_inplace(const char *ID1_name, const char *ID2_name)
{
    arith_image_function_2_1_inplace(ID1_name, ID2_name, &Ppow);
    return(0);
}
int arith_image_add_inplace(const char *ID1_name, const char *ID2_name)
{
    arith_image_function_2_1_inplace(ID1_name, ID2_name, &Padd);
    return(0);
}
int arith_image_sub_inplace(const char *ID1_name, const char *ID2_name)
{
    arith_image_function_2_1_inplace(ID1_name, ID2_name, &Psub);
    return(0);
}
int arith_image_mult_inplace(const char *ID1_name, const char *ID2_name)
{
    arith_image_function_2_1_inplace(ID1_name, ID2_name, &Pmult);
    return(0);
}
int arith_image_div_inplace(const char *ID1_name, const char *ID2_name)
{
    arith_image_function_2_1_inplace(ID1_name, ID2_name, &Pdiv);
    return(0);
}
int arith_image_minv_inplace(const char *ID1_name, const char *ID2_name)
{
    arith_image_function_2_1_inplace(ID1_name, ID2_name, &Pminv);
    return(0);
}
int arith_image_maxv_inplace(const char *ID1_name, const char *ID2_name)
{
    arith_image_function_2_1_inplace(ID1_name, ID2_name, &Pmaxv);
    return(0);
}
int arith_image_testlt_inplace(const char *ID1_name, const char *ID2_name)
{
    arith_image_function_2_1_inplace(ID1_name, ID2_name, &Ptestlt);
    return(0);
}
int arith_image_testmt_inplace(const char *ID1_name, const char *ID2_name)
{
    arith_image_function_2_1_inplace(ID1_name, ID2_name, &Ptestmt);
    return(0);
}


int arith_image_fmod_inplace_byID(long ID1, long ID2)
{
    arith_image_function_2_1_inplace_byID(ID1, ID2, &Pfmod);
    return(0);
}
int arith_image_pow_inplace_byID(long ID1, long ID2)
{
    arith_image_function_2_1_inplace_byID(ID1, ID2, &Ppow);
    return(0);
}
int arith_image_add_inplace_byID(long ID1, long ID2)
{
    arith_image_function_2_1_inplace_byID(ID1, ID2, &Padd);
    return(0);
}
int arith_image_sub_inplace_byID(long ID1, long ID2)
{
    arith_image_function_2_1_inplace_byID(ID1, ID2, &Psub);
    return(0);
}
int arith_image_mult_inplace_byID(long ID1, long ID2)
{
    arith_image_function_2_1_inplace_byID(ID1, ID2, &Pmult);
    return(0);
}
int arith_image_div_inplace_byID(long ID1, long ID2)
{
    arith_image_function_2_1_inplace_byID(ID1, ID2, &Pdiv);
    return(0);
}
int arith_image_minv_inplace_byID(long ID1, long ID2)
{
    arith_image_function_2_1_inplace_byID(ID1, ID2, &Pminv);
    return(0);
}
int arith_image_maxv_inplace_byID(long ID1, long ID2)
{
    arith_image_function_2_1_inplace_byID(ID1, ID2, &Pmaxv);
    return(0);
}
int arith_image_testlt_inplace_byID(long ID1, long ID2)
{
    arith_image_function_2_1_inplace_byID(ID1, ID2, &Ptestlt);
    return(0);
}
int arith_image_testmt_inplace_byID(long ID1, long ID2)
{
    arith_image_function_2_1_inplace_byID(ID1, ID2, &Ptestmt);
    return(0);
}










/* ------------------------------------------------------------------------- */
/* complex image, complex image  -> complex image                            */
/* ------------------------------------------------------------------------- */
// complex float (CF), complex float (CF) -> complex float (CF)
errno_t arith_image_function_CF_CF__CF(
    const char *ID_name1,
    const char *ID_name2,
    const char *ID_out,
    complex_float(*pt2function)(complex_float, complex_float)
)
{
    imageID ID1;
    imageID ID2;
    imageID IDout;
    long ii;
    uint32_t *naxes = NULL;
    long nelement;
    long naxis;
    uint8_t datatype1; //, datatype2;
    long i;

    ID1 = image_ID(ID_name1);
    ID2 = image_ID(ID_name2);
    datatype1 = data.image[ID1].md[0].datatype;
    //datatype2 = data.image[ID2].md[0].datatype;
    naxis = data.image[ID1].md[0].naxis;
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }

    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[ID1].md[0].size[i];
    }

    IDout = create_image_ID(ID_out, naxis, naxes, datatype1, data.SHARED_DFT,
                            data.NBKEWORD_DFT);
    free(naxes);
    nelement = data.image[ID1].md[0].nelement;

# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
        #pragma omp for
# endif
        for(ii = 0; ii < nelement; ii++)
        {
            data.image[IDout].array.CF[ii] = pt2function(data.image[ID1].array.CF[ii],
                                             data.image[ID2].array.CF[ii]);
        }
# ifdef _OPENMP
    }
# endif

    return RETURN_SUCCESS;
}




// complex double (CD), complex double (CD) -> complex double (CD)
errno_t arith_image_function_CD_CD__CD(
    const char *ID_name1,
    const char *ID_name2,
    const char *ID_out,
    complex_double(*pt2function)(complex_double, complex_double)
)
{
    imageID ID1;
    imageID ID2;
    imageID IDout;
    long ii;
    uint32_t *naxes = NULL;
    long nelement;
    long naxis;
    uint8_t datatype1; //, datatype2;
    long i;

    ID1 = image_ID(ID_name1);
    ID2 = image_ID(ID_name2);
    datatype1 = data.image[ID1].md[0].datatype;
    //datatype2 = data.image[ID2].md[0].datatype;
    naxis = data.image[ID1].md[0].naxis;
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }

    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[ID1].md[0].size[i];
    }

    IDout = create_image_ID(ID_out, naxis, naxes, datatype1, data.SHARED_DFT,
                            data.NBKEWORD_DFT);
    free(naxes);
    nelement = data.image[ID1].md[0].nelement;

# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
        #pragma omp for
# endif
        for(ii = 0; ii < nelement; ii++)
        {
            data.image[IDout].array.CD[ii] = pt2function(data.image[ID1].array.CD[ii],
                                             data.image[ID2].array.CD[ii]);
        }
# ifdef _OPENMP
    }
# endif

    return RETURN_SUCCESS;
}






complex_double CPadd_CD_CD(complex_double a, complex_double b)
{
    complex_double v;
    v.re = a.re + b.re;
    v.im = a.im + b.im;
    return(v);
}

complex_double CPsub_CD_CD(complex_double a, complex_double b)
{
    complex_double v;
    v.re = a.re - b.re;
    v.im = a.im - b.im;
    return(v);
}

complex_double CPmult_CD_CD(complex_double a, complex_double b)
{
    complex_double v;
    v.re = a.re * b.re - a.im * b.im;
    v.im = a.re * b.im + a.im * b.re;
    return(v);
}


complex_double CPdiv_CD_CD(complex_double a, complex_double b)
{
    complex_double v;
    double amp, pha;
    double are, aim, bre, bim;

    are = a.re;
    aim = a.im;
    bre = b.re;
    bim = b.im;

    amp = sqrt(are * are + aim * aim);
    amp /= sqrt(bre * bre + bim * bim);
    pha = atan2(aim, are);
    pha -= atan2(bim, bre);

    v.re = (double)(amp * cos(pha));
    v.im = (double)(amp * sin(pha));

    return(v);
}

complex_float CPadd_CF_CF(complex_float a, complex_float b)
{
    complex_float v;
    v.re = a.re + b.re;
    v.im = a.im + b.im;
    return(v);
}

complex_float CPsub_CF_CF(complex_float a, complex_float b)
{
    complex_float v;
    v.re = a.re - b.re;
    v.im = a.im - b.im;
    return(v);
}

complex_float CPmult_CF_CF(complex_float a, complex_float b)
{
    complex_float v;
    v.re = a.re * b.re - a.im * b.im;
    v.im = a.re * b.im + a.im * b.re;
    return(v);
}

complex_float CPdiv_CF_CF(complex_float a, complex_float b)
{
    complex_float v;
    float amp, pha;
    float are, aim, bre, bim;

    are = a.re;
    aim = a.im;
    bre = b.re;
    bim = b.im;

    amp = sqrt(are * are + aim * aim);
    amp /= sqrt(bre * bre + bim * bim);
    pha = atan2(aim, are);
    pha -= atan2(bim, bre);

    v.re = (float)(amp * cos(pha));
    v.im = (float)(amp * sin(pha));

    return(v);
}




errno_t arith_image_Cadd(
    const char *ID1_name,
    const char *ID2_name,
    const char *ID_out
)
{
    uint8_t atype1, atype2;
    imageID ID1;
    imageID ID2;

    ID1 = image_ID(ID1_name);
    ID2 = image_ID(ID2_name);
    atype1 = data.image[ID1].md[0].datatype;
    atype2 = data.image[ID2].md[0].datatype;

    if((atype1 == _DATATYPE_COMPLEX_FLOAT) && (atype2 ==  _DATATYPE_COMPLEX_FLOAT))
    {
        arith_image_function_CF_CF__CF(ID1_name, ID2_name, ID_out, &CPadd_CF_CF);
        return RETURN_SUCCESS;
    }

    if((atype1 == _DATATYPE_COMPLEX_DOUBLE)
            && (atype2 ==  _DATATYPE_COMPLEX_DOUBLE))
    {
        arith_image_function_CD_CD__CD(ID1_name, ID2_name, ID_out, &CPadd_CD_CD);
        return RETURN_SUCCESS;
    }
    PRINT_ERROR( "data types do not match");

    return RETURN_FAILURE;
}



errno_t arith_image_Csub(
    const char *ID1_name,
    const char *ID2_name,
    const char *ID_out
)
{
    uint8_t datatype1, datatype2;
    imageID ID1;
    imageID ID2;

    ID1 = image_ID(ID1_name);
    ID2 = image_ID(ID2_name);
    datatype1 = data.image[ID1].md[0].datatype;
    datatype2 = data.image[ID2].md[0].datatype;

    if((datatype1 == _DATATYPE_COMPLEX_FLOAT)
            && (datatype2 ==  _DATATYPE_COMPLEX_FLOAT))
    {
        arith_image_function_CF_CF__CF(ID1_name, ID2_name, ID_out, &CPsub_CF_CF);
        return RETURN_SUCCESS;
    }

    if((datatype1 == _DATATYPE_COMPLEX_DOUBLE)
            && (datatype2 ==  _DATATYPE_COMPLEX_DOUBLE))
    {
        arith_image_function_CD_CD__CD(ID1_name, ID2_name, ID_out, &CPsub_CD_CD);
        return RETURN_SUCCESS;
    }
    PRINT_ERROR("data types do not match");

    return RETURN_FAILURE;
}



errno_t arith_image_Cmult(
    const char *ID1_name,
    const char *ID2_name,
    const char *ID_out
)
{
    uint8_t datatype1, datatype2;
    imageID ID1;
    imageID ID2;

    ID1 = image_ID(ID1_name);
    ID2 = image_ID(ID2_name);
    datatype1 = data.image[ID1].md[0].datatype;
    datatype2 = data.image[ID2].md[0].datatype;

    if((datatype1 == _DATATYPE_COMPLEX_FLOAT)
            && (datatype2 ==  _DATATYPE_COMPLEX_FLOAT))
    {
        arith_image_function_CF_CF__CF(ID1_name, ID2_name, ID_out, &CPmult_CF_CF);
        return RETURN_SUCCESS;
    }

    if((datatype1 == _DATATYPE_COMPLEX_DOUBLE)
            && (datatype2 ==  _DATATYPE_COMPLEX_DOUBLE))
    {
        arith_image_function_CD_CD__CD(ID1_name, ID2_name, ID_out, &CPmult_CD_CD);
        return RETURN_SUCCESS;
    }
    PRINT_ERROR("data types do not match");

    return RETURN_FAILURE;
}



int arith_image_Cdiv(
    const char *ID1_name,
    const char *ID2_name,
    const char *ID_out
)
{
    uint8_t datatype1, datatype2;
    imageID ID1;
    imageID ID2;

    ID1 = image_ID(ID1_name);
    ID2 = image_ID(ID2_name);
    datatype1 = data.image[ID1].md[0].datatype;
    datatype2 = data.image[ID2].md[0].datatype;

    if((datatype1 == _DATATYPE_COMPLEX_FLOAT)
            && (datatype2 ==  _DATATYPE_COMPLEX_FLOAT))
    {
        arith_image_function_CF_CF__CF(ID1_name, ID2_name, ID_out, &CPdiv_CF_CF);
        return RETURN_SUCCESS;
    }

    if((datatype1 == _DATATYPE_COMPLEX_DOUBLE)
            && (datatype2 ==  _DATATYPE_COMPLEX_DOUBLE))
    {
        arith_image_function_CD_CD__CD(ID1_name, ID2_name, ID_out, &CPdiv_CD_CD);
        return RETURN_SUCCESS;
    }
    PRINT_ERROR("data types do not match");

    return RETURN_FAILURE;
}










/* ------------------------------------------------------------------------- */
/* image, double  -> image                                                */
/* ------------------------------------------------------------------------- */


int arith_image_function_1f_1(const char *ID_name, double f1,
                              const char *ID_out, double (*pt2function)(double, double))
{
    long ID;
    long IDout;
    long ii;
    uint32_t *naxes = NULL;
    long nelement;
    long naxis;
    uint8_t datatype, datatypeout;
    long i;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxis = data.image[ID].md[0].naxis;
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }

    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[ID].md[0].size[i];
    }

    datatypeout = _DATATYPE_FLOAT;
    if(datatype == _DATATYPE_DOUBLE)
    {
        datatypeout = _DATATYPE_DOUBLE;
    }

    IDout = create_image_ID(ID_out, naxis, naxes, datatypeout, data.SHARED_DFT,
                            data.NBKEWORD_DFT);

    free(naxes);
    nelement = data.image[ID].md[0].nelement;



# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif


        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI8[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI16[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI32[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI64[ii]), f1);
            }
        }


        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI8[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI16[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI32[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI64[ii]), f1);
            }
        }


        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.F[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.D[ii] = (double) pt2function((double)(
                                                    data.image[ID].array.D[ii]), f1);
            }
        }
# ifdef _OPENMP
    }
# endif



    return EXIT_SUCCESS;
}



int arith_image_function_1f_1_inplace_byID(long ID, double f1,
        double (*pt2function)(double, double))
{
    long ii;
    long nelement;
    uint8_t datatype;

    datatype = data.image[ID].md[0].datatype;
    nelement = data.image[ID].md[0].nelement;

# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif


        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(data.image[ID].array.UI8[ii]),
                                             f1);
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI16[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI32[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.UI64[ii]), f1);
            }
        }


        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(data.image[ID].array.SI8[ii]),
                                             f1);
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI16[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI32[ii]), f1);
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(
                                                 data.image[ID].array.SI64[ii]), f1);
            }
        }


        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(data.image[ID].array.F[ii]),
                                             f1);
            }
        }
        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.D[ii] = (double) pt2function((double)(
                                                 data.image[ID].array.D[ii]), f1);
            }
        }
# ifdef _OPENMP
    }
# endif

    return EXIT_SUCCESS;
}




int arith_image_function_1f_1_inplace(const char *ID_name, double f1,
                                      double (*pt2function)(double, double))
{
    long ID;
    ID = image_ID(ID_name);

    return (arith_image_function_1f_1_inplace_byID(ID, f1, pt2function));
}











int arith_image_cstfmod(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Pfmod);
    return(0);
}
int arith_image_cstadd(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Padd);
    return(0);
}
int arith_image_cstsub(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Psub);
    return(0);
}
int arith_image_cstsubm(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Psubm);
    return(0);
}
int arith_image_cstmult(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Pmult);
    return(0);
}
int arith_image_cstdiv(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Pdiv);
    return(0);
}
int arith_image_cstdiv1(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Pdiv1);
    return(0);
}
int arith_image_cstpow(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Ppow);
    return(0);
}
int arith_image_cstmaxv(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Pmaxv);
    return(0);
}
int arith_image_cstminv(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Pminv);
    return(0);
}
int arith_image_csttestlt(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Ptestlt);
    return(0);
}
int arith_image_csttestmt(const char *ID_name, double f1, const char *ID_out)
{
    arith_image_function_1f_1(ID_name, f1, ID_out, &Ptestmt);
    return(0);
}

int arith_image_cstfmod_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Pfmod);
    return(0);
}
int arith_image_cstadd_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Padd);
    return(0);
}
int arith_image_cstsub_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Psub);
    return(0);
}
int arith_image_cstmult_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Pmult);
    return(0);
}
int arith_image_cstdiv_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Pdiv);
    return(0);
}
int arith_image_cstdiv1_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Pdiv1);
    return(0);
}
int arith_image_cstpow_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Ppow);
    return(0);
}
int arith_image_cstmaxv_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Pmaxv);
    return(0);
}
int arith_image_cstminv_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Pminv);
    return(0);
}
int arith_image_csttestlt_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Ptestlt);
    return(0);
}
int arith_image_csttestmt_inplace(const char *ID_name, double f1)
{
    arith_image_function_1f_1_inplace(ID_name, f1, &Ptestmt);
    return(0);
}

int arith_image_cstfmod_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Pfmod);
    return(0);
}
int arith_image_cstadd_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Padd);
    return(0);
}
int arith_image_cstsub_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Psub);
    return(0);
}
int arith_image_cstmult_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Pmult);
    return(0);
}
int arith_image_cstdiv_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Pdiv);
    return(0);
}
int arith_image_cstdiv1_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Pdiv1);
    return(0);
}
int arith_image_cstpow_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Ppow);
    return(0);
}
int arith_image_cstmaxv_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Pmaxv);
    return(0);
}
int arith_image_cstminv_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Pminv);
    return(0);
}
int arith_image_csttestlt_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Ptestlt);
    return(0);
}
int arith_image_csttestmt_inplace_byID(long ID, double f1)
{
    arith_image_function_1f_1_inplace_byID(ID, f1, &Ptestmt);
    return(0);
}





/* ------------------------------------------------------------------------- */
/* image, double, double -> image                                      */
/* ------------------------------------------------------------------------- */


int arith_image_function_1ff_1(const char *ID_name, double f1, double f2,
                               const char *ID_out, double (*pt2function)(double, double, double))
{
    long ID;
    long IDout;
    long ii;
    uint32_t *naxes = NULL;
    long nelement;
    long naxis;
    uint8_t datatype;
    uint8_t datatypeout;
    long i;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    naxis = data.image[ID].md[0].naxis;
    naxes = (uint32_t *) malloc(sizeof(uint32_t) * naxis);
    if(naxes == NULL)
    {
        PRINT_ERROR("malloc() error");
        exit(0);
    }

    for(i = 0; i < naxis; i++)
    {
        naxes[i] = data.image[ID].md[0].size[i];
    }
    datatypeout = _DATATYPE_FLOAT;
    if(datatype == _DATATYPE_DOUBLE)
    {
        datatypeout = _DATATYPE_DOUBLE;
    }

    IDout = create_image_ID(ID_out, naxis, naxes, datatypeout, data.SHARED_DFT,
                            data.NBKEWORD_DFT);
    free(naxes);
    nelement = data.image[ID].md[0].nelement;

# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif

        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI8[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI16[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI32[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.UI64[ii]), f1, f2);
            }
        }


        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI8[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI16[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI32[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.SI64[ii]), f1, f2);
            }
        }

        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.F[ii] = pt2function((double)(
                                                    data.image[ID].array.F[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[IDout].array.D[ii] = pt2function((double)(
                                                    data.image[ID].array.D[ii]), f1, f2);
            }
        }
# ifdef _OPENMP
    }
# endif

    return(0);
}






int arith_image_function_1ff_1_inplace(const char *ID_name, double f1,
                                       double f2, double (*pt2function)(double, double, double))
{
    long ID;
    long ii;
    long nelement;
    uint8_t datatype;

    ID = image_ID(ID_name);
    datatype = data.image[ID].md[0].datatype;
    nelement = data.image[ID].md[0].nelement;


# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif


        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.UI8[ii] = (uint8_t) pt2function((double)(
                                                   data.image[ID].array.UI8[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.UI16[ii] = (uint16_t) pt2function((double)(
                                                    data.image[ID].array.UI16[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.UI32[ii] = (uint32_t) pt2function((double)(
                                                    data.image[ID].array.UI32[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.UI64[ii] = (uint64_t) pt2function((double)(
                                                    data.image[ID].array.UI64[ii]), f1, f2);
            }
        }


        if(datatype == _DATATYPE_INT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.SI8[ii] = (int8_t) pt2function((double)(
                                                   data.image[ID].array.SI8[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_INT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.SI16[ii] = (int16_t) pt2function((double)(
                                                    data.image[ID].array.SI16[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.SI32[ii] = (int32_t) pt2function((double)(
                                                    data.image[ID].array.SI32[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_INT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.SI64[ii] = (int64_t) pt2function((double)(
                                                    data.image[ID].array.SI64[ii]), f1, f2);
            }
        }



        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(data.image[ID].array.F[ii]),
                                             f1, f2);
            }
        }
        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.D[ii] = pt2function((double)(data.image[ID].array.D[ii]),
                                             f1, f2);
            }
        }
# ifdef _OPENMP
    }
# endif

    return(0);
}





int arith_image_function_1ff_1_inplace_byID(long ID, double f1, double f2,
        double (*pt2function)(double, double, double))
{
    long ii;
    long nelement;
    uint8_t datatype;

    datatype = data.image[ID].md[0].datatype;
    nelement = data.image[ID].md[0].nelement;

# ifdef _OPENMP
    #pragma omp parallel if (nelement>OMP_NELEMENT_LIMIT)
    {
# endif


        if(datatype == _DATATYPE_UINT8)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.UI8[ii] = (uint8_t) pt2function((double)(
                                                   data.image[ID].array.UI8[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_UINT16)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.UI16[ii] = (uint16_t) pt2function((double)(
                                                    data.image[ID].array.UI16[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_UINT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.UI32[ii] = (uint32_t) pt2function((double)(
                                                    data.image[ID].array.UI32[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_UINT64)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.UI64[ii] = (uint64_t) pt2function((double)(
                                                    data.image[ID].array.UI64[ii]), f1, f2);
            }
        }



        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.SI8[ii] = (int8_t) pt2function((double)(
                                                   data.image[ID].array.SI8[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.SI16[ii] = (int16_t) pt2function((double)(
                                                    data.image[ID].array.SI16[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.SI32[ii] = (int32_t) pt2function((double)(
                                                    data.image[ID].array.SI32[ii]), f1, f2);
            }
        }
        if(datatype == _DATATYPE_INT32)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.SI64[ii] = (int64_t) pt2function((double)(
                                                    data.image[ID].array.SI64[ii]), f1, f2);
            }
        }


        if(datatype == _DATATYPE_FLOAT)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.F[ii] = pt2function((double)(data.image[ID].array.F[ii]),
                                             f1, f2);
            }
        }

        if(datatype == _DATATYPE_DOUBLE)
        {
# ifdef _OPENMP
            #pragma omp for
# endif
            for(ii = 0; ii < nelement; ii++)
            {
                data.image[ID].array.D[ii] = pt2function((double)(data.image[ID].array.D[ii]),
                                             f1, f2);
            }
        }
# ifdef _OPENMP
    }
# endif

    return(0);
}


double Ptrunc(double a, double b, double c)
{
    double value;
    value = a;
    if(a < b)
    {
        value = b;
    };
    if(a > c)
    {
        value = c;
    };
    return(value);
}

int arith_image_trunc(const char *ID_name, double f1, double f2,
                      const char *ID_out)
{
    arith_image_function_1ff_1(ID_name, f1, f2, ID_out, &Ptrunc);
    return(0);
}

int arith_image_trunc_inplace(const char *ID_name, double f1, double f2)
{
    arith_image_function_1ff_1_inplace(ID_name, f1, f2, &Ptrunc);
    return(0);
}
int arith_image_trunc_inplace_byID(long ID, double f1, double f2)
{
    arith_image_function_1ff_1_inplace_byID(ID, f1, f2, &Ptrunc);
    return(0);
}




int isoperand(const char *word)
{
    int value = 0;

    if(strcmp(word, "+") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "-") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "/") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "*") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "^") == 0)
    {
        value = 1;
    }

    return(value);
}


int isfunction(const char *word)
{
    int value = 0;

    if(strcmp(word, "acos") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "asin") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "atan") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "ceil") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "cos") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "cosh") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "exp") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "fabs") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "floor") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "imedian") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "itot") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "imean") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "imin") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "imax") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "ln") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "log") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "sqrt") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "sin") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "sinh") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "tan") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "tanh") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "posi") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "imdx") == 0)
    {
        value = 1;
    }
    if(strcmp(word, "imdy") == 0)
    {
        value = 1;
    }


    /*  if (!strcmp(word,"pow"))
        value = 1;
      if (!strcmp(word,"max"))
        value = 1;
      if (!strcmp(word,"min"))
        value = 1;
      if (!strcmp(word,"median"))
        value = 1;
    */
    return(value);
}



int isfunction_sev_var(const char *word)
{
    int value = 0; /* number of input variables */

    if(strcmp(word, "fmod") == 0)
    {
        value = 2;
    }
    if(strcmp(word, "trunc") == 0)
    {
        value = 3;
    }
    if(strcmp(word, "perc") == 0)
    {
        value = 2;
    }
    if(strcmp(word, "min") == 0)
    {
        value = 2;
    }
    if(strcmp(word, "max") == 0)
    {
        value = 2;
    }
    if(strcmp(word, "testlt") == 0)
    {
        value = 2;
    }
    if(strcmp(word, "testmt") == 0)
    {
        value = 2;
    }


    return(value);
}


int isanumber(const char *word)
{
    int value = 1; // 1 if number, 0 otherwise
    char *endptr;
    __attribute__((unused)) double v1;

    v1 = strtod(word, &endptr);
    if((long)(endptr - word) == (long) strlen(word))
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    return(value);
}


/*int isanumber(const char *word)
{
  int value = 1;
  unsigned int i;
  int passed_point=0;

  for(i=0;i<strlen(word);i++)
    {
      if(!isdigit(word[i]))
	{
	  if(word[i]=='.')
	    {
	      if (passed_point==0)
		passed_point = 1;
	      else
		value = 0;
	    }
	  else
	    value = 0;
	}
    }

  return(value);
}
*/


imageID arith_make_slopexy(
    const char *ID_name,
    long l1,
    long l2,
    double sx,
    double sy
)
{
    imageID ID;
    uint32_t naxes[2];
    double coeff;

    create_2Dimage_ID(ID_name, l1, l2);
    ID = image_ID(ID_name);
    naxes[0] = data.image[ID].md[0].size[0];
    naxes[1] = data.image[ID].md[0].size[1];

    coeff = sx * (naxes[0] / 2) + sy * (naxes[1] / 2);

    for(uint32_t jj = 0; jj < naxes[1]; jj++)
        for(uint32_t ii = 0; ii < naxes[0]; ii++)
        {
            data.image[ID].array.F[jj * naxes[0] + ii] = sx * ii + sy * jj - coeff;
        }

    return ID;
}





/*^-----------------------------------------------------------------------------
| int
| execute_arith :
|     const char *cmd :
|
|
|    0 : unknown
|    1 : non-existing variable or image
|    2 : existing variable
|    3 : number
|    4 : operand
|    5 : opening brace
|    6 : closing brace
|    7 : coma
|    8 : function
|    9 : equal sign
|    10 : existing image
|    11 : function of several variables/images, returning one variable/image
|
|
+-----------------------------------------------------------------------------*/
int execute_arith(const char *cmd1)
{
    char word[100][100];
    int i, w, l, j;
    int nbword;
    int word_type[100];
    int par_level[100];
    int parlevel;
    int intr_priority[100]; /* 0 (+,-)  1 (*,/)  2 (functions) */


    int found_word_type;
    int highest_parlevel;
    int highest_intr_priority;
    int highest_priority_index;
    int passedequ;
    int tmp_name_index;
//    char name[STRINGMAXLEN_IMGNAME];
//    char name1[SBUFFERSIZE];
    double tmp_prec;
    int nb_tbp_word;
    int type = 0;
    int nbvarinput;

    char cmd[SBUFFERSIZE];
    long cntP;
    int OKea = 1;
    int n;

    int Debug = 0;

    //  if( Debug > 0 )   fprintf(stdout, "[execute_arith]\n");
    //  if( Debug > 0 )   fprintf(stdout, "[execute_arith] str: [%s]\n", cmd1);

    for(i = 0; i < 100; i++)
    {
        word_type[i] = 0;
        par_level[i] = 0;
        intr_priority[i] = 0;
    }




    /*
       Pre-process string:
       - remove any spaces in cmd1
       - replace "=-" by "=0-" and "=+" by "="
       copy result into cmd */
    j = 0;

    for(i = 0; i < (int)(strlen(cmd1)); i++)
    {
        if((cmd1[i] == '=') && (cmd1[i + 1] == '-'))
        {
            cmd[j] = '=';
            j++;
            cmd[j] = '0';
            j++;
        }
        else if((cmd1[i] == '=') && (cmd1[i + 1] == '+'))
        {
            cmd[j] = '=';
            j++;
            i++;
        }
        else if(cmd1[i] != ' ')
        {
            cmd[j] = cmd1[i];
            j++;
        }
    }
    cmd[j] = '\0';
    //  if( Debug > 0 )   fprintf(stdout, "[execute_arith] preprocessed str %s -> %s\n", cmd1, cmd);



    /*
    * cmd is first broken into words.
    * The spacing between words is operands (+,-,/,*), equal (=),
    * space ,comma and braces
    */
    w = 0;
    l = 0;
    for(i = 0; i < (signed) strlen(cmd); i++)
    {
        switch(cmd[i])
        {

            case '+':
            case '-':
                if(((cmd[i - 1] == 'e') || (cmd[i - 1] == 'E')) && (isdigit(cmd[i - 2]))
                        && (isdigit(cmd[i + 1])))
                {
                    // + or - is part of exponent
                    word[w][l] = cmd[i];
                    l++;
                }
                else
                {
                    if(l > 0)
                    {
                        word[w][l] = '\0';
                        w++;
                    }
                    l = 0;
                    word[w][l] = cmd[i];
                    word[w][1] = '\0';
                    if(i < (signed)(strlen(cmd) - 1))
                    {
                        w++;
                    }
                    l = 0;
                }
                break;

            case '*':
            case '/':
            case '^':
            case '(':
            case ')':
            case '=':
            case ',':
                if(l > 0)
                {
                    word[w][l] = '\0';
                    w++;
                }
                l = 0;
                word[w][l] = cmd[i];
                word[w][1] = '\0';
                if(i < (signed)(strlen(cmd) - 1))
                {
                    w++;
                }
                l = 0;
                break;

            case ' ':
                word[w][l] = '\0';
                w++;
                l = 0;

                /*word[w][l] = '\0';
                  w++;
                  l = 0;*/
                break;

            default:
                word[w][l] = cmd[i];
                l++;
                break;
        }
    }


    if(l > 0)
    {
        word[w][l] = '\0';
    }
    nbword = w + 1;


    //  printf("number of words is %d\n",nbword);

    for(i = 0; i < nbword; i++)
    {
        if(Debug > 0)
        {
            printf("TESTING WORD %d = %s\n", i, word[i]);
        }
        word_type[i] = 0;
        found_word_type = 0;
        if((isanumber(word[i]) == 1) && (found_word_type == 0))
        {
            word_type[i] = 3;
            found_word_type = 1;
        }
        if((isfunction(word[i]) == 1) && (found_word_type == 0))
        {
            word_type[i] = 8;
            found_word_type = 1;
        }
        if((isfunction_sev_var(word[i]) != 0) && (found_word_type == 0))
        {
            word_type[i] = 11;
            found_word_type = 1;
        }
        if((isoperand(word[i]) == 1) && (found_word_type == 0))
        {
            word_type[i] = 4;
            found_word_type = 1;
        }
        if((strcmp(word[i], "=") == 0) && (found_word_type == 0))
        {
            word_type[i] = 9;
            found_word_type = 1;
        }
        if((strcmp(word[i], ",") == 0) && (found_word_type == 0))
        {
            word_type[i] = 7;
            found_word_type = 1;
        }
        if((i < nbword - 1) && (found_word_type == 0))
        {
            if((strcmp(word[i + 1], "(") == 0) && (isfunction(word[i]) == 1))
            {
                word_type[i] = 8;
                found_word_type = 1;
            }
        }
        if((strcmp(word[i], "(") == 0) && (found_word_type == 0))
        {
            word_type[i] = 5;
            found_word_type = 1;
        }
        if((strcmp(word[i], ")") == 0) && (found_word_type == 0))
        {
            word_type[i] = 6;
            found_word_type = 1;
        }
        if((variable_ID(word[i]) != -1) && (found_word_type == 0))
        {
            word_type[i] = 2;
            found_word_type = 1;
        }
        if((image_ID(word[i]) != -1) && (found_word_type == 0))
        {
            word_type[i] = 10;
            found_word_type = 1;
        }
        if(found_word_type == 0)
        {
            word_type[i] = 1;
        }
        if(Debug > 0)
        {
            printf("word %d is  \"%s\" word typ is %d\n", i, word[i], word_type[i]);
        }
    }









    /* checks for obvious errors */

    passedequ = 0;
    for(i = (nbword - 1); i > -1; i--)
    {
        if(passedequ == 1)
        {
            if(word_type[i] == 9)
            {
                PRINT_WARNING("line has multiple \"=\"");
                OKea = 0;
            }
            if(word_type[i] == 4)
            {
                PRINT_WARNING("operand on left side of \"=\"");
                OKea = 0;
            }
            if(word_type[i] == 5)
            {
                PRINT_WARNING("\"(\" on left side of \"=\"");
                OKea = 0;
            }
            if(word_type[i] == 6)
            {
                PRINT_WARNING( "\")\" on left side of \"=\"");
                OKea = 0;
            }
        }
        if(word_type[i] == 9)
        {
            passedequ = 1;
        }
        if((passedequ == 0)
                && (word_type[i] == 1)) /* non-existing variable or image as input */
        {
            PRINT_WARNING("%s is a non-existing variable or image", word[i]);
            OKea = 0;
        }
    }

    for(i = 0; i < nbword - 1; i++)
    {
        if((word_type[i] == 4) && (word_type[i + 1] == 4))
        {
            PRINT_WARNING("consecutive operands");
            OKea = 0;
        }
        if((word_type[i + 1] == 5) && (!((word_type[i] == 5) || (word_type[i] == 8)
                                         || (word_type[i] == 11) || (word_type[i] == 9) || (word_type[i] == 4))))
        {
            PRINT_WARNING("\"(\" should be preceeded by \"=\", \"(\", operand or function");
            OKea = 0;
        }
    }

    cntP = 0;
    for(i = 0; i < nbword; i++)
    {
        if(word_type[i] == 5)
        {
            cntP ++;
        }
        if(word_type[i] == 6)
        {
            cntP --;
        }
        if(cntP < 0)
        {
            PRINT_WARNING("parentheses error");
            OKea = 0;
        }
    }
    if(cntP != 0)
    {
        PRINT_WARNING("parentheses error");
        OKea = 0;
    }










    if(OKea == 1)
    {
        /* numbers are saved into variables */
        tmp_name_index = 0;
        for(i = 0; i < nbword; i++)
        {
            if(word_type[i] == 3)
            {
                CREATE_IMAGENAME(name, "_tmp%d_%d", tmp_name_index, (int) getpid());

                create_variable_ID(name, 1.0 * strtod(word[i], NULL));
                strcpy(word[i], name);
                word_type[i] = 2;
                tmp_name_index++;
            }
        }

        /* computing the number of to-be-processed words */
        passedequ = 0;
        nb_tbp_word = 0;
        for(i = (nbword - 1); i > -1; i--)
        {
            if(word_type[i] == 9)
            {
                passedequ = 1;
            }
            if(passedequ == 0)
            {
                nb_tbp_word++;
            }
        }

        /* main loop starts here */
        while(nb_tbp_word > 1)
        {
            /* non necessary braces are removed
             */
            for(i = 0; i < nbword - 2; i++)
                if((word_type[i] == 5) && (word_type[i + 2] == 6))
                {
                    strcpy(word[i], word[i + 1]);
                    word_type[i] = word_type[i + 1];
                    for(j = i + 1; j < nbword - 2; j++)
                    {
                        strcpy(word[j], word[j + 2]);
                        word_type[j] = word_type[j + 2];
                    }
                    nbword = nbword - 2;
                }
            for(i = 0; i < nbword - 3; i++)
                if((word_type[i] == 5) && (word_type[i + 3] == 6)
                        && (strcmp(word[i + 1], "-") == 0))
                {
                    data.variable[variable_ID(word[i + 2])].value.f = -data.variable[variable_ID(
                                word[i + 2])].value.f;
                    strcpy(word[i], word[i + 2]);
                    word_type[i] = word_type[i + 2];
                    for(j = i + 2; j < nbword - 3; j++)
                    {
                        strcpy(word[j], word[j + 3]);
                        word_type[j] = word_type[j + 3];
                    }
                    nbword = nbword - 3;
                }

            /* now the priorities are given */

            parlevel = 0;
            for(i = 0; i < nbword; i++)
            {
                if(word_type[i] == 5)
                {
                    parlevel++;
                }
                if(word_type[i] == 6)
                {
                    parlevel--;
                }
                if((word_type[i] == 4) || (word_type[i] == 8) || (word_type[i] == 11))
                {
                    par_level[i] = parlevel;
                    if(word_type[i] == 8)
                    {
                        intr_priority[i] = 2;
                    }
                    if(word_type[i] == 11)
                    {
                        intr_priority[i] = 2;
                    }
                    if(word_type[i] == 4)
                    {
                        if((strcmp(word[i], "+") == 0) || (strcmp(word[i], "-") == 0))
                        {
                            intr_priority[i] = 0;
                        }
                        if((strcmp(word[i], "*") == 0) || (strcmp(word[i], "/") == 0))
                        {
                            intr_priority[i] = 1;
                        }
                    }
                }
            }

            /* the highest priority operation is executed */
            highest_parlevel = 0;
            highest_intr_priority = -1;
            highest_priority_index = -1;

            for(i = 0; i < nbword; i++)
            {
                if((word_type[i] == 4) || (word_type[i] == 8) || (word_type[i] == 11))
                {
                    /*printf("operation \"%s\" (%d,%d)\n",word[i],par_level[i],intr_priority[i]);*/
                    if(par_level[i] > highest_parlevel)
                    {
                        highest_priority_index = i;
                        highest_parlevel = par_level[i];
                        highest_intr_priority = 0;
                    }
                    else
                    {
                        if((par_level[i] == highest_parlevel)
                                && (intr_priority[i] > highest_intr_priority))
                        {
                            highest_priority_index = i;
                            highest_intr_priority = intr_priority[i];
                        }
                    }
                }
            }

            /*      printf("executing operation  %s\n",word[highest_priority_index]);*/

            i = highest_priority_index;

            /*      printf("before : ");
              for (j=0;j<nbword;j++)
              {
              if(j==i)
              printf(">>");
              if(variable_ID(word[j])!=-1)
              printf(" %s(%f) ",word[j],data.variable[variable_ID(word[j])].value.f);
              else
              printf(" %s ",word[j]);
              }
              printf("\n");
            */
            if(word_type[i] == 4)
            {
				// name of image/variable where output is written
				CREATE_IMAGENAME(name, "_tmp%d_%d", tmp_name_index, (int) getpid());
				
                if(strcmp(word[i], "+") == 0)
                {
                    if((word_type[i - 1] == 2) && (word_type[i + 1] == 2))
                    {
                        tmp_prec = data.variable[variable_ID(word[i - 1])].value.f +
                                   data.variable[variable_ID(word[i + 1])].value.f;
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if((word_type[i - 1] == 2) && (word_type[i + 1] == 10))
                    {
                        arith_image_cstadd(word[i + 1],
                                           (double) data.variable[variable_ID(word[i - 1])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i - 1] == 10) && (word_type[i + 1] == 2))
                    {
                        arith_image_cstadd(word[i - 1],
                                           (double) data.variable[variable_ID(word[i + 1])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i - 1] == 10) && (word_type[i + 1] == 10))
                    {
                        arith_image_add(word[i - 1], word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "-") == 0)
                {
                    if((word_type[i - 1] == 2) && (word_type[i + 1] == 2))
                    {
                        tmp_prec = data.variable[variable_ID(word[i - 1])].value.f -
                                   data.variable[variable_ID(word[i + 1])].value.f;
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if((word_type[i - 1] == 2) && (word_type[i + 1] == 10))
                    {
                        CREATE_IMAGENAME(name1, "_tmp1%d_%d", tmp_name_index, (int) getpid());
                        arith_image_cstsub(word[i + 1],
                                           (double) data.variable[variable_ID(word[i - 1])].value.f, name1);
                        arith_image_cstmult(name1, (double) -1.0, name);
                        delete_image_ID(name1);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i - 1] == 10) && (word_type[i + 1] == 2))
                    {
                        arith_image_cstsub(word[i - 1],
                                           (double) data.variable[variable_ID(word[i + 1])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i - 1] == 10) && (word_type[i + 1] == 10))
                    {
                        arith_image_sub(word[i - 1], word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "*") == 0)
                {
                    if((word_type[i - 1] == 2) && (word_type[i + 1] == 2))
                    {
                        tmp_prec = data.variable[variable_ID(word[i - 1])].value.f *
                                   data.variable[variable_ID(word[i + 1])].value.f;
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if((word_type[i - 1] == 2) && (word_type[i + 1] == 10))
                    {
                        arith_image_cstmult(word[i + 1],
                                            (double) data.variable[variable_ID(word[i - 1])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i - 1] == 10) && (word_type[i + 1] == 2))
                    {
                        arith_image_cstmult(word[i - 1],
                                            (double) data.variable[variable_ID(word[i + 1])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i - 1] == 10) && (word_type[i + 1] == 10))
                    {
                        arith_image_mult(word[i - 1], word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "/") == 0)
                {
                    if((word_type[i - 1] == 2) && (word_type[i + 1] == 2))
                    {
                        tmp_prec = data.variable[variable_ID(word[i - 1])].value.f /
                                   data.variable[variable_ID(word[i + 1])].value.f;
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if((word_type[i - 1] == 2) && (word_type[i + 1] == 10))
                    {
                        //    printf("CASE 1\n");
                        arith_image_cstdiv1(word[i + 1],
                                            (double) data.variable[variable_ID(word[i - 1])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i - 1] == 10) && (word_type[i + 1] == 2))
                    {
                        arith_image_cstdiv(word[i - 1],
                                           (double) data.variable[variable_ID(word[i + 1])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i - 1] == 10) && (word_type[i + 1] == 10))
                    {
                        arith_image_div(word[i - 1], word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "^") == 0)
                {
                    if((word_type[i - 1] == 2) && (word_type[i + 1] == 2))
                    {
                        if(data.variable[variable_ID(word[i + 1])].value.f < 0)
                        {
                            tmp_prec = pow(data.variable[variable_ID(word[i - 1])].value.f,
                                           -data.variable[variable_ID(word[i + 1])].value.f);
                            tmp_prec = 1.0 / tmp_prec;
                        }
                        else
                        {
                            tmp_prec = pow(data.variable[variable_ID(word[i - 1])].value.f,
                                           data.variable[variable_ID(word[i + 1])].value.f);
                        }
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if((word_type[i - 1] == 2) && (word_type[i + 1] == 10))
                    {
                        CREATE_IMAGENAME(name1, "_tmp1%d_%d", tmp_name_index, (int) getpid());
                        arith_image_cstadd(word[i + 1],
                                           (double) data.variable[variable_ID(word[i - 1])].value.f, name1);
                        arith_image_pow(name1, word[i + 1], name);
                        delete_image_ID(name1);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i - 1] == 10) && (word_type[i + 1] == 2))
                    {
                        arith_image_cstpow(word[i - 1],
                                           (double) data.variable[variable_ID(word[i + 1])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i - 1] == 10) && (word_type[i + 1] == 10))
                    {
                        arith_image_pow(word[i - 1], word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                strcpy(word[i - 1], name);
                word_type[i - 1] = type;
                for(j = i; j < nbword - 2; j++)
                {
                    strcpy(word[j], word[j + 2]);
                    word_type[j] = word_type[j + 2];
                }
                nbword = nbword - 2;
            }



            if(word_type[i] == 8)
            {
				CREATE_IMAGENAME(name, "_tmp%d_%d", tmp_name_index, (int) getpid());
				
                if(strcmp(word[i], "acos") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = acos(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_acos(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "asin") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = asin(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_asin(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "atan") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = atan(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_atan(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "ceil") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = (double) ceil(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_ceil(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "cos") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = cos(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_cos(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "cosh") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = cosh(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_cosh(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "exp") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = exp(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_exp(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "fabs") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = fabs(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_fabs(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "floor") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = floor(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_floor(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "imedian") == 0)
                {
                    if(word_type[i + 1] == 10)
                    {
                        tmp_prec = arith_image_median(word[i + 1]);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                }

                if(strcmp(word[i], "itot") == 0)
                {
                    if(word_type[i + 1] == 10)
                    {
                        tmp_prec = arith_image_total(word[i + 1]);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                }

                if(strcmp(word[i], "imean") == 0)
                {
                    if(word_type[i + 1] == 10)
                    {
                        tmp_prec = arith_image_mean(word[i + 1]);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                }

                if(strcmp(word[i], "imin") == 0)
                {
                    if(word_type[i + 1] == 10)
                    {
                        tmp_prec = arith_image_min(word[i + 1]);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                }

                if(strcmp(word[i], "imax") == 0)
                {
                    if(word_type[i + 1] == 10)
                    {
                        tmp_prec = arith_image_max(word[i + 1]);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                }

                if(strcmp(word[i], "ln") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = log(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_ln(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "log") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = log10(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_log(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "sqrt") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = sqrt(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_sqrt(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "sin") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = sin(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_sin(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "sinh") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = sinh(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_sinh(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "tan") == 0)
                {
                    printf("LINE 4440\n");//TBE
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = tan(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_tan(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "tanh") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = tanh(data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_tanh(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "posi") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        tmp_prec = Ppositive((double) data.variable[variable_ID(word[i + 1])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_positive(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "imdx") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        PRINT_ERROR("Function imdx only applicable on images");
                        exit(0);
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_dx(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "imdy") == 0)
                {
                    if(word_type[i + 1] == 2)
                    {
                        PRINT_ERROR("Function imdy only applicable on images");
                        exit(0);
                    }
                    if(word_type[i + 1] == 10)
                    {
                        arith_image_dy(word[i + 1], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }


                strcpy(word[i], name);
                word_type[i] = type;
                for(j = i + 1; j < nbword - 1; j++)
                {
                    strcpy(word[j], word[j + 1]);
                    word_type[j] = word_type[j + 1];
                }
                nbword = nbword - 1;
            }




            if(word_type[i] == 11)
            {
                nbvarinput = isfunction_sev_var(word[i]);
                CREATE_IMAGENAME(name, "_tmp%d_%d", tmp_name_index, (int) getpid());

                if(strcmp(word[i], "fmod") == 0)
                {
                    if((word_type[i + 2] == 2) && (word_type[i + 4] == 2))
                    {
                        tmp_prec = fmod(data.variable[variable_ID(word[i + 2])].value.f,
                                        data.variable[variable_ID(word[i + 4])].value.f);                        
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if((word_type[i + 2] == 2) && (word_type[i + 4] == 10))
                    {
                        printf("function not available\n");
                    }
                    if((word_type[i + 2] == 10) && (word_type[i + 4] == 2))
                    {
                        arith_image_cstfmod(word[i + 2],
                                            (double) data.variable[variable_ID(word[i + 4])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i + 2] == 10) && (word_type[i + 4] == 10))
                    {
                        arith_image_fmod(word[i + 2], word[i + 4], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }


                if(strcmp(word[i], "min") == 0)
                {
                    if((word_type[i + 2] == 2) && (word_type[i + 4] == 2))
                    {
                        if(data.variable[variable_ID(word[i + 2])].value.f < data.variable[variable_ID(
                                    word[i + 4])].value.f)
                        {
                            tmp_prec = data.variable[variable_ID(word[i + 2])].value.f;
                        }
                        else
                        {
                            tmp_prec = data.variable[variable_ID(word[i + 4])].value.f;
                        }
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    if((word_type[i + 2] == 2) && (word_type[i + 4] == 10))
                    {
                        arith_image_cstminv(word[i + 4],
                                            (double) data.variable[variable_ID(word[i + 2])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i + 2] == 10) && (word_type[i + 4] == 2))
                    {
                        arith_image_cstminv(word[i + 2],
                                            (double) data.variable[variable_ID(word[i + 4])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    if((word_type[i + 2] == 10) && (word_type[i + 4] == 10))
                    {
                        arith_image_minv(word[i + 2], word[i + 4], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }


                if(strcmp(word[i], "max") == 0)
                {
                    if((word_type[i + 2] == 2) && (word_type[i + 4] == 2))
                    {
                        if(data.variable[variable_ID(word[i + 2])].value.f > data.variable[variable_ID(
                                    word[i + 4])].value.f)
                        {
                            tmp_prec = data.variable[variable_ID(word[i + 2])].value.f;
                        }
                        else
                        {
                            tmp_prec = data.variable[variable_ID(word[i + 4])].value.f;
                        }
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    else if((word_type[i + 2] == 2) && (word_type[i + 4] == 10))
                    {
                        arith_image_cstmaxv(word[i + 4],
                                            (double) data.variable[variable_ID(word[i + 2])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    else if((word_type[i + 2] == 10) && (word_type[i + 4] == 2))
                    {
                        arith_image_cstmaxv(word[i + 2],
                                            (double) data.variable[variable_ID(word[i + 4])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    else if((word_type[i + 2] == 10) && (word_type[i + 4] == 10))
                    {
                        arith_image_maxv(word[i + 2], word[i + 4], name);
                        tmp_name_index++;
                        type = 10;
                    }
                }

                if(strcmp(word[i], "testlt") == 0)
                {
                    if((word_type[i + 2] == 2) && (word_type[i + 4] == 2))
                    {
                        if(data.variable[variable_ID(word[i + 2])].value.f > data.variable[variable_ID(
                                    word[i + 4])].value.f)
                        {
                            tmp_prec = 0.0;
                        }
                        else
                        {
                            tmp_prec = 1.0;
                        }
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    else if((word_type[i + 2] == 2) && (word_type[i + 4] == 10))
                    {
                        arith_image_csttestmt(word[i + 4],
                                              (double) data.variable[variable_ID(word[i + 2])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    else if((word_type[i + 2] == 10) && (word_type[i + 4] == 2))
                    {
                        arith_image_csttestlt(word[i + 2],
                                              (double) data.variable[variable_ID(word[i + 4])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    else if((word_type[i + 2] == 10) && (word_type[i + 4] == 10))
                    {
                        arith_image_testlt(word[i + 2], word[i + 4], name);
                        tmp_name_index++;
                        type = 10;
                    }
                    else
                    {
                        PRINT_ERROR("Wrong input to function testlt");
                    }
                }

                if(strcmp(word[i], "testmt") == 0)
                {
                    if((word_type[i + 2] == 2) && (word_type[i + 4] == 2))
                    {
                        if(data.variable[variable_ID(word[i + 2])].value.f > data.variable[variable_ID(
                                    word[i + 4])].value.f)
                        {
                            tmp_prec = 1.0;
                        }
                        else
                        {
                            tmp_prec = 0.0;
                        }
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                    else if((word_type[i + 2] == 2) && (word_type[i + 4] == 10))
                    {
                        arith_image_csttestlt(word[i + 4],
                                              (double) data.variable[variable_ID(word[i + 2])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    else if((word_type[i + 2] == 10) && (word_type[i + 4] == 2))
                    {
                        arith_image_csttestmt(word[i + 2],
                                              (double) data.variable[variable_ID(word[i + 4])].value.f, name);
                        tmp_name_index++;
                        type = 10;
                    }
                    else if((word_type[i + 2] == 10) && (word_type[i + 4] == 10))
                    {
                        arith_image_testmt(word[i + 2], word[i + 4], name);
                        tmp_name_index++;
                        type = 10;
                    }
                    else
                    {
                        PRINT_ERROR("Wrong input to function testlt");
                    }
                }


                if(strcmp(word[i], "perc") == 0)
                {
                    //	      printf("%d %d\n",word_type[i+2],word_type[i+4]);
                    if((word_type[i + 2] != 10) || (word_type[i + 4] != 2))
                    {
                        PRINT_ERROR("Wrong input to function perc\n");
                    }
                    else
                    {
                        //		  printf("Running percentile args = %s %f\n",word[i+2],data.variable[variable_ID(word[i+4])].value.f);
                        tmp_prec = arith_image_percentile(word[i + 2],
                                                          (double) data.variable[variable_ID(word[i + 4])].value.f);
                        create_variable_ID(name, tmp_prec);
                        tmp_name_index++;
                        type = 2;
                    }
                }

                if(strcmp(word[i], "trunc") == 0)
                {
                    if((word_type[i + 2] == 10) && (word_type[i + 4] == 2)
                            && (word_type[i + 6] == 2))
                    {
                        tmp_name_index++;
                        arith_image_trunc(word[i + 2],
                                          (double) data.variable[variable_ID(word[i + 4])].value.f,
                                          (double) data.variable[variable_ID(word[i + 6])].value.f, name);
                        type = 10;
                    }
                    else
                    {
                        printf("Syntax error with function trunc\n");
                    }
                }

                strcpy(word[i], name);
                word_type[i] = type;
                for(j = i + 1; j < nbword - (nbvarinput * 2 + 1); j++)
                {
                    strcpy(word[j], word[j + (nbvarinput * 2 + 1)]);
                    word_type[j] = word_type[j + (nbvarinput * 2 + 1)];
                }
                nbword = nbword - nbvarinput * 2 - 1;
            }




            /*      printf("after : ");
              for (i=0;i<nbword;i++)
              {
              if(variable_ID(word[i])!=-1)
              printf(" %s(%f) ",word[i],data.variable[variable_ID(word[i])].value.f);
              else
              printf(" %s ",word[i]);
              }
              printf("\n");
            */
            /* computing the number of to-be-processed words */
            passedequ = 0;
            nb_tbp_word = 0;
            for(i = (nbword - 1); i > -1; i--)
            {
                if(word_type[i] == 9)
                {
                    passedequ = 1;
                }
                if(passedequ == 0)
                {
                    nb_tbp_word++;
                }
            }

        }

        if(nbword > 2)
        {
            if(word_type[1] == 9)
            {
                if(variable_ID(word[0]) != -1)
                {
                    delete_variable_ID(word[0]);
                }
                if(image_ID(word[0]) != -1)
                {
                    delete_image_ID(word[0]);
                }

                if(word_type[2] == 2)
                {
                    create_variable_ID(word[0], data.variable[variable_ID(word[2])].value.f);
                    printf("%.20g\n", data.variable[variable_ID(word[2])].value.f);
                }
                if(word_type[2] == 10)
                {
                    chname_image_ID(word[2], word[0]);
                }
            }
        }
        else
        {
            printf("%.20g\n", data.variable[variable_ID(word[0])].value.f);
        }

        for(i = 0; i < tmp_name_index; i++)
        {
            CREATE_IMAGENAME(name, "_tmp%d_%d", i, (int) getpid());
            if(variable_ID(name) != -1)
            {
                delete_variable_ID(name);
            }
            if(image_ID(name) != -1)
            {
                delete_image_ID(name);
            }
        }
    }

    return(0);
}
