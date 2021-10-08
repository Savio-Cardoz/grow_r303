#include <stdio.h>
#include <stdlib.h>
#include "growR303.h"
#include "driver/uart.h"
#include "uart_comms.h"

void growr303_init() {
	comm_init();
}

bool is_finger_on_sensor() {
	return (gen_finger_img() == ERR_OK) ? true : false;
}

static err_t gen_finger_img()
{
	uint8_t buffer[SIZEOF_GEN_IMG_CMD];
	grow_r303_instr_t conf_packet;

	buffer[0] = GROW_R303_HEADER / 256;
	buffer[1] = GROW_R303_HEADER % 256;
	buffer[2] = 0xFF;
	buffer[3] = 0xFF;
	buffer[4] = 0xFF;
	buffer[5] = 0xFF;
	buffer[6] = GROW_R303_CMD_PKT;
	buffer[7] = 0x00;
	buffer[8] = 0x03;
	buffer[9] = GROW_R303_INSTR_GET_FINGER_IMG;
	uint32_t chksum = checksum(&buffer[6], 4);
	buffer[10] = chksum / 256;
	buffer[11] = chksum % 256;

	comm_send(buffer, SIZEOF_GEN_IMG_CMD);
	if (COMM_OK == comm_recv(&conf_packet, sizeof(grow_r303_instr_t), 1000))
		return conf_packet.instruction_code;
	
	return ERR_RECV_PKG;
}

static err_t gen_char_file(uint8_t char_buffer_num)
{
	uint8_t buffer[SIZEOF_GEN_CHAR_CMD];
	grow_r303_instr_t conf_packet;

	buffer[0] = GROW_R303_HEADER / 256;
	buffer[1] = GROW_R303_HEADER % 256;
	buffer[2] = 0xFF;
	buffer[3] = 0xFF;
	buffer[4] = 0xFF;
	buffer[5] = 0xFF;
	buffer[6] = GROW_R303_CMD_PKT;
	buffer[7] = 0x00;
	buffer[8] = 0x04;
	buffer[9] = GROW_R303_INSTR_IMG_TO_CHAR;
	buffer[10] = char_buffer_num;
    uint32_t chksum = checksum(&buffer[6], 5);
	buffer[11] = chksum / 256;
	buffer[12] = chksum % 256;
	
    comm_send(buffer, SIZEOF_GEN_CHAR_CMD);
	if(COMM_OK == comm_recv(&conf_packet, sizeof(grow_r303_instr_t), 1000))
		return conf_packet.instruction_code;

	return ERR_RECV_PKG;
}

err_t gen_tmplt_file()
{
	uint8_t buffer[SIZEOF_GEN_TMPLT_CMD];
	grow_r303_instr_t conf_packet;

	buffer[0] = GROW_R303_HEADER / 256;
	buffer[1] = GROW_R303_HEADER % 256;
	buffer[2] = 0xFF;
	buffer[3] = 0xFF;
	buffer[4] = 0xFF;
	buffer[5] = 0xFF;
	buffer[6] = GROW_R303_CMD_PKT;
	buffer[7] = 0x00;
	buffer[8] = 0x03;
	buffer[9] = GROW_R303_INSTR_MAKE_TMPLT;
	uint32_t chksum = checksum(&buffer[6], 4);
	buffer[10] = chksum / 256;
	buffer[11] = chksum % 256;

    comm_send(buffer, SIZEOF_GEN_TMPLT_CMD);
	if(COMM_OK == comm_recv(&conf_packet, sizeof(grow_r303_instr_t), 1000))
		return conf_packet.instruction_code;

	return ERR_RECV_PKG;
}

err_t save_tmplt_file(uint8_t char_buffer_num, uint8_t tmplt_id)
{
	uint8_t buffer[SIZEOF_SAVE_TMPLT_CMD];
	grow_r303_instr_t conf_packet;

	buffer[0] = GROW_R303_HEADER / 256;
	buffer[1] = GROW_R303_HEADER % 256;
	buffer[2] = 0xFF;
	buffer[3] = 0xFF;
	buffer[4] = 0xFF;
	buffer[5] = 0xFF;
	buffer[6] = GROW_R303_CMD_PKT;
	buffer[7] = 0x00;
	buffer[8] = 0x06;
	buffer[9] = GROW_R303_INSTR_STORE_TMPLT;
	buffer[10] = char_buffer_num;
	buffer[11] = tmplt_id / 256;
	buffer[12] = tmplt_id % 256;
    uint32_t chksum = checksum(&buffer[6], 7);
	buffer[13] = chksum / 256;
	buffer[14] = chksum % 256;

    comm_send(buffer, SIZEOF_SAVE_TMPLT_CMD);
	if(COMM_OK == comm_recv(&conf_packet, sizeof(grow_r303_instr_t), 1000))
		return conf_packet.instruction_code;

	return ERR_RECV_PKG;
}

err_t search_tmplt(uint8_t char_buffer_num, uint8_t *tmplt_id)
{
	uint8_t buffer[SIZEOF_SEARCH_TMPLT_CMD];
	grow_r303_instr_t conf_packet;

	buffer[0] = GROW_R303_HEADER / 256;
	buffer[1] = GROW_R303_HEADER % 256;
	buffer[2] = 0xFF;
	buffer[3] = 0xFF;
	buffer[4] = 0xFF;
	buffer[5] = 0xFF;
	buffer[6] = GROW_R303_CMD_PKT;
	buffer[7] = 0x00;
	buffer[8] = 0x08;
	buffer[9] = GROW_R303_INSTR_SEARCH_LIB;
	buffer[10] = char_buffer_num;
	buffer[11] = 1 / 256;
	buffer[12] = 1 % 256;
	buffer[13] = 1 / 256;
	buffer[14] = 1 % 256;
    uint32_t chksum = checksum(&buffer[6], 9);
	buffer[15] = chksum / 256;
	buffer[16] = chksum % 256;
	
    comm_send(buffer, SIZEOF_SEARCH_TMPLT_CMD);
	if(COMM_OK == comm_recv(&conf_packet, sizeof(grow_r303_instr_t), 1000))
		return conf_packet.instruction_code;

	return ERR_RECV_PKG;
}

uint32_t checksum(uint8_t* buffer, uint8_t len) {
	uint32_t checksum = 0;
	for(uint8_t i = 0; i < len; i++) {
		checksum += buffer[i];
	}
	return checksum;
}

