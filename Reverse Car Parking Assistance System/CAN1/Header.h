typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;

typedef struct CAN1_MSG
{
   u32 id;
   u32 byteA;
   u32 byteB;
   u8 rtr;
   u8 dlc;
}CAN1;
 
extern void delay_ms(u32);
extern void delay_s(u32);
extern void lcd_data(u8);
extern void lcd_cmd(u8);
extern void lcd_int(void);
extern void lcd_string(char *);
extern void lcd_atoi(int);
extern void lcd_atof(float);
extern void lcd_cgram(void);
extern void uart0_init(u32 baud);
extern void uart0_tx(u8 data);
extern u8 uart0_rx(void);
extern void uart0_tx_string(char *ptr);
extern void uart0_hex(u8 ascii);
extern void uart0_rx_string(char *,u8 );
extern u8 spi0(u8 data);
extern void spi0_init(void);
extern u16 read_mcp3204(u8 ch_num);
extern void uart0_tx_integer(int num);
extern void uart0_tx_float(float f);
extern void i2c_byte_write_frame(u8 sa,u8 mr, u8 data);
extern u8 i2c_byte_read_frame(u8 sa, u8 mr);
extern void i2c_init(void);
extern void can1_init(void);
extern void can1_tx(CAN1 v);
extern void can2_init(void);
extern void can2_tx(CAN1 v);
extern void config_vic(void);
extern void en_int(void);
#define CS0 (1<<7)
