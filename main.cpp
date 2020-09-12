/***************************************************
* COP4530 Programming Assignment 1 - Due 9/16/2020
* Cure Reconstruction using matchings
* Author: Kaedon Hamm (kah16h)
* Partner: Karl Cooley
****************************************************/

#include <iostream>
#include <fstream>

// Function Declaration
int compute_nn_edges();         // Calculates Edges (weight? rank?)
void compute_matching(void);    // Has to compute the array G2


struct edge {
    int x;
    int y;
};


// Body of program
int main(){

    std::fstream ifile("data.txt", std::ios_base::in);

    int num_pts;
    ifile << num_pts;

    while(1){
        
    }

    int G1_size = 10;

    int G1 [10];

    /* Things needed:

    array G1 - stores edges? (returns of compute_nn_edges() is stored in this))
             - G1[i] = j
    array G2 - (computed by compute_matching(void)) such that (i, G2[i])
             - This would be the finished product from what I understand

    */




    std::cout << "You can do it!\n";
    return 1;
}


// Function Descriptions
int compute_nn_edges(){
    return 1;
}


/*
    sl-vertex  - single and looking vertex
               - have only one edge incident on it
    sl-edge    - single and looking edge
               - connects two sl-verices
               - w_ij is the weight of the sl-edge


*/
void compute_matching(void){

}