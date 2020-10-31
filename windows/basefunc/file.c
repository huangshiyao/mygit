#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int copy(const char *name, const char *name_copy)
{
    char buf[100];
    int rd;
    ssize_t rn;
    char *p;
    int wd;
    ssize_t wn;

    while(true)
    {
        rd=open(name, O_RDONLY);
        if(rd<0)
        {
            if(EINTR!=errno)
                return -1;
        }
        else
            break;
    }

    while(true)
    {
        wd=open(name_copy, O_CREAT|O_RDWR, 0755);
        if(wd<0)
        {
            if(EINTR!=errno)
                return -1;
        }
        else
            break;
    }

    while(true)
    {
        rn=read(rd, buf, sizeof(buf));
        if(rn<0)
        {
            if(EINTR!=errno)
                return -1;
        }
        else if(0==rn)
            break;
        else
        {
            p=buf;
            while(rn>0)
            {
                wn=write(wd, p, rn);
                if(wn<0)
                {
                    if(EINTR!=errno)
                        return -1;
                }
                else
                {
                    rn-=wn;
                    p+=wn;
                }
            }
        }
    }

    if(0!=close(wd))
        return -1;
    if(0!=close(rd))
        return -1;

    return 0;
}
