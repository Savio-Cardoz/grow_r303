#include <stdio.h>
#include <stdlib.h>
#include "uart_comms.h"
#include "driver/uart.h"

void comm_init() {
	// Initialize the UART of the controller
	// ESP32 UART initialization
	uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

	int intr_alloc_flags = 0;
	ESP_ERROR_CHECK(uart_driver_install(UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT_NUM, TXD, RXD, RTS, CTS));
}

comm_error_t comm_send(const void* buffer, size_t size) {
	size_t sent_bytes = uart_write_bytes(UART_PORT_NUM, buffer, size);
	if(sent_bytes != size) 
		return COMM_ERR;
	
	return COMM_OK;
}

comm_error_t comm_recv(void* buffer, size_t size, uint32_t timeout) {
	size_t recv_bytes = uart_read_bytes(UART_PORT_NUM, buffer, size, timeout/portTICK_RATE_MS);
	if(recv_bytes != size)
		return COMM_ERR_REVD_LESS;

	return COMM_OK;
}