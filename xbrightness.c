#include "xbrightness.h"

void cmd(char *command, char *output) {
    FILE *fp;

    fp = popen(command, "r");
    if (fp == NULL) {
        output[0] = 0;
    } else {
        fgets(output, sizeof(output), fp);
        pclose(fp);
    }
}

float current() {
    char out[BUFFER];
    cmd("xrandr --verbose | grep Brightness: | cut -f2 -d\" \"", out); //TODO: Check when 0 screen connected and two or more connected and catch output error
    return strtof(out, NULL); //TODO: Return NULL when convert fail
}

void set(float brightness) {
    char screen[BUFFER]; //TODO: Better buffer
    char command[BUFFER] = "xrandr --output ";
    char command2[] = " --brightness ";
    char b[3];
    cmd("xrandr | grep \" connected\" | cut -f1 -d\" \"", screen); //TODO: Check when 0 screen connected and two or more connected and catch output error
    screen[strlen(screen)-1] = 0;
    strcat(command, screen);
    strcat(command, command2);
    gcvt(brightness, 3, b);
    strcat(command, b);
    cmd(command, NULL); //TODO: Catch output error
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Current: %.2f\n", current());
        return 0;
    } else if (argc > 2) {
        printf("Too many arguments !\n");
        return 1;
    }

    char *entPrt;
    float b = strtof(argv[1], &entPrt);
    if (*entPrt != '\0') {
        printf("Invalid brightness level !\n");
        return 1;
    } else {
        if (argv[1][0] == '+' ||argv[1][0] == '-') {
            b = current()+b;
            set(b);
        } else {
            set(b);
        }
        printf("Brightness set to %.2f\n", b);
    }
    return 0;
}
