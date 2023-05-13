#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#define SERVER_PORT_1 9501
#define SERVER_PORT_2 9502
#define SERVER_PORT_3 9503
#define SERVER_PORT_4 9504
#define SERVER_PORT_5 9505
#define SERVER_PORT_6 9506
#define SERVER_PORT_7 9507
#define SERVER_PORT_8 9508
#define SERVER_PORT_9 9509
#define SERVER_PORT_10 9510

#define MAX_LENGTH 256


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
