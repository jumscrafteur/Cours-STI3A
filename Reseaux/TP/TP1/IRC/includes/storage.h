#ifndef STORAGE_H
#define STORAGE_H

void appendKeyValuePair(char *key, char *value);
int getValueFromKey(char *key, char *out);
void removeKeyValuePair(char *key);
void updateValueFromKey(char *key, char *value);
bool isKeyInStorage(char *key);

#endif