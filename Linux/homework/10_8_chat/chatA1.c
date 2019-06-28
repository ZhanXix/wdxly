#include <func.h>

int main(int argc,char *argv[])
{
    system("clear");
    int ret;
    int fdr_AA=open("chatAA.pipe",O_RDONLY);
    ERROR_CHECK(fdr_AA,-1,"open");
    int fdr_BA=open("chatBA.pipe",O_RDONLY);
    ERROR_CHECK(fdr_BA,-1,"open");
    int fd_max=fdr_AA>fdr_BA?fdr_AA+1:fdr_BA+1;
    fd_set r_set;
    char buf[256]={0};
    while(1)
    {
        FD_ZERO(&r_set);
        FD_SET(fdr_AA,&r_set);
        FD_SET(fdr_BA,&r_set);
        ret=select(fd_max,&r_set,NULL,NULL,NULL);
        ERROR_CHECK(ret,-1,"select");
        if(FD_ISSET(fdr_AA,&r_set))
        {
            bzero(buf,sizeof(buf));
            ret=read(fdr_AA,buf,sizeof(buf));
            if(ret)
            {
                printf("%76s\n",buf);
            }else{
                printf("---对话主动终止---\n");
                break;
            }
        }
        if(FD_ISSET(fdr_BA,&r_set))
        {
            bzero(buf,sizeof(buf));
            ret=read(fdr_BA,buf,sizeof(buf));
            if(ret)
            {
                printf("%s\n",buf);
            }else{
                printf("---对话已终止---\n");
                break;
            }
        }
    }
    close(fdr_AA);
    close(fdr_BA);
    return 0;
}

