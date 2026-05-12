#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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

\
void visualizza_struttura(NumerazioneCivica dati[], int i) 
{
    for(int j = 0; j < i; j++)
    {
        cout << j + 1 << ") " 
             << dati[j].ClasseToponimo << " " 
             << dati[j].DescrizioneToponimo << " n." 
             << dati[j].Numero << " (CAP: " 
             << dati[j].CAP << ")" << endl;
    }
}


void ordina(NumerazioneCivica arr[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        int indiceMinimo = i;

        for (int j = i + 1; j < n; j++) 
        {
            if (arr[j].Numero < arr[indiceMinimo].Numero) 
            {
                indiceMinimo = j;
            }
        }

        if (indiceMinimo != i) 
        {
            NumerazioneCivica temp = arr[i];
            arr[i] = arr[indiceMinimo];
            arr[indiceMinimo] = temp;
        }
    }
    cout << "Ordinamento completato." << endl;
}

void inserisci_struttura(NumerazioneCivica dati[],int &i) 
{
    ifstream fileInput("Comune_Bergamo_-_Numerazione_civica.csv");
    string linea;
    

    if (!fileInput.is_open()) 
	{
        cout << "Impossibile aprire il file" << endl;
        return;
    }

    getline(fileInput, linea);

    while (getline(fileInput, linea) && i < 1000) 
	{
        stringstream riga(linea);
        string temp;

        getline(riga, dati[i].ClasseToponimo, ',');
        getline(riga, dati[i].DescrizioneToponimo, ',');
        getline(riga, dati[i].Numero, ',');
        getline(riga, dati[i].Subalterno, ',');
        getline(riga, dati[i].CAP, ',');
        getline(riga, dati[i].SezioneISTAT, ',');
        
        getline(riga, temp, ',');
        dati[i].Lat = dati[i].Posto.lat = (temp != "") ? stod(temp) : 0;
        
        getline(riga, temp, ',');
        dati[i].Lon = dati[i].Posto.lon = (temp != "") ? stod(temp) : 0;

        i++;
    }

    cout << "Caricate " << i << " righe." << endl;
    fileInput.close();
}

int main()
{
	int cont = 3;
	NumerazioneCivica dati[1000];	
	int i = 0;
	
	do
	{	
		cout << "\n0 - Esci"<<endl;
		cout << "1 - inserisci dati nella struttura"<<endl;
		cout << "2 - Visualizzazione"<<endl;
		cout << "3 - ordina numeri civici"<<endl;
		cout<< "scegli la funzione:";
		cin >> cont;
		
		switch (cont)
		{
			case 1:
				inserisci_struttura(dati,i);
				break;
			case 2:
				visualizza_struttura(dati,i);
				break;	
			case 3:
				ordina(dati,i);
				break;
							
		}
	}while(cont != 0);
 

    return 0;
}