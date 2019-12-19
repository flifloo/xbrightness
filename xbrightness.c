#include "xbrightness.h"

static void cmd(char *command, char *output) {
    FILE *fp = popen(command, "r");

    if (fp == NULL) {
        output[0] = 0;
    } else {
        fgets(output, sizeof(output), fp);
        pclose(fp);

        if (output && output[strlen(output)-1] == '\n') {
            output[strlen(output)-1] = 0;
        }
    }
}

float current() {
    char out[BUFFER];
    cmd("xrandr --verbose | grep Brightness: | cut -f2 -d\" \"", out);
    return strtof(out, NULL);
}

void set(float brightness) {
    char screenName[64], b[3], command[BUFFER] = "xrandr --output ";
    cmd("xrandr | grep \" connected\" | cut -f1 -d\" \"", screenName);
    strcat(strcat(strcat(command, screenName), " --brightness "), gcvt(brightness, 3, b));
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
