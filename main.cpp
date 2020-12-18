#include <iostream>
#include <cmath>
//#include "vector.hpp"
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

typedef int TP;

template <class T>
struct Factory
{
    public:

    int classid = 0;
    int count = 0;
    pair<T, T> a[4];

    Factory(){
        for (int i = 0; i < this->count; i++)
        {
            this->a[i].first = 0;
            this->a[i].second = 0;
        }
        
    }

    Factory(const Factory<T> &s){
        this->count = s.count;
        this->classid = s.classid;
        for (int i = 0; i < count; i++)
        {
            this->a[i].first = s.a[i].first;
            this->a[i].second = s.a[i].second;
        }
    }

    void virtual Print(){
        printf("Factory\n");
        for (int i = 0; i < this->count; i++)
        {
            printf("Вершина №%d: ", i+1);
            cout<<this->a[i].first<<" "<<this->a[i].second<<endl;
        }
    }


    ~Factory(){}
};

template <class T>
struct Rectangle : public Factory<T>
{
    Rectangle(){
        this->count = 4;
        this->classid = 2;
    }

    Rectangle(const Rectangle<T> &s){
        this->count = s.count;
        this->classid = s.classid;
        for (int i = 0; i < this->count; i++)
        {
            this->a[i].first = s.a[i].first;
            this->a[i].second = s.a[i].second;
        }
    }

    Rectangle(T x1, T y1, T x2, T y2){ //диагональные вершины
        this->classid = 2;
        this->count = 4;
        this->a[0].first = x1;
        this->a[0].second = y1;
        this->a[2].first = x2;
        this->a[2].second = y2;
        
        this->a[1].first = x2;
        this->a[1].second = y1;
        
        this->a[3].first = x1;
        this->a[3].second = y2;
    }

    void virtual Print(){
        printf("Прямоугольник: \n");
        for (int i = 0; i < this->count; i++)
        {
            printf("Вершина №%d: ", i+1);
            cout<<this->a[i].first<<" "<<this->a[i].second<<endl;
        }
        
    }

    ~Rectangle(){}
};

template <class T>
struct Triangle : public Factory<T>
{
    Triangle(){
        this->count = 3;
        this->classid = 1;
    }

    Triangle(const Triangle<T> &s){
        this->count = s.count;
        this->classid = s.classid;
        for (int i = 0; i < this->count; i++)
        {
            this->a[i].first = s.a[i].first;
            this->a[i].second = s.a[i].second;
        }
    }
    
    Triangle(T x, T y, T x1, T y1)
    {
        this->classid = 1;
        double angle = 3.14 / 180.0 * (360 / 3);
        this->count = 3;
        for (int i = 0; i < 3; i++)
        {
            this->a[i].first = x;
            this->a[i].second = y;
            T nextX = ((x1 - x) * cos(angle) + (y1 - y) * -sin(angle)) + x1;
            T nextY = ((x1 - x) * sin(angle) + (y1 - y) * cos(angle)) + y1;
            x = x1;
            y = y1;
            x1 = nextX;
            y1 = nextY;
        }
    }

    void Print(){
        printf("Треугольник: \n");
        for (int i = 0; i < this->count; i++)
        {
            printf("Вершина №%d: ", i+1);
            cout<<this->a[i].first<<" "<<this->a[i].second<<endl;
        }
        
    }

    ~Triangle(){}
};

template <class T>
struct Square : public Rectangle<T>{

    Square(){
        this->count = 4;
        this->classid = 3;
    }
    
    Square(T x1, T y1, T x2, T y2){ //диагональные вершины
        this->classid = 3;
        this->count = 4;
        if(x2-x1 != y2-y1){
            printf("Вершины квадрата введены неверно\n");
            return;
        }
        this->a[0].first = x1;
        this->a[0].second = y1;
        this->a[2].first = x2;
        this->a[2].second = y2;
        
        this->a[1].first = x2;
        this->a[1].second = y1;
        
        this->a[3].first = x1;
        this->a[3].second = y2;
    }

     Square(const Square<T> &s){
        this->count = s.count;
        this->classid = s.classid;
        for (int i = 0; i < this->count; i++)
        {
            this->a[i].first = s.a[i].first;
            this->a[i].second = s.a[i].second;
        }
    }

    void Print(){
        printf("Квадрат: \n");
        for (int i = 0; i < this->count; i++)
        {
            printf("Вершина №%d: ", i+1);
            cout<<this->a[i].first<<" "<<this->a[i].second<<endl;
        }
        
    }
};

/* создание нового документа
импорт документа из файла
экспорт документа в файл
создание графического примитива (согласно варианту задания)
удаление графического примитива
 отображение документа на экране (печать перечня графических объектов и их характеристик в std::cout)
 реализовать операцию undo, отменяющую последнее сделанное действие. Должно действовать для операций добавления/удаления фигур.
 */

void help()
{
    printf("Для выполнения операции введите соответствующую цифру:\n ");
    printf("\t 1 - создание нового документа\n ");
    printf("\t 2 - импорт документа из файла\n ");
    printf("\t 3 - экспорт документа в файл\n ");
    printf("\t 4 - создание фигуры\n ");
    printf("\t 5 - удаление фигуры\n ");
    printf("\t 6 - Распечатать все фигуры\n ");
    printf("\t 7 - Отмена\n ");
    printf("\t 0 - Выход\n ");
}



int main()
{

    int i = 1;
    char enter = -1;
    TP xl, yl, xr, yr;
    const int bufsize = 5;

    int numb[bufsize], undo[bufsize], un = 0;

    for (int i = 0; i < bufsize; i++)
    {
        numb[i] = -1;
        undo[i] = -1;
    }
    
    Factory<TP> nd[bufsize];

    vector<Factory<TP>> vec;

    help();
    std::cin >> enter;
    while (isdigit(enter))
    {
        switch (enter - 48)
        {

        case 1://printf("\t 1 - создание нового документа\n ");
        {
            vec.clear();
            for (int i = 0; i < bufsize; i++)
            {
                numb[i] = -1;
                undo[i] = -1;
            }
            un = 0;
            printf("Открыт новый файл.\n ");
            break;
        }
        case 2://printf("\t 2 - импорт документа из файла\n ");
        {
            char filename[260];
            int c,n1,n2;
            cin>>filename;
            ifstream fin(filename);
            while(fin>>c){
                switch (c)
            {
            case 1:
            {
            fin >> xl >> yl >> xr >> yr >> n1 >> n2;
            
            Triangle<TP> d(xl, yl, xr, yr);
            vec.push_back(d);
                break;
            }
            case 2:
            {
            fin >> xl >> yl >> n1 >> n2 >> xr >> yr>> n1 >> n2;
            Rectangle<TP> a(xl, yl, xr, yr);
            vec.push_back(a);
                break;
            }
            case 3:
            {
            fin >> xl >> yl >> n1 >> n2 >> xr >> yr>> n1 >> n2;
            Square<TP> a(xl, yl, xr, yr);
            vec.push_back(a);
                break;
            }
                
            
            default:printf("Введённый номер не соответствует фигуре\n");
                break;
            }
            };

            fin.close();
            printf("Импорт произведён.\n ");
            break;
        }
        case 3://printf("\t 3 - экспорт документа в файл\n ");
        { 
            char filename[260];
            cin>>filename;
            FILE* fl = fopen(filename, "w+");
            for_each(vec.begin(), vec.end(), [&](Factory<TP> &tr) {
                fprintf(fl, "%d\n", tr.classid);
                for (int i = 0; i < tr.count; i++)
                {
                fprintf(fl, "%d %d\n", tr.a[i].first, tr.a[i].second);
                }
            });
            printf("Экспорт произведён.\n ");
            fclose(fl);
            break;
        }
        case 4://printf("\t 4 - создание фигуры\n ");
        {
            int fig = 0;
            std::cout << "Введите номер добавляемой фигуры:\n1 - Треугольник\n2 - Прямоугольник\n3 - Квадрат" << endl;
            cin>>fig;
            switch (fig)
            {
            case 1:
            {
            std::cin >> xl >> yl >> xr >> yr;
            Triangle<TP> a(xl, yl, xr, yr);
            vec.push_back(a);
            undo[un % bufsize] = enter - 48;
            un++;
            std::cout << "Элемент вставлен." << endl;
                break;
            }
            case 2:
            {
            std::cin >> xl >> yl >> xr >> yr;
            Rectangle<TP> a(xl, yl, xr, yr);
            vec.push_back(a);
            undo[un % bufsize] = enter - 48;
            un++;
            std::cout << "Элемент вставлен." << endl;
                break;
            }
            case 3:
            {
            std::cin >> xl >> yl >> xr >> yr;
            Square<TP> a(xl, yl, xr, yr);
            vec.push_back(a);
            undo[un % bufsize] = enter - 48;
            un++;
            std::cout << "Элемент вставлен." << endl;
                break;
            }
                
            
            default:printf("Введённый номер не соответствует фигуре\n");
                break;
            }

            break;
        }
        case 5://printf("\t 5 - удаление фигуры\n ");
        {
            int fig = -1;
            cin>>fig;
            vector<Factory<TP>>::iterator itbeg(vec.begin()), itend(vec.end()), it(vec.begin() + fig-1);
            if((it < itbeg)||(it >= itend)){
                printf("Элемента с таким номером нет.\n");
                break;
            }else{
            nd[un % bufsize] = vec[fig-1];
            vec.erase(it);
            undo[un % bufsize] = enter - 48;
            numb[un % bufsize] = fig-1;
            un++;
            printf("Фигура удалена\n");
            break;
            }
        }
        case 6://printf("\t 6 - Распечатать все фигуры\n ");
        {
            if(vec.size() == 0){
                printf("Фигур нет.\n");
            }
            for_each(vec.begin(), vec.end(), [&](Factory<TP> &tr) {
                printf("Фигура №%d\n", i);
                i++;
                for (int i = 0; i < tr.count; i++)
                {
                    printf("Вершина №%d: ", i+1);
                    cout<<tr.a[i].first<<" "<<tr.a[i].second<<endl;
                    
                }
                
            });
            i = 1;
            break;
        }
        case 7://printf("\t 7 - Отмена\n ");
        {
            /* for (int i = 0; i < bufsize; i++)
            {
                printf("%d ", undo[i]);
            }
            printf("\n"); */
            if (undo[un-1 % bufsize] == -1)
            {
                printf("В буфере нет информации о введённых операциях\nВозможно вы отменили слишком много действий(размер буыера %d)\n", bufsize);
                
            }else{
                un--;
                switch (undo[un % bufsize])
                {
                case 4://create
                    {
                        vec.pop_back();
                        printf("Действие отменено.\n");
                    break;
                    }
                    case 5://delete
                    {
                        vector<Factory<TP>>::iterator it(vec.begin() + numb[un % bufsize]);
                        vec.insert(it, Factory<TP>(nd[un % bufsize]));
                        printf("Действие отменено.\n");
                    }
                default:
                    break;
                }
                
            }
            break;
        }
        case 0://printf("\t 0 - Выход\n ");
        {
            std::cout << "Выход из программы..." << endl;
            return 0;
        }
        default:
        {
            help();
            break;
        }
        }
        enter = 48;
        std::cin >> enter;
    }
    if(!(isdigit(enter))){
        std::cout << "Похоже не цифра введена, ну в другой раз не промахнётесь по клавиатуре ;-) \n\n"<< endl;
    }
    return 0;
}



/* int main(){

Square<int> a(1,1,2,2);
Square<int> b(a);

for (int i = 0; i < 4; i++){
            cout<<b.a[i].first<<" "<<b.a[i].second<<endl;
        }
for (int i = 0; i < 4; i++){
            cout<<a.a[i].first<<" "<<a.a[i].second<<endl;
        }
b.Print();
a.Print();




} */