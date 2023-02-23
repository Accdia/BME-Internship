#include "temp.h"
#include "usart.h"

void TEMP_Init(void)
{
    /* �Զ���ȡ�¶�ָ�� */
    uint8_t cmd[3] = {0xA5, 0x45, 0xEA};
    /* ����ָ�� */
    HAL_UART_Transmit(&huart2, &cmd[0], 1, 0xFFFF);
    HAL_UART_Transmit(&huart2, &cmd[1], 1, 0xFFFF);
    HAL_UART_Transmit(&huart2, &cmd[2], 1, 0xFFFF);
}

uint8_t Receive_ok;
uint8_t rebuf[20] = {0};
/* �������� */
void RxTempInfo(uint8_t tmp)
{
    static uint8_t i = 0;
  
    rebuf[i++] = tmp; //��ȡ�������ݣ�ͬʱ����ձ�־
    if (rebuf[0] != 0x5a) //֡ͷ����
        i = 0;
    if ((i == 2) && (rebuf[1] != 0x5a)) //֡ͷ����
        i = 0;
    if (i > 3) //i ���� 4 ʱ���Ѿ����յ��������ֽ� rebuf[3]
    {
        if (i != (rebuf[3] + 5)) //�ж��Ƿ����һ֡�������
            return ;
        switch (rebuf[2]) //������Ϻ���
        {
        case 0x45:
            if (!Receive_ok) //�����ݴ�����ɺ�Ž����µ�����
            {
                Receive_ok = 1; //������ɱ�־
            }
            break;
        case 0x15:
            break;
        case 0x35:
            break;
        }
        i = 0; //������ 0
    }
}

/* ��ȡ�¶� */
void GetTempInfo(void)
{
    if (Receive_ok)
    {
      float TO = 0, TA = 0;
      uint8_t sum = 0, i = 0;
      for (sum = 0, i = 0; i < (rebuf[3] + 4); i++)
          sum += rebuf[i];
      if (sum == rebuf[i]) //У����ж�
      {
          TO = (float)((rebuf[4] << 8) | rebuf[5]) / 100; //�õ���ʵ�¶�
          TA = (float)((rebuf[6] << 8) | rebuf[7]) / 100; //�õ���ʵ�¶�
      }
      printf("Ŀ���¶�TO: %f\r\n", TO);
      printf("�����¶�TA: %f\r\n", TA);
      Receive_ok = 0;
    }
}
