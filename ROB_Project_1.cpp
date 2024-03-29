/*
NYCU DME 0811070 TingWei Ou
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
void output_check(double JOINT_VARIABLE_SOLUTION[6]);

//GLOBAL VARIABLE
double PI = 3.141593;
double d2 = 6.375000;
char mode;
double CartesianPoint[4]={0,0,0,0}; // [0] = n, [1] = o, [2] = a, [3] = p
double joint_variables[6]={0,0,0,0,0,0}; // [0] = θ1, [1] = θ2, [2] = d3 , [3] = θ4, [4] = θ5, [5] = d6
Eigen::Matrix<double, 4, 4> noap_input;

//8 solution by calculation
double JOINT_VARIABLE_SOLUTION_1[6] = {0,0,0,0,0,0};
double JOINT_VARIABLE_SOLUTION_2[6] = {0,0,0,0,0,0};
double JOINT_VARIABLE_SOLUTION_3[6] = {0,0,0,0,0,0};
double JOINT_VARIABLE_SOLUTION_4[6] = {0,0,0,0,0,0};
double JOINT_VARIABLE_SOLUTION_5[6] = {0,0,0,0,0,0};
double JOINT_VARIABLE_SOLUTION_6[6] = {0,0,0,0,0,0};
double JOINT_VARIABLE_SOLUTION_7[6] = {0,0,0,0,0,0};
double JOINT_VARIABLE_SOLUTION_8[6] = {0,0,0,0,0,0};

//WHILE FLAG
bool while_flag = false;

//NAMESPACE
using namespace Eigen;
using namespace std;

int main(){

    noap_input << 0, 0, 0, 0,
              0, 0, 0, 0,
              0, 0, 0, 0,
              0, 0, 0, 1;

    while(1){   //press ctrl-c to stop the loop
        choose_input_mode();

        if(mode == 'a'){    //choose mode a will into this loop
            CartesianPoint_input(); 
            CartesianPoint_output();
            
            output_check(JOINT_VARIABLE_SOLUTION_1);
            output_check(JOINT_VARIABLE_SOLUTION_2);
            output_check(JOINT_VARIABLE_SOLUTION_3);
            output_check(JOINT_VARIABLE_SOLUTION_4);
            output_check(JOINT_VARIABLE_SOLUTION_5);
            output_check(JOINT_VARIABLE_SOLUTION_6);
            output_check(JOINT_VARIABLE_SOLUTION_7);
            output_check(JOINT_VARIABLE_SOLUTION_8);
            
            
            cout<<"-----------------------------------"<<endl;

        }else{              //choose mode b ,will into this loop
            joint_variables_mode_input();
            joint_variables_mode_output();

        }
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

    // theta 1
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
    while(while_flag == false){// theta 2
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
    while(while_flag == false){// d 3
            cout<<"     d3 (-30 ~ 30) = ";
            cin>>joint_variables[2];

            if(joint_variables[2] <= 30 && joint_variables[2] >= -30){
                while_flag = true;

            }else{
                cout<<"[error] d3 is out of range"<<endl;

            }
    }

    while_flag = false;
    while(while_flag == false){// theta 4
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
    while(while_flag == false){// theta 5
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
    while(while_flag == false){//theta 6
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

    cout<<" please enter nx , ox , ax , px : ";
    cin>>noap_input(0, 0) >> noap_input(0, 1) >> noap_input(0, 2) >> noap_input(0, 3);
    cout<<" please enter ny , oy , ay , py : ";
    cin>>noap_input(1, 0) >> noap_input(1, 1) >> noap_input(1, 2) >> noap_input(1, 3);
    cout<<" please enter nz , oz , az , pz : ";
    cin>>noap_input(2, 0) >> noap_input(2, 1) >> noap_input(2, 2) >> noap_input(2, 3);

    //test data
    /*
    noap_input(0, 0) = 0.312899788315632;  //n
    noap_input(1, 0) = 0.777300157424024;
    noap_input(2, 0) = -0.545800501777546;
    noap_input(3, 0) = 0;

    noap_input(0, 1) = -0.777300157424024;  //o
    noap_input(1, 1) = 0.539800721952620;
    noap_input(2, 1) = 0.323140288184588;
    noap_input(3, 1) = 0;

    noap_input(0, 2) = 0.545800501777546;   //a
    noap_input(1, 2) = 0.323140288184588;
    noap_input(2, 2) = 0.773099066363012;    
    noap_input(3, 2) = 0;

    noap_input(0, 3) = 4.247497683164255;   //p
    noap_input(1, 3) = 8.330096026320385;
    noap_input(2, 3) = 18.793852415718170;
    noap_input(3, 3) = 1;
    */

    cout<<"-----------------------------------"<<endl;
}

//this function handles for computing joint variables input and output Cartesian Point & eular angle
//this function using local variable 'x' 'y' 'z' 'a' 'A' 'B' 'C'
//this function using local double matrix 'A1' 'A2' 'A3' 'A4' 'A5' 'A6' 'T6'
//this function will calculate & print Cartesian Point
void joint_variables_mode_output(){
    
    double x, y, z, A, B, C;
    Matrix<double, 4, 4> A1;
    Matrix<double, 4, 4> A2;
    Matrix<double, 4, 4> A3;
    Matrix<double, 4, 4> A4;
    Matrix<double, 4, 4> A5;
    Matrix<double, 4, 4> A6;
    Matrix<double, 4, 4> T6;

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
    // B = θ , A = ϕ , C = ψ
    B = atan2(sqrt(pow(T6(2, 0), 2) + pow(T6(2, 1), 2)), T6(2, 2))*180/PI;
    A = atan2((T6(1, 2)/sin(B)), (T6(0, 2)/sin(B)))*180/PI;
    C = atan2((T6(2, 1)/sin(B)), (-1*T6(2, 0)/sin(B)))*180/PI;

    //show solution
    cout<<"(n, o, a, p) = "<<endl;
    cout<<T6<<endl;
    cout<<" "<<endl;
    cout<<"Cartesian Point (x, y, z, ϕ, θ, ψ) = "<<endl;
    cout<<"     ( "<<x<<", "<<y<<", "<<z<<", "<<A<<", "<<B<<", "<<C<<" )"<<endl;
    cout<<"-----------------------------------"<<endl;
}

//this function handles inverse kinematics & calculate six JOINT VARIABLE
//this function using local variable 'double theta' & 'temp_a' 'temp_b'
//this function using global matrix 'noap_input'
//this finction will assign value to global array 'JOINT_VARIABLE_SOLUTION'
void CartesianPoint_output(){
    double theta_1_1, theta_1_2, 
           theta_2_1, theta_2_2, theta_2_3, theta_2_4,
           theta_4_1_1, theta_4_1_2, theta_4_2_1, theta_4_2_2, theta_4_3_1, theta_4_3_2, theta_4_4_1, theta_4_4_2,
           theta_5_1_1, theta_5_1_2, theta_5_2_1, theta_5_2_2, theta_5_3_1, theta_5_3_2, theta_5_4_1, theta_5_4_2,
           theta_6_1_1, theta_6_1_2, theta_6_2_1, theta_6_2_2, theta_6_3_1, theta_6_3_2, theta_6_4_1, theta_6_4_2,
           d_3_1, d_3_2;

    double temp_fr, temp_bk;
    double temp_a, temp_b;

    //dx = 03 ; dy = 13 ; dz = 23

    //θ1 -> two solution
    //θ1-1 (20)
    theta_1_1 = atan2(noap_input(1, 3), noap_input(0, 3)) - atan2(d2, sqrt(pow(noap_input(0, 3), 2) + pow(noap_input(1, 3), 2) - pow(d2, 2)));
        JOINT_VARIABLE_SOLUTION_5[0] = (theta_1_1*180/PI);
        JOINT_VARIABLE_SOLUTION_6[0] = (theta_1_1*180/PI);
        JOINT_VARIABLE_SOLUTION_7[0] = (theta_1_1*180/PI);
        JOINT_VARIABLE_SOLUTION_8[0] = (theta_1_1*180/PI);

    //θ1-2 (-74)
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

    //θ2-2 (160)
    theta_2_2 = atan2((cos(theta_1_1)*noap_input(0, 3)) + (sin(theta_1_1)*noap_input(1, 3)), -1*noap_input(2, 3));
        JOINT_VARIABLE_SOLUTION_3[1] = (theta_2_2*180/PI);
        JOINT_VARIABLE_SOLUTION_4[1] = (theta_2_2*180/PI);

    //θ2-3 (-20)
    theta_2_3 = atan2((cos(theta_1_2)*noap_input(0, 3)) + (sin(theta_1_2)*noap_input(1, 3)), noap_input(2, 3));
        JOINT_VARIABLE_SOLUTION_1[1] = (theta_2_3*180/PI);
        JOINT_VARIABLE_SOLUTION_2[1] = (theta_2_3*180/PI);

    //θ2-4 (-160)
    theta_2_4 = atan2((cos(theta_1_2)*noap_input(0, 3)) + (sin(theta_1_2)*noap_input(1, 3)), -1*noap_input(2, 3));
        JOINT_VARIABLE_SOLUTION_7[1] = (theta_2_4*180/PI);
        JOINT_VARIABLE_SOLUTION_8[1] = (theta_2_4*180/PI);

    //d3 -> two solution
    //d_3_1 (20)
    d_3_1 = noap_input(2, 3) / cos(theta_2_1);
        JOINT_VARIABLE_SOLUTION_1[2] = d_3_1;
        JOINT_VARIABLE_SOLUTION_2[2] = d_3_1;
        JOINT_VARIABLE_SOLUTION_5[2] = d_3_1;
        JOINT_VARIABLE_SOLUTION_6[2] = d_3_1;

    //d_3_2 (-20)
    d_3_2 = noap_input(2, 3) / cos(theta_2_2);
        JOINT_VARIABLE_SOLUTION_3[2] = d_3_2;
        JOINT_VARIABLE_SOLUTION_4[2] = d_3_2;
        JOINT_VARIABLE_SOLUTION_7[2] = d_3_2;
        JOINT_VARIABLE_SOLUTION_8[2] = d_3_2;

    //θ4 -> eight solution
    //θ4-1 (79)
    theta_4_1_1 = atan2((-1*sin(theta_1_2)*noap_input(0, 2)) + (cos(theta_1_2)*noap_input(1, 2)), (cos(theta_1_2)*cos(theta_2_3)*noap_input(0, 2)) + (sin(theta_1_2)*cos(theta_2_3)* noap_input(1, 2)) - (sin(theta_2_3)*noap_input(2, 2)));
        JOINT_VARIABLE_SOLUTION_1[3] = theta_4_1_1*180/PI;

    //θ4-1 - 180 (-100)
    theta_4_1_2 = ((theta_4_1_1*180/PI) - 180)*PI/180;
        JOINT_VARIABLE_SOLUTION_2[3] = theta_4_1_2*180/PI;

    //θ4-2(100)
    theta_4_2_1 = atan2((-1*sin(theta_1_2)*noap_input(0, 2)) + (cos(theta_1_2)*noap_input(1, 2)), (cos(theta_1_2)*cos(theta_2_2)*noap_input(0, 2)) + (sin(theta_1_2)*cos(theta_2_2)* noap_input(1, 2)) - (sin(theta_2_2)*noap_input(2, 2)));
        JOINT_VARIABLE_SOLUTION_3[3] = theta_4_2_1*180/PI;
    
    //θ4-2 - 180  (-79)
    theta_4_2_2 = ((theta_4_2_1*180/PI) - 180)*PI/180;
        JOINT_VARIABLE_SOLUTION_4[3] = theta_4_2_2*180/PI;
    
    //θ4-3 (20)
    theta_4_3_1 = atan2((-1*sin(theta_1_1)*noap_input(0, 2)) + (cos(theta_1_1)*noap_input(1, 2)), (cos(theta_1_1)*cos(theta_2_1)*noap_input(0, 2)) + (sin(theta_1_1)*cos(theta_2_1)* noap_input(1, 2)) - (sin(theta_2_1)*noap_input(2, 2)));
        JOINT_VARIABLE_SOLUTION_5[3] = theta_4_3_1*180/PI;

    //θ4-3 - 180 (-160)
    theta_4_3_2 = ((theta_4_3_1*180/PI) - 180)*PI/180;
        JOINT_VARIABLE_SOLUTION_6[3] = theta_4_3_2*180/PI;

    //θ4-4 (160)
    theta_4_4_1 = atan2((-1*sin(theta_1_1)*noap_input(0, 2)) + (cos(theta_1_1)*noap_input(1, 2)), (cos(theta_1_1)*cos(theta_2_4)*noap_input(0, 2)) + (sin(theta_1_1)*cos(theta_2_4)* noap_input(1, 2)) - (sin(theta_2_4)*noap_input(2, 2)));
        JOINT_VARIABLE_SOLUTION_7[3] = theta_4_4_1*180/PI;

    //θ4-4 - 180 (-20)
    theta_4_4_2 = ((theta_4_4_1*180/PI) - 180)*PI/180;
        JOINT_VARIABLE_SOLUTION_8[3] = theta_4_4_2*180/PI;

    //θ5 -> eight solution
    //θ5-1 
    temp_a = ((cos(theta_1_2)*cos(theta_2_3)*cos(theta_4_1_1) - sin(theta_1_2)*sin(theta_4_1_1))*noap_input(0 ,2)) + ((sin(theta_1_2)*cos(theta_2_3)*cos(theta_4_1_1) + cos(theta_1_2)*sin(theta_4_1_1))*noap_input(1, 2)) + ((-1*sin(theta_2_3)*cos(theta_4_1_1))*noap_input(2, 2));
    temp_b = (cos(theta_1_2)*sin(theta_2_3)*noap_input(0, 2)) + (sin(theta_1_2)*sin(theta_2_3)*noap_input(1, 2)) + (cos(theta_2_3)*noap_input(2, 2));
    theta_5_1_1 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_1[4] = theta_5_1_1*180/PI;

    //θ5-1-2
    temp_a = ((cos(theta_1_2)*cos(theta_2_3)*cos(theta_4_1_2) - sin(theta_1_2)*sin(theta_4_1_2))*noap_input(0 ,2)) + ((sin(theta_1_2)*cos(theta_2_3)*cos(theta_4_1_2) + cos(theta_1_2)*sin(theta_4_1_2))*noap_input(1, 2)) + ((-1*sin(theta_2_3)*cos(theta_4_1_2))*noap_input(2, 2));
    temp_b = (cos(theta_1_2)*sin(theta_2_3)*noap_input(0, 2)) + (sin(theta_1_2)*sin(theta_2_3)*noap_input(1, 2)) + (cos(theta_2_3)*noap_input(2, 2));
    theta_5_1_2 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_2[4] = theta_5_1_2*180/PI;

    //θ5-2-1
    temp_a = ((cos(theta_1_2)*cos(theta_2_2)*cos(theta_4_2_1) - sin(theta_1_2)*sin(theta_4_2_1))*noap_input(0 ,2)) + ((sin(theta_1_2)*cos(theta_2_2)*cos(theta_4_2_1) + cos(theta_1_2)*sin(theta_4_2_1))*noap_input(1, 2)) + ((-1*sin(theta_2_2)*cos(theta_4_2_1))*noap_input(2, 2));
    temp_b = (cos(theta_1_2)*sin(theta_2_2)*noap_input(0, 2)) + (sin(theta_1_2)*sin(theta_2_2)*noap_input(1, 2)) + (cos(theta_2_2)*noap_input(2, 2));
    theta_5_2_1 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_3[4] = theta_5_2_1*180/PI;

    //θ5-2-2
    temp_a = ((cos(theta_1_2)*cos(theta_2_2)*cos(theta_4_2_2) - sin(theta_1_2)*sin(theta_4_2_2))*noap_input(0 ,2)) + ((sin(theta_1_2)*cos(theta_2_2)*cos(theta_4_2_2) + cos(theta_1_2)*sin(theta_4_2_2))*noap_input(1, 2)) + ((-1*sin(theta_2_2)*cos(theta_4_2_2))*noap_input(2, 2));
    temp_b = (cos(theta_1_2)*sin(theta_2_2)*noap_input(0, 2)) + (sin(theta_1_2)*sin(theta_2_2)*noap_input(1, 2)) + (cos(theta_2_2)*noap_input(2, 2));
    theta_5_2_2 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_4[4] = theta_5_2_2*180/PI;

    //θ5-3-1
    temp_a = ((cos(theta_1_1)*cos(theta_2_1)*cos(theta_4_3_1) - sin(theta_1_1)*sin(theta_4_3_1))*noap_input(0 ,2)) + ((sin(theta_1_1)*cos(theta_2_1)*cos(theta_4_3_1) + cos(theta_1_1)*sin(theta_4_3_1))*noap_input(1, 2)) + ((-1*sin(theta_2_1)*cos(theta_4_3_1))*noap_input(2, 2));
    temp_b = (cos(theta_1_1)*sin(theta_2_1)*noap_input(0, 2)) + (sin(theta_1_1)*sin(theta_2_1)*noap_input(1, 2)) + (cos(theta_2_1)*noap_input(2, 2));
    theta_5_3_1 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_5[4] = theta_5_3_1*180/PI;

    //θ5-3-2
    temp_a = ((cos(theta_1_1)*cos(theta_2_1)*cos(theta_4_3_2) - sin(theta_1_1)*sin(theta_4_3_2))*noap_input(0 ,2)) + ((sin(theta_1_1)*cos(theta_2_1)*cos(theta_4_3_2) + cos(theta_1_1)*sin(theta_4_3_2))*noap_input(1, 2)) + ((-1*sin(theta_2_1)*cos(theta_4_3_2))*noap_input(2, 2));
    temp_b = (cos(theta_1_1)*sin(theta_2_1)*noap_input(0, 2)) + (sin(theta_1_1)*sin(theta_2_1)*noap_input(1, 2)) + (cos(theta_2_1)*noap_input(2, 2));
    theta_5_3_2 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_6[4] = theta_5_3_2*180/PI;


    //θ5-4-1
    temp_a = ((cos(theta_1_1)*cos(theta_2_4)*cos(theta_4_4_1) - sin(theta_1_1)*sin(theta_4_4_1))*noap_input(0 ,2)) + ((sin(theta_1_1)*cos(theta_2_4)*cos(theta_4_4_1) + cos(theta_1_1)*sin(theta_4_4_1))*noap_input(1, 2)) + ((-1*sin(theta_2_4)*cos(theta_4_4_1))*noap_input(2, 2));
    temp_b = (cos(theta_1_1)*sin(theta_2_4)*noap_input(0, 2)) + (sin(theta_1_1)*sin(theta_2_4)*noap_input(1, 2)) + (cos(theta_2_4)*noap_input(2, 2));
    theta_5_4_1 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_7[4] = theta_5_4_1*180/PI;

    //θ5-4-2
    temp_a = ((cos(theta_1_1)*cos(theta_2_4)*cos(theta_4_4_2) - sin(theta_1_1)*sin(theta_4_4_2))*noap_input(0 ,2)) + ((sin(theta_1_1)*cos(theta_2_4)*cos(theta_4_4_2) + cos(theta_1_1)*sin(theta_4_4_2))*noap_input(1, 2)) + ((-1*sin(theta_2_4)*cos(theta_4_4_2))*noap_input(2, 2));
    temp_b = (cos(theta_1_1)*sin(theta_2_4)*noap_input(0, 2)) + (sin(theta_1_1)*sin(theta_2_4)*noap_input(1, 2)) + (cos(theta_2_4)*noap_input(2, 2));
    theta_5_4_2 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_8[4] = theta_5_4_2*180/PI;

    //θ6 -> eight solution
    //θ6-1-1
    temp_fr = -1*((cos(theta_1_2)*cos(theta_2_3)*sin(theta_4_1_1)) + (sin(theta_1_2)*cos(theta_4_1_1)));
    temp_bk = -1*((sin(theta_1_2)*cos(theta_2_3)*sin(theta_4_1_1)) - (cos(theta_1_2)*cos(theta_4_1_1)));
    temp_a = (temp_fr)*noap_input(0, 0) + (temp_bk)*noap_input(1, 0) + (sin(theta_2_3)*sin(theta_4_1_1))*noap_input(2, 0);
    temp_b = (temp_fr)*noap_input(0, 1) + (temp_bk)*noap_input(1, 1) + (sin(theta_2_3)*sin(theta_4_1_1))*noap_input(2, 1);
    theta_6_1_1 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_1[5] = theta_6_1_1*180/PI;

    //θ6-1-2
    temp_fr = (-1*(cos(theta_1_2)*cos(theta_2_3)*sin(theta_4_1_2))) - (sin(theta_1_2)*cos(theta_4_1_2));
    temp_bk = (-1*(sin(theta_1_2)*cos(theta_2_3)*sin(theta_4_1_2))) + (cos(theta_1_2)*cos(theta_4_1_2));
    temp_a = (temp_fr)*noap_input(0, 0) + (temp_bk)*noap_input(1, 0) + (sin(theta_2_3)*sin(theta_4_1_2))*noap_input(2, 0);
    temp_b = (temp_fr)*noap_input(0, 1) + (temp_bk)*noap_input(1, 1) + (sin(theta_2_3)*sin(theta_4_1_2))*noap_input(2, 1);
    theta_6_1_2 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_2[5] = theta_6_1_2*180/PI;

    //θ6-2-1
    temp_fr = (-1*(cos(theta_1_2)*cos(theta_2_2)*sin(theta_4_2_1))) - (sin(theta_1_2)*cos(theta_4_2_1));
    temp_bk = (-1*(sin(theta_1_2)*cos(theta_2_2)*sin(theta_4_2_1))) + (cos(theta_1_2)*cos(theta_4_2_1));
    temp_a = (temp_fr)*noap_input(0, 0) + (temp_bk)*noap_input(1, 0) + (sin(theta_2_2)*sin(theta_4_2_1))*noap_input(2, 0);
    temp_b = (temp_fr)*noap_input(0, 1) + (temp_bk)*noap_input(1, 1) + (sin(theta_2_2)*sin(theta_4_2_1))*noap_input(2, 1);
    theta_6_2_1 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_3[5] = theta_6_2_1*180/PI;

    //θ6-2-2
    temp_fr = (-1*(cos(theta_1_2)*cos(theta_2_2)*sin(theta_4_2_2))) - (sin(theta_1_2)*cos(theta_4_2_2));
    temp_bk = (-1*(sin(theta_1_2)*cos(theta_2_2)*sin(theta_4_2_2))) + (cos(theta_1_2)*cos(theta_4_2_2));
    temp_a = (temp_fr)*noap_input(0, 0) + (temp_bk)*noap_input(1, 0) + (sin(theta_2_2)*sin(theta_4_2_2))*noap_input(2, 0);
    temp_b = (temp_fr)*noap_input(0, 1) + (temp_bk)*noap_input(1, 1) + (sin(theta_2_2)*sin(theta_4_2_2))*noap_input(2, 1);
    theta_6_2_2 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_4[5] = theta_6_2_2*180/PI;

    //θ6-3-1
    temp_fr = (-1*(cos(theta_1_1)*cos(theta_2_1)*sin(theta_4_3_1))) - (sin(theta_1_1)*cos(theta_4_3_1));
    temp_bk = (-1*(sin(theta_1_1)*cos(theta_2_1)*sin(theta_4_3_1))) + (cos(theta_1_1)*cos(theta_4_3_1));
    temp_a = (temp_fr)*noap_input(0, 0) + (temp_bk)*noap_input(1, 0) + (sin(theta_2_1)*sin(theta_4_3_1))*noap_input(2, 0);
    temp_b = (temp_fr)*noap_input(0, 1) + (temp_bk)*noap_input(1, 1) + (sin(theta_2_1)*sin(theta_4_3_1))*noap_input(2, 1);
    theta_6_3_1 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_5[5] = theta_6_3_1*180/PI;

    //θ6-3-2
    temp_fr = (-1*(cos(theta_1_1)*cos(theta_2_1)*sin(theta_4_3_2))) - (sin(theta_1_1)*cos(theta_4_3_2));
    temp_bk = (-1*(sin(theta_1_1)*cos(theta_2_1)*sin(theta_4_3_2))) + (cos(theta_1_1)*cos(theta_4_3_2));
    temp_a = (temp_fr)*noap_input(0, 0) + (temp_bk)*noap_input(1, 0) + (sin(theta_2_1)*sin(theta_4_3_2))*noap_input(2, 0);
    temp_b = (temp_fr)*noap_input(0, 1) + (temp_bk)*noap_input(1, 1) + (sin(theta_2_1)*sin(theta_4_3_2))*noap_input(2, 1);
    theta_6_3_2 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_6[5] = theta_6_3_2*180/PI;

    //θ6-4-1
    temp_fr = (-1*(cos(theta_1_1)*cos(theta_2_4)*sin(theta_4_4_1))) - (sin(theta_1_1)*cos(theta_4_4_1));
    temp_bk = (-1*(sin(theta_1_1)*cos(theta_2_4)*sin(theta_4_4_1))) + (cos(theta_1_1)*cos(theta_4_4_1));
    temp_a = (temp_fr)*noap_input(0, 0) + (temp_bk)*noap_input(1, 0) + (sin(theta_2_4)*sin(theta_4_4_1))*noap_input(2, 0);
    temp_b = (temp_fr)*noap_input(0, 1) + (temp_bk)*noap_input(1, 1) + (sin(theta_2_4)*sin(theta_4_4_1))*noap_input(2, 1);
    theta_6_4_1 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_7[5] = theta_6_4_1*180/PI;

    //θ6-4-1
    temp_fr = (-1*(cos(theta_1_1)*cos(theta_2_4)*sin(theta_4_4_2))) - (sin(theta_1_1)*cos(theta_4_4_2));
    temp_bk = (-1*(sin(theta_1_1)*cos(theta_2_4)*sin(theta_4_4_2))) + (cos(theta_1_1)*cos(theta_4_4_2));
    temp_a = (temp_fr)*noap_input(0, 0) + (temp_bk)*noap_input(1, 0) + (sin(theta_2_4)*sin(theta_4_4_2))*noap_input(2, 0);
    temp_b = (temp_fr)*noap_input(0, 1) + (temp_bk)*noap_input(1, 1) + (sin(theta_2_4)*sin(theta_4_4_2))*noap_input(2, 1);
    theta_6_4_2 = atan2(temp_a, temp_b);
        JOINT_VARIABLE_SOLUTION_8[5] = theta_6_4_2*180/PI; 

}

//this function handles for showing the answer calculated by inverse kinematics
//this function using global matrix & determine whether the angle limit is met
void output_check(double JOINT_VARIABLE_SOLUTION[6]){
    cout<<"<sol>Corresponding variables (θ1, θ2, d3, θ4, θ5, θ6): "<<endl;
    cout<<" (";
    for(int i = 0; i < 6; i++){
        cout<<"  "<<JOINT_VARIABLE_SOLUTION[i]<<" ";
    }
    cout<<" )"<<endl;

    if(JOINT_VARIABLE_SOLUTION[0] >= 160 || JOINT_VARIABLE_SOLUTION[0] <= -160){
        cout<<"[error] θ1 is out of range"<<endl;

    }

    if(JOINT_VARIABLE_SOLUTION[1] >= 125 || JOINT_VARIABLE_SOLUTION[1] <= -125){
        cout<<"[error] θ2 is out of range"<<endl;
    }

    if(JOINT_VARIABLE_SOLUTION[2] >= 30 || JOINT_VARIABLE_SOLUTION[2] <= -30){
        cout<<"[error] d3 is out of range"<<endl;
    }

    if(JOINT_VARIABLE_SOLUTION[3] >= 140 || JOINT_VARIABLE_SOLUTION[3] <= -140){
        cout<<"[error] θ4 is out of range"<<endl;
    }

    if(JOINT_VARIABLE_SOLUTION[4] >= 100 || JOINT_VARIABLE_SOLUTION[4] <= -100){
        cout<<"[error] θ5 is out of range"<<endl;
    }

    if(JOINT_VARIABLE_SOLUTION[5] >= 260 || JOINT_VARIABLE_SOLUTION[0] <= -260){
        cout<<"[error] θ6 is out of range"<<endl;
    }

    cout<<endl;
    cout<<endl;
        
}
