using namespace std;
#include <vector>
#include <string>

class Pixels{
    private:
    public:
        void mergeSort(vector<Pixels> pixelVec, int left, int right);
        void merge(vector<Pixels> pixelVec, int left, int mid, int right);
};

//sources: Sorting 2 powerpoint by Professor Kapoor

void Pixels::merge(vector<Pixels> pixelVec, string pixelColor, int left, int mid, int right){
    
    if(pixelColor == Red){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Pixels X[n1];
    Pixels Y[n2];

    for(int i = 0; i < n1; i++){
        X[i] = pixelVec[left+i];
    }
    for(int j = 0; j < n2; j++){
        Y[j] = pixelVec[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while ( i < n1 && j < n2){
        if(X[i] <= Y[j]){
            pixelVec[k] = X[i];
            i++;
        }
        else{
            pixelVec[k] = Y[j];
            j++;
        }
        k++;
    }
    while ( i < n1){
        pixelVec[k] = X[i];
        i++;
        k++;
    }
    
    while ( j < n2){
        pixelVec[k] = Y[j];
        j++;
        k++;
    }
}
}
else if(pixelColor == Green){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Pixels X[n1];
    Pixels Y[n2];

    for(int i = 0; i < n1; i++){
        X[i] = pixelVec[left+i];
    }
    for(int j = 0; j < n2; j++){
        Y[j] = pixelVec[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while ( i < n1 && j < n2){
        if(X[i] <= Y[j]){
            pixelVec[k] = X[i];
            i++;
        }
        else{
            pixelVec[k] = Y[j];
            j++;
        }
        k++;
    }
    while ( i < n1){
        pixelVec[k] = X[i];
        i++;
        k++;
    }
    
    while ( j < n2){
        pixelVec[k] = Y[j];
        j++;
        k++;
    }
}
}
else if(pixelColor == Blue){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Pixels X[n1];
    Pixels Y[n2];

    for(int i = 0; i < n1; i++){
        X[i] = pixelVec[left+i];
    }
    for(int j = 0; j < n2; j++){
        Y[j] = pixelVec[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while ( i < n1 && j < n2){
        if(X[i] <= Y[j]){
            pixelVec[k] = X[i];
            i++;
        }
        else{
            pixelVec[k] = Y[j];
            j++;
        }
        k++;
    }
    while ( i < n1){
        pixelVec[k] = X[i];
        i++;
        k++;
    }
    
    while ( j < n2){
        pixelVec[k] = Y[j];
        j++;
        k++;
    }
}
}


void Pixels::mergeSort(vector<Pixels> pixelVec, string pixelColor, int left, int right){
    if (left < right){
        int mid = left +(right - left)/2;
        mergeSort(pixelVec, pixelColor, left, mid);
        mergeSort(pixelVec, pixelColor, mid + 1, right);
        merge(pixelVec, pixelColor, left, mid, right);
    }
}
