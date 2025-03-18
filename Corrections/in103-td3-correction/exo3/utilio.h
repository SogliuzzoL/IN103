#ifndef __UTILIO_H__
#define __UTILIO_H__

char* trimspace (char * s);

char** csv_to_array (char *str, int nbfields);

char* command_to_string (char *command);

int command_to_int (char* command);
#endif
