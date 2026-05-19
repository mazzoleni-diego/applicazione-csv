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


void visualizza_struttura(NumerazioneCivica dati[], int i) 
{
    for(int j = 0; j < i; j++)
    {
        cout << "--- RECORD " << j + 1 << " ---" << endl;
        cout << "Toponimo: " << dati[j].ClasseToponimo << " " << dati[j].DescrizioneToponimo << endl;
        cout << "Numero Civico: " << dati[j].Numero << endl;
        cout << "Subalterno: " << dati[j].Subalterno << endl;
        cout << "CAP: " << dati[j].CAP << endl;
        cout << "Sezione ISTAT: " << dati[j].SezioneISTAT << endl;
        cout << "Latitudine (diretta): " << dati[j].Lat << endl;
        cout << "Longitudine (diretta): " << dati[j].Lon << endl;
        cout << "Posto - Latitudine: " << dati[j].Posto.lat << endl;
        cout << "Posto - Longitudine: " << dati[j].Posto.lon << endl;
        cout << "----------------------\n" << endl;
    }
}


void ordina(NumerazioneCivica arr[], int n, string viaScelta)
{
    // array per memorizzare solo la via scleta
    NumerazioneCivica filtrati[1000];
    // variabile per filtrare i numeri della via
    int temp = 0;

    for (int i = 0; i < n; i++) 
    {
        if (arr[i].DescrizioneToponimo == viaScelta) 
        {
            filtrati[temp] = arr[i];
            temp++;
        }
    }


    if (temp == 0) 
    {
        cout << "\nNessun civico trovato per via " << viaScelta << endl;
        return;
    }

    // ordiniamento dei record filtrati 
    for (int i = 0; i < temp - 1; i++) 
    {
        int indiceMinimo = i;

        for (int j = i + 1; j < temp; j++) 
        {
            if (stoi(filtrati[j].Numero) < stoi(filtrati[indiceMinimo].Numero)) 
            {
                indiceMinimo = j;
            }
        }

        if (indiceMinimo != i) 
        {
            NumerazioneCivica Temp = filtrati[i];
            filtrati[i] = filtrati[indiceMinimo];
            filtrati[indiceMinimo] = Temp;
        }
    }

    // stampa
    cout << "\nNumeri civici ordinati per VIA " << viaScelta << ":" << endl;
    for (int j = 0; j < temp; j++) 
    {
        cout << filtrati[j].ClasseToponimo << " " << filtrati[j].DescrizioneToponimo << " N. " << filtrati[j].Numero;
        if (!filtrati[j].Subalterno.empty()) cout << " / " << filtrati[j].Subalterno;
        cout << endl;
    }
    cout << "Ordinamento completato con successo. Record trovati: " << temp << endl;
}
void file_istat(NumerazioneCivica dati[], int n)
{
    ofstream outfile("dati_istat.html", ios::out);
    
    if (outfile) 
    {
        outfile << "<html>\n<body>\n";
        outfile << "<h2>Report Sezioni ISTAT</h2>\n";
        outfile << "<table border='1'>\n"; 
        outfile << "  <tr><th>Sezione ISTAT</th><th>Numero Record</th></tr>\n";

        //prendo i record
        for (int i = 0; i < n; i++) 
        {
            //salta i record vuoti
            if (dati[i].SezioneISTAT == "") continue;

            //controllo per i duplicati
            bool doppio = false;
            for (int k = 0; k < i; k++) 
            {
                if (dati[k].SezioneISTAT == dati[i].SezioneISTAT) 
                {
                    doppio = true;
                    break;
                }
            }

            if (doppio == false) 
            {
                int conteggio = 0;
                for (int j = 0; j < n; j++) 
                {
                    if (dati[j].SezioneISTAT == dati[i].SezioneISTAT) 
                    {
                        conteggio++;
                    }
                }

                outfile << "  <tr>\n"
                        << "    <td>" << dati[i].SezioneISTAT << "</td>\n"
                        << "    <td>" << conteggio << "</td>\n"
                        << "  </tr>\n";
            }
        }

        //chiudo i tag
        outfile << "</table>\n</body>\n</html>";
        
        cout << "\nFile 'dati_istat.html' creato con successo!" << endl;
        outfile.close();
    }
    else 
    {
        cout << "Errore nell'apertura del file!" << endl;
    }
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
		if (temp != "") 
		{
		    dati[i].Lat = stod(temp);
		    dati[i].Posto.lat = stod(temp);
		} else 
		{
		    dati[i].Lat = 0;
		    dati[i].Posto.lat = 0;
		}
		
		getline(riga, temp, ',');
		if (temp != "") 
		{
		    dati[i].Lon = stod(temp);
		    dati[i].Posto.lon = stod(temp);
		} else 
		{
		    dati[i].Lon = 0;
		    dati[i].Posto.lon = 0;
		}
				
    i++;
    }
    fileInput.close();
}

int main()
{
	int cont = 3;
	NumerazioneCivica dati[1000];	
	int i = 0;
	string viaScelta;
	
	do
	{	
		cout << "\n0 - Esci"<<endl;
		cout << "1 - Inserisci dati nella struttura"<<endl;
		cout << "2 - Visualizzazione"<<endl;
		cout << "3 - Ordina numeri civici data una via"<<endl;
		cout << "4 - Crea file html per ordinare i dati istat"<<endl;
		cout<< "Scegli la funzione:";
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
  				cout << "Inserisci il nome della via: ";
  				cin.ignore();
				getline(cin,viaScelta);
				ordina(dati,i,viaScelta);
				break;
			case 4:
				file_istat(dati, i);
				break;
							
		}
	}while(cont != 0);

    return 0;
}