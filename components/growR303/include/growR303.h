#ifndef GROWR303_H_
#define GROWR303_H_

#define GROW_R303_HEADER				0xEF01
#define GROW_R303_DEFAULT_ADDR			0xFFFFFFFF
#define GROW_R303_CMD_PKT				0x01
#define GROW_R303_DATA_PKT				0x02
#define GROW_R303_ACK_PKT				0x07
#define GROW_R303_DATA_END				0x08

#define GROW_R303_INSTR_GET_FINGER_IMG	0x01
#define GROW_R303_INSTR_IMG_TO_CHAR		0x02
#define GROW_R303_INSTR_COMPARE_TMPLT	0x03
#define GROW_R303_INSTR_SEARCH_LIB		0x04
#define GROW_R303_INSTR_MAKE_TMPLT		0x05
#define GROW_R303_INSTR_STORE_TMPLT		0x06
#define GROW_R303_INSTR_LOAD_TMPLT		0x07
#define GROW_R303_INSTR_UPLD_TMPLT		0x08
#define GROW_R303_INSTR_DWNLD_TMPLT		0x09
#define GROW_R303_INSTR_UPLD_IMG		0x0A
#define GROW_R303_INSTR_DWNLD_IMG		0x0B
#define GROW_R303_INSTR_DELETE_TMPLT	0x0C
#define GROW_R303_INSTR_EMPTY_LIB		0x0D
#define GROW_R303_INSTR_BASIC_PARAM		0x0E
#define GROW_R303_INSTR_RD_SYS_PARAM	0x0F

#define GROW_R303_INSTR_SET_PSSWD		0x12
#define GROW_R303_INSTR_VERIFY_PSSWD	0x13
#define GROW_R303_INSTR_MAKE_RAND_CODE	0x14
#define GROW_R303_INSTR_SET_ADDR		0x15

#define GROW_R303_INSTR_SET_PORT		0x17
#define GROW_R303_INSTR_WRITE_NOTEPAD	0x18
#define GROW_R303_INSTR_READ_NOTEPAD	0x19

#define GROW_R303_INSTR_RD_TMPLT_NO		0x1D

#define GROW_R303_CHAR_BUF_1			0x01
#define GROW_R303_CHAR_BUF_2			0x02

#define SIZEOF_GEN_IMG_CMD				12		// 12 Bytes
#define SIZEOF_GEN_CHAR_CMD				13
#define SIZEOF_GEN_TMPLT_CMD			12
#define SIZEOF_SAVE_TMPLT_CMD			15
#define SIZEOF_SEARCH_TMPLT_CMD			17

typedef enum{
	ERR_OK = 0,
	ERR_RECV_PKG,
	ERR_NO_FINGER,
	ERR_GETTING_FINGER 				= 5,
	ERR_NO_CHAR_FILE_BAD_IMAGE 		= 6,
	ERR_NO_CHAR_FILE_SMALL_IMAGE 	= 7,
	ERR_TMPLT_DIFF					= 8,
	ERR_NO_MATCH_IN_LIBRARY			= 9,
	ERR_NO_TMPLT_CHAR_FILES_DIFF 	= 10,
	ERR_PAGEID_ADDR_OVERFLOW		= 11,
	ERR_READING_TMPLT				= 12,
	ERR_UPLD_TMPLT 					= 13,
	ERR_DELETING_TMPLT				= 16,
	ERR_STORING_TMPLT				= 24,
    ERR_UNKOWN                      = 25
}err_t;

typedef struct{
	uint16_t header;
	uint32_t module_address;
	uint8_t package_id;
	uint16_t package_len;
	uint8_t instruction_code;
	uint16_t checksum;
}__attribute__((packed, aligned(1))) grow_r303_instr_t;

void growr303_init();
bool is_finger_on_sensor();
err_t save_finger_as_template()
static err_t gen_finger_img();
static err_t gen_char_file(uint8_t char_buffer_num);
err_t gen_tmplt_file();
err_t save_tmplt_file(uint8_t char_buffer_num, uint8_t tmplt_id);
err_t search_tmplt(uint8_t char_buffer_num, uint8_t *tmplt_id);
uint32_t checksum(uint8_t* buffer, uint8_t len);

#endif /* GROW_R303_H_ */
