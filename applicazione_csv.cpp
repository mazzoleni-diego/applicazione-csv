#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct location
	{
		double lon;
		double lat;
	};

	struct NumerazioneCivica
	{
		string ClasseToponimo;
		string DescrizioneToponimo;
		string Numero;
		string Subalterno;
		string CAP;
		string SezioneISTAT;
		double Lat;
		double Lon;
		location Posto;
	};  

void visualizza_struttura(NumerazioneCivica dati[]) 
{

}

void lettura_struttura(NumerazioneCivica dati[])
{
	    ifstream fileInput("Comune_Bergamo_-_Numerazione_civica.csv"); 
    string linea;

    if (fileInput.is_open()) 
	{
        while (fileInput >> linea)
		{ 
        	cout << linea << endl;
        	i++;
        }
        fileInput.close();
    } else 
	{
        cout << "Impossibile aprire il file";
    }
}

int main()
{
	int cont = 3;
	NumerazioneCivica dati[1000];	

	do
	{	
		cout << "\n0 - Esci"<<endl;
		cout << "1 - Lettura"<<endl;
		cout << "2 - Visualizzazione"<<endl;
		cout<< "scegli la funzione:";
		cin >> cont;
		
		switch (cont)
		{
			case 1:
				lettura_struttura(dati);
				break;
			case 2:
				visualizza_struttura( dati);
				break;				
		}
	}while(cont != 0);
 

    return 0;
}