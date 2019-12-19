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
    char out[1028];
    cmd("xrandr --verbose | grep Brightness: | cut -f2 -d\" \"", out);
    return strtof(out, NULL);
}

void set(float brightness) {
    char screen[1028];
    char command[1028] = "xrandr --output ";
    char command2[] = " --brightness ";
    char b[3];
    cmd("xrandr | grep \" connected\" | cut -f1 -d\" \"", screen);
    screen[strlen(screen)-1] = 0;
    strcat(command, screen);
    strcat(command, command2);
    gcvt(brightness, 3, b);
    strcat(command, b);
    cmd(command, NULL);
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
            set(current()+b);
        } else {
            set(b);
        }
    }
    return 0;
}
