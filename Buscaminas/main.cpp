#include<iostream>
#include<string>
#include<windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>




using namespace std;

//Esta funcion sirve para crear las columnas de cada una de las matrices
void creacion_mt(string **mt,int f,int c,int i=0){
    if (f==i) return;
    *(mt+i)=new string[c];
    i++;
    creacion_mt(mt,f,c,i);
  }

//Esta funion sirve para hacer el llenado de las matrices , con lo numeros que el usuaro dicte
void llenado(string **mt,int f,int c,int i=0,int j=0){
    if (j==c){
        i++;
        j=0;
    }
    if (i==f) return;
    *(*(mt+i)+j) = "0";
    j++;
    llenado(mt,f,c,i,j);
}

//Esta funcion sirve para qque se impriman las matrices que queramos
void imprimir(string **mt,int f,int c,int i=0,int j=0){
    if (j==c){
       cout<<"\n";
        i++;
        j=0;
    }
    if (i==f) return;
    cout<<*(*(mt+i)+j)<<"  ";
    j++;
    imprimir(mt,f,c,i,j);
}


//Esta funcion elimina los espacios que fueron resevados para las matrices dinamicas
void eliminar(string **mt,int f,int i=0){
		if (i==f){
			delete[] mt;
			return;
		}
		delete[] *(mt+i);
		i++;
		eliminar(mt,f,i);

}
//Esta funcion cumple de entrada , para toamr los valores de la matriz
int entrada(){
  int a;
  cin>>a;
  return a;
}

void creacion_mt1(int **mt,int f,int c,int i=0){
    if (f==i) return;
    *(mt+i)=new int[c];
    i++;
    creacion_mt1(mt,f,c,i);
  }

void llenado_matriz_auxiliar(string **mt,int f,int c,int i=0,int j=0){
    if (j==c){
        i++;
        j=0;
    }
    if (i==f) return;

    *(*(mt+i)+j) = "_" ;
    j++;
    llenado_matriz_auxiliar(mt,f,c,i,j);
}
string  transformacion(int cont){
    if (cont ==0)return "-";
    if (cont ==1)return "1";
    if (cont ==2)return "2";
    if (cont ==3)return "3";
    if (cont ==4)return "4";
    if (cont ==5)return "5";
    if (cont ==6)return "6";
    if (cont ==7)return "7";
    if (cont ==8)return "8";
    return "-";
}
void mapeo(string **mt,int i ,int j,int f,int c){
    int cont=0;
    for (int b=0;b<3;b++){
        for (int a=0;a<3;a++){
            if ( (i-1+b)<f and (j-1+a)<c and (i-1+b)>=0 and (j-1+a)>=0 ){
                if (mt[i-1+b][j-1+a]=="*"){
                       cont++;}
           }
         }
       }
       mt[i][j]=transformacion(cont);
 }
void llenado_matriz_aleatoria(string **mt,int f,int c){
    for (int i=0; i<f; i+=1){
        for (int j =0;j<c;j+= 1){
            if ((mt[i][j])!="*"){
                 mapeo(mt,i,j,f,c);
                 }
            }
        }
     return;
 }

void imprimir1(int **mt,int f,int c,int i=0,int j=0){
    if (j==c){
       cout<<"\n";
        i++;
        j=0;
    }
    if (i==f) return;
    cout<<*(*(mt+i)+j)<<"  ";
    j++;
    imprimir1(mt,f,c,i,j);
}
//esta funcion libera la memoria separada por los punteros
void eliminar1(int **mt,int f,int i=0){
        if (i==f){
            delete[] mt;
            return;
        }
        delete[] *(mt+i);
        i++;
        eliminar1(mt,f,i);

}
//funcion que crea las minas en la matriz aleatoriamente
void llenado_ramdon(int **mt,string **mt1,int matriz_filas,int matriz_columnas,int numero_bombas){
    int a=0;
    int b=0;
    srand(time(NULL));
    for(int i=0;i<numero_bombas;i++){
        a=rand()%matriz_filas;
        mt[i][0]=a;
           b=rand()%matriz_columnas;
           mt[i][1]=b;
        mt1[a][b]="*";
    }
    return;
}
//funcion que comprueba si hemos perdido las vidas
void gameover(int vida){
    if(vida==0){
        cout<<"\n\n"<<"   GAME OVER   "<<endl;
    }
}
//Funcion para mostrar de una matriz a otra
int mostrar(int x, int y,string **a,string **c,int vidas,string &temp){
if (c[x][y]=="*"){
    vidas=0;
}else{
    a[x][y]=c[x][y];
    temp=a[x][y];
}
return vidas ;
}

int main()
{
    int x=0;
    int y=0;
    int vida=1;
    char var;
    string **mt2;
    int **posiciones_bombas;
    string **mt1;
    cout<<"TAMAÑO DEL JUEGO:\n";
    cout<<"Poner filas:\n";
    int filas1=entrada();
    cout<<"Poner columnas:\n";
    int columnas1=entrada();
    //Defenimos a la  matriz qu contendra las bombas y los numeros aleatorios
    int filas2=filas1;
    int columnas2=columnas1;
    int numero_bombas= filas1+columnas1;
    //Desarrollo de la primera matriz
    mt1=new string*[filas1];
    creacion_mt( mt1,filas1,columnas1,0);
    llenado(mt1,filas1,columnas1,0,0);
     //Desarrollo de la matriz aleatoria
    mt2=new string*[filas2];
    creacion_mt( mt2,filas2,columnas2,0);
    llenado_matriz_auxiliar(mt2,filas2,columnas2,0,0);
    //Matriz de numero de bombas
    posiciones_bombas=new int*[numero_bombas];
    creacion_mt1(posiciones_bombas,numero_bombas,2,0);
    llenado_ramdon(posiciones_bombas, mt2, filas2,columnas2,numero_bombas);
     //Continuamos con la matriz aleatoria
    llenado_matriz_aleatoria(mt2,filas2,columnas2);
    imprimir(mt2,filas2,columnas2,0,0);
    string temp="0";
    mt1[x][y]="x";
    //temp es una variable para almacenar el dato anterior y una vez que pase el jugadr por ensima no lo borre
while(vida==1){
    //temp=mt1[x][y];
    int mov;
    var=_getch();
    system("cls");
    Beep(500,400);
    mov=int(var);
    if(mov==97){
        if(y==0){
        mt1[x][y]="x";
        imprimir(mt1,filas1,columnas1,0,0);
        }
        else{
          mt1[x][y]=temp;
          y=y-1;
          temp=mt1[x][y];
          mt1[x][y]="x";
        imprimir(mt1,filas1,columnas1,0,0);
        }
    }
    else if(mov==100){
        if(y==filas1-1){
          mt1[x][y]="x";
        imprimir(mt1,filas1,columnas1,0,0);
        }
        else{
          mt1[x][y]=temp;
          y=y+1;
          temp=mt1[x][y];
          mt1[x][y]="x";
        imprimir(mt1,filas1,columnas1,0,0);
        }
    }
    else if(mov==115){
        if(x==columnas1-1){
          mt1[x][y]="x";
        imprimir(mt1,filas1,columnas1,0,0);
        }
        else{
          mt1[x][y]=temp;
          x=x+1;
          temp=mt1[x][y];
          mt1[x][y]="x";
          imprimir(mt1,filas1,columnas1,0,0);
        }
    }
    else if(mov==119){
        if(x==0){
          mt1[x][y]="x";
        imprimir(mt1,filas1,columnas1,0,0);
        }
        else{
            mt1[x][y]=temp;
            x=x-1;
            temp=mt1[x][y];
            mt1[x][y]="x";
            imprimir(mt1,filas1,columnas1,0,0);
        }
    }
    else if(mov==13){
        vida=mostrar(x,y,mt1,mt2,vida,temp);
        imprimir(mt1,filas1,columnas1,0,0);
    }
//si el jugador revela todos los espacios menos las bombas es que ah ganado

  }
  gameover(vida);
  eliminar(mt1,filas1,0);
  eliminar1(posiciones_bombas,numero_bombas,0);
  eliminar(mt2,filas2,0);
    return 0;
}
