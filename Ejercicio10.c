#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>

int main(){
	struct passwd *p = getpwuid(getuid());

        printf("UID Real: %d\n", getuid());
        printf("UID Efectivo: %d\n", geteuid());
        printf("Nombre Usuario: %s\n", p->pw_name);
        printf("Directorio Home: %s\n", p->pw_dir);
        printf("Descripcion Usuario: %s\n", p->pw_gecos);

        return 0;
}

