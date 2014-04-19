#include "leds.h"
#include "int_macro.h"
#include "debug_serial.h"
void abort(const char * c){
IRQ_D();
printd_c(c);red_led_on();green_led_on();while(1);
}




#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>


// errno
#undef errno
extern int errno;

/*
 Переменные среды - пустой список.
 */
char *__env[1] = { 0 };
char **environ = __env;

int _write(int file, char *ptr, int len);

// exit - экстренный выход. В качестве выхода - зацикливаемся.
void _exit(int status)
{	abort("_exit");
    while (1);
}

// close - закрытие файла - возвращаем ошибку 
int _close(int file)
{abort("_close");
    return -1;
}
/*
 execve - передача управления новому процессу - процессов нет -> возвращаем ошибку.
 */
int _execve(char *name, char **argv, char **env)
{abort("_execve");
    errno = ENOMEM;
    return -1;
}

/*
 fork = создание нового процесса
 */
int _fork()
{abort("_fork");
    errno = EAGAIN;
    return -1;
}

/*
 fstat - состояние открытого файла
 */
int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 getpid - получить ID текущего процесса
 */

int _getpid()
{abort("_getpid");
    return 1;
}

/*
 isatty - является ли файл терминалом.
 */
int _isatty(int file)
{
    switch (file)
    {
    case STDOUT_FILENO:
    case STDERR_FILENO:
    case STDIN_FILENO:
        return 1;
    default:
        //errno = ENOTTY;
        errno = EBADF;
        return 0;
    }
}

/*
 kill - послать сигнал процессу
 */
int _kill(int pid, int sig)
{abort("_kill");
    errno = EINVAL;
    return (-1);
}

/*
 link - устанвить новое имя для существующего файла.
 */

int _link(char *old, char *_new)
{abort("_link");
    errno = EMLINK;
    return -1;
}

/*
 lseek - установить позицию в файле
 */
int _lseek(int file, int ptr, int dir)
{abort("_lseek");
    return 0;
}

/*
 sbrk - увеличить размер области данных, использутся для malloc
 */
 char *heap_end=0;
    
 extern int STACK_POINTER();
caddr_t _sbrk(int incr)
{
    extern char __heap_start; 
    char *prev_heap_end;
//static char *heap_end=0;
   
    if (heap_end == 0)
    {
        heap_end = &__heap_start;
    }
    prev_heap_end = heap_end;

    char * stack = (char*) STACK_POINTER();
    if (heap_end + incr > stack)
    {
        _write(STDERR_FILENO, "Heap and stack collision\n", 25);
        errno = ENOMEM;
        abort("ENOMEM: heap and stack collision");
        return (caddr_t) -1;
        //abort ();
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;

}

/*
 read - чтение из файла, у нас пока для чтения есть только stdin
 */

int _read(int file, char *ptr, int len)
{abort("_read");
	/*
    int n;
    int num = 0;
    switch (file)
    {
    case STDIN_FILENO:
        for (n = 0; n < len; n++)
        {
            while (USART_GetFlagStatus(STDIN_USART, USART_FLAG_RXNE) == RESET);
            char c = (char) (USART_ReceiveData(STDIN_USART) & (uint16_t) 0x01FF);
            *ptr++ = c;
            num++;
        }
        break;
    default:
        errno = EBADF;
        return -1;
    }
    return num;*/
}

/*
 stat - состояние открытого файла.
 */

int _stat(const char *filepath, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 times - временная информация о процессе (сколько тиков: системных, процессорных и т.д.)
 */

clock_t _times(struct tms *buf)
{abort("_times");
    return -1;
}

/*
 unlink - удалить имя файла.
 */
int _unlink(char *name)
{abort("_unlink");
    errno = ENOENT;
    return -1;
}

/*
 wait - ожидания дочерних процессов
 */
int _wait(int *status)
{abort("_wait");
    errno = ECHILD;
    return -1;
}


#include "debug_serial.h"
/*
 write - запись в файл - у нас есть только stderr/stdout
 */
 int _write(int file, char *ptr, int len)
{
	
	
	
	debug_serial_write_c(ptr,len);
	/*
    int n;
    switch (file)
    {
    case STDOUT_FILENO: //stdout
        for (n = 0; n < len; n++)
        {
            while (USART_GetFlagStatus(STDOUT_USART, USART_FLAG_TC) == RESET);
            USART_SendData(STDOUT_USART, (uint8_t) * ptr++);
        }
        break;
    case STDERR_FILENO: // stderr 
        for (n = 0; n < len; n++)
        {
            while (USART_GetFlagStatus(STDERR_USART, USART_FLAG_TC) == RESET);
            USART_SendData(STDERR_USART, (uint8_t) * ptr++);
        }
        break;
    default:
        errno = EBADF;
        return -1;
    }
    return len;*/
}



