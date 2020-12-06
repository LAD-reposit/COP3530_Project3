using namespace std;
#include <vector>
#include <string>


//sources: Sorting 2 powerpoint by Professor Kapoor
void merge(vector<Pixels> pixelVec, string pixelColor, int left, int mid, int right){
    
    if(pixelColor == "Red"){ //if the user wants to merge sort by red
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int X[n1].getRed();
        int Y[n2].getRed();

        for(int i = 0; i < n1; i++){ //sorting
            X[i] = pixelVec[left+i].getRed();
        }
        for(int j = 0; j < n2; j++){
            Y[j] = pixelVec[mid + 1 + j].getRed();
        }

        int i = 0;
        int j = 0;
        int k = left;

        while ( i < n1 && j < n2){ //sorting part
            if(X[i] <= Y[j]){
                pixelVec[k].getRed() = X[i];
                i++;
            }
            else{
                pixelVec[k].getRed() = Y[j];
                j++;
            }
            k++;
        }

        while ( i < n1){ //sorting parts
            pixelVec[k].getRed() = X[i];
            i++;
            k++;
        }
    
        while ( j < n2){ //sorting parts
            pixelVec[k].getRed() = Y[j];
            j++;
            k++;
        }
    }

    else if(pixelColor == "Green"){ //if the user wants to merge sort by green
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int X[n1].getGreen();
        int Y[n2].getGreen();

        for(int i = 0; i < n1; i++){ //sorting
            X[i] = pixelVec[left+i].getGreen();
        }
        for(int j = 0; j < n2; j++){
            Y[j] = pixelVec[mid + 1 + j].getGreen();
        }

        int i = 0;
        int j = 0;
        int k = left;

        while ( i < n1 && j < n2){ //sorting part
            if(X[i] <= Y[j]){
                pixelVec[k].getGreen() = X[i];
                i++;
            }
            else{
                pixelVec[k].getGreen() = Y[j];
                j++;
            }
            k++;
        }

        while ( i < n1){ //sorting part
            pixelVec[k].getGreen() = X[i];
            i++;
            k++;
        }
    
        while ( j < n2){ //sorting part
            pixelVec[k].getGreen() = Y[j];
            j++;
            k++;
        }
    }

    else if(pixelColor == "Blue"){ //if the user wants to merge sort by green
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int X[n1].getBlue();
        int Y[n2].getBlue();

        for(int i = 0; i < n1; i++){ //sorting
            X[i] = pixelVec[left+i].getBlue();
        }
        for(int j = 0; j < n2; j++){
            Y[j] = pixelVec[mid + 1 + j].getBlue();
        }

        int i = 0;
        int j = 0;
        int k = left;

        while ( i < n1 && j < n2){ //sorting part
            if(X[i] <= Y[j]){
                pixelVec[k].getBlue() = X[i];
                i++;
            }
            else{
                pixelVec[k].getBlue() = Y[j];
                j++;
            }
            k++;
        }
    
        while ( i < n1){ //sorting part
            pixelVec[k].getBlue() = X[i];
            i++;
            k++;
        }
    
        while ( j < n2){ //sorting part
            pixelVec[k].getBlue() = Y[j];
            j++;
            k++;
        }
    }
}



void mergeSort(vector<Pixels> pixelVec, string pixelColor, int left, int right){ //sorting function that calls the helper sort
    if (left < right){
        int mid = left +(right - left)/2; //splits vector and then sorts each part
        mergeSort(pixelVec, pixelColor, left, mid);
        mergeSort(pixelVec, pixelColor, mid + 1, right);
        merge(pixelVec, pixelColor, left, mid, right); //merges it all together
    }
}
