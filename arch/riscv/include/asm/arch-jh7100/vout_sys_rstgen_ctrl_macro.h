/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

/******************************************************************
*
* vout_sys_rstgen controller C MACRO generated by ezchip
*
******************************************************************/

#ifndef _VOUT_SYS_RSTGEN_MACRO_H_
#define _VOUT_SYS_RSTGEN_MACRO_H_

//#define VOUT_SYS_RSTGEN_BASE_ADDR 0x0
#define vout_sys_rstgen_Software_RESET_assert0_REG_ADDR  VOUT_SYS_RSTGEN_BASE_ADDR + 0x0

#define vout_sys_rstgen_Software_RESET_status0_REG_ADDR  VOUT_SYS_RSTGEN_BASE_ADDR + 0x4

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_mapconv_apb_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR); \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_mapconv_apb_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1); \
	_ezchip_macro_read_value_ |= (0x1&0x1); \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR); \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_mapconv_apb_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1); \
	_ezchip_macro_read_value_ |= (0x0&0x1); \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR); \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_mapconv_axi_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 1; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_mapconv_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<1); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<1; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>1; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_mapconv_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<1); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<1; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>1; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_disp0_axi_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 2; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_disp0_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<2); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<2; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>2; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_disp0_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<2); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<2; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>2; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_disp1_axi_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 3; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_disp1_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<3); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<3; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>3; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_disp1_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<3); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<3; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>3; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_lcdc_oclk_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 4; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_lcdc_oclk_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<4); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<4; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>4; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_lcdc_oclk_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<4); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<4; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>4; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_lcdc_axi_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 5; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_lcdc_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<5); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<5; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>5; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_lcdc_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<5); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<5; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>5; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_vpp0_axi_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 6; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_vpp0_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<6); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<6; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>6; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_vpp0_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<6); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<6; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>6; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_vpp1_axi_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 7; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_vpp1_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<7); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<7; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>7; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_vpp1_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<7); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<7; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>7; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_vpp2_axi_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 8; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_vpp2_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<8); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<8; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>8; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_vpp2_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<8); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<8; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>8; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_pixrawout_apb_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 9; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_pixrawout_apb_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<9); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<9; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>9; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_pixrawout_apb_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<9); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<9; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>9; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_pixrawout_axi_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 10; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_pixrawout_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<10); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<10; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>10; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_pixrawout_axi_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<10); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<10; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>10; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_csi2tx_strm0_apb_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 11; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_csi2tx_strm0_apb_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<11); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<11; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>11; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_csi2tx_strm0_apb_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<11); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<11; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>11; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_csi2tx_strm0_pix_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 12; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_csi2tx_strm0_pix_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<12); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<12; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>12; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_csi2tx_strm0_pix_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<12); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<12; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>12; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_csi2tx_ppi_tx_esc_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 13; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_csi2tx_ppi_tx_esc_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<13); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<13; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>13; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_csi2tx_ppi_tx_esc_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<13); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<13; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>13; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_csi2tx_ppi_txbyte_hs_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 14; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_csi2tx_ppi_txbyte_hs_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<14); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<14; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>14; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_csi2tx_ppi_txbyte_hs_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<14); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<14; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>14; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_dsi_apb_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 15; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_dsi_apb_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<15); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<15; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>15; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_dsi_apb_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<15); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<15; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>15; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_dsi_sys_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 16; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_dsi_sys_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<16); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<16; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>16; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_dsi_sys_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<16); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<16; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>16; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_dsi_dpi_pix_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 17; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_dsi_dpi_pix_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<17); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<17; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>17; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_dsi_dpi_pix_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<17); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<17; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>17; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_dsi_ppi_txbyte_hs_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 18; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_dsi_ppi_txbyte_hs_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<18); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<18; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>18; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_dsi_ppi_txbyte_hs_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<18); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<18; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>18; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_dsi_ppi_tx_esc_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 19; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_dsi_ppi_tx_esc_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<19); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<19; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>19; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_dsi_ppi_tx_esc_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<19); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<19; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>19; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#define _READ_RESET_STATUS_vout_sys_rstgen_rstn_dsi_ppi_rx_esc_(_ezchip_macro_read_value_) { \
	_ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR) >> 20; \
	_ezchip_macro_read_value_ &= 0x1;\
}

#define _ASSERT_RESET_vout_sys_rstgen_rstn_dsi_ppi_rx_esc_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<20); \
	_ezchip_macro_read_value_ |= (0x1&0x1)<<20; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>20; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x0); \
}

#define _CLEAR_RESET_vout_sys_rstgen_rstn_dsi_ppi_rx_esc_ { \
	uint32_t _ezchip_macro_read_value_=MA_INW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x1<<20); \
	_ezchip_macro_read_value_ |= (0x0&0x1)<<20; \
	MA_OUTW(vout_sys_rstgen_Software_RESET_assert0_REG_ADDR,_ezchip_macro_read_value_); \
	do { \
		_ezchip_macro_read_value_ = MA_INW(vout_sys_rstgen_Software_RESET_status0_REG_ADDR)>>20; \
		_ezchip_macro_read_value_ &= 0x1;\
	} while(_ezchip_macro_read_value_!=0x1); \
}

#endif //_VOUT_SYS_RSTGEN_MACRO_H_
