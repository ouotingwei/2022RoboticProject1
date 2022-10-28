/*
NYCU DME 0811070 TingWei Ou
TODO:
    1. input interface
    2. limit the operating region

        -160<θ1<160    -125<θ2<125
        -30<d3<30      -140<θ4<140
        -100<θ5<100    -260<θ6<260

    3. use atan2 to calculate
    4.input: Cartesian point (n, o, a, p), output: the corresponding joint variables.
    5.input: joint variables, output: Cartesian point (n, o, a, p) and (x, y, z, ϕ, θ, ψ).
    
*/
#include<iostream>
#include<Eigen/Dense>
#include<cmath>

//FUNCTION
void choose_input_mode();
void joint_variables_mode_input();
void CartesianPoint_input();
void joint_variables_mode_output();
void CartesianPoint_output();

//GLOBAL VARIABLE
float PI = 3.1415926;
char mode;
float CartesianPoint[4]={0,0,0,0}; // [0] = n, [1] = o, [2] = a, [3] = p
float joint_variables[6]={0,0,0,0,0,0}; // [0] = θ1, [1] = θ2, [2] = d3 , [3] = θ4, [4] = θ5, [5] = d6


//WHILE FLAG
bool while_flag = false;

//NAMESPACE
using namespace Eigen;
using namespace std;

int main(){
    choose_input_mode();

    if(mode == 'a'){    //choose mode a ,will into this loop
        CartesianPoint_input();
        CartesianPoint_output();

    }else{              //choose mode b ,will into this loop
        joint_variables_mode_input();
        joint_variables_mode_output();

    }

    return 0;
}

//this function handles mode selection
void choose_input_mode(){
    cout<<"<-> which mode do you want ?"<<endl;
    cout<<"    input (n o a p)       -> enter a"<<endl;
    cout<<"    input joint variables -> enter b"<<endl;
    cout<<"-----------------------------------"<<endl;

    while(while_flag == false){
        cin>>mode;

        if(mode == 'b' || mode == 'a'){
            while_flag = true;

        }else{
            cout<<"[input error] Please choose again"<<endl;

        }
    }

    while_flag = false;
}

//this function handles user input joint variables( θ1~θ6 & d3 )
//this function using global array joint_variables[i]
void joint_variables_mode_input(){
    cout<<"<-> please enter joint variables "<<endl;

    while(while_flag == false){
            cout<<"     θ1 (-160 ~ 160) = ";
            cin>>joint_variables[0];

            if(joint_variables[0] <= 160 && joint_variables[0] >= -160){
                while_flag = true;
                joint_variables[0] = joint_variables[0]*PI/180; //Angle conversion

            }else{
                cout<<"[error] θ1 is out of range"<<endl;

            }
    }
    
    while_flag = false;
    while(while_flag == false){
            cout<<"     θ2 (-125 ~ 125) = ";
            cin>>joint_variables[1];

            if(joint_variables[1] <= 125 && joint_variables[1] >= -125){
                while_flag = true;
                joint_variables[1] = joint_variables[1]*PI/180; //Angle conversion

            }else{
                cout<<"[error] θ2 is out of range"<<endl;

            }
    }

    while_flag = false;
    while(while_flag == false){
            cout<<"     d3 (-30 ~ 30) = ";
            cin>>joint_variables[2];

            if(joint_variables[2] <= 30 && joint_variables[2] >= -30){
                while_flag = true;

            }else{
                cout<<"[error] d3 is out of range"<<endl;

            }
    }

    while_flag = false;
    while(while_flag == false){
            cout<<"     θ4 (-140 ~ 140) = ";
            cin>>joint_variables[3];

            if(joint_variables[3] <= 140 && joint_variables[3] >= -140){
                while_flag = true;
                joint_variables[3] = joint_variables[3]*PI/180; //Angle conversion

            }else{
                cout<<"[error] θ4 is out of range"<<endl;

            }
    }

    while_flag = false;
    while(while_flag == false){
            cout<<"     θ5 (-100 ~ 100) = ";
            cin>>joint_variables[4];

            if(joint_variables[4] <= 100 && joint_variables[4] >= -100){
                while_flag = true;
                joint_variables[4] = joint_variables[4]*PI/180; //Angle conversion

            }else{
                cout<<"[error] θ5 is out of range"<<endl;

            }
    }

    while_flag = false;
    while(while_flag == false){
            cout<<"     θ6 (-260 ~ 260) = ";
            cin>>joint_variables[5];

            if(joint_variables[5] <= 260 && joint_variables[5] >= -260){
                while_flag = true;
                joint_variables[5] = joint_variables[5]*PI/180; //Angle conversion

            }else{
                cout<<"[error] θ6 is out of range"<<endl;

            }
    }

    //cout<< joint_variables[0]<<" "<< joint_variables[1]<<" "<< joint_variables[2]<<" "<< joint_variables[3]<<" "<< joint_variables[4]<<" "<< joint_variables[5]<<endl;
    cout<<"-----------------------------------"<<endl;
}

//this function handles user input Cartesian Point(n, o, a, p)
//this function using global array CartesianPoint[i]
void CartesianPoint_input(){

    for(int i = 0; i < 4; i++){
        cout<<"<-> please enter Cartesian Point [n, o, a, p] -> ";

        if( i == 0){
            cout<<"n = ";
            cin>>CartesianPoint[i];

        }else if( i == 1){
            cout<<"o = ";
            cin>>CartesianPoint[i];

        }else if( i == 2){
            cout<<"a = ";
            cin>>CartesianPoint[i];

        }else if( i == 3){
            cout<<"p = ";
            cin>>CartesianPoint[i];

        }
    }

    cout<<"-----------------------------------"<<endl;
}

//this function handles for computing joint variables input and output Cartesian Point & eular angle
//this function using local variable : x, y, z, a, A, B, C
//this function will print Cartesian Point
void joint_variables_mode_output(){
    
    float x, y, z, A, B, C, a;
    Matrix<float, 4, 4> A1;
    Matrix<float, 4, 4> A2;
    Matrix<float, 4, 4> A3;
    Matrix<float, 4, 4> A4;
    Matrix<float, 4, 4> A5;
    Matrix<float, 4, 4> A6;
    Matrix<float, 4, 4> T6;

    A1 <<    cos(joint_variables[0]),  0, -1*sin(joint_variables[0]), 0,
             sin(joint_variables[0]),  0,    cos(joint_variables[0]), 0,
          0                         , -1,                          0, 0,
          0                         ,  0,                          0, 1;

    A2 <<    cos(joint_variables[1]),  0,    sin(joint_variables[1]), 0,
             sin(joint_variables[1]),  0, -1*cos(joint_variables[1]), 0,
          0                         ,  1,                          0, 6.375,
          0                         ,  0,                          0, 1;

    A3 << 1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, joint_variables[2],
          0, 0, 0, 1;

    A4 <<    cos(joint_variables[3]),  0, -1*sin(joint_variables[3]), 0,
             sin(joint_variables[3]),  0,    cos(joint_variables[3]), 0,
          0                         , -1,                          0, 0,
          0                         ,  0,                          0, 1;

    A5 <<    cos(joint_variables[4]),  0,    sin(joint_variables[4]), 0,
             sin(joint_variables[4]),  0, -1*cos(joint_variables[4]), 0,
          0                         ,  1,                          0, 0,
          0                         ,  0,                          0, 1;

    A6 << cos(joint_variables[5]), -1*sin(joint_variables[5]), 0, 0,
          sin(joint_variables[5]),    cos(joint_variables[5]), 0, 0,
          0                      , 0                         , 1, 0,
          0                      , 0                         , 0, 1;
    
    T6 << 0, 0, 0, 0,
          0, 0, 0, 0,
          0, 0, 0, 0,
          0, 0, 0, 0;
    

    T6 = (A1*(A2*(A3*(A4*(A5*A6)))));  // 1T6 MATRIX

    //euler angle z-y-z (x, y, z)
    x = T6(0,3);
    y = T6(1,3);
    z = T6(2,3);
    //euler angle z-y-z (ϕ, θ, ψ)
    a = atan2(T6(1, 2), T6(0, 2));
    A = a*180/PI;
    B = (atan2((T6(0, 2)*cos(a)) + (T6(1, 2)*sin(a)), T6(2,2))*180/PI);
    C = (atan2((-1*T6(0, 0)*sin(a) + (T6(1, 0)*cos(a))), (-1*T6(0, 1)*sin(a)) + (T6(1, 1)*cos(a)))*180/PI);

    //show solution
    cout<<"(n, o, a, p) = "<<endl;
    cout<<T6<<endl;
    cout<<" "<<endl;
    cout<<"Cartesian Point (x, y, z, ϕ, θ, ψ) = "<<endl;
    cout<<"     ( "<<x<<", "<<y<<", "<<z<<", "<<A<<", "<<B<<", "<<C<<" )"<<endl;
    cout<<"-----------------------------------"<<endl;
}

//this function handles inverse kinematics
void CartesianPoint_output(){

}