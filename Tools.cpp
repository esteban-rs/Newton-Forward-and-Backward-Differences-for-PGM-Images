#include <bits/stdc++.h>
#include "Tools.hpp"

PGM::PGM(string filename) {
    ifstream file(filename);

    if (file.is_open() == 0){
        cerr << "No existe el archivo." <<endl;
        exit(-1);
    }

    string line;              // Variable local
    /* **** C o m i e n z a  l e c t u r a **** */                 
    getline(file, line);
    if (line.compare("P2") != 0){
        cout << "Formato no válido." << endl;
    }

    ///getline(file, line);
    //while (line[0] == '#'){  // Salto comentarios
    //    getline(file, line);
    //}
    /* *********** A l o c a c i o n ********** */                 
    file >> cols;
    file >> rows;

    Image.assign(rows, vector<double> (cols,0.0));
    gx.assign(rows, vector<double> (cols,0.0));

    file >> max_scale;
    /* ******* L e e  C o n t e n i d o ******* */                 
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            file >> Image[i][j];
        }
    }
    file.close();

}

void PGM::WritePGM_GX(string filename) {
    ofstream file(filename);
    // Comienza escritura
    file << "P2"<<endl;
    file << "# CREATED BY ESTEBANRS" << endl;
    file << cols << " " << rows << endl;
    file << max_scale << endl;

    // Escribe valores
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            file << (int) gx[i][j] << " ";
        }
        file << endl;
    }
    file.close();
    cout << "¡Hurra! Se escribió imagen en " << filename << endl;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            gx[i][j] = 0;
        }
    }
}

void PGM::normalize_GX(){
    double max = gx[0][0];
    double min = gx[0][0];

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (gx[i][j] > max){
                max = gx[i][j];
            }
            if (gx[i][j] < min){
                min = gx[i][j];
            }
        }
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            gx[i][j] = max_scale*(gx[i][j] - min)/(max - min);
        }
    }
}

int factorial(int n){
    if (n <= 1) return 1;
    return n*factorial(n-1);
}

double PGM::forward_table (int i, int n, vector <double> &row){
    if (n == 0){
        return row[i];
    }
    return (forward_table(i+1, n-1, row) - forward_table(i, n-1, row));
}

double PGM::backward_table(int i, int n, vector <double> &row){
    if (n == 0){
        return row[i];
    }
    return backward_table(i,n-1, row) - backward_table(i-1,n-1,row);
}

void PGM::forward_differece_by_rows(int npoints, vector <int> &fac){
    vector <int> num = {1, 1, -1, 2, -6, 24};
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < (cols - npoints); j++){
            for (int k = 0; k < npoints-1; k++){
                gx[i][j] += (num[k]/fac[k+1])*forward_table(j,k+1, Image[i]);
            }
        }
    }
}

void PGM::forward_differece_by_cols(int npoints, vector <int> &fac){
    vector <int> num = {1, 1, -1, 2, -6, 24};
    
    vector <double> col; 
    col.assign(rows, 0.0);

    for (int i = 0; i < rows - npoints; i++){
        for (int j = 0; j < cols; j++){
            // copio columna
            for (int r = 0; r < rows; r++){
                col[r] = Image[r][j];
            }
            for (int k = 0; k < npoints-1; k++){
                gx[i][j] += ((double)(num[k]/fac[k+1]))*forward_table(i, k+1, col);
            }
        }
    }  
}

void PGM::backward_differece_by_rows(int npoints, vector <int> &fac){
    vector <int> num = {1,-1, -1,-2, -6,-24};
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < (cols - npoints); j++){
            for (int k = 0; k < npoints-1; k++){
                gx[i][j] += (num[k]/fac[k+1])*backward_table(j,k+1, Image[i]);
            }
        }
    }
}

void PGM::backward_differece_by_cols(int npoints, vector <int> &fac){
    vector <int> num = {1,-1, -1,-2, -6,-24};
    
    vector <double> col; 
    col.assign(rows, 0.0);

    for (int i = 0; i < rows - npoints; i++){
        for (int j = 0; j < cols; j++){
            for (int r = 0; r < rows; r++){
                col[r] = Image[r][j];
            }
            for (int k = 0; k < npoints-1; k++){
                gx[i][j] += (num[k]/fac[k+1])*backward_table(i,k+1, col);
            }
        }
    }  
}