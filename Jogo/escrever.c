#include <stdio.h>

ESTADO file2estado(){
	FILE *f;
	ESTADO e;
	f = fopen("tmp/exemplo","r");
	fread(&e, sizeof(ESTADO), 1 , f);
	fclose(f);
	return e;
}

void estado2file(ESTADO e){
	FILE *f;
	f = fopen("tmp/exemplo", "w");
	fwrite(&e, sizeof(ESTADO), 1, f);
	fclose(f);
}