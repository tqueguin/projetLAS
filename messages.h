#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#define SERVER_IP "127.0.0.1" /* localhost */
#define MAX_LENGTH 256


/* Possible server ports */
typedef enum
{
  SERVER_PORT_1 = 9501, SERVER_PORT_2, SERVER_PORT_3, SERVER_PORT_4,
  SERVER_PORT_5, SERVER_PORT_6, SERVER_PORT_7, SERVER_PORT_8, SERVER_PORT_9,
  SERVER_PORT_10
} Port;


typedef enum
{
  COMMAND_MESSAGE = 10,
  RESULT_MESSAGE = 11,
} Code;

/* struct message used between server and client */
typedef struct
{
  char messageText[MAX_LENGTH];
  int code;
} StructMessage;
#endif
