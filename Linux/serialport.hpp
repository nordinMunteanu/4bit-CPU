#ifndef __IOSTREAM__
#include <iostream>
#endif

#ifndef __STRING__
#include <string>
#endif

#ifndef __CSTRING__
#include <cstring>
#endif

#ifndef _FCNTL_H
#include <fcntl.h>
#endif

#ifndef _TERMIOS_H
#include <termios.h>
#endif

#ifndef _UNISTD_H
#include <unistd.h>
#endif

#ifndef _SYS_SELECT_H
#include <sys/select.h>
#endif


class SerialPort {
    private:
        int fd;
    public:
        SerialPort(const char* port, int baudrate) {
            fd = open(port, O_RDWR | O_NOCTTY);
            if (fd == -1) {
                throw std::runtime_error("Failed to open serial port");
            }
    
            tcflush(fd, TCIOFLUSH);
    
            struct termios options;
            tcgetattr(fd, &options);
    
            cfsetispeed(&options, baudrate);
            cfsetospeed(&options, baudrate);
    
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            options.c_cflag &= ~CSIZE;
            options.c_cflag |= CS8;
            options.c_cflag |= (CLOCAL | CREAD);
    
            options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    
            options.c_oflag &= ~OPOST;
    
            options.c_cflag &= ~CRTSCTS;
            options.c_iflag &= ~(IXON | IXOFF | IXANY);
    
            options.c_cc[VMIN] = 1;
            options.c_cc[VTIME] = 0;
    
            if (tcsetattr(fd, TCSANOW, &options) != 0) {
                throw std::runtime_error("Failed to set serial port attributes");
            }
    
            usleep(2000000);
        }
    
        ~SerialPort() {
            if (fd != -1) {
                close(fd);
            }
        }
    
        void writeString(const std::string& data) {
            if (write(fd, data.c_str(), data.length()) == -1) {
                throw std::runtime_error("Failed to write to serial port");
            }
            if (write(fd, "\n", 1) == -1) {
                throw std::runtime_error("Failed to write newline to serial port");
            }
    
            tcdrain(fd);
        }
    
        std::string readLine(int timeout_sec = 1) {
            std::string result;
            char buffer[256];
    
            while (true) {
                fd_set set;
                struct timeval timeout;
    
                FD_ZERO(&set);
                FD_SET(fd, &set);
    
                timeout.tv_sec = timeout_sec;
                timeout.tv_usec = 0;
    
                int rv = select(fd + 1, &set, NULL, NULL, &timeout);
                if (rv == -1) {
                    throw std::runtime_error("Error in select()");
                } else if (rv == 0) {
                    if (result.empty()) {
                        throw std::runtime_error("Timeout waiting for response");
                    } else {
                        break;
                    }
                } else {
                    ssize_t n = read(fd, buffer, sizeof(buffer) - 1);
                    if (n > 0) {
                        buffer[n] = '\0';
                        result += buffer;
    
                        if (result.find('\n') != std::string::npos) {
                            break;
                        }
                    } else {
                        throw std::runtime_error("Error reading from serial port");
                    }
                }
            }
    
            if (!result.empty() && result.back() == '\n') {
                result.pop_back();
            }
            if (!result.empty() && result.back() == '\r') {
                result.pop_back();
            }
    
            return result;
        }
    
        void flushInput() {
            tcflush(fd, TCIFLUSH);
        }
};