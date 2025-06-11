#include <fcntl.h>     // open
#include <unistd.h>    // read, write
#include <stdio.h>     // perror

int main() {
    int fd = open("/tmp/flag", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buf[48] = { 0 };
    ssize_t len = read(fd, buf, sizeof(buf));
    if (len < 0) {
        perror("read");
        return 1;
    }

    write(1, buf, len);  // stdout
    return 0;
}
