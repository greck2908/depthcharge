/*
 * Copyright 2015 Mediatek Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __MTK_I2C_H__
#define __MTK_I2C_H__

#include "drivers/bus/i2c/i2c.h"
#include <libpayload.h>
#include <assert.h>
#include <stddef.h>

/* I2C Configuration */
enum {
	I2C_TRANSFER_TIMEOUT_US  = 100 * 1000,
};

enum i2c_modes {
	I2C_WRITE_MODE		= 0,
	I2C_READ_MODE		= 1,
	I2C_WRITE_READ_MODE	= 2,
};

enum {
	I2C_DMA_CON_TX          = 0x0,
	I2C_DMA_CON_RX          = 0x1,
	I2C_DMA_START_EN        = 0x1,
	I2C_DMA_INT_FLAG_NONE   = 0x0,
	I2C_DMA_CLR_FLAG        = 0x0,
	I2C_DMA_FLUSH_FLAG      = 0x1,
};

/* I2C DMA Registers */
struct mt8173_i2c_dma_regs {
	uint32_t dma_int_flag;
	uint32_t dma_int_en;
	uint32_t dma_en;
	uint32_t dma_rst;
	uint32_t reserved1;
	uint32_t dma_flush;
	uint32_t dma_con;
	uint32_t dma_tx_mem_addr;
	uint32_t dma_rx_mem_addr;
	uint32_t dma_tx_len;
	uint32_t dma_rx_len;
};

check_member(mt8173_i2c_dma_regs, dma_tx_len, 0x24);

/* I2C Register */
struct mt8173_i2c_regs {
	uint32_t data_port;
	uint32_t slave_addr;
	uint32_t intr_mask;
	uint32_t intr_stat;
	uint32_t control;
	uint32_t transfer_len;
	uint32_t transac_len;
	uint32_t delay_len;
	uint32_t timing;
	uint32_t start;
	uint32_t ext_conf;
	uint32_t reserved1;
	uint32_t fifo_stat;
	uint32_t fifo_thresh;
	uint32_t fifo_addr_clr;
	uint32_t reserved2;
	uint32_t io_config;
	uint32_t debug;
	uint32_t hs;
	uint32_t reserved3;
	uint32_t softreset;
	uint32_t dcm;
	uint32_t reserved4[3];
	uint32_t debug_stat;
	uint32_t debug_ctrl;
	uint32_t transfer_aux_len;
};

check_member(mt8173_i2c_regs, debug_stat, 0x64);

typedef struct MTKI2c {
	I2cOps ops;
	struct mt8173_i2c_regs *base;
	struct mt8173_i2c_dma_regs *dma_base;
	uint8_t *write_buffer;
	uint8_t *read_buffer;
} MTKI2c;

enum {
	I2C_TRANS_LEN_MASK = (0xff),
	I2C_TRANS_AUX_LEN_MASK = (0x1f << 8),
	I2C_CONTROL_MASK = (0x3f << 1)
};

/* Register mask */
enum {
	I2C_HS_NACKERR = (1 << 2),
	I2C_ACKERR = (1 << 1),
	I2C_TRANSAC_COMP = (1 << 0),
};

/* i2c control bits */
enum {
	ACK_ERR_DET_EN = (1 << 5),
	DIR_CHG = (1 << 4),
	CLK_EXT = (1 << 3),
	DMA_EN = (1 << 2),
	REPEATED_START_FLAG = (1 << 1),
	STOP_FLAG = (0 << 1)
};

/* I2C Status Code */

enum {
	I2C_OK = 0x0000,
	I2C_SET_SPEED_FAIL_OVER_SPEED = 0xA001,
	I2C_TRANSFER_INVALID_LENGTH = 0xA002,
	I2C_TRANSFER_FAIL_HS_NACKERR = 0xA003,
	I2C_TRANSFER_FAIL_ACKERR = 0xA004,
	I2C_TRANSFER_FAIL_TIMEOUT = 0xA005,
	I2C_TRANSFER_INVALID_ARGUMENT = 0xA006
};

/* -----------------------------------------------------------------------
 * mtk i2c init function.
 *   i2c:    I2C chip config.
 *   Returns: bus
 */
MTKI2c *new_mtk_i2c(uintptr_t base, uintptr_t dma_base);

#endif /* __MTK_I2C_H__ */
