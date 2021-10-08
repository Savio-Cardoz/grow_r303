#ifndef UART_COMMS_H_
#define UART_COMMS_H_

#define TXD (4)
#define RXD (5)
#define RTS (UART_PIN_NO_CHANGE)
#define CTS (UART_PIN_NO_CHANGE)

#define UART_PORT_NUM      (1)
#define UART_BAUD_RATE     (57600)
#define TASK_STACK_SIZE    (2048)
#define BUF_SIZE (1024)

typedef enum error{
	COMM_OK,
	COMM_ERR,
	COMM_ERR_REVD_LESS
}comm_error_t;

void comm_init();
comm_error_t comm_send(const void* buffer, size_t size);
comm_error_t comm_recv(void* buffer, size_t size, uint32_t timeout);

#endif