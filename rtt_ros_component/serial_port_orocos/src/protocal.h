#ifndef _PROTOCAL_H_
#define	_PROTOCAL_H


//��ͨѶ��ʽ
//0XAA 0X55 ID Len_H Len_L MainCmd SubCmd data CRC_H CRC_L
#define	LENTH_H								3
#define	LENTH_L								4
#define	TYPE_H								5
#define	TYPE_L								6
#define	DATA_STAR							7
#define	PACK_LEN							9
#define MAX_FRAME_LEN                       43

//���������������
#define MAIN_MOVE							0x02
#define SUB_LEFT_WITH_DEFAULT_SPEED			0X00
#define SUB_LEFT_WITH_SET_SPEED				0X01
#define SUB_RIGHT_WITH_DEFAULT_SPEED		0X02
#define SUB_RIGHT_WITH_SET_SPEED			0X03
#define SUB_FRONT_WITH_DEFAULT_SPEED		0X04
#define SUB_FRONT_WITH_SET_SPEED			0X05
#define SUB_BACK_WITH_DEFAULT_SPEED			0X06
#define SUB_BACK_WITH_SET_SPEED				0X07
#define SUB_NORMAL_STOP						0X08
#define SUB_EMERGENCY_STOP					0X09
#define SUB_FREE_STOP						0X0A
#define SUB_SET_TWO_WHEEL_SPEED				0X11
#define SUB_GET_POS_OF_WHEELS				0X42
#define SUB_GET_SPEED_OF_WHEELS				0x43
#define SUB_TEST_COMMUNICATION_MULTITIME	0x50

#define MAIN_FACE_LED						0xA0
#define SUB_CUSTOMIZE_COLOR					0x03

#define MAIN_EEPROM_SPECIAL_OPERATION		0xA1
#define	SUB_WRITE_EEPROM					0x01
#define	SUB_READ_EEPROM						0x02


#define MAIN_EEPROM_COMMON_OPERATION		0xA2
#define	SUB_WRITE_EEPROM					0x01
#define	SUB_READ_EEPROM						0x02

#define MAIN_SYSTEM							0XF0
#define SUB_KS103_DETECT					0X0A
#define SUB_GET_POWER_PERCENT				0X11
#define SUB_GET_EMERGENCY_STATE				0X13
#define SUB_SET_VOICE_OUTPUT				0x14
#define SUB_BEGIN_POWER_OFF					0x15
#define SUB_BEGIN_RESTART					0x16
#define SUB_TEST_LED						0x17
#define SUB_GET_PA3_POWER_STATUS			0x18
#define SUB_GET_POS_AND_MPU6050				0x19
#define SUB_GET_SPEED_AND_MPU6050			0x1A
#define SUB_GET_ULTRASONIC_STOP_STATUS		0x1B

#define SUB_GET_CHARGE_POWER_STATUS			0x7E
#define SUB_POWER_OFF_THE_SYSTEM			0x7F

#define SUB_GET_VERSION						0X80
#define SUB_READ_REGEDIT					0x83
#define SUB_WRITE_REGEDIT					0x86

#define DEFAULT_FRONT_SPEED					7000
#define DEFAULT_BACK_SPEED					7000
#define DEFAULT_CW_SPEED					3000
#define DEFAULT_ACW_SPEED					3000

#define MOTOR_NORMAL_STOP 			0x00   //����ֹͣ
#define MOTOR_EMERGENCY_STOP		0x01   //��ͣ
#define MOTOR_FREE_STOP             0x02   //����ֹͣ

#endif
