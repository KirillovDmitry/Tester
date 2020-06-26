      
#ifndef CVE_constants_H
#define CVE_constants_H

const double StepAlt    = 0.125;
const double StepAtt    = 1;
const double StepAuxAtt = 1;


const int bMaxAlt    = 255;
const int bMinAlt    = 0;
const int bStepAlt   = 1;
const int bMaxAtt    = 127;
const int bMinAtt    = 0;
const int bStepAtt   = 1;
const int bMaxAuxAtt = 15;
const int bMinAuxAtt = 0;

const int NAlt    = (int) (bMaxAlt-bMinAlt)/bStepAlt+1; // количество заначений высоты
const int NAtt    = (int) (bMaxAtt-bMinAtt)/bStepAtt+1; // количество заначений ослабления
const int NAuxAtt = (int) (bMaxAuxAtt-bMinAuxAtt)+1;

#endif
