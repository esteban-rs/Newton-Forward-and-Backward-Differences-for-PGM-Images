#include <bits/stdc++.h>
#include <time.h>
#include "Tools.hpp"

int main(int argc, char const *argv[]){

    if (argc == 1 || argc > 2){
        cout << "Ingrese el nombre de un solo fichero. " << endl;
        exit(-1);
    }

    string name  = argv[1];
    string name1 = name.substr(8,9);

    PGM Image(name);   

    vector < int> fac;
    for (int k = 0; k < 10; k++){
        fac.push_back(factorial(k));
    }

    vector <int> id = {3,5,7};

    for (int i = 0; i < id.size(); i++) {
    	cout << "* " << id[i] << " puntos de interpolación *" << endl;
        Image.forward_differece_by_rows(id[i],fac);
        Image.normalize_GX();
        
        Image.WritePGM_GX("Out/forward_X_" + to_string(id[i]) + "_" + name1);
        
        Image.forward_differece_by_cols(id[i],fac);
        Image.normalize_GX();
        Image.WritePGM_GX("Out/forward_Y_" + to_string(id[i])+ "_" + name1);

        Image.backward_differece_by_cols(id[i],fac);
        Image.normalize_GX();
        Image.WritePGM_GX("Out/backward_Y_" + to_string(id[i])+ "_" + name1);
    
        Image.backward_differece_by_rows(id[i],fac);
        Image.normalize_GX();
        Image.WritePGM_GX("Out/backward_X_" + to_string(id[i])+ "_" + name1);
    }

    return 0;
}
