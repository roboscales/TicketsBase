//  скроллинг 

// размер консоли
const Console_count_lines   = 50;
const Console_count_row     = 120

// размер тела скролла
// все значения по-умолчанию просто инициализируешь при создании объекта структуры
typedef struct Scroll{
    const width  = 2; // размер в символах
    const height = 45;

    const button_size = 1; // по-умолчанию размер кнопок листания (ширина по-умолчанию равна ширине скролла)

    short x = 120 - width; // по-умолчанию положение рядом с правым краем
    short y = 5;           // по-умолчанию положение по вертикали

    short Slider_width = width; // по-умолчанию равен ширине скролла
    short Slider_height;        // по умолчанию не определен 

    short Slider_x = x; // по-умолчанию высчитывается от положения
    short Slider_y = y + 1;

    short step = 0; // начальный шаг скролла
    short max_step;

} Scroll;

// функция которая заливает один символ определенным цветом
// поменяешь на встроенную функцию
void drawFillSymbol(short x, short y, short color);


void renderScrollButton(Scroll* scroll)
{
    short i = 0;
    short j = 0;
    short x = 0;
    short y = 0;

    // отрисовка кнопки вверх
    for (i = 0; i < scroll->width; i++)
    {
        x = scroll->x + i;
        y = scroll->y + 1;

        drawFillSymbol(x, y, YOUR_COLOUR);
    }

     // отрисовка кнопки вниз
    for (i = 0; i < scroll->width; i++)
    {
        x = scroll->x + i;
        y = scroll->y + scroll->height;

        drawFillSymbol(x, y, YOUR_COLOUR);
    }
}

void renderScrollBody(Scroll* scroll)
{
    short i = 0;
    short j = 0;
    short x = 0;
    short y = 0;

    
    for (i = 0; i < scroll->width; i++)
    {
        for (j = 1; j < scroll->height - 1; j++)
        {
            x = scroll->x + i;
            y = scroll->y + j;

            drawFillSymbol(x, y, YOUR_COLOUR);
        }
    }

    // после отрисовки тела, отрисовываем сразу ползунок
    renderScrollSlider(scroll);
}


void renderScrollSlider(Scroll* scroll)
{
    short i = 0;
    short j = 0;
    short x = 0;
    short y = 0;
    
    scroll->Slider_y = Slider_height * step;

    for (i = 0; i < scroll->Slider_width; i++)
    {
        for (j = 0; j < scroll->Slider_height; j++)
        {
            x = scroll->Slider_x + i;
            y = scroll->Slider_y + j;

            drawFillSymbol(x, y, YOUR_COLOUR);
        }
    }
}


void prevStep(Scroll* scroll)
{
    if (scroll->step > 0){
        scroll->step--;
        renderScrollBody(scrool;)
    }
}


void nextStep(Scroll* scroll)
{
    if (scroll->step < scroll->max_step){
        scroll->step++;
        renderScrollBody(scrool;
    }
}

// инициализируешь там где надо структуру //

//Scroll...

int count_record; // тут количество твоих записей в базе


Scroll.width  = 2; 
Scroll.height = 45;

Scroll.button_size = 1; 

Scroll.x = Console_count_row - Scroll.width; 
Scroll.y = 5;           

Scroll.Slider_width = Scroll.width; 

// ВАЖНО Расчитываем высоту ползунка //
Scroll.Slider_height = floor(Scroll.height / count_record);         
////


Scroll.Slider_x = x; 
Scroll.Slider_y = 5;

Scroll.step = 0;

// ВАЖНО Расчитываем количество возможных шагов ползунка //
Scroll.max_step = floor(scroll->height / scroll->Scroll_height);
////

/////////////////////Конец инициализации//////////////////
