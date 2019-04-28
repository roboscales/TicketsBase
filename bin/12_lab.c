#include <stdio.h>
#include <conio.h>

#define N 10
#define MAXSTR 80
#define ESC 27

typedef struct{

	char cou[MAXSTR];
	char tr[MAXSTR];
	int len;
	int rub;

} Ticket;

Ticket t[N], *pt;

void interface(void);

void see(void);
void create(void);
void find(void);
void sort(void);

void load(void);
void save(void);

void head(void);
void table(char*, char*, int, int);

int comp_rub(const void*, const void*); //простите, нужно для функции qsort
int comp_rubm(const void*, const void*);
int comp_str(const void*, const void*);
int comp_strm(const void*, const void*);


int main(){
	interface();
	return 0;
}

//ok now, let's do this

void interface(void){
	char key;

	load();

	while(1){
	  clrscr();

	  printf("1 - Просмотр\n2 - Создание\n3 - Поиск\n4 - Сортировка\n5 - Выход\n");

	  key = getch();
	  switch(key){
		case '1':
			see();
			break;
		case '2':
			create();
			break;
		case '3':
			find();
			break;
		case '4':
			sort();
			break;
		case '5':
		save();
		return;
	  }
	}
}

void create(void){

	clrscr();

	printf("Введите новый билет\n");

	for(pt = t; pt->cou[0] && pt < &t[N]; pt++);

	if(pt == &t[N]){
		printf("We have't any space to read");
		getch();
		return;
		}

		else{
			printf("Страна:\n");
			while(!pt->cou[0])
				gets(pt -> cou);
			fflush(stdin);

			printf("Вид транспорта:\n");
				gets(pt->tr);
			fflush(stdin);

			printf("Время путешествия:\n");
				scanf("%d", &pt->len);
			fflush(stdin);

			printf("Стоимость в рублях:\n");
				scanf("%d", &pt->rub);
			fflush(stdin);

			printf("Press ESC to exit!");
		}

	while(1){
		if(getch() == ESC) break;
	}
}

void load(void){

	FILE *data = NULL;

	if(!(data = fopen("data.bin", "ab+"))){
		printf("Error on open file!");
		getch();
		exit(1);
	}
	rewind(data);

	for(pt = t; pt < &t[N]; pt++)
		pt->cou[0] = '\0';

	for(pt = t; pt < &t[N]; pt++){

		if (fread(pt, sizeof(Ticket), 1, data) != 1){
			if(feof(data)) break;
			printf("ERROR Read");
			exit(1);
		}
		}

	if(fclose(data)){
		printf("Error closing file");
		exit(1);
		}

		data = NULL;
}

void see(void){

	clrscr();

	pt = t;

	if(pt->cou[0] == '\0'){
	 printf("No info about tickets!");
	 }

	else{
	head();

	for(pt = t; pt->cou[0] && pt<&t[N]; pt++)
		table(pt->cou, pt->tr, pt->len, pt->rub);
	}

		while(1){
			if(getch() == ESC) break;
		}
}

void head(void){

	int i = 0;

	char s1[MAXSTR] = "Страна", s2[MAXSTR] = "Транспорт", s3[MAXSTR] = "Протяженность", s4[MAXSTR] = "Стоимость";

	clrscr();

	for(i = 0; i < MAXSTR; i++){

		if(i == 0){
			printf("%c", 201);
			continue;
		}

		else if(i == MAXSTR - 1){
			printf("%c", 187);
		}

		else if(i == 24){
			printf("%c", 203);
		}

		else if(i == 55) printf("%c", 203);
		else if(i == 69) printf("%c", 203);

		else printf("%c", 205);
	}

       //	printf("\n");

	printf("%c%-23s%c%-30s%c%-13s%c%-9s%c", 186, s1, 186, s2, 186, s3, 186, s4, 186);


	for(i = 0; i < MAXSTR; i++){

		if(i == 0){
			printf("%c", 204);
			continue;
		}

		else if(i == MAXSTR - 1){
			printf("%c", 185);
		}

		else if(i == 24){
			printf("%c", 206);
		}

		else if(i == 55) printf("%c", 206);
		else if(i == 69) printf("%c", 206);


		else printf("%c", 205);
	}

}

void table(char *s1, char *s2, int i, int j){

	printf("%c%-23s%c%-30s%c%-13d%c%-9d%c", 186, s1, 186, s2, 186, i, 186, j, 186);

	if(pt < &t[N] && (pt + 1)->cou[0]){
		for(i = 0; i < MAXSTR; i++){

		if(i == 0){
			printf("%c", 204);
			continue;
		}

		else if(i == MAXSTR - 1){
			printf("%c", 185);
		}

		else if(i == 24){
			printf("%c", 206);
		}

		else if(i == 55) printf("%c", 206);
		else if(i == 69) printf("%c", 206);


		else printf("%c", 205);
	}
	}

	else{
		for(i = 0; i < MAXSTR; i++){

		if(i == 0){
			printf("%c", 200);
			continue;
		}

		else if(i == MAXSTR - 1){
			printf("%c", 188);
		}

			else if(i == 24){
			printf("%c", 202);
		}

		else if(i == 55) printf("%c", 202);
		else if(i == 69) printf("%c", 202);


		else printf("%c", 205);
	}
	}
}

void find(void){
	char k1[MAXSTR];
	int r1, st;

	clrscr();

	printf("Введите страну:\n");
	scanf("%s", k1);

	fflush(stdin);

	printf("Введите цену\n");
	scanf("%d", &r1);

	head();

	for(pt = t; pt->cou[0] && pt < &t[N]; pt++){
		if(!strcmp(pt->cou, k1) && pt->rub <= r1){
			table(pt -> cou, pt->tr, pt->len, pt->rub);
			st++;
		}
	}

	if(!st){
		clrscr();
		puts("Cannot to find this");
	}

	while(1){
		if(getch() == ESC) break;
	}
}

void save(void){
	FILE *data = NULL;

	if(!(data = fopen("data.bin", "wb"))){
		printf("Error on open file!");
		getch();
		exit(1);
	}

	rewind(data);

	for(pt = t; pt->cou[0] && pt < &t[N]; pt++){

		if(fwrite(pt, sizeof(Ticket), 1, data) != 1){
			if(feof(data)) break;
			printf("ERROR Write");
			exit(1);
		}
		}

	if(fclose(data)){
		printf("Error closing file");
		exit(1);
		}

		data = NULL;

}

void sort(void){

	//ok now

	char key;
	int real = 0;

	for(pt = t; pt->cou[0]; pt++) real++;

	pt = t;

	clrscr();

	printf("Выберите тип сортировки\n1,2 - По стране(1 - по возрастанию, 2 - по убыванию)\n3,4 - По стоимости!(1 - по возрастанию 2 - убыванию)\n");

	while(1){

	  key = getch();
	  switch(key){
		case '1':
			qsort((void*)pt, real, sizeof(Ticket), comp_str);
			clrscr();
			printf("Sorted");
			break;
		case '2':
			qsort((void*)pt, real, sizeof(Ticket), comp_strm);
			clrscr();
			printf("Sorted");
			break;
		case '3':
			qsort((void*)pt, real, sizeof(Ticket), comp_rub);
			clrscr();
			printf("Sorted");
			break;
		case '4':
			qsort((void*)pt, real, sizeof(Ticket), comp_rubm);
			clrscr();
			printf("Sorted");
			break;
		case ESC:
			break;
	  }
	  if(getch() == ESC) break;
	}

		while(1){
			if(getch() == ESC) break;
		}
}

int comp_rub(const void *a, const void *b){
	Ticket x1 = *(Ticket *)a, x2 = *(Ticket *)b;

	if(x1.rub < x2.rub) return -1;
	else if(x1.rub > x2.rub) return 1;
	else return 0;
     }

int comp_rubm(const void *a, const void *b){
	Ticket x1 = *(Ticket *)a, x2 = *(Ticket *)b;

	if(x1.rub < x2.rub) return 1;
	else if(x1.rub > x2.rub) return -1;
	else return 0;
     }

int comp_str(const void *a, const void *b){
	Ticket x1 = *(Ticket *)a, x2 = *(Ticket *)b;

	if(x1.cou[0] < x2.cou[0]) return -1;
	else if(x1.cou[0] > x2.cou[0]) return 1;
	else return 0;
}

int comp_strm(const void *a, const void *b){
	Ticket x1 = *(Ticket *)a, x2 = *(Ticket *)b;

	if(x1.cou[0] < x2.cou[0]) return 1;
	else if(x1.cou[0] > x2.cou[0]) return -1;
	else return 0;
}

