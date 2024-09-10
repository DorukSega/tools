#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
     if (argc < 2) {
EXIT:
        printf("Starts a mixrank project shell\n");
        printf("Usage: %s <project>\n", argv[0]);
        return 1;
    }
    char *nix_init = "nix-shell default.nix"; // slowly move to nix develop
    char custom = 0;
    if (argv[1][0] == '-'){
        if      (!strcmp(argv[1], "-h"))
            goto EXIT;
        else if (!strcmp(argv[1], "-c"))
            custom = 1;
        else if (!strcmp(argv[1], "-l"))
        {
            printf("Mixrank Projects:\n");
            system("ls -1 ~/Desktop/mixrank-base/");
            return 0;
        }
        else{
            printf("[ERR] Not a valid command\n");
            goto EXIT;
        }
    } 
   
    char *project = argc >= 3 ? argv[argc-1] : argv[1]; 
    if (!strcmp(project, "mixrank") && !custom){
        system("alacritty -T \"MIXRANK / Mixrank\" -e /bin/sh -c \"cd ~/Desktop/mixrank-base/mixrank && nix develop\" &");
    } else if (!strcmp(project, "schematic") && !custom){
        system("alacritty -T \"SCHEMATIC / Schematic\" -e /bin/sh -c \"cd ~/Desktop/mixrank-base/schematic && nix develop\" &");
    } else {
        if (custom) {
            nix_init = malloc((strlen(argv[2])+1) * sizeof(char));
            nix_init = argv[2];
        }
        char *generic_mx = malloc(110 + strlen(project)*2*sizeof(char) + strlen(nix_init)*sizeof(char));
        sprintf(generic_mx ,"alacritty -T \"MIXRANK / %s\" -e /bin/sh -c \"cd ~/Desktop/mixrank-base/%s && %s\" &", project, project, nix_init);
        const int status = system(generic_mx);
        if (status != 0) {
            free(generic_mx);
            goto EXIT;
        } 
        free(generic_mx);
        //if (custom) free(nix_init);
    }
    printf("Starting %s shell\n", project);
    return 0;
}
