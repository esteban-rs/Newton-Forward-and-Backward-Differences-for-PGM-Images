#ifndef TOOLS_HPP
#define TOOLS_HPP

using namespace std;

class PGM{
    private:
        int rows      = 0;
        int cols      = 0;
        int max_scale = 0;
        vector<vector<double>> Image; // Guarda Imagen Original
        vector<vector<double>> gx;    // Gradiente

        double forward_table(int i, int n, vector <double> &row);
        double backward_table(int i, int n, vector <double> &row);
    public:
        PGM(string filename);

        void normalize_GX();
        void forward_differece_by_cols(int npoints, vector <int> &fac);
        void forward_differece_by_rows(int npoints, vector <int> &fac);
        void backward_differece_by_cols(int npoints, vector <int> &fac);
        void backward_differece_by_rows(int npoints, vector <int> &fac);


        void WritePGM_GX(string filename);   // Escribe imagen original
        void WritePGM_GY(string filename);// Escribe Max y Min
};

int factorial (int n);

#endif
