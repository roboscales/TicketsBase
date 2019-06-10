#define TL

#include "core.h"


TicketTL *addEnd(TicketTL **pnew){
	TicketTL *t = NULL;

	t = getlast(tfirst);
	(*pnew) -> tnext = NULL;
	(*pnew) -> tprev = t;
	t -> tnext = (*pnew);
	t = t->tnext;
	t->tnext = NULL;

	return (*pnew);
}

TicketTL *addBegin(TicketTL **first){

			(*first) -> tnext = NULL;
			(*first) -> tprev = NULL;
			tfirst = (*first);
			(*first) = NULL;

			return (*first);
}

TicketTL *deleteBegin(TicketTL **head){
		if((*head) -> tnext){
				(*head) = (*head)->tnext;
				free((*head)->tprev);
				(*head)->tprev = NULL;
			}
			else{
			free((*head));
			(*head) = NULL;
			}

			return (*head);
}

TicketTL *deleteMid(TicketTL **nowDelete){

	TicketTL *nowDeletePrev = NULL;

		      nowDeletePrev = (*nowDelete)->tprev;
		      nowDeletePrev->tnext = (*nowDelete)->tnext;
		      (*nowDelete)->tnext->tprev = nowDeletePrev;
		      free((*nowDelete));
		      (*nowDelete) = nowDeletePrev;
		      nowDeletePrev = nowDeletePrev->tprev;

		      return (*nowDelete);

}

TicketTL *getlast(TicketTL *first){

	if(!first) return NULL;
	while(first -> tnext)
		first = first -> tnext;

	return first;
}

/*void OLSwap(TicketTL *first, TicketTL *sec){
}*/

void ListDestroy(TicketTL **head){

	while((*head)->tnext){
		(*head) = (*head)->tnext;
		free((*head)->tprev);
	}
	free((*head));
	(*head) = NULL;

}

void twoLinkSwap(TicketTL *first, TicketTL *second){

	if(first == tfirst){

		tfirst->tnext->tnext->tprev = tfirst;
		tfirst->tprev = tfirst->tnext;
		tfirst->tnext = tfirst->tnext->tnext;
		tfirst = tfirst->tprev;
		tfirst ->tnext = tfirst->tprev;
		tfirst->tprev = NULL;

	}

	else if(!second->tnext){

		first->tprev->tnext = second;
		second->tprev = first->tprev;
		first->tprev = second;
		first->tnext = NULL;
		second->tnext = first;
	}

	else{
	(second) = (first)->tnext;
	(first)->tprev->tnext=(second);
	(second)->tnext->tprev = first;
	(second)->tprev = (first)->tprev;
	(first)->tnext = (second)->tnext;
	(first)->tprev = (second);
	(second)->tnext = (first);
	}
}


TicketTL *bsortssb(TicketTL **head){

	TicketTL *foward = NULL;

	int i, j;

	foward = (*head);

	while(foward){
		if(foward->tnext && strcmp(foward->cou, foward->tnext->cou) > 0){
			twoLinkSwap(foward, foward->tnext);
			j = 1;
		}
		foward = foward->tnext;
		if(!foward && j == 1){
			j = 0;
			foward = (*head);
		}
	}

	return (*head);

}

TicketTL *deleteLast(TicketTL **nowDelete){

	TicketTL *nowDeletePrev = NULL;

	  nowDeletePrev = (*nowDelete)->tprev;
		       free((*nowDelete));
		       nowDeletePrev->tnext = NULL;
		       (*nowDelete) = nowDeletePrev;
		       nowDeletePrev = nowDeletePrev -> tprev;

		       return (*nowDelete);
}

TicketTL *bsortsbs(TicketTL **head){

	TicketTL *foward = NULL;

	int i, j, ListSize = 0;

	foward = (*head);

	while(foward){
		if(foward->tnext && strcmp(foward->cou, foward->tnext->cou) < 0){
			twoLinkSwap(foward, foward->tnext);
			j = 1;
		}
		foward = foward->tnext;
		if(!foward && j == 1){
			j = 0;
			foward = (*head);
		}
	}

	return (*head);

}

TicketTL *bsortrsb(TicketTL **head){

	TicketTL *foward = NULL;

	int i, j, ListSize = 0;

	foward = (*head);

	while(foward){
		if(foward->tnext && foward->rub > foward->tnext->rub){
			twoLinkSwap(foward, foward->tnext);
			j = 1;
		}
		foward = foward->tnext;
		if(!foward && j == 1){
			j = 0;
			foward = (*head);
		}
	}

	return (*head);

}

TicketTL *bsortrbs(TicketTL **head){

	TicketTL *foward = NULL;

	int i, j, ListSize = 0;

	foward = (*head);

	while(foward){
		if(foward->tnext && foward->rub < foward->tnext->rub){
			twoLinkSwap(foward, foward->tnext);
			j = 1;
		}
		foward = foward->tnext;
		if(!foward && j == 1){
			j = 0;
			foward = (*head);
		}
	}

	return (*head);

}

void load(void){

	FILE *data = NULL;
	TicketTL *tnew = NULL, *t = NULL;
	int wr = 0;

	if(!(data = fopen("data.bin", "rb"))){
		printf("Невозможно открыть файл Data.bin\n Обратитесь к системному администратору для решения этой проблемы.\n Нажмите ESC для выхода.");
		while(1)
		if(getch() == ESC) exit(1);
	}


	fseek(data, 0, SEEK_END);
	str_count = ftell(data) / sizeof(TicketTL);

	rewind(data);

	wr = 0;

	while(!feof(data)){

		fseek(data, wr*sizeof(TicketTL), SEEK_SET);
		if(wr == str_count) break;
		wr++;

		if(!(tnew = (TicketTL*)malloc(sizeof(TicketTL)))){
			printf("Error on allocate!");
			getch();
			exit(1);
		}
		fread(tnew, sizeof(TicketTL), 1, data);

		if(tfirst){
		   addEnd(&tnew);
		}

		else if(!tfirst){
			addBegin(&tnew);
		}
		}

	if(fclose(data)){
		printf("Ошибка закрытия файла Data.bin\n Обратитесь к системому администратору для решения этой проблемы.\n Нажмите ESC для выхода.");
		while(1)
		if(getch() == ESC) exit(1);
		}

		data = NULL;
}


void save(void){

	TicketTL *t = NULL;
	FILE *data = NULL;

	clrscr();

	if(!(data = fopen("data.bin", "wb"))){
		printf("Ошибка открытия файла!");
		getch();
		exit(1);
	}

	for(t = tfirst; t; t = t->tnext){
		fwrite(t, sizeof(TicketTL), 1, data);
	}


	if(fclose(data)){
		printf("Ошибка закрытия файла Data!");
		getch();
		exit(1);
		}

		data = NULL;

	windofch = WINDOFF;
}	