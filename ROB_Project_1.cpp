/*
NYCU DME 0811070 TingWei Ou
TODO:
    1. input interface
    2. limit the operating region

        -160<θ1<160    -125<θ2<125
        -30<θ3<30      -140<θ4<140
        -100<θ5<100    -260<θ6<260

    3. use atan2 to calculate
    4.input: Cartesian point (n, o, a, p), output: the corresponding joint variables.
    5.input: joint variables, output: Cartesian point (n, o, a, p) and (x, y, z, ϕ, θ, ψ).
    
*/
#include<iostream>
#include<Eigen/Dense>
#include<cmath>

using namespace Eigen;

//FUNCTION
void choose_input_mode();
void joint_variables_mode_input();
void CartesianPoint_input();

//VARIABLE
char mode;
float CartesianPoint[4]={0,0,0,0}; // [0] = n, [1] = o, [2] = a, [3] = p
float joint_variables[6]={0,0,0,0,0,0}; // [0] = θ1, [1] = θ2, [2] = d3 , [3] = θ4, [4] = θ5, [5] = d6

//WHILE FLAG
bool while_flag = false;

int main(){
    choose_input_mode();

    if(mode == 'a'){
        CartesianPoint_input();

    }else{
        joint_variables_mode_input();

    }

    return 0;
}

void choose_input_mode(){
    std::cout<<"<-> which mode do you want ?"<<std::endl;
    std::cout<<"    input (n o a p)       -> enter a"<<std::endl;
    std::cout<<"    input joint variables -> enter b"<<std::endl;
    std::cout<<"-----------------------------------"<<std::endl;

    while(while_flag == false){
        std::cin>>mode;

        if(mode == 'b' || mode == 'a'){
            while_flag = true;

        }else{
            std::cout<<"[input error] Please choose again"<<std::endl;

        }
    }

    while_flag = false;
}

void joint_variables_mode_input(){

    for(int i = 0; i < 6; i++){
        std::cout<<"<-> please enter joint variables ";

        if(i != 3){
            std::cout<<"θ"<<i<<std::endl;

        }else{
            std::cout<<"d"<<i<<std::endl;

        }
    
        std::cin>>joint_variables[i];
    }

    std::cout<<"<-> joint_variables : "<<std::endl;

    for(int i = 0; i < 6; i++){
        if(i != 2){
            std::cout<<"        θ"<<i+1<<" = "<<joint_variables[i]<<std::endl;

        }else{
            std::cout<<"        d"<<i+1<<" = "<<joint_variables[i]<<std::endl;

        }
    }

    std::cout<<"-----------------------------------"<<std::endl;
}

void CartesianPoint_input(){

    for(int i = 0; i < 4; i++){
        std::cout<<"<-> please enter Cartesian Point [n, o, a, p] -> ";

        if( i == 0){
            std::cout<<"n = ";
            std::cin>>CartesianPoint[i];

        }else if( i == 1){
            std::cout<<"o = ";
            std::cin>>CartesianPoint[i];

        }else if( i == 2){
            std::cout<<"a = ";
            std::cin>>CartesianPoint[i];

        }else if( i == 3){
            std::cout<<"p = ";
            std::cin>>CartesianPoint[i];

        }
    }

    std::cout<<"-----------------------------------"<<std::endl;
}
