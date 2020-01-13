#include "openjvs.h"

int running = 1;

int main(int argc, char **argv)
{
    printf("OpenJVS3 Development Version\n");

    /* Setup the IO we are trying to emulate */
    JVSCapabilities capabilities;
    capabilities.players = 2;
    capabilities.switches = 8;

    /* Setup the JVS Emulator with the RS485 path and capabilities */
    if (!initJVS("/dev/ttyUSB0", &capabilities))
    {
        printf("Error: Couldn't connect to serial\n");
        return 1;
    }

    /* Process packets forever */
    while (running)
    {
        if (!processPacket())
        {
            printf("Error: Failed to process packet properly.");
            return 1;
        }
    }

    /* Close the file pointer */
    if (!disconnectJVS())
    {
        printf("Error: Couldn't disconnect from serial\n");
        return 1;
    }

    return 0;
}