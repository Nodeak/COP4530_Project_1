/***************************************************
* COP4530 Programming Assignment 1 - Due 9/16/2020
* Cure Reconstruction using matchings
* Author: Kaedon Hamm (kah16h)
* Partner: Karl Cooley
****************************************************/

#include <iostream>
#include <string>
#include <vector>

// Function Declaration
int compute_nn_edges();         // Calculates Edges (weight? rank?)
void compute_matching(void);    // Has to compute the array G2


struct Point {
    int x;
    int y;
    int degree;

};

vector<Point> points;

using namespace std;

// Body of program
int main(){
    int num_points;
    cin >> num_points;

    for (int i = 0; i < num_points; i++){
        struct Point point;
        string input;
        cin >> input;
        point.num = i + 1;
        point.x = stoi(input.substr(0, input.find(',')));
        point.y = stoi(input.substr(input.find(',') + 1));
    }

    return 1;
}


// Function Descriptions
int compute_nn_edges(){

    return 1;
}

void compute_matching(void){

}