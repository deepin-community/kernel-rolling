/*
 * Copyright © 2021 Glenfly Tech Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */
typedef union _REG_MM48C00_MM48C78	//Tile_Surface_Start_Range_Registers_0-15
{
	struct
	{
		CBIOS_U32	TS_Height_8	:11;
		CBIOS_U32	TS_Start_Range_28to8	:21;
	};
	CBIOS_U32	Value;
}REG_MM48C00_MM48C78;


typedef union _REG_MM48C04_MM48C7C	//Tile_Surface_End_Range_Registers_0-15
{
	struct
	{
		CBIOS_U32	TS_Width_8	:11;
		CBIOS_U32	End_Range_Value	:21;
	};
	CBIOS_U32	Value;
}REG_MM48C04_MM48C7C;


typedef union _REG_MM48C80_MM48CBC	//Tile_Surface_Description_Registers__0-15
{
	struct
	{
		CBIOS_U32	Format	:4;
		CBIOS_U32	Rotation_Angle	:2;
		CBIOS_U32	Start_Range_Value_29	:1;
		CBIOS_U32	End_Range_Value_29	:1;
		CBIOS_U32	Reserved	:1;
		CBIOS_U32	Reciprical_of_Surface_Width	:14;
		CBIOS_U32	Destination_Surface	:1;
		CBIOS_U32	Destination_Surface_Width	:8;
	};
	CBIOS_U32	Value;
}REG_MM48C80_MM48CBC;


