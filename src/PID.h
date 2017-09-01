#ifndef PID_H
#define PID_H


class PID {
public:
  /*
  * Errors
  */
  //p error, i error, d error
  double errors[3];

  /*
  * Coefficients
  */
  //Kp, Ki, Kd
  double params[3];

  //for twiddle
  double dparams[3];

  double best_err;
  double err;

  bool twiddle;
  bool twiddle_flag;

  int it=1;
  int count=0;

  int curr_param=0;

  double prev_cte;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */

  double Abs(double number);


  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Update the PID error variables given cross track error with the help of twiddle.
  */
  void UpdateErrorWithTwiddle(double cte);

  /*
  * Calculate the total PID error.
  */
  double SteerValue();
};

#endif /* PID_H */
