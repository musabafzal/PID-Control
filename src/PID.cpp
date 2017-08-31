#include "PID.h"
#include <iostream>



using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

double PID::Abs(double number){
  if(number<0){
    number*=-1;
  }
  return number;
}

void PID::Init(double Kp, double Ki, double Kd) {
    params[0]=Kp;
    params[1]=Ki;
    params[2]=Kd;
    errors[0]=0.0;
    errors[1]=0.0;
    errors[2]=0.0;
    dparams[0]=0.1*params[0];
    dparams[1]=0.1*params[1];
    dparams[2]=0.1;
    twiddle=false;
}

void PID::UpdateError(double cte) {

  if (count==0) {
    prev_cte=cte;
    best_err=Abs(cte);
    count++;
  }

  errors[0] = cte;
  errors[2] = cte - prev_cte;
  prev_cte=cte;
  errors[1] += cte;



  if(it==1){

    params[curr_param]+=dparams[curr_param];
    it=2;
  }else if(it==2){
    err=Abs(cte);
    if(Abs(err)<Abs(best_err)){
  //    cout<<"lol"<<endl;
      best_err=err;
      dparams[curr_param]*=1.1;
      it=1;
      if(curr_param==2){
          curr_param=0;
      }else{
        curr_param++;
      }
    }else{
  //    cout<<"notlol"<<endl;
      it=3;
    }
  }else if(it==3){
      params[curr_param]-=2*dparams[curr_param];
      it=4;
  }else if(it==4){
      err=Abs(cte);
      if(Abs(err)<Abs(best_err)){
        best_err=err;
        dparams[curr_param]*=1.1;
      }else{
        params[curr_param]+=dparams[curr_param];
        dparams[curr_param]*=0.9;
      }
      it=1;
      if(curr_param==2){
          curr_param=0;
      }else{
        curr_param++;
      }
    }

}

double PID::TotalError() {
  return - params[0] * errors[0] - params[1] * errors[1] - params[2] * errors[2];
}
