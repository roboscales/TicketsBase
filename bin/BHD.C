#define BHD

#include "core.h"

void interface(void){
	//char key;
	//int sel = 0, pos[4] = {3, 15, 33, 47}, ent = OUT;
	char *men[] = {"Просмотр", "Редактирование", "Сортировка", "Выход"};

	textattr(WHITE);
	textbackground(BLACK);
	clrscr();

	load();

	clrscr();
	mainPanel(4, men[0], men[1], men[2], men[3]);
	seeDialog();



}

void create(void){

	TicketTL *tnew = NULL, *t = NULL;
	float cost_en, cel, drob; //╨╝╨░╤Б╤Б╨╕╨▓ ╨┤╨╗╤П ╨▓╨▓╨╛╨┤╨░ ╨▓╨╡╤Й╨╡╤Б╤В╨▓╨╡╨╜╨╛╨│╨╛ ╤З╨╕╤Б╨╗╨░(╨▒╨░╨│ ╤Б╨╛ ╤Б╤В╤А╤Г╨║╤В╤Г╤А╨░╨╝╨╕)
	int hour = 0, min = 0, l = 0, h = 0, li = 0, isDot = 0;
	char dvoe, ent, ch[3], cm[3], cost[9] = { 0 };

	clrscr();

	tnew = (TicketTL*)malloc(sizeof(TicketTL));
	str_count++;

	printf("Создайте новую запись!\n");

	t = getlast(tfirst);

			fflush(stdin);
			puts("Страна:");

			l = -1;

			while(1){

				ent = getch();

				if(l!=18){
					if(ent == ' ' || ent>='А'&&ent<='Я' || ent>='а' && ent <= 'п' || ent>='р' && ent <= 'я'){
					l++;
					if(l==0){
					if(ent>='a'&&ent<='z') ent-=32;
					else if(ent>='а'&&ent<='п') ent-=32;
					else if(ent>='р'&&ent<='я') ent -=80;
					}
					tnew->cou[l] = ent;
					printf("%c", ent);
					}
				}

				if(ent ==13){
				l++;
				tnew->cou[l] = '\0';
				break;
				}

				else if(ent == BACKSPACE && l>=0){
					printf("\b");
					printf(" ");
					printf("\b");
					l--;
				}

				if(ent==ESC) return;
			}

			printf("\n");

			fflush(stdin);
			puts("Вид транспорта:");
			choicetr(&tnew);
			puts(tnew->tr);

			fflush(stdin);
			printf("Время путешествия\n");

				l = 0;
			       //	printf("  :  \r");
				while(1){
					ent = getch();

					if (l != 5){
					if(isdigit(ent) || ent == ':' && l <= 5){
					   if(l == 0){
					    printf("%c", ent);
					    hour+=(int)ent-48;
					    }
					    if (l==1){
						hour*=10;
						hour+=(int)ent-48;
						printf("%c", ent);
					    }

					    if(l==2){
						ent = ':';
					       printf("%c",ent);
					    }

					    if(l==3){
						printf("%c", ent);
						min += (int)ent-48;
					    }

					    if (l==4){
						min*=10;
						min+=(int)ent-48;
						printf("%c", ent);
					    }

					       l++;
					}
				}


					if(ent == ESC) break;
					if (ent == ENTER && l==5) break;
					else if(ent == BACKSPACE && l>=0){
					printf("\b");
					printf(" ");
					printf("\b");
					if(l==4) min/=10;
					if(l==3) min/=10;
					if(l==1) hour/=10;
					if(l==0) hour/=10;
					l--;
				}


				}
				tnew->len = (hour * 60) + min;

			fflush(stdin);
			printf("\n");
			printf("Стоимость:\n");
			l = 0;
			li = 0;
			isDot = 0;
			while(1){

				ent = getch();

				if(isdigit(ent) && isDot == 0){
				cost[l] = ent;
				printf("%c", ent);

				l++;
				}

				else if(ent == '.'){
					isDot = 1;
					h = l + 1;
					printf(".");
					cost[l] = ent;
				}

				else if(isdigit(ent) && isDot == 1 && h < l + 3){
					cost[h] = ent;
					printf("%c", ent);
					h++;
				}

				if(ent ==13){
				h++;
				cost[h] = '\0';
				break;
				}

				else if(ent == BACKSPACE && l>=0){
					printf("\b");
					printf(" ");
					printf("\b");
					if(isDot == 1){
					 h--;
					 cost[h] = ' ';
					 }
					else if(h == 0){
					 isDot = 0;
					 }
					else if(isDot == 0){
					 l--;
					 cost[l] = ' ';
					 }
				}

				if(ent==ESC) return;

			}
			tnew->rub = atof(cost);
			fflush(stdin);

			printf("\n");

		if(tfirst){
		    addEnd(&tnew);
		}

		else{
		    addBegin(&tnew);
		}

			printf("Press ESC to exit!");

			windofch = WINDON;

	while(1)
		if(getch() == ESC) break;
}

void choicetr(TicketTL **pt){

	char key;

	while(1){

		printf("Выберите вид транспорта:\n1 - Автомобиль\n2 - Самолет\n3 - Круизный лайнер\n4 - Автобус\n5 - Пешком\n");

		key = getch();

		switch(key){
			case '1':
				strcpy((*pt)->tr, "Автомобиль");
				return;
			case '2':
				strcpy((*pt)->tr, "Самолет");
				return;
			case '3':
				strcpy((*pt)->tr, "Круизный лайнер");
				return;
			case '4':
				strcpy((*pt)->tr, "Автобус");
				return;
			case '5':
				strcpy((*pt)->tr, "Пешком");
				return;
		}
	}
}

void see(void){

	TicketTL *t = NULL;
	int count = 0;

	clrscr();

	if(!tfirst){
		printf("Нет записей. ESC - для выхода");
		while(1){
			if(getch()==ESC) break;
			}
	}

	else{

	head();

	for(t = tfirst; t; t = t->tnext, count++)
		table(t, count+1);

	endt();
	while(1){
			if(getch() == ESC) break;
		}
	}
}

void head(void){

	int l = 0;

	char s1[MAXSTR] = "Страна", s2[MAXSTR] = "Транспорт", s3[MAXSTR] = "Продолжительность", s4[MAXSTR] = "Стоимость, руб";

	clrscr();

	for(l = 0; l < MAXSTR; l++){

		if(l == 0){
			printf("%c", 201);
			continue;
		}

		if(l==3){
			printf("%c", 203);
		}

		else if(l == MAXSTR - 1){
			printf("%c", 187);
		}

		else if(l == 24){
			printf("%c", 203);
		}

		else if(l == 46) printf("%c", 203);
		else if(l == 64) printf("%c", 203);
		else printf("%c", 205);
	}

       //	printf("\n");

	printf("%cN%2c%10s%11c%15s%7c%-13s%c%-9s%c", 186, 186, s1, 186, s2, 186, s3, 186, s4, 186);


	for(l = 0; l < MAXSTR; l++){

		if(l == 0){
			printf("%c", 204);
			continue;
		}

		if(l==3){
			printf("%c", 206);
		}

		else if(l == MAXSTR - 1){
			printf("%c", 185);
		}

		else if(l == 24){
			printf("%c", 206);
		}

		else if(l == 46) printf("%c", 206);
		else if(l == 64) printf("%c", 206);


		else printf("%c", 205);
	}

}

void table(TicketTL *t, int count){

	printf("%c%2d%c%-20s%c%-21s%c%*d:%02d%8c%10.2f%5c", 186, count, 186, t->cou, 186, t->tr, 186, 7, (t->len / 60), (t->len % 60), 186, t->rub, 186);
}

void ctable(TicketTL *t, int count){

	cprintf("%c%2d%c%-20s%c%-21s%c%*d:%02d%8c%10.2f%5c", 186, count, 186, t->cou, 186, t->tr, 186, 7, (t->len / 60), (t->len % 60), 186, t->rub, 186);
}

void endt(void){
	int l;

	for(l = 0; l < MAXSTR; l++){

		if(l == 0){
			printf("%c", 200);
			continue;
		}

		if(l == 3)
			printf("%c",202);

		else if(l == MAXSTR - 1){
			printf("%c", 188);
		}

			else if(l == 24){
			printf("%c", 202);
		}

		else if(l == 46) printf("%c", 202);
		else if(l == 64) printf("%c", 202);


		else printf("%c", 205);
	}
}

void find(void){

	TicketTL *pt = NULL;
	char k1[MAXSTR], cost[9], ent;
	int st = 0, count = 0, l = 0, h = 0, li = 0, isDot = 0;
	float r1 = 0.0;

	clrscr();

	printf("Введите страну:\n");

			l = -1;

			while(1){

				ent = getch();

				if(l!=18){
					if(ent == ' ' || ent>='А'&&ent<='Я' || ent>='а' && ent <= 'п' || ent>='р' && ent <= 'я'){
					l++;
					if(l==0){
					if(ent>='a'&&ent<='z') ent-=32;
					else if(ent>='а'&&ent<='п') ent-=32;
					else if(ent>='р'&&ent<='я') ent -=80;
					}
					k1[l] = ent;
					printf("%c", ent);
					}
				}

				if(ent ==13){
				l++;
				k1[l] = '\0';
				break;
				}

				else if(ent == BACKSPACE && l>=0){
					printf("\b");
					printf(" ");
					printf("\b");
					l--;
				}

				if(ent==ESC) return;
			}

	fflush(stdin);

	printf("\nВведите стоимость в рублях:\n");
	l = 0;
			li = 0;
			isDot = 0;
			while(1){

				ent = getch();

				if(isdigit(ent) && isDot == 0){
				cost[l] = ent;
				printf("%c", ent);

				l++;
				}

				else if(ent == '.'){
					isDot = 1;
					h = l + 1;
					printf(".");
					cost[l] = ent;
				}

				else if(isdigit(ent) && isDot == 1 && h < l + 3){
					cost[h] = ent;
					printf("%c", ent);
					h++;
				}

				if(ent ==13){
				h++;
				cost[h] = '\0';
				break;
				}

				else if(ent == BACKSPACE && l>=0){
					printf("\b");
					printf(" ");
					printf("\b");
					if(isDot == 1){
					 h--;
					 cost[h] = ' ';
					 }
					else if(h == 0){
					 isDot = 0;
					 }
					else if(isDot == 0){
					 l--;
					 cost[l] = ' ';
					 }
				}

				if(ent==ESC) return;

			}
			r1 = atof(cost);

	head();

	for(pt = tfirst; pt; pt = pt->tnext){
		if(!strcmp(pt->cou, k1) && pt->rub <= r1){
			table(pt, count+1);
			st++;
			count++;
		}
	}

	endt();

	if(!st){
		clrscr();
		puts("Cannot to find this");
	}

	while(1){
		if(getch() == ESC) break;
	}
}

void sort(void){
	char key;

	clrscr();

	puts("Выберите тип сортировки");
	puts("1 - По стране(А-Я)");
	puts("2 - По стране(Я-А)");
	puts("3 - По стоимости(по возрастанию)");
	puts("4 - По стоимости(по убыванию)");

	key=getch();

	switch(key){
		case '1':
			if(tfirst && tfirst->tnext){
			 bsortssb(&tfirst);
			 windofch = WINDON;
			 puts("Отсортировано. ESC - для продолжения");
				//while(1)
				if(getch()==ESC) break;
			 }
			else if((tfirst && !tfirst->tnext) || !tfirst){
			puts("Нет элементов для сортировки! ESC - для продолжения");
				windofch = WINDOFF;
				//while(1)
				if(getch()==ESC) break;
			}
		 case '2':
			if(tfirst && tfirst->tnext){
			 bsortsbs(&tfirst);
			 windofch = WINDON;
			 puts("Отсортировано! ESC - для продолжения");
				//while(1)
				if(getch()==ESC) break;
			 }
			else if((tfirst && !tfirst->tnext) || !tfirst){
			puts("Нет элементов для сортировки! ESC - для продолжения");
				windofch = WINDOFF;
				if(getch()==ESC) break;
			}
		 case '3':
			if(tfirst && tfirst->tnext){
			 bsortrsb(&tfirst);
			 windofch = WINDON;
			 puts("Отсортировано! ESC - для продолжения");
				//while(1)
				if(getch()==ESC) break;
			 }
			else if((tfirst && !tfirst->tnext) || !tfirst){
			puts("Нет элементов для сортировки! ESC - для продолжения");
				windofch = WINDOFF;
				//while(1)
				if(getch()==ESC) break;
			}
		 case '4':
			if(tfirst && tfirst->tnext){
			 bsortrbs(&tfirst);
			 windofch = WINDON;
			 puts("Отсортировано! ESC - для продолжения");
				//while(1)
				if(getch()==ESC) break;
			 }
			else if((tfirst && !tfirst->tnext) || !tfirst){
			puts("Нет элементов для сортировки! ESC - для продолжения");
				windofch = WINDOFF;
				//while(1)
				if(getch()==ESC) break;
			}
	}
}

void del(TicketTL **nowDelete){

		if((*nowDelete) == tfirst){
			deleteBegin(&tfirst);
		}

	       else if(!(*nowDelete)->tnext){
		       deleteLast(nowDelete);

	       }

	       else{
		     deleteMid(nowDelete);
		}
		//windofch = WINDON;
}


void twoButtonDialog(int x1, int y1, int x2, int y2, char *message, char *first, char *second){

	int i = 0;

	window(x1, y1, x2, y2);
	textattr(WHITE);
	textbackground(BLUE);

	clrscr();

	gotoxy(1, 1);
	cprintf("╔");

	for(i = 0; i < (x2 - x1) - 1; i++){
	 //gotoxy(i, 1);
	 cprintf("═");
	 }

	gotoxy((x2-x1) + 1, 1);
	cprintf("╗");

	//gotoxy(1, 3);

	for(i = 2; i < (y2 - y1) + 1; i++){
		gotoxy(1, i);
		cprintf("║");
		gotoxy((x2-x1) + 1, i);
		cprintf("║");
	}

	gotoxy(1, (y2-y1));
	cprintf("╚");

	for(i = 0; i < (x2 - x1) - 1; i++) cprintf("═");

	gotoxy((x2-x1) + 1, (y2-y1));
	cprintf("╝");


	gotoxy(4, 4);
	cputs(message);

	gotoxy(5, 8);
	cputs(first);

	gotoxy(19, 8);
	cputs(second);

}

void closemo(void){

	char key, sel;
	int pos = 5, l;

	//textattr(WHITE);
	//textbackground(BLACK);
	clrscr();

	if(windofch == WINDOFF){
	if(tfirst) ListDestroy(&tfirst);
	 return;
	 }
	else if(windofch == WINDON){
		while(1){
			while(1){
		     _setcursortype(_NOCURSOR);
		     twoButtonDialog(26, 6, 54, 15, "Сохранить изменения?", "Да","Нет");
		     sel = 0;

			gotoxy(pos, 8);
			if(pos == 5){
			 textattr(BLACK);
			 textbackground(RED);
			 cprintf("Да");
			 sel = '1';
			 }
			if(pos == 19){
			 textattr(BLACK);
			 textbackground(RED);
			 cprintf("Нет");
			 sel = '2';
			 }


			key = getch();

			if (key == 9 && pos == 5){
			 pos = 19;
			 }
			else if(key == 9 && pos == 19){
			 pos = 5;
			 }

			if(key==27) return;
			if(key == 13) break;

			}
			switch(sel){
				case '1':
					save();
					if(tfirst) ListDestroy(&tfirst);
					return;
				case '2':
					if(tfirst) ListDestroy(&tfirst);
					return;
			}
		     }
		     }
	}

void diagnos(void){
	TicketTL *t = NULL;

	clrscr();

	puts("State of List:");

	for(t = tfirst; t; t=t->tnext){
		printf("Current:%p\nPrev:%p  Next:%p\n", t, t->tprev, t->tnext);
		printf("\n");
	}

	while(1){
		if(getch()==27) break;
	}
}

void deleteDialog(void){

	int i = 0, pos = 1;
	char key;
	TicketTL *t = NULL, *tmask = NULL;

	window(1,2,80,25);

	//while(1){
		while(1){
		     //_setcursortype(_NOCURSOR);
		     //clrscr();
		     clrscr();
		     textattr(WHITE);
		     textbackground(BLUE);
		     clrscr();
		     //sel = 0;

		     key = getch();

		     gotoxy(1, pos);

		     if(key == '1') pos++;
		     else if (key == '2') pos--;

		     if(key == 27) return;
		     }
			/*gotoxy(pos, 8);
			if(pos == 5){
			 textattr(BLACK);
			 textbackground(RED);
			 cprintf("Да");
			 sel = '1';
			 }
			if(pos == 19){
			 textattr(BLACK);
			 textbackground(RED);
			 cprintf("Нет");
			 sel = '2';
			 }


			key = getch();

			if (key == 9 && pos == 5){
			 pos = 19;
			 }
			else if(key == 9 && pos == 19){
			 pos = 5;
			 }

			if(key==27) return;
			if(key == 13) break;

			}
			switch(sel){
				case '1':
					save();
					if(tfirst) ListDestroy(&tfirst);
					return;
			case '2':
					if(tfirst) ListDestroy(&tfirst);
					return;
			}*/
		   //  }

}

void mainPanel(size_t num, char *first, ...){

	va_list args;
	char *str = { '\0' };
	int men = 0, pos = 3, sel = 0;

	window(1,1,80,1);
	textattr(WHITE);
	textbackground(BLACK);
	//clrscr();

	va_start(args, num);

	str = va_arg(args, char*);


	clrscr();
	//cputs(first);
	//men = strlen(first);

	while(num--){
		gotoxy(men+4, 1);
		cputs(str);
		men += strlen(str) + 4;
		//str[strlen(str)] = '\0';
		str = va_arg(args, char*);
	}

	//gotoxy(men, 1);

	if(str == NULL){
			str--;
			*str = '\0';
		}

	va_end(args);
}

void listMenu(int x1, int y1, size_t num, char * first, ...){

	va_list args;
	int *size, i = 0, xbig = 0;
	size_t n = num, s = num;
	char *str = { '\0' }, *big = { '\0' };

	va_start(args, num);

	str = va_arg(args, char*);

	while(n--){
		if(strlen(str) > strlen(big))
			big = str;
		str = va_arg(args, char*);
	}

	va_end(args);

	xbig = strlen(big);

	window(x1 - 1, y1, x1 + xbig + 4, y1 + num + 1);

	textattr(BLACK);
	textbackground(LIGHTGRAY);

	va_start(args, num);

	n = num;

	str = NULL;

	str = va_arg(args, char*);

	//cputs(first);
	clrscr();

	//n = num;

	gotoxy(2,1);
	cprintf("┌");

	for(i = 0; i < (xbig+2); i++)
		cprintf("─");

	cprintf("┐");

	i = 2;

	while(n--){
	   gotoxy(3, i);
	   cputs(str);
	   i++;
	   str = va_arg(args, char*);
	}

	for(i = 2; i < s + 2; i++){
	    gotoxy(2, i);
	    cprintf("│");
	    gotoxy(xbig+5, i);
	    cprintf("│");
	}

	gotoxy(2, num+2);
	cprintf("└");

	for(i = 0; i < (xbig+2); i++)
		cprintf("─");

	cprintf("┘");

	va_end(args);
}

/*void entkey (char *key){

	switch(*key = getch()){
		case 0:
			*key = getch() + 1;
			break;
		default:
			*key = getch();
			break;
	}
}*/


/*void mainPanel(char * first, char * second, char * third, char * fourth){

	register int men = 0;

	window(1,1,80,1);
	textattr(BLACK);
	textbackground(7);
	clrscr();

	gotoxy(3,1);
	cputs(first);

	men+=strlen(first)+6;

	gotoxy(men, 1);
	cputs(second);

	men+=strlen(second)+4;

	gotoxy(men, 1);
	cputs(third);

	men+=strlen(third)+4;

	gotoxy(men, 1);
	cputs(fourth);

}*/

//now, the masterpiece

/*void seeDialog(void){

	int i = 0, sel = 4, scrollRate = -1, curs = 0, *scroLoc, listSize = 0, *s, j = 0;
	char key;
	TicketTL *temp = NULL, *tmask = tfirst, *top = tfirst, *bottom = NULL;

	while(1){
	window(1,2,80,25);
	textattr(WHITE);
	textbackground(BLACK);

	gotoxy(1,1);
	headConsole();

	bottom = top->tnext->tnext->tnext->tnext;

	gotoxy(1, 4);
	tableConsole(top);

	for(temp = top->tnext, i = 5; temp!=bottom; temp=temp->tnext, i++){
		gotoxy(1, i);
		tableConsole(temp);
	}

	gotoxy(1, i);
	tableConsole(bottom);

	gotoxy(1, i+1);
	endConsole();

	//scroll
	gotoxy(80, 3);
	textattr(BLACK);
	textbackground(WHITE);
	cprintf("");

	for(i = 4; i < 24; i++){
		gotoxy(80, i);
		cprintf("▒");
	}

	gotoxy(80, 23);
	cprintf("");

	for(temp = tfirst, listSize = 0; temp; temp = temp->tnext, listSize++);

	scroLoc = (int*)malloc(((listSize/5)+1)*sizeof(int));

	for(s = scroLoc, j = 0; s < &scroLoc[listSize/5]; s++, j++)
		*s = j + 4;

	scroLoc[(listSize/5)] = 22;

	key = getch();

	switch(key){
		case 0:
			key = getch();
			scrollRate = 0;
		default:
			break;
	}

	switch(key){
		case 72:
			if(top->tprev){
			top = top->tprev;
			scrollRate--;
			//tmask = tmask->tprev;
			sel--;
			if((scrollRate % 5) == 0){
				curs--;
				//scrollRate = 0;
				}
			}
			else if(!top->tprev){
				curs = 0;
				//scrollRate = 0;
			}
			break;
		case 80:
			if(top->tnext && bottom->tnext){
			top = top->tnext;
			scrollRate++;
			//tmask = tmask->tnext;
			sel++;
			}
			if((scrollRate % 6) == 0){
				curs++;
				//scrollRate = 0;
			}
			else if(!bottom->tnext){
				curs = (listSize/5);
				//scrollRate = 0;
			}
			break;
		case 81:
			if(bottom){
			top = bottom->tnext;
			curs++;
			}
			break;
		case ENTER:
			del(&tmask);
			//tmask = tmask->tnext;
			break;
	}

	gotoxy(80, scroLoc[curs]);
	cprintf("█");

	if(sel<=3){
	 tmask = tfirst;
	 sel = 4;
	 }
	else if(!tmask){
		tmask = tfirst;
		sel = 4;

	}
	else{
	gotoxy(1, sel);
	textattr(BLACK);
	textbackground(GREEN);
	tableConsole(tmask);
	}

	if(getch()==ESC) break;
	}
}*/

/*void seeDialog(void){

	TicketTL *top = NULL, *bottom = NULL, *temp = NULL, *counter = NULL, *page = NULL, *pageIndicator = NULL, *last = getlast(tfirst);
	int *pages = NULL, scrollRate = 4, loc = 4, listSize = 0, cursorLoc = 0, weReachNextPage = 0, state = 0, pageCount = 0, renderLoc = 0, *p, nowPage = 0;
	char key;

	//starting this party
	top = tfirst;

	pageIndicator = top;
	page = pageIndicator->tnext->tnext->tnext->tnext;

	while(1){

		window(1,2,80,25);
		textattr(WHITE);
		textbackground(BLACK);
		clrscr();

		//rendering the table

		bottom = top->tnext->tnext->tnext->tnext;

		headConsole();
		tableConsole(top);
		for(temp = top->tnext; temp != bottom; temp = temp->tnext)
			tableConsole(temp);
		tableConsole(bottom);
		endConsole();

		gotoxy(80, 3);
		textattr(BLACK);
		textbackground(WHITE);
		cprintf("");

		for(renderLoc = 4; renderLoc < 24; renderLoc++){
		gotoxy(80, renderLoc);
		cprintf("▒");
		}

		gotoxy(80, 23);
		cprintf("");

		//now let's locate our pages
		//for this we need a dynamical array

		for(counter = tfirst, listSize = 0; counter; counter = counter->tnext, listSize++);

			pageCount = listSize / 5;

		pages = (int*)malloc((pageCount+1)*sizeof(int));

		for(p = pages, renderLoc = 0; p < &pages[pageCount]; p++, renderLoc++)
			*p = renderLoc + 4;

		pages[pageCount] = 22;

		if(nowPage >= 0 && nowPage <= pageCount){
		gotoxy(80, pages[nowPage]);
		cprintf("0");
		}

		key = getch();

		switch(key){ // checking: if this key have 2 bytes
			case 0:
				key = getch();
			default:
				break;
		}

		//checking on system keys

		switch(key){
			case UP:
				if(top->tprev){
					top = top->tprev;
				}
				if(top == pageIndicator){
					nowPage--;
					pageIndicator = pageIndicator->tprev->tprev->tprev->tprev;
					page = pageIndicator->tnext->tnext->tnext->tnext;
				}
				if(!top->tprev){
					nowPage = 0;
					pageIndicator = tfirst;
					page = pageIndicator->tnext->tnext->tnext->tnext;
				}
				break;
			case DOWN:
				if(bottom->tnext){
					top = top->tnext;
				}
				if(top == page->tnext){
					nowPage++;
					pageIndicator = top;
					page = pageIndicator->tnext->tnext->tnext->tnext;
				}
				if(!bottom->tnext->tnext){
					nowPage = pageCount;
					//page = bottom;
					//pageIndicator=page->tprev->tprev->tprev->tprev;
					}
				break;
			case PGUP:
				if(top->tprev){
						if(bottom == last){
						top = pageIndicator;
						nowPage--;
						}
						else{
						pageIndicator = pageIndicator->tprev->tprev->tprev->tprev->tprev;
						page = pageIndicator->tnext->tnext->tnext->tnext;
						top = pageIndicator;
						nowPage--;
						}
					}
				break;
			case PGDN:
				if(bottom->tnext){
					top = bottom->tnext;
						if(top->tnext->tnext->tnext->tnext){
						pageIndicator = top;
						page = pageIndicator->tnext->tnext->tnext->tnext;
						}
						if(!bottom->tnext->tnext->tnext->tnext){
						bottom = getlast(tfirst);
						top = bottom->tprev->tprev->tprev->tprev;
						//pageIndicator = top;
						//page = pageIndicator->tnext->tnext->tnext->tnext;
						}
					nowPage++;
					}
				break;
			case HOME:
				top = tfirst;
				pageIndicator = top;
				page = pageIndicator->tnext->tnext->tnext->tnext;
				nowPage = 0;
				break;
			case END:
				bottom = getlast(tfirst);
				top = bottom->tprev->tprev->tprev->tprev;
				//pageIndicator = top;
				//page = pageIndicator->tnext->tnext->tnext->tnext;
				nowPage = pageCount;
				break;
		}

		if(getch() == ESC) break;
	}
}*/

void headConsole(void){

	int i;
	char *country = "Страна", *transport = "Транспорт", *length = "Продолжительность", *cost = "Стоимость, руб";
	//window(1,2,80,25);
	textattr(WHITE);
	textbackground(BLACK);
	clrscr();

	for(i = 0; i < 79; i++){

		switch(i){
			case 0:
				cprintf("╔");
				break;
			case 78:
				cprintf("╗");
				break;
			case 18:
				cprintf("╦");
				break;
			case 40:
				cprintf("╦");
				break;
			case 60:
				cprintf("╦");
				break;
			default:
				cprintf("═");
				break;
		}
	}

	gotoxy(1,2);
	cprintf("║");

	gotoxy(7, 2);
	cputs(country);

	gotoxy(19, 2);
	cprintf("║");

	gotoxy(26, 2);
	cputs(transport);

	gotoxy(41, 2);
	cprintf("║");

	gotoxy(43, 2);
	cputs(length);

	gotoxy(61, 2);
	cprintf("║");

	gotoxy(63, 2);
	cputs(cost);

	gotoxy(79, 2);
	cprintf("║");

	gotoxy(1, 3);
	for(i = 0; i < 79; i++){

		switch(i){
			case 0:
				cprintf("╠");
				break;
			case 78:
				cprintf("╣");
				break;
			case 18:
				cprintf("╬");
				break;
			case 40:
				cprintf("╬");
				break;
			case 60:
				cprintf("╬");
				break;
			default:
				cprintf("═");
				break;
		}
	}
	cprintf("\r\n");
}

void tableConsole(TicketTL * t){

	cprintf("%c%-17s%c%-21s%1c%*d:%02d%8c%12.2f%6c\r\n", 186, t->cou, 186, t->tr, 186, 9, (t->len / 60), (t->len % 60), 186, t->rub, 186);

}

void endConsole(void){

	int i = 0;

	for(i = 0; i < 79; i++){

		switch(i){
			case 0:
				cprintf("╚");
				break;
			case 78:
				cprintf("╝");
				break;
			case 18:
				cprintf("╩");
				break;
			case 40:
				cprintf("╩");
				break;
			case 60:
				cprintf("╩");
				break;
			default:
				cprintf("═");
				break;
		}
	}
}

void createDialog(void){

	int i;

	window(9,5,71,22);
	textattr(LIGHTGRAY);
	textbackground(BLACK);
	clrscr();

	cprintf("╔");

	for(i = 0; i < 61; i++)
		cprintf("═");

	cprintf("╗");

	for(i = 2; i < 16; i++){
		gotoxy(1, i);
		cprintf("║");
		gotoxy(63, i);
		cprintf("║");
		}

		cprintf("╚");

	for(i = 0; i < 61; i++)
		cprintf("═");

	cprintf("╝");

	gotoxy(26, 1);
	cputs(" Cоздание ");

	gotoxy(3, 3);
	cputs("Страна:");

	gotoxy(3, 5);
	cputs("Выберите вид транспорта:");

	gotoxy(3, 10);
	cputs("Время:");

	gotoxy(3, 12);
	cputs("Стоимость в руб.:");

}

void sortDialog(void){

	int i;

	window(20, 9, 61, 17);
	textattr(WHITE);
	textbackground(BLACK);
	clrscr();

		cprintf("╔");

	for(i = 0; i < 38; i++)
		cprintf("═");

	cprintf("╗");

	for(i = 2; i < 9; i++){
		gotoxy(1, i);
		cprintf("║");
		gotoxy(40, i);
		cprintf("║");
		}

		cprintf("  ╚");

	for(i = 0; i < 38; i++)
		cprintf("═");

	cprintf("╝");

	gotoxy(14, 1);
	cputs(" Сортировка ");

	gotoxy(3, 3);
	cprintf("┌");

	for(i = 0; i < 17; i++)
		cprintf("─");

	cprintf("┐");

	for(i = 4; i < 8; i++){
		gotoxy(3, i);
		cprintf("│");
		gotoxy(21, i);
		cprintf("│");
	}

	gotoxy(3, 8);
	cprintf("└");

	for(i = 0; i < 17; i++)
		cprintf("─");

	cprintf("┘");


	gotoxy(22, 3);
	cprintf("┌");

	for(i = 0; i < 15; i++)
		cprintf("─");

	cprintf("┐");

	for(i = 4; i < 8; i++){
		gotoxy(22, i);
		cprintf("│");
		gotoxy(38, i);
		cprintf("│");
	}

	gotoxy(22, 8);
	cprintf("└");

	for(i = 0; i < 15; i++)
		cprintf("─");

	cprintf("┘");

	gotoxy(4, 4);
	cputs(" ( )По стране");

	gotoxy(4, 6);
	cputs(" ( )По стоимости");

	gotoxy(24, 4);
	cputs("По возрастанию");

	gotoxy(24, 6);
	cputs("По убыванию");
}