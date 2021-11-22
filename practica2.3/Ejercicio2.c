#include <sched.h>
#include <stdio.h>

int main(){

	switch(sched_getscheduler(0)){
                case SCHED_OTHER :
                        printf("SCHED_OTHER ");
                        break;
                case SCHED_FIFO :
                        printf("SCHED_FIFO ");
                        break;
                case SCHED_RR :
                        printf("SCHED_RR ");
                        break;
        }
	struct sched_param param;
        sched_getparam(0, &param);
        printf("prio %d, prio max %d, prio min %d\n",
        param.sched_priority, sched_get_priority_max(sched_getscheduler(0)),
        sched_get_priority_min(sched_getscheduler(0)));


        return 0;
}
