#include <sys/types.h>  // Required for `open`, `lseek`
#include <sys/stat.h>   // Required for `open`
#include <fcntl.h>      // Required for `fcntl` and `open`
#include <unistd.h>     // Required for `write`, `lseek`, and `fcntl`
#include <stdio.h>      // Required for `perror` and `printf`

// Structure definition for a record - Example: "10" indicates that record 1 holds the value 0
struct record
{
    int id;
    int value;
};

char *file_path = "18-file"; // Path to the file where records are stored

int main()
{
    struct flock fileLock;
    int lockStatus;
    int fileHandle;
    ssize_t bytesRead, bytesWritten;

    // Set up file locking parameters
    fileLock.l_type = F_WRLCK;
    fileLock.l_len = 0;
    fileLock.l_start = 0;
    fileLock.l_whence = SEEK_SET;
    fileLock.l_pid = getpid();

    struct record dataRecords[3];

    fileHandle = open(file_path, O_CREAT | O_RDWR, S_IRWXU);

    if (fileHandle == -1) {
        perror("Failed to open the file");
    } else {
        lockStatus = fcntl(fileHandle, F_SETLKW, &fileLock);
        if (lockStatus == -1) {
            perror("Failed to lock the file");
        } else {
            bytesRead = read(fileHandle, dataRecords, sizeof(struct record) * 3);

            if (bytesRead == -1) {
                perror("Failed to read the file");
            } else {
                // Initialize file content if empty
                dataRecords[0].id = 1;
                dataRecords[0].value = 0;

                dataRecords[1].id = 2;
                dataRecords[1].value = 0;

                dataRecords[2].id = 3;
                dataRecords[2].value = 0;

                bytesWritten = write(fileHandle, dataRecords, sizeof(struct record) * 3);

                if (bytesWritten == -1) {
                    perror("Failed to write to the file");
                }
            }
            fileLock.l_type = F_UNLCK;
            lockStatus = fcntl(fileHandle, F_SETLKW, &fileLock);

            if (lockStatus == -1) {
                perror("Failed to unlock the file");
            }
        }
        close(fileHandle); // Close the file descriptor
    }
    return 0;
}
