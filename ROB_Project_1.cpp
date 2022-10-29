/*
NYCU DME 0811070 TingWei Ou
TODO:
    1. input interface ok
    2. limit the operating region

        -160<θ1<160    -125<θ2<125
        -30<d3<30      -140<θ4<140
        -100<θ5<100    -260<θ6<260

    3. use atan2 to calculate ok
    4.input: Cartesian point (n, o, a, p), output: the corresponding joint variables.
    5.input: joint variables, output: Cartesian point (n, o, a, p) and (x, y, z, ϕ, θ, ψ). ok
    
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
float d2 = 6.375;
char mode;
float CartesianPoint[4]={0,0,0,0}; // [0] = n, [1] = o, [2] = a, [3] = p
float joint_variables[6]={0,0,0,0,0,0}; // [0] = θ1, [1] = θ2, [2] = d3 , [3] = θ4, [4] = θ5, [5] = d6
Eigen::Matrix<float, 4, 4> noap_input;

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

    cout<<"<-> please enter Cartesian Point [n, o, a, p] : "<<endl;
    cout<<" | 00 , 01 , 02 , 03 |"<<endl;
    cout<<" | 10 , 11 , 12 , 13 |"<<endl;
    cout<<" | 20 , 21 , 22 , 23 |"<<endl;
    cout<<" | 30 , 31 , 32 , 33 |"<<endl;

    /*
    for(int column = 0; column < 4; column++){
        for(int row = 0; row < 4 ; row++){
            cout<<" -> please enter "<<row<<column<<" : ";
            cin>>noap_input(row, column);
        }
    }
    */
    noap_input(0, 0) = 0.3129;
    noap_input(1, 0) = 0.7773;
    noap_input(2, 0) = -0.5258;
    noap_input(3, 0) = 0;

    noap_input(0, 1) = -0.7773;
    noap_input(1, 1) = 0.5398;
    noap_input(2, 1) = 0.3231;
    noap_input(3, 1) = 0;

    noap_input(0, 2) = 0.5458;
    noap_input(1, 2) = 0.3231;
    noap_input(2, 2) = 0.7731;    
    noap_input(3, 2) = 0;

    noap_input(0, 3) = 4.2475;
    noap_input(1, 3) = 8.3301;
    noap_input(2, 3) = 18.7939;
    noap_input(3, 3) = 1;

    cout<<noap_input<<endl;

    
    //cout<<noap_input<<endl;
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
    float theta_1_1, theta_1_2, 
          theta_2_1, theta_2_2, theta_2_1_neg, theta_2_2_neg,
          theta_4_1, theta_4_2,
          theta_5_1, theta_5_2,
          theta_6_1, theta_6_2,
          d_3_1, d_3_2;
    //8 solution by calculation

    float JOINT_VARIABLE_SOLUTION_1[6] = {0,0,0,0,0,0};
    float JOINT_VARIABLE_SOLUTION_2[6] = {0,0,0,0,0,0};
    float JOINT_VARIABLE_SOLUTION_3[6] = {0,0,0,0,0,0};
    float JOINT_VARIABLE_SOLUTION_4[6] = {0,0,0,0,0,0};
    float JOINT_VARIABLE_SOLUTION_5[6] = {0,0,0,0,0,0};
    float JOINT_VARIABLE_SOLUTION_6[6] = {0,0,0,0,0,0};
    float JOINT_VARIABLE_SOLUTION_7[6] = {0,0,0,0,0,0};
    float JOINT_VARIABLE_SOLUTION_8[6] = {0,0,0,0,0,0};

    //dx = 03 ; dy = 13 ; dz = 23

    //θ1 -> two solution
    //θ1-1 (-74)
    theta_1_1 = atan2(noap_input(1, 3), noap_input(0, 3)) - atan2(d2, sqrt(pow(noap_input(0, 3), 2) + pow(noap_input(1, 3), 2) - pow(d2, 2)));
    JOINT_VARIABLE_SOLUTION_5[0] = (theta_1_1*180/PI);
    JOINT_VARIABLE_SOLUTION_6[0] = (theta_1_1*180/PI);
    JOINT_VARIABLE_SOLUTION_7[0] = (theta_1_1*180/PI);
    JOINT_VARIABLE_SOLUTION_8[0] = (theta_1_1*180/PI);

    //θ1-2 (20)
    theta_1_2 = (atan2(noap_input(1, 3), noap_input(0, 3)) - atan2(d2, -1*sqrt(pow(noap_input(0, 3), 2) + pow(noap_input(1, 3), 2) - pow(d2, 2))));
    JOINT_VARIABLE_SOLUTION_1[0] = (theta_1_2*180/PI);
    JOINT_VARIABLE_SOLUTION_2[0] = (theta_1_2*180/PI);
    JOINT_VARIABLE_SOLUTION_3[0] = (theta_1_2*180/PI);
    JOINT_VARIABLE_SOLUTION_4[0] = (theta_1_2*180/PI);

    //θ2 -> four solution
    //θ2-1 (20)
    theta_2_1 = atan2((cos(theta_1_1)*noap_input(0, 3)) + (sin(theta_1_1)*noap_input(1, 3)), noap_input(2, 3));
    JOINT_VARIABLE_SOLUTION_5[1] = (theta_2_1*180/PI);
    JOINT_VARIABLE_SOLUTION_6[1] = (theta_2_1*180/PI);

    //θ2-1 (neg) (160)
    theta_2_1_neg = atan2((cos(theta_1_1)*noap_input(0, 3)) + (sin(theta_1_1)*noap_input(1, 3)), -1*noap_input(2, 3));
    JOINT_VARIABLE_SOLUTION_3[1] = (theta_2_1_neg*180/PI);
    JOINT_VARIABLE_SOLUTION_4[1] = (theta_2_1_neg*180/PI);

    //θ2-2 (20)
    theta_2_2 = atan2((cos(theta_1_2)*noap_input(0, 3)) + (sin(theta_1_2)*noap_input(1, 3)), noap_input(2, 3));
    JOINT_VARIABLE_SOLUTION_1[1] = (theta_2_2*180/PI);
    JOINT_VARIABLE_SOLUTION_2[1] = (theta_2_2*180/PI);

    //θ2-2 (neg) (-120)
    theta_2_2_neg = atan2((cos(theta_1_2)*noap_input(0, 3)) + (sin(theta_1_2)*noap_input(1, 3)), -1*noap_input(2, 3));
    JOINT_VARIABLE_SOLUTION_7[1] = (theta_2_2_neg*180/PI);
    JOINT_VARIABLE_SOLUTION_8[1] = (theta_2_2_neg*180/PI);

    cout<<"[test]"<<theta_2_1*180/PI<<endl;
    cout<<"[test]"<<theta_2_1_neg*180/PI<<endl;
    cout<<"[test]"<<theta_2_2*180/PI<<endl;
    cout<<"[test]"<<theta_2_2_neg*180/PI<<endl;

    //d3 -> two solution
    d_3_1 = sin(theta_1_1)*cos(theta_1_1)*noap_input(0, 3) + sin(theta_1_1)*sin(theta_2_1)*noap_input(1, 3) + cos(theta_2_1)*noap_input(2, 3);
    JOINT_VARIABLE_SOLUTION_1[2] = d_3_1;
    JOINT_VARIABLE_SOLUTION_2[2] = d_3_1;
    JOINT_VARIABLE_SOLUTION_5[2] = d_3_1;
    JOINT_VARIABLE_SOLUTION_6[2] = d_3_1;

    //d3-2
    d_3_2 = d_3_1*-1;
    JOINT_VARIABLE_SOLUTION_3[2] = d_3_2;
    JOINT_VARIABLE_SOLUTION_4[2] = d_3_2;
    JOINT_VARIABLE_SOLUTION_7[2] = d_3_2;
    JOINT_VARIABLE_SOLUTION_8[2] = d_3_2;
    

    //θ4


    //θ5


    //θ6



/*
    cout<<" | 00 , 01 , 02 , 03 |"<<endl;
    cout<<" | 10 , 11 , 12 , 13 |"<<endl;
    cout<<" | 20 , 21 , 22 , 23 |"<<endl;
    cout<<" | 30 , 31 , 32 , 33 |"<<endl;
*/
    //print solution 1
    cout<<"<sol_1>Corresponding variables (θ1, θ2, d3, θ4, θ5, θ6): "<<endl;
    for(int i = 0; i < 6; i++){
        cout<<JOINT_VARIABLE_SOLUTION_1[i]<<" ";
    }
    cout<<endl;

    if(JOINT_VARIABLE_SOLUTION_1[0] >= 160 && JOINT_VARIABLE_SOLUTION_1[0] <= -160){
            cout<<"[error] θ1 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_1[1] >= 125 && JOINT_VARIABLE_SOLUTION_1[1] <= -125){
            cout<<"[error] θ2 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_1[2] >= 30 && JOINT_VARIABLE_SOLUTION_1[2] <= -30){
            cout<<"[error] d3 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_1[3] >= 140 && JOINT_VARIABLE_SOLUTION_1[3] <= -140){
            cout<<"[error] θ4 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_1[4] >= 100 && JOINT_VARIABLE_SOLUTION_1[4] <= -100){
            cout<<"[error] θ5 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_1[5] >= 260 && JOINT_VARIABLE_SOLUTION_1[0] <= -260){
            cout<<"[error] θ6 is out of range"<<endl;
        }

    //print solution 2
    cout<<"<sol_2>Corresponding variables (θ1, θ2, d3, θ4, θ5, θ6): "<<endl;
    for(int i = 0; i < 6; i++){
        cout<<JOINT_VARIABLE_SOLUTION_2[i]<<" ";
    }
    cout<<endl;

    if(JOINT_VARIABLE_SOLUTION_1[0] >= 160 && JOINT_VARIABLE_SOLUTION_1[0] <= -160){
            cout<<"[error] θ1 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_2[1] >= 125 && JOINT_VARIABLE_SOLUTION_3[1] <= -125){
            cout<<"[error] θ2 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_2[2] >= 30 && JOINT_VARIABLE_SOLUTION_3[2] <= -30){
            cout<<"[error] d3 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_2[3] >= 140 && JOINT_VARIABLE_SOLUTION_3[3] <= -140){
            cout<<"[error] θ4 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_2[4] >= 100 && JOINT_VARIABLE_SOLUTION_3[4] <= -100){
            cout<<"[error] θ5 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_2[5] >= 260 && JOINT_VARIABLE_SOLUTION_3[0] <= -260){
            cout<<"[error] θ6 is out of range"<<endl;
        }

    //print solution 3
    cout<<"<sol_3>Corresponding variables (θ1, θ2, d3, θ4, θ5, θ6): "<<endl;
    for(int i = 0; i < 6; i++){
        cout<<JOINT_VARIABLE_SOLUTION_3[i]<<" ";
    }
    cout<<endl;

    if(JOINT_VARIABLE_SOLUTION_3[0] >= 160 && JOINT_VARIABLE_SOLUTION_1[0] <= -160){
            cout<<"[error] θ1 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_3[1] >= 125 && JOINT_VARIABLE_SOLUTION_3[1] <= -125){
            cout<<"[error] θ2 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_3[2] >= 30 && JOINT_VARIABLE_SOLUTION_3[2] <= -30){
            cout<<"[error] d3 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_3[3] >= 140 && JOINT_VARIABLE_SOLUTION_3[3] <= -140){
            cout<<"[error] θ4 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_3[4] >= 100 && JOINT_VARIABLE_SOLUTION_3[4] <= -100){
            cout<<"[error] θ5 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_3[5] >= 260 && JOINT_VARIABLE_SOLUTION_3[0] <= -260){
            cout<<"[error] θ6 is out of range"<<endl;
        }
    
    //print solution 4
    cout<<"<sol_4>Corresponding variables (θ1, θ2, d3, θ4, θ5, θ6): "<<endl;
    for(int i = 0; i < 6; i++){
        cout<<JOINT_VARIABLE_SOLUTION_4[i]<<" ";
    }
    cout<<endl;

    if(JOINT_VARIABLE_SOLUTION_4[0] >= 160 && JOINT_VARIABLE_SOLUTION_1[0] <= -160){
            cout<<"[error] θ1 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_4[1] >= 125 && JOINT_VARIABLE_SOLUTION_4[1] <= -125){
            cout<<"[error] θ2 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_4[2] >= 30 && JOINT_VARIABLE_SOLUTION_4[2] <= -30){
            cout<<"[error] d3 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_4[3] >= 140 && JOINT_VARIABLE_SOLUTION_4[3] <= -140){
            cout<<"[error] θ4 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_4[4] >= 100 && JOINT_VARIABLE_SOLUTION_4[4] <= -100){
            cout<<"[error] θ5 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_4[5] >= 260 && JOINT_VARIABLE_SOLUTION_4[0] <= -260){
            cout<<"[error] θ6 is out of range"<<endl;
        }

    //print solution 5
    cout<<"<sol_5>Corresponding variables (θ1, θ2, d3, θ4, θ5, θ6): "<<endl;
    for(int i = 0; i < 6; i++){
        cout<<JOINT_VARIABLE_SOLUTION_5[i]<<" ";
    }
    cout<<endl;

    if(JOINT_VARIABLE_SOLUTION_5[0] >= 160 && JOINT_VARIABLE_SOLUTION_1[0] <= -160){
            cout<<"[error] θ1 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_5[1] >= 125 && JOINT_VARIABLE_SOLUTION_5[1] <= -125){
            cout<<"[error] θ2 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_5[2] >= 30 && JOINT_VARIABLE_SOLUTION_5[2] <= -30){
            cout<<"[error] d3 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_5[3] >= 140 && JOINT_VARIABLE_SOLUTION_5[3] <= -140){
            cout<<"[error] θ4 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_5[4] >= 100 && JOINT_VARIABLE_SOLUTION_5[4] <= -100){
            cout<<"[error] θ5 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_5[5] >= 260 && JOINT_VARIABLE_SOLUTION_5[0] <= -260){
            cout<<"[error] θ6 is out of range"<<endl;
        }

    //print solution 6
    cout<<"<sol_6>Corresponding variables (θ1, θ2, d3, θ4, θ5, θ6): "<<endl;
    for(int i = 0; i < 6; i++){
        cout<<JOINT_VARIABLE_SOLUTION_6[i]<<" ";
    }
    cout<<endl;

    if(JOINT_VARIABLE_SOLUTION_6[0] >= 160 && JOINT_VARIABLE_SOLUTION_1[0] <= -160){
            cout<<"[error] θ1 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_6[1] >= 125 && JOINT_VARIABLE_SOLUTION_6[1] <= -125){
            cout<<"[error] θ2 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_6[2] >= 30 && JOINT_VARIABLE_SOLUTION_6[2] <= -30){
            cout<<"[error] d3 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_6[3] >= 140 && JOINT_VARIABLE_SOLUTION_6[3] <= -140){
            cout<<"[error] θ4 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_6[4] >= 100 && JOINT_VARIABLE_SOLUTION_6[4] <= -100){
            cout<<"[error] θ5 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_6[5] >= 260 && JOINT_VARIABLE_SOLUTION_6[0] <= -260){
            cout<<"[error] θ6 is out of range"<<endl;
        }

    //print solution 7
    cout<<"<sol_7>Corresponding variables (θ1, θ2, d3, θ4, θ5, θ6): "<<endl;
    for(int i = 0; i < 6; i++){
        cout<<JOINT_VARIABLE_SOLUTION_7[i]<<" ";
    }
    cout<<endl;

    if(JOINT_VARIABLE_SOLUTION_7[0] >= 160 && JOINT_VARIABLE_SOLUTION_1[0] <= -160){
            cout<<"[error] θ1 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_7[1] >= 125 && JOINT_VARIABLE_SOLUTION_7[1] <= -125){
            cout<<"[error] θ2 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_7[2] >= 30 && JOINT_VARIABLE_SOLUTION_7[2] <= -30){
            cout<<"[error] d3 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_7[3] >= 140 && JOINT_VARIABLE_SOLUTION_7[3] <= -140){
            cout<<"[error] θ4 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_7[4] >= 100 && JOINT_VARIABLE_SOLUTION_7[4] <= -100){
            cout<<"[error] θ5 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_7[5] >= 260 && JOINT_VARIABLE_SOLUTION_7[0] <= -260){
            cout<<"[error] θ6 is out of range"<<endl;
        }
    
    //print solution 8
    cout<<"<sol_8>Corresponding variables (θ1, θ2, d3, θ4, θ5, θ6): "<<endl;
    for(int i = 0; i < 6; i++){
        cout<<JOINT_VARIABLE_SOLUTION_8[i]<<" ";
    }
    cout<<endl;

    if(JOINT_VARIABLE_SOLUTION_8[0] >= 160 && JOINT_VARIABLE_SOLUTION_8[0] <= -160){
            cout<<"[error] θ1 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_8[1] >= 125 && JOINT_VARIABLE_SOLUTION_8[1] <= -125){
            cout<<"[error] θ2 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_8[2] >= 30 && JOINT_VARIABLE_SOLUTION_8[2] <= -30){
            cout<<"[error] d3 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_8[3] >= 140 && JOINT_VARIABLE_SOLUTION_8[3] <= -140){
            cout<<"[error] θ4 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_8[4] >= 100 && JOINT_VARIABLE_SOLUTION_8[4] <= -100){
            cout<<"[error] θ5 is out of range"<<endl;
        }else if(JOINT_VARIABLE_SOLUTION_8[5] >= 260 && JOINT_VARIABLE_SOLUTION_8[0] <= -260){
            cout<<"[error] θ6 is out of range"<<endl;
        }

}