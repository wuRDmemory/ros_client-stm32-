#include "includes.h"
#include "usart3.h"

const static int UART_BUFSIZE = 512;
/* @brief Receive buffer. */
volatile uint8_t RX[UART_BUFSIZE];
volatile uint8_t TX[UART_BUFSIZE];
/* @brief Receive buffer head. */
volatile uint16_t RX_Head=0;
/* @brief Receive buffer tail. */
volatile uint16_t RX_Tail=0;
/* @brief Transmit buffer head. */
volatile uint16_t TX_Head=0;
/* @brief Transmit buffer tail. */
volatile uint16_t TX_Tail=0;

// 引脚配置
static void Usart3_GpioConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);			//RX
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);			//TX

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);       
}

// 模式配置
static void Usart3_ModeConfig(long baud)
{
    USART_InitTypeDef USART_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    USART_InitStructure.USART_BaudRate            = baud;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

    USART_Cmd(USART3, ENABLE);
}

// Usart3初始化
void Usart_Configuration(long baud)
{
    Usart3_GpioConfig();
    Usart3_ModeConfig(baud);
}


char Usart_FreeSpace(void)
{
    uint16_t tempHead = (TX_Head + 1) % (UART_BUFSIZE-1);
    uint16_t tempTail = TX_Tail;
    return (tempHead != tempTail);
}

char Usart_Putch(uint8_t data)
{
    uint16_t tempTX_Head;
    bool isFree = Usart_FreeSpace();

    if(isFree)
    {
        tempTX_Head = TX_Head;

        USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
        USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
        TX[tempTX_Head]= data;
        /* Advance buffer head. */
        TX_Head = (tempTX_Head + 1) % (UART_BUFSIZE-0);
        USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
        USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
    }
    return isFree;
}

char Usart_DataAvailable()
{
    uint16_t tempHead = RX_Head;
    uint16_t tempTail = RX_Tail;
    /* There are data left in the buffer unless Head and Tail are equal. */
    return (tempHead != tempTail);
}

uint8_t Usart_Getch()
{
    uint8_t ans;

    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    ans = (RX[RX_Tail]);
    RX_Tail = (RX_Tail + 1) % (UART_BUFSIZE-0);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

    return ans;
}

// 中断程序
extern "C" void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        uint16_t tempRX_Head = (RX_Head + 1) % (UART_BUFSIZE-0);
        
        uint16_t tempRX_Tail = RX_Tail;
        uint8_t data = USART_ReceiveData(USART3);
        
        if (tempRX_Head == tempRX_Tail) {
            USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
        }else{
            RX[RX_Head] = data;
            RX_Head = tempRX_Head;
        }
    }
    
    if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
    {
        uint16_t tempTX_Tail = TX_Tail;
        if (TX_Head == tempTX_Tail)
        {
            USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
        }
        else
        {
            uint8_t data = TX[TX_Tail];
            USART_SendData(USART3, (unsigned char) data);
            TX_Tail = (TX_Tail + 1) % (UART_BUFSIZE-0);
        }
    }
}

