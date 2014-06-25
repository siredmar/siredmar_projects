/*
 * filter_types.h
 *
 *  Created on: Jan 26, 2014
 *      Author: armin
 */

#include "../inc/std_types.h"

#ifndef FILTER_TYPES_H_
#define FILTER_TYPES_H_


typedef struct
{
   sint16 R;
   sint16 G;
   sint16 B;
} image_rgb888_type;

typedef struct
{
   uint16 xres;
   uint16 yres;
   uint16 *content;
   uint16 x_offset;
   uint16 y_offset;

} framebuffer_type;

typedef struct
{
   uint16 x_dimension;
   uint16 y_dimension;
   sint16 *coeff;
   uint16 inv_normalization;
   uint8 *name;
}filter_type;

#endif /* FILTER_TYPES_H_ */
