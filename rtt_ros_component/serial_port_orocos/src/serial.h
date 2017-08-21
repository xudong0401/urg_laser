#include <fcntl.h>
#include <termios.h>

static int open_serial(std::string tty_name, int baud_rate, int data_bits, char parity, int stop_bits)
{
    int fd = open(tty_name.c_str(), O_RDWR|O_NOCTTY|O_NDELAY);
    if (fd < 0) {
        printf("failure: open serial port %s", tty_name.c_str());
        return fd;
    // } else if (0 == isatty(STDIN_FILENO)) {
    //     printf("failure: standard input %s is not a terminal device", tty_name.c_str());
    //     return -1;
    } else if (fcntl(fd, F_SETFL, 0) < 0) {
        printf("failure: set fcntl file %s", tty_name.c_str());
        return -1;
    } else {
        printf("success: open serial port %s", tty_name.c_str());
    }

    struct termios newtio, oldtio;
    if (0 != tcgetattr(fd, &oldtio)) {
        printf("failure: get attr %s", tty_name.c_str());
        return -1;
    }
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch (baud_rate)
    {
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    default:
        printf("failure: set %s baud rate %d", tty_name.c_str(), baud_rate);
        return -1;
    }

    switch (data_bits)
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    default:
        printf("failure: set %s data bits %d", tty_name.c_str(), data_bits);
        return -1;
    }

    switch (parity)
    {
    case 'O':                     //奇校验
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':                     //偶校验
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':                     //无校验
        newtio.c_cflag &= ~PARENB;
        break;
    default:
        printf("failure: set %s parity %c", tty_name.c_str(), parity);
        return -1;
    }

    switch (stop_bits)
    {
    case 1:
        newtio.c_cflag &=  ~CSTOPB;
        break;
    case 2:
        newtio.c_cflag |=  CSTOPB;
        break;
    default:
        printf("failure: set %s stop bits %d", tty_name.c_str(), stop_bits);
        return -1;
    }

    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;
    tcflush(fd, TCIFLUSH);
    if (0 != (tcsetattr(fd, TCSANOW, &newtio))) {
        printf("failure: set attr %s", tty_name.c_str());
        return -1;
    }
    printf("success: setup serial port %s", tty_name.c_str());

    return fd;
}
