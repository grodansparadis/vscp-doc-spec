/* Read-only Linux RS-485 capability probe. Build: cc -std=c11 -Wall -Wextra -Werror -o rs485-capability-probe rs485-capability-probe.c */
#define _DEFAULT_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/serial.h>
#include <asm/ioctls.h>
#ifndef SER_RS485_ADDRB
#define SER_RS485_ADDRB (1U << 6)
#endif
#ifndef SER_RS485_ADDR_RECV
#define SER_RS485_ADDR_RECV (1U << 7)
#endif
#ifndef SER_RS485_ADDR_DEST
#define SER_RS485_ADDR_DEST (1U << 8)
#endif
int main(int argc, char **argv) {
    struct serial_rs485 cfg = {0};
    int fd;
    if (argc != 2) {
        fprintf(stderr, "usage: %s /dev/ttyXXX\n", argv[0]);
        return 2;
    }
    fd = open(argv[1], O_RDONLY | O_NOCTTY | O_NONBLOCK);
    if (fd < 0) {
        fprintf(stderr, "open %s: %s\n", argv[1], strerror(errno));
        return 1;
    }
    if (ioctl(fd, TIOCGRS485, &cfg) < 0) {
        fprintf(stderr, "TIOCGRS485: %s (driver may not implement RS-485 ioctl)\n", strerror(errno));
        close(fd);
        return 1;
    }
    printf("Current RS-485 configuration flags: 0x%08x\n", cfg.flags);
    printf("RS-485 enabled: %s\n", (cfg.flags & SER_RS485_ENABLED) ? "yes" : "no");
    printf("Address mode enabled: %s\n", (cfg.flags & SER_RS485_ADDRB) ? "yes" : "no");
    printf("Receive address filtering enabled: %s\n", (cfg.flags & SER_RS485_ADDR_RECV) ? "yes" : "no");
    printf("Destination address enabled: %s\n", (cfg.flags & SER_RS485_ADDR_DEST) ? "yes" : "no");
    puts("NOTE: These are CURRENT settings, not a complete hardware capability report.");
    puts("Unsupported bits may be silently filtered by TIOCSRS485; do not modify a live bus to probe.");
    puts("9-bit address marking and reception require separate hardware tests.");
    close(fd);
    return 0;
}
