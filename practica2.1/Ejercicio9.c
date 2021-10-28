#include <unistd.h>
#include <stdio.h>

int main(){
	printf("UID Real:%d\n", getuid());
        printf("UID Efectivo:%d\n", geteuid());
        return 0;
}

//Nos podemos asegurar que el bit setuid esta activo cuando el uid es
//diferente al euid.
