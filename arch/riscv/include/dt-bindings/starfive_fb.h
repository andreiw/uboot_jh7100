/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

#ifndef __STARFIVE_FB_H
#define __STARFIVE_FB_H

/*color code*/
#define COLOR_CODE_16BIT_CONFIG1	0	//PACKET RGB565
#define	COLOR_CODE_16BIT_CONFIG2	1	//UNPACKET RGB565
#define	COLOR_CODE_16BIT_CONFIG3	2	//UNPACKET RGB565
#define	COLOR_CODE_18BIT_CONFIG1	3	//PACKET RGB666
#define	COLOR_CODE_18BIT_CONFIG2	4	//UNPACKET RGB666
#define	COLOR_CODE_24BIT		5	//PACKET RGB888
#define	COLOR_CODE_MAX			6

/*command code*/
#define	DCS_CMD				02
#define	GEN_CMD				03
#define	SW_PACK0			04
#define	SW_PACK1			05
#define	SW_PACK2			06
#define	LW_PACK				07
#define	SHUTDOWN_SW_PACK		08

/*color format, need match to enum COLOR_FORMAT in starfive_vpp.h*/
#define	COLOR_YUV422_UYVY	0
#define	COLOR_YUV422_VYUY	1
#define	COLOR_YUV422_YUYV	2
#define	COLOR_YUV422_YVYU	3
#define	COLOR_YUV420P	4
#define	COLOR_YUV420_NV21	5
#define	COLOR_YUV420_NV12	6
#define	COLOR_RGB888_ARGB	7
#define	COLOR_RGB888_ABGR	8
#define	COLOR_RGB888_RGBA	9
#define	COLOR_RGB888_BGRA	10
#define	COLOR_RGB565	11

#define	SRC_COLORBAR_VIN_ISP	0
#define	SRC_DVP_SENSOR_VIN	1
#define	SRC_DVP_SENSOR_VIN_ISP	2
#define	SRC_CSI2RX_VIN_ISP	3
#define	SRC_DVP_SENSOR_VIN_OV5640	4

#define	WIN_FMT_RGB565		4
#define	WIN_FMT_xRGB1555		5
#define	WIN_FMT_xRGB4444		6
#define	WIN_FMT_xRGB8888		7

#endif
