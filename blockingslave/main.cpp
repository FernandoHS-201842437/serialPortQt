#include <QApplication>
#include "dialog.h"
#include "main.h"
#include <iostream>
#include <QString>
#include "QDebug"
#include <math.h>
#include <QByteArray>
#include <string>
#include <cstring>

using namespace std;

QString decimalbin(int numero, QString &in)
 {
    QString binario = "";
    if (numero > 0) {
        while (numero > 0) {
            if (numero%2 == 0) {
                binario = "0"+binario;
                in = "1"+in;
            } else {
                binario = "1"+binario;
                in = "0"+in;
            }
            numero = (int) numero/2;
        }
    }

 return binario;
}

int binariodec(long b)
{
    int d=0,e=0,c=0;
    while(b>=10){
        c=0;
        while(b>=10){
            b=b-10;
            c++;
        }
        d=d+b*pow(2,e);
        e++;
        b=c;
    }
    d=d+c*pow(2,e);
    return d;
}

QString megafuncion(QString txtrama){
    bitset<8>texto[200];
    string str = txtrama.toStdString();
    for (int i = 0; i < txtrama.length(); ++i){
        texto[i]=bitset<8>(str.c_str()[i]);
    }

    int suma=0;
    for(int i=0;i<200;i++)
    {
        string b = texto[i].to_string();
        long bn1 = atoi(b.c_str());
        suma+=binariodec(bn1);
    }

    QString inv="";

//    qDebug()<<decimalbin(suma, inv)<<endl;

   // qDebug()<<"inverso: "<<inv;


    return decimalbin(suma, inv);
}


bool minifuncion(QString n1, QString n2){
    /*string a = n1.toStdString();
    long num1 = atoi(a.c_str());
    string b = n2.toStdString();
    long num2 = atoi(b.c_str());
    qDebug()<<"microfuncion originales:  "<<n1<<"  "<<n2<<endl;
     cout<<"microfuncion strings: "<<a<<"  "<<b<<endl;
    qDebug()<<"microfuncion: "<<num1<<"  "<<num2<<endl;
    return microfuncion(num1,num2);



    int main()
    {
        std::string s = "Hello World!";

        char cstr[s.size() + 1];
        strcpy(cstr, s.c_str());	// or pass &s[0]

        std::cout << cstr << '\n';

        return 0;
    }
*/

    string result = ""; // Initialize result
    int s = 0;          // Initialize digit sum
    string a = n1.toStdString();
    string b = n2.toStdString();
    // Traverse both strings starting from last
    // characters
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || s == 1)
    {
        // Comput sum of last digits and carry
        s += ((i >= 0)? a[i] - '0': 0);
        s += ((j >= 0)? b[j] - '0': 0);

        // If current digit sum is 1 or 3, add 1 to result
        result = char(s % 2 + '0') + result;

        // Compute carry
        s /= 2;

        // Move to next digits
        i--; j--;
    }
    //QString res = QString::fromStdString(result);
    char resultArray[result.size() + 1];
    strcpy(resultArray, result.c_str());
    QString cop(resultArray);
    //qDebug()<< cop;
    for(int k=0; i<sizeof(resultArray); k++){
        QString it(resultArray[k]);
        qDebug() << it << endl;
        if(resultArray[k] == '0'){
            return 0;
        }
    }
    return 1;
}

bool microfuncion(long bn1, long bn2)
{
        int i=0, r=0;
        int sum[20];
        bool band=1;
      while (bn1 != 0 || bn2 != 0)
      {
       sum[i++] = (int)((bn1 % 10 + bn2 % 10 + r) % 2);
       r = (int)((bn1 % 10 + bn2 % 10 + r) / 2);
       bn1 = bn1 / 10;
       bn2 = bn2 / 10;
      }
      if (r != 0) {
       sum[i++] = r;
      }
      --i;

      while (i >= 0) {
       qDebug()<<sum[i];
          if(sum[i--]==0)
       {
           band=0;
           break;
       }
      }
      return band;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
