#ifndef COMMANDS_H
#define COMMANDS_H

#define CMD_NICKNAME 0
#define CMD_REGISTER 1
#define CMD_UNREGISTER 2
#define CMD_EXIT 3
#define CMD_DATE 4

typedef struct cmd
{
    char prefix[20];
    int cmdType;
} cmd;

#define CMD_COUNT 6

cmd cmdList[CMD_COUNT] = {
    {"/nickname", CMD_NICKNAME},
    {"/register", CMD_REGISTER},
    {"/unregister", CMD_UNREGISTER},
    {"/exit", CMD_EXIT},
    {"/date", CMD_DATE},
};

#endif